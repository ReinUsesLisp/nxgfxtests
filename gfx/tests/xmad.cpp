#include "gfx/common_tests.h"

template <const char* shader_glsl, int passed_value, int expected_value>
static bool Test() {
    constexpr float float_expected = static_cast<float>(expected_value);
    const auto callback = [](const Gfx::Context& ctx, const Gfx::Shader& shader) {
        ctx.ProgramUniform1i(shader.GetHandle(), 0, passed_value);
    };
    return Gfx::SinglePixelTest(shader_glsl, float_expected, callback);
}

static constexpr const char GLSL_1[] = R"(
#version 430 core
layout (location = 0) uniform int value;
layout (location = 0) out float pixel;
void main() {
    pixel = value * value * value;
}
)";

ADD_TEST("XMAD(1)", Test, GLSL_1, 4, 64);
ADD_TEST("XMAD(2)", Test, GLSL_1, 2, 8);
ADD_TEST("XMAD(3)", Test, GLSL_1, -1, -1);
ADD_TEST("XMAD(4)", Test, GLSL_1, -6, -216);
