// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#include <cstdlib>

#include "common/hwtests.h"
#include "common/test_list.h"
#include "gfx/context.h"

int main(int argc, char* argv[]) {
    const Context nx_context;

    RunTests();

    // TODO: Wait until button press.
    while (true)
        ;

    return EXIT_SUCCESS;
}