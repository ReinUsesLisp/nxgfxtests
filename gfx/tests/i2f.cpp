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
    pixel = float(value);
}
)";

static constexpr const char GLSL_2[] = R"(
#version 430 core
layout (location = 0) uniform int value;
layout (location = 0) out float pixel;
void main() {
    pixel = float(value);
}
)";

static constexpr const char GLSL_3[] = R"(
#version 430 core
layout (location = 0) uniform int value;
layout (location = 0) out float pixel;
void main() {
    pixel = float(-value);
}
)";

static AddTest test1{"I2F.F32.S32(1)", Test<GLSL_1, 4, 4>};
static AddTest test2{"I2F.F32.S32(2)", Test<GLSL_2, -6545, -6545>};
static AddTest test3{"I2F.F32.S32(3)", Test<GLSL_3, 50000, -50000>};
