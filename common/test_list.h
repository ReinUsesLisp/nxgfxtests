// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include "common/commo_funcs.h"

#define ADD_TEST(name, pfn, ...)                                                                   \
    namespace {                                                                                    \
    ::AddTest CONCAT2(test, __LINE__){name, pfn<__VA_ARGS__>};                                     \
    }

#define ADD_TEST_FIXED(name, pfn)                                                                  \
    namespace {                                                                                    \
    ::AddTest CONCAT2(test, __LINE__){name, pfn};                                                  \
    }

class AddTest {
public:
    AddTest(const char* name, bool (*pfn)());
};

void RunTests();
