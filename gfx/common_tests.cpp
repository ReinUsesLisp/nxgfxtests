// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#include "common/test_list.h"

#include "gfx/common_tests.h"
#include "gfx/context.h"
#include "gfx/framebuffer.h"
#include "gfx/program_pipeline.h"
#include "gfx/shader.h"
#include "gfx/texture.h"
#include "gfx/vertex_array.h"

namespace Gfx {

constexpr const char VERTEX_SHADER[] = R"(
#version 430 core
void main() {
    vec2 positions[4] = vec2[](vec2(-1,  1),
                               vec2( 1, -1),
                               vec2(-1, -1),
                               vec2( 1,  1));
    gl_Position = vec4(positions[gl_VertexID], 0, 1);
}
)";

bool SinglePixelTest(const char* pixel_shader_glsl, float expected_value, SetupCallback callback) {
    const Context ctx(Context::Profile::OpenGL_Core, 4, 3);

    const VertexShader vertex_shader(ctx, VERTEX_SHADER);
    const PixelShader pixel_shader(ctx, pixel_shader_glsl);

    const ProgramPipeline pipeline(ctx, {vertex_shader, pixel_shader});
    pipeline.Bind();

    const VertexArray vao(ctx);
    vao.Bind();

    const Texture texture(ctx, GL_TEXTURE_2D, GL_R32F, 1, 1, 1);
    const Framebuffer framebuffer(ctx);
    framebuffer.AttachColor(texture, 0, 0);
    framebuffer.Bind();

    if (callback) {
        callback(ctx, pixel_shader);
    }

    ctx.ClearColor(0, 0, 0, 1);
    ctx.Clear(GL_COLOR_BUFFER_BIT);
    ctx.DrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    float pixel;
    ctx.ReadPixels(0, 0, 1, 1, GL_RED, GL_FLOAT, &pixel);
    if (pixel != expected_value) {
        fprintf(stderr, "Expected %f but got %f\n", expected_value, pixel);
    }

    return pixel == expected_value;
}

} // namespace Gfx
