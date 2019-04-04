#include "gfx/common_tests.h"
#include "gfx/texture.h"

template <const char* shader_glsl, int expected_value>
static bool Test2D() {
    const auto callback = [](const Gfx::Context& ctx, const Gfx::Shader& shader) {
        (new Gfx::Texture(ctx, GL_TEXTURE_2D, GL_RGBA8, 8, 256, 512))->BindTexture();
    };
    return Gfx::SinglePixelTest(shader_glsl, static_cast<float>(expected_value), callback);
}

static constexpr const char GLSL_1[] = R"(
#version 430 core
layout (binding = 0) uniform sampler2D img;
layout (location = 0) out float pixel;
void main() {
    pixel = textureSize(img, 0).x;
}
)";

static constexpr const char GLSL_2[] = R"(
#version 430 core
layout (binding = 0) uniform sampler2D img;
layout (location = 0) out float pixel;
void main() {
    pixel = textureSize(img, 0).y;
}
)";

static constexpr const char GLSL_3[] = R"(
#version 430 core
layout (binding = 0) uniform sampler2D img;
layout (location = 0) out float pixel;
void main() {
    pixel = textureSize(img, 1).x;
}
)";

static constexpr const char GLSL_4[] = R"(
#version 430 core
layout (binding = 0) uniform sampler2D img;
layout (location = 0) out float pixel;
void main() {
    pixel = textureSize(img, 1).y;
}
)";

static constexpr const char GLSL_5[] = R"(
#version 430 core
layout (binding = 0) uniform sampler3D img;
layout (location = 0) out float pixel;
void main() {
    pixel = textureQueryLevels(img);
}
)";

static AddTest test1{"TXQ.DIM(1)", Test2D<GLSL_1, 256>};
static AddTest test2{"TXQ.DIM(2)", Test2D<GLSL_2, 512>};
static AddTest test3{"TXQ.DIM(3)", Test2D<GLSL_3, 128>};
static AddTest test4{"TXQ.DIM(4)", Test2D<GLSL_4, 256>};
static AddTest test6{"TXQ.LEVELS", Test2D<GLSL_5, 8>};
