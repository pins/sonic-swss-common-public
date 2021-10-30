#include "swss/fakes/fake_producer_state_table.h"

#include "glog/logging.h"

namespace swss {

FakeProducerStateTable::FakeProducerStateTable(const std::string &table_name,
                                               FakeSonicDbTable *sonic_db_table)
    : table_name_(table_name), sonic_db_table_(sonic_db_table) {
  LOG_IF(FATAL, sonic_db_table == nullptr)
      << "FakeSonicDbTable cannot be nullptr.";
}

void FakeProducerStateTable::set(const std::string &key,
                                 const std::vector<FieldValueTuple> &values,
                                 const std::string &op,
                                 const std::string &prefix) {
  VLOG(1) << "Insert table entry: " << key;
  sonic_db_table_->InsertTableEntry(key, values);
  sonic_db_table_->PushNotification(key);
}

void FakeProducerStateTable::set(
    const std::vector<KeyOpFieldsValuesTuple> &key_values) {
  for (const auto &[key, op, values] : key_values) {
    FakeProducerStateTable::set(key, values);
  }
}

void FakeProducerStateTable::del(const std::string &key, const std::string &op,
                                 const std::string &prefix) {
  VLOG(1) << "Delete table entry: " << key;
  sonic_db_table_->DeleteTableEntry(key);
  sonic_db_table_->PushNotification(key);
}

void FakeProducerStateTable::del(const std::vector<std::string> &keys) {
  for (const auto &key : keys) {
    FakeProducerStateTable::del(key);
  }
}

}  // namespace swss
