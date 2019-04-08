#include <cstdint>
#include <cstring>
#include "gfx/common_tests.h"

template <const char* shader_glsl, int low, int high, int expected_value>
static bool Test() {
    const __fp16 low_fp16{low};
    const __fp16 high_fp16{high};

    uint32_t raw{};
    auto ptr = reinterpret_cast<uint8_t*>(&raw);
    std::memcpy(ptr, &low_fp16, 2);
    std::memcpy(ptr + 2, &high_fp16, 2);

    const auto callback = [raw](const Gfx::Context& ctx, const Gfx::Shader& shader) {
        ctx.ProgramUniform1i(shader.GetHandle(), 0, raw);
    };
    return Gfx::SinglePixelTest(shader_glsl, static_cast<float>(expected_value), callback);
}

static constexpr const char GLSL_1[] = R"(
#version 430 core
layout (location = 0) out float pixel;
layout (location = 0) uniform uint value;
void main() {
    pixel = unpackHalf2x16(value).x;
}
)";

static constexpr const char GLSL_2[] = R"(
#version 430 core
layout (location = 0) out float pixel;
layout (location = 0) uniform uint value;
void main() {
    pixel = unpackHalf2x16(value).y;
}
)";

static AddTest test1{"F2F.F16(1)", Test<GLSL_1,   4,  8,   4>};
static AddTest test2{"F2F.F16(2)", Test<GLSL_1, -12,  8, -12>};
static AddTest test3{"F2F.F16(3)", Test<GLSL_1,   8, 13,  13>};
static AddTest test4{"F2F.F16(4)", Test<GLSL_1,   8, -2,  -2>};
