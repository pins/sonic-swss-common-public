#pragma once

#include "gmock/gmock.h"
#include "swss/producerstatetableinterface.h"

namespace swss {

class MockProducerStateTable final : public ProducerStateTableInterface {
 public:
  MOCK_METHOD(void, set,
              (const std::string& key,
               const std::vector<FieldValueTuple>& values,
               const std::string& op, const std::string& prefix),
              (override));
  MOCK_METHOD(void, set,
              (const std::vector<KeyOpFieldsValuesTuple>& key_values),
              (override));
  MOCK_METHOD(void, del,
              (const std::string& key, const std::string& op,
               const std::string& prefix),
              (override));
  MOCK_METHOD(void, del, (const std::vector<std::string>& keys), (override));
  MOCK_METHOD(std::string, get_table_name, (), (const, override));
};

}  // namespace swss
