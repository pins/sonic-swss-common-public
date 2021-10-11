package(default_visibility = ["//visibility:public"])

cc_library(
    name = "fake_consumer_notifier",
    testonly = True,
    srcs = ["fake_consumer_notifier.cc"],
    hdrs = ["fake_consumer_notifier.h"],
    include_prefix = "swss/fakes",
    deps = [
        ":fake_sonic_db_table",
        "//:libswsscommon",
        "@com_github_google_glog//:glog",
        "@com_google_absl//absl/status",
    ],
)

cc_library(
    name = "fake_producer_state_table",
    testonly = True,
    srcs = ["fake_producer_state_table.cc"],
    hdrs = ["fake_producer_state_table.h"],
    include_prefix = "swss/fakes",
    deps = [
        ":fake_sonic_db_table",
        "//:libswsscommon",
        "@com_github_google_glog//:glog",
    ],
)

cc_library(
    name = "fake_db_connector",
    testonly = True,
    srcs = ["fake_db_connector.cc"],
    hdrs = ["fake_db_connector.h"],
    include_prefix = "swss/fakes",
    deps = [
        ":fake_sonic_db_table",
        "//:libswsscommon",
        "@com_github_google_glog//:glog",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "fake_sonic_db_table",
    testonly = True,
    srcs = ["fake_sonic_db_table.cc"],
    hdrs = ["fake_sonic_db_table.h"],
    include_prefix = "swss/fakes",
    deps = [
        "@com_github_google_glog//:glog",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
)

cc_test(
    name = "fake_sonic_db_table_test",
    srcs = ["fake_sonic_db_table_test.cc"],
    deps = [
        ":fake_sonic_db_table",
        "@com_google_absl//absl/status",
        "@com_github_google_glog//:glog",
        "@com_google_googletest//:gtest",
    ],
)
