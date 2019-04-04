// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

class AddTest {
public:
    AddTest(const char* name, bool(*pfn)());
};

void RunTests();
