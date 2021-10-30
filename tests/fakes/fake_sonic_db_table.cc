#include "swss/fakes/fake_sonic_db_table.h"

#include "absl/status/statusor.h"
#include "glog/logging.h"

namespace swss {

void FakeSonicDbTable::InsertTableEntry(const std::string &key,
                                        const SonicDbEntryList &values) {
  VLOG(1) << "Insert table entry: " << key;
  auto& entry = entries_[key];
  for (const auto&[field, data] : values) {
    entry.insert_or_assign(field, data);
  }
}

void FakeSonicDbTable::DeleteTableEntry(const std::string &key) {
  VLOG(1) << "Delete table entry: " << key;
  if (auto iter = entries_.find(key); iter != entries_.end()) {
    entries_.erase(iter);
  }
}

void FakeSonicDbTable::SetResponseForKey(const std::string &key,
                                         const std::string &code,
                                         const std::string &message) {
  VLOG(1) << "Setting response for: " << key;
  responses_[key] = ResponseInfo{.code = code, .message = message};
}

void FakeSonicDbTable::PushNotification(const std::string &key) {
  VLOG(1) << "Pushing notification: " << key;
  notifications_.push(key);

  // If the user has overwritten the default response with a custom failure
  // value then we do not update the StateDB.
  auto response_iter = responses_.find(key);
  if (response_iter != responses_.end() &&
      response_iter->second.code != "SWSS_RC_SUCCESS") {
    VLOG(2) << "Will not update StateDB entry because user set error code.";
    return;
  }

  auto entry_iter = entries_.find(key);
  // If the key exists Insert into the StateDb, otherwise delete.
  if (entry_iter != entries_.end()) {
   InsertStateDbTableEntry(key, entry_iter->second);
  } else {
   DeleteStateDbTableEntry(key);
  }
}

void FakeSonicDbTable::GetNextNotification(std::string &op, std::string &data,
                                           SonicDbEntryList &values) {
  if (notifications_.empty()) {
    // TODO(rhalstea): we probably want to return a timeout error if we never
    // get a notification?
    LOG(FATAL) << "Could not find a notification.";
  }

  VLOG(1) << "Reading next notification: " << notifications_.front();
  data = notifications_.front();
  notifications_.pop();

  // If the user has overwritten the default response with custom values we will
  // use those. Otherwise, we default to success.
  if (auto response_iter = responses_.find(data);
      response_iter != responses_.end()) {
    op = response_iter->second.code;
    values.push_back({"err_str", response_iter->second.message});
  } else {
    op = "SWSS_RC_SUCCESS";
    values.push_back({"err_str", "SWSS_RC_SUCCESS"});
  }
}

absl::StatusOr<SonicDbEntryMap> FakeSonicDbTable::ReadTableEntry(
    const std::string &key) const {
  VLOG(1) << "Read table entry: " << key;
  if (auto entry = entries_.find(key); entry != entries_.end()) {
    return entry->second;
  }
  return absl::Status(absl::StatusCode::kNotFound,
                      absl::StrCat("AppDb missing: ", key));
}

std::vector<std::string> FakeSonicDbTable::GetAllKeys() const {
  std::vector<std::string> result;
  VLOG(1) << "Get all table entry keys";
  for (const auto &entry : entries_) {
    result.push_back(entry.first);
  }
  return result;
}

void FakeSonicDbTable::DebugState() const {
  for (const auto &[key, values] : entries_) {
    LOG(INFO) << "AppDb entry: " << key;
    for (const auto &[field, data] : values) {
      LOG(INFO) << "  " << field << " " << data;
    }
  }
}

void FakeSonicDbTable::InsertStateDbTableEntry(const std::string &key,
                                               const SonicDbEntryMap &values) {
  // If the StateDB is not set then we do not try to update.
  if (state_db_ == nullptr) return;

  // Convert the map values to a list.
  SonicDbEntryList list;
  for (const auto&[first, second] : values) {
    list.push_back({first, second});
  }

  // OrchAgent should clear the existing entry to remove any unused fileds, and
  // reinsert.
  VLOG(2) << "Updating StateDB entry with new values.";
  state_db_->DeleteTableEntry(key);
  state_db_->InsertTableEntry(key, list);
}

void FakeSonicDbTable::DeleteStateDbTableEntry(const std::string &key) {
  // If the StateDB is not set then we do not try to update.
  if (state_db_ == nullptr) return;

  // OrchAgent should clear the existing entry to remove any unused fileds, and
  // reinsert.
  VLOG(2) << "Removing StateDB entry.";
  state_db_->DeleteTableEntry(key);
}

}  // namespace swss
