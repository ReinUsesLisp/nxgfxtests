// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#include <cstdio>
#include <string>
#include <utility>
#include <vector>

#include "test_list.h"

static std::vector<std::pair<std::string, bool (*)()>> s_tests;

AddTest::AddTest(const char* name, bool (*pfn)()) {
    s_tests.emplace_back(name, pfn);
}

void RunTests() {
    std::vector<std::string> failed_tests;
    for (const auto pair : s_tests) {
        const auto& [name, pfn] = pair;
        const bool success = pfn();
        fprintf(stderr, "Test %s: %s\n", name.c_str(), success ? "Success" : "Failure");
        if (!success) {
            failed_tests.push_back(name);
        }
    }

    const auto tests_count = static_cast<int>(s_tests.size());
    const auto failed_count = static_cast<int>(failed_tests.size());
    const auto success_count = tests_count - failed_count;

    fprintf(stderr, "Result: %d out of %d tests passed\n", success_count, tests_count);

    switch (failed_count) {
    case 0:
        break;
    case 1:
        fprintf(stderr, "Failed test: %s\n", failed_tests[0].c_str());
        break;
    default:
        fprintf(stderr, "Failed tests: ");
        for (const auto& test : failed_tests) {
            fprintf(stderr, "%s ", test.c_str());
        }
        fprintf(stderr, "\n");
        break;
    }
}