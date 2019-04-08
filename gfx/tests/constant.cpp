#include "common/test_list.h"
#include "gfx/common_tests.h"

static constexpr const char PIXEL_SHADER[] = R"(
#version 430 core
layout (location = 0) out float pixel;
void main() {
    pixel = 0.125f;
}
)";

static bool Test() {
    return Gfx::SinglePixelTest(PIXEL_SHADER, 0.125f);
}

static AddTest test{"Constant", Test};
