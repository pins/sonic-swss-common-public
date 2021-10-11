package(default_visibility = ["//visibility:public"])

cc_library(
    name = "mock_consumer_notifier",
    testonly = True,
    hdrs = ["mock_consumer_notifier.h"],
    include_prefix = "swss/mocks",
    deps = [
        "//:libswsscommon",
        "@com_google_googletest//:gtest",
    ],
)

cc_library(
    name = "mock_db_connector",
    testonly = True,
    hdrs = ["mock_db_connector.h"],
    include_prefix = "swss/mocks",
    deps = [
        "//:libswsscommon",
        "@com_google_googletest//:gtest",
    ],
)

cc_library(
    name = "mock_producer_state_table",
    testonly = True,
    hdrs = ["mock_producer_state_table.h"],
    include_prefix = "swss/mocks",
    deps = [
        "//:libswsscommon",
        "@com_google_googletest//:gtest",
    ],
)
