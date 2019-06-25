// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#include <GL/glcorearb.h>

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cassert>

#include "gfx/context.h"
#include "gfx/shader.h"

namespace Gfx {

constexpr GLenum GetShaderType(Shader::Type type) {
    switch (type) {
        case Shader::Type::Vertex:
            return GL_VERTEX_SHADER;
        case Shader::Type::Hull:
            return GL_TESS_CONTROL_SHADER;
        case Shader::Type::Domain:
            return GL_TESS_EVALUATION_SHADER;
        case Shader::Type::Geometry:
            return GL_GEOMETRY_SHADER;
        case Shader::Type::Pixel:
            return GL_FRAGMENT_SHADER;
        case Shader::Type::Compute:
            return GL_COMPUTE_SHADER;
    }
    std::abort();
}

Shader::Shader(const Context& ctx, Type type, const std::string& code) : ctx{ctx}, type{type} {
    const GLenum gl_type = GetShaderType(type);
    const char* c_code = code.c_str();
    handle = ctx.CreateShaderProgramv(gl_type, 1, &c_code);
    assert(handle != 0);

    GLint log_length = 0;
    ctx.GetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        std::string log(static_cast<std::size_t>(log_length), ' ');
        ctx.GetProgramInfoLog(handle, static_cast<GLsizei>(log_length), nullptr, log.data());
        std::fputs(log.c_str(), stderr);

        std::fputs(code.c_str(), stderr);
    }

    GLint link_status = GL_FALSE;
    ctx.GetProgramiv(handle, GL_LINK_STATUS, &link_status);
    assert(link_status == GL_TRUE);
}

Shader::~Shader() {
    ctx.DeleteProgram(handle);
}

} // namespace Gfx
