
#include "gfx/buffer.h"
#include "gfx/common_tests.h"
#include "gfx/texture.h"

template <const char* shader_glsl, int texture_pixel, int expected_value>
static bool Test() {
    const auto callback = [](const Gfx::Context& ctx, const Gfx::Shader& shader) {
        constexpr auto texture_pixel_float = static_cast<float>(texture_pixel);
        const auto texture{new Gfx::Texture(ctx, GL_TEXTURE_2D, GL_RGBA8, 1, 1, 1)};
        texture->Upload(0, 0, 1, GL_RED, GL_FLOAT, &texture_pixel_float);

        const GLuint64 handle = texture->GetBindlessHandle();
        ctx.MakeTextureHandleResident(handle);

        const auto buffer{new Gfx::Buffer(ctx)};
        buffer->InvalidateUpload(sizeof(handle), &handle);
        buffer->BindAsUniform(0);
    };
    return Gfx::SinglePixelTest(shader_glsl, static_cast<float>(expected_value), callback);
}

static constexpr const char GLSL_1[] = R"(
#version 430 core
#extension GL_ARB_bindless_texture : require
layout (location = 0) uniform uint index = 0;
layout (binding = 0) uniform Textures { sampler2D img[1]; };
layout (location = 0) out float pixel;
void main() {
    pixel = texture(img[index], vec2(0, 0)).r;
}
)";

/*
ADD_TEST("TEXTURE.BINDLESS(1)", Test, GLSL_1, 4, 4);
ADD_TEST("TEXTURE.BINDLESS(2)", Test, GLSL_1, 12, 12);
*/
