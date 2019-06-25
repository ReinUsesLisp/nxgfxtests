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
    fprintf(stderr, "Prepare context\n");

    const Context ctx(Context::Profile::OpenGL_Core, 4, 3);

    fprintf(stderr, "CTX built\n");

    const VertexShader vertex_shader(ctx, VERTEX_SHADER);

    fprintf(stderr, "Vertex built\n");

    const PixelShader pixel_shader(ctx, pixel_shader_glsl);

    fprintf(stderr, "Pixel built\n");

    fprintf(stderr, "Shaders built\n");

    const ProgramPipeline pipeline(ctx, {vertex_shader, pixel_shader});
    pipeline.Bind();

    fprintf(stderr, "Pipeline built\n");

    const VertexArray vao(ctx);
    vao.Bind();

    fprintf(stderr, "VAO built\n");

    const Texture texture(ctx, GL_TEXTURE_2D, GL_R32F, 1, 1, 1);
    const Framebuffer framebuffer(ctx);
    framebuffer.AttachColor(texture, 0, 0);
    framebuffer.Bind();

    fprintf(stderr, "FBO built\n");

    fprintf(stderr, "Before callback\n");

    if (callback) {
        callback(ctx, pixel_shader);
    }

    fprintf(stderr, "Callback done\n");

    fprintf(stderr, "Before ClearColor\n");

    ctx.ClearColor(0, 0, 0, 1);

    fprintf(stderr, "ClearColor done\n");

    ctx.Clear(GL_COLOR_BUFFER_BIT);

    fprintf(stderr, "Clear done\n");

    ctx.DrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    std::vector<int> foo(1000000);
    std::sort(foo.begin(), foo.end());

    fprintf(stderr, "Draw done\n");

    float pixel;
    ctx.ReadPixels(0, 0, 1, 1, GL_RED, GL_FLOAT, &pixel);

    fprintf(stderr, "Read pixels done\n");

    if (pixel != expected_value) {
        fprintf(stderr, "Expected %f but got %f\n", expected_value, pixel);
    }

    fprintf(stderr, "Done\n");

    return pixel == expected_value;
}

} // namespace Gfx
