#include <string>

#include "common/common_types.h"
#include "gfx/common_tests.h"

template <std::string& shader_glsl, s32 passed_value, s32 expected_value>
static bool TestS32() {
    constexpr float float_expected = static_cast<float>(expected_value);
    const auto callback = [](const Gfx::Context& ctx, const Gfx::Shader& shader) {
        ctx.ProgramUniform1i(shader.GetHandle(), 0, passed_value);
    };
    return Gfx::SinglePixelTest(shader_glsl.c_str(), float_expected, callback);
}

template <std::string& shader_glsl, u32 passed_value, u32 expected_value>
static bool TestU32() {
    constexpr float float_expected = static_cast<float>(expected_value);
    const auto callback = [](const Gfx::Context& ctx, const Gfx::Shader& shader) {
        ctx.ProgramUniform1ui(shader.GetHandle(), 0, passed_value);
    };
    return Gfx::SinglePixelTest(shader_glsl.c_str(), float_expected, callback);
}

static std::string GenerateGLSL(std::string uniform_type, std::string expresion) {
    return "#version 430 core\n"
           "layout (location = 0) uniform " +
           uniform_type +
           " value;\n"
           "layout (location = 0) out float pixel;\n"
           "void main() {\n"
           "    pixel = " +
           expresion +
           ";\n"
           "}\n";
}

static std::string GLSL_1 = GenerateGLSL("int", "float(value)");
static std::string GLSL_2 = GenerateGLSL("int", "float(-value)");

static std::string GLSL_3 = GenerateGLSL("uint", "bitfieldExtract(value, 0, 8)");
static std::string GLSL_4 = GenerateGLSL("uint", "bitfieldExtract(value, 8, 8)");
static std::string GLSL_5 = GenerateGLSL("uint", "bitfieldExtract(value, 16, 8)");
static std::string GLSL_6 = GenerateGLSL("uint", "bitfieldExtract(value, 24, 8)");

static std::string GLSL_7 = GenerateGLSL("uint", "bitfieldExtract(value, 0, 16)");
static std::string GLSL_8 = GenerateGLSL("uint", "bitfieldExtract(value, 16, 16)");
/*
ADD_TEST("I2F.F32.S32(1)", TestS32, GLSL_1, 4, 4);
ADD_TEST("I2F.F32.S32(2)", TestS32, GLSL_1, -6545, -6545);
ADD_TEST("I2F.F32.S32(3)", TestS32, GLSL_2, 50000, -50000);

ADD_TEST("I2F.F32.U8(1)", TestU32, GLSL_3, 0xAABBCCDDu, 0xDDu); // B0
ADD_TEST("I2F.F32.U8(2)", TestU32, GLSL_4, 0xAABBCCDDu, 0xCCu); // B1
ADD_TEST("I2F.F32.U8(3)", TestU32, GLSL_5, 0xAABBCCDDu, 0xBBu); // B2
ADD_TEST("I2F.F32.U8(4)", TestU32, GLSL_6, 0xAABBCCDDu, 0xAAu); // B3

ADD_TEST("I2F.F32.U16(1)", TestU32, GLSL_7, 0xAABBCCDDu, 0xCCDDu); // H0
ADD_TEST("I2F.F32.U16(2)", TestU32, GLSL_8, 0xAABBCCDDu, 0xAABBu); // H1
*/