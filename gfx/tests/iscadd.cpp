#include "gfx/common_tests.h"

template <const char* shader_glsl, u32 value1, u32 value2, int expected>
static bool Test() {
    const auto callback = [](const Gfx::Context& ctx, const Gfx::Shader& shader) {
        ctx.ProgramUniform1ui(shader.GetHandle(), 0, value1);
        ctx.ProgramUniform1ui(shader.GetHandle(), 1, value2);
    };
    return Gfx::SinglePixelTest(shader_glsl, static_cast<float>(expected), callback);
}

static constexpr const char GLSL_1[] = R"(
#version 430 core
layout (location = 0) uniform uint value1;
layout (location = 1) uniform uint value2;
layout (location = 0) out float pixel;
void main() {
    pixel = (value1 << 3) + value2;
}
)";
/*
ADD_TEST("ISCADD(1)", Test, GLSL_1, 2, 6, 22);
ADD_TEST("ISCADD(2)", Test, GLSL_1, 0, 6, 6);
ADD_TEST("ISCADD(3)", Test, GLSL_1, 8, 17, 81);
*/