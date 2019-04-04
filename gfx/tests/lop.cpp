#include "gfx/common_tests.h"

template <const char* shader_glsl, int passed_value, int expected_value>
static bool Test() {
    constexpr float float_expected = static_cast<float>(expected_value);
    const auto callback = [](const Gfx::Context& ctx, const Gfx::Shader& shader) {
        ctx.ProgramUniform1i(shader.GetHandle(), 0, passed_value);
    };
    return Gfx::SinglePixelTest(shader_glsl, float_expected, callback);
}

static constexpr const char LOP_AND[] = R"(
#version 430 core
layout (location = 0) uniform int value;
layout (location = 0) out float pixel;
void main() {
    pixel = float(value >> 2 << 2);
}
)";

static AddTest test1{"LOP.AND", Test<LOP_AND, 105, 104>};
