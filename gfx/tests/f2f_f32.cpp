#include "gfx/common_tests.h"

template <const char* shader_glsl, int value_divided_10, int expected>
static bool Test() {
    const auto callback = [](const Gfx::Context& ctx, const Gfx::Shader& shader) {
        ctx.ProgramUniform1f(shader.GetHandle(), 0, static_cast<float>(value_divided_10) / 10.0f);
    };
    return Gfx::SinglePixelTest(shader_glsl, static_cast<float>(expected), callback);
}

static constexpr const char GLSL_1[] = R"(
#version 430 core
layout (location = 0) out float pixel;
layout (location = 0) uniform float value;
void main() {
    pixel = floor(value);
}
)";

static constexpr const char GLSL_2[] = R"(
#version 430 core
layout (location = 0) out float pixel;
layout (location = 0) uniform float value;
void main() {
    pixel = ceil(value);
}
)";

static constexpr const char GLSL_3[] = R"(
#version 430 core
layout (location = 0) out float pixel;
layout (location = 0) uniform float value;
void main() {
    pixel = roundEven(value);
}
)";

static constexpr const char GLSL_4[] = R"(
#version 430 core
layout (location = 0) out float pixel;
layout (location = 0) uniform float value;
void main() {
    pixel = trunc(value);
}
)";
/*
ADD_TEST("F2F.FLOOR(1)", Test, GLSL_1, 43, 4);
ADD_TEST("F2F.FLOOR(2)", Test, GLSL_1, 49, 4);
ADD_TEST("F2F.FLOOR(3)", Test, GLSL_1, -13, -2);
ADD_TEST("F2F.FLOOR(4)", Test, GLSL_1, 80, 8);

ADD_TEST("F2F.CEIL(1)", Test, GLSL_2, 43, 5);
ADD_TEST("F2F.CEIL(2)", Test, GLSL_2, 49, 5);
ADD_TEST("F2F.CEIL(3)", Test, GLSL_2, -13, -1);
ADD_TEST("F2F.CEIL(4)", Test, GLSL_2, 80, 8);

ADD_TEST("F2F.ROUND(1)", Test, GLSL_3, 43, 4);
ADD_TEST("F2F.ROUND(2)", Test, GLSL_3, 49, 5);
ADD_TEST("F2F.ROUND(3)", Test, GLSL_3, -13, -1);
ADD_TEST("F2F.ROUND(4)", Test, GLSL_3, 80, 8);
ADD_TEST("F2F.ROUND(5)", Test, GLSL_3, 45, 4);

ADD_TEST("F2F.TRUNC(1)", Test, GLSL_4, 43, 4);
ADD_TEST("F2F.TRUNC(2)", Test, GLSL_4, 49, 4);
ADD_TEST("F2F.TRUNC(3)", Test, GLSL_4, -13, -1);
ADD_TEST("F2F.TRUNC(4)", Test, GLSL_4, 80, 8);
ADD_TEST("F2F.TRUNC(5)", Test, GLSL_4, -19, -1);
*/