#include "swss/fakes/fake_consumer_notifier.h"

#include "glog/logging.h"

namespace swss {

FakeConsumerNotifier::FakeConsumerNotifier(FakeSonicDbTable *sonic_db_table)
    : sonic_db_table_(sonic_db_table) {
  LOG_IF(FATAL, sonic_db_table == nullptr)
      << "FakeSonicDbTable cannot be nullptr.";
}

bool FakeConsumerNotifier::WaitForNotificationAndPop(std::string &op,
                                                     std::string &data,
                                                     SonicDbEntryList &values,
                                                     int64_t timeout_ms) {
  sonic_db_table_->GetNextNotification(op, data, values);
  return true;
}

}  // namespace swss
