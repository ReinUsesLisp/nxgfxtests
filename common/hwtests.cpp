// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#include <switch.h>
#include <switch/arm/atomics.h>
#include <switch/kernel/ipc.h>
#include <switch/services/sm.h>
#include <switch/types.h>
#include <unistd.h>

#include <cassert>
#include <cstdio>

#include "common/common_types.h"
#include "common/hwtests.h"

#ifdef ENABLE_NXLINK

static int s_nxlinkSock = -1;

static void initNxLink() {
    if (R_FAILED(socketInitializeDefault()))
        return;

    s_nxlinkSock = nxlinkStdio();
    if (s_nxlinkSock < 0) {
        socketExit();
    }
}

static void deinitNxLink() {
    if (s_nxlinkSock < 0)
        return;
    close(s_nxlinkSock);
    socketExit();
    s_nxlinkSock = -1;
}

extern "C" void userAppInit() {
    initNxLink();
}

extern "C" void userAppExit() {
    deinitNxLink();
}

#endif // ENABLE_NXLINK

Context::Context() {
    InitializeConsole();
}

Context::~Context() = default;

void Context::InitializeConsole() {
    consoleDebugInit(debugDevice_SVC);
}
