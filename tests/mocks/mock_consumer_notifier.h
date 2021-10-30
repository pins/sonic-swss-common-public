#pragma once

#include "gmock/gmock.h"
#include "swss/consumernotifierinterface.h"

namespace swss {

class MockConsumerNotifier final : public ConsumerNotifierInterface {
 public:
  MOCK_METHOD(bool, WaitForNotificationAndPop,
              (std::string & op, std::string &data,
               std::vector<swss::FieldValueTuple> &values, int64_t timeout_ms),
              (override));
};

}  // namespace swss
