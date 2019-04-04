#include "gfx/common_tests.h"

template <const char* shader_glsl, int passed_value, int expected_value>
static bool Test() {
    constexpr float float_passed = static_cast<float>(passed_value);
    constexpr float float_expected = static_cast<float>(expected_value);

    const auto callback = [](const Gfx::Context& ctx, const Gfx::Shader& shader) {
        ctx.ProgramUniform1f(shader.GetHandle(), 0, float_passed);
    };
    return Gfx::SinglePixelTest(shader_glsl, float_expected, callback);
}

static constexpr const char GLSL_1[] = R"(
#version 430 core
layout (location = 0) uniform float value;
layout (location = 0) out float pixel;
void main() {
    pixel = value + value;
}
)";

static constexpr const char GLSL_2[] = R"(
#version 430 core
layout (location = 0) uniform float value;
layout (location = 0) out float pixel;
void main() {
    pixel = value - value;
}
)";

static constexpr const char GLSL_3[] = R"(
#version 430 core
layout (location = 0) uniform float value;
layout (location = 0) out float pixel;
void main() {
    pixel = value * value;
}
)";

static AddTest test1{"FADD(1)", Test<GLSL_1, 8, 16>};
static AddTest test2{"FADD(2)", Test<GLSL_1, -8, -16>};
static AddTest test3{"FADD(3)", Test<GLSL_2, 412, 0>};
static AddTest test4{"FADD(4)", Test<GLSL_2, 836, 0>};
static AddTest test5{"FADD(5)", Test<GLSL_2, -42314, 0>};

static AddTest test6{"FMUL(6)", Test<GLSL_3, 3, 9>};
static AddTest test7{"FMUL(7)", Test<GLSL_3, -3, 9>};
static AddTest test8{"FMUL(8)", Test<GLSL_3, 60, 3600>};
