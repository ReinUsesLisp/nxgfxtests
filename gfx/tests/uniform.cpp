#include "gfx/common_tests.h"

static constexpr const char PIXEL_SHADER[] = R"(
#version 430 core
layout (location = 0) out float pixel;
layout (location = 0) uniform float value;
void main() {
    pixel = value;
}
)";

static bool Test() {
    constexpr float value = 0.8864f;
    const auto callback = [](const Gfx::Context& ctx, const Gfx::Shader& shader) {
        ctx.ProgramUniform1f(shader.GetHandle(), 0, value);
    };
    return Gfx::SinglePixelTest(PIXEL_SHADER, value, callback);
}

// ADD_TEST_FIXED("Uniform", Test);
