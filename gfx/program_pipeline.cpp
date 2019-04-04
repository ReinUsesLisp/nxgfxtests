// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#include <GL/glcorearb.h>

#include <cstdlib>
#include <vector>

#include "gfx/context.h"
#include "gfx/shader.h"
#include "gfx/program_pipeline.h"

namespace Gfx {

constexpr GLbitfield GetShaderStage(Shader::Type type) {
    switch (type) {
        case Shader::Type::Vertex:
            return GL_VERTEX_SHADER_BIT;
        case Shader::Type::Hull:
            return GL_TESS_CONTROL_SHADER_BIT;
        case Shader::Type::Domain:
            return GL_TESS_EVALUATION_SHADER_BIT;
        case Shader::Type::Geometry:
            return GL_GEOMETRY_SHADER_BIT;
        case Shader::Type::Pixel:
            return GL_FRAGMENT_SHADER_BIT;
        case Shader::Type::Compute:
            return GL_COMPUTE_SHADER_BIT;
    }
    std::abort();
}

ProgramPipeline::~ProgramPipeline() {
    ctx.DeleteProgramPipelines(1, &handle);
}

void ProgramPipeline::Bind() const {
    ctx.BindProgramPipeline(handle);
}

void ProgramPipeline::Create() {
    ctx.CreateProgramPipelines(1, &handle);
}

void ProgramPipeline::AttachShader(const Shader& shader) {
    const auto type = shader.GetType();
    const auto stage = GetShaderStage(type);
    ctx.UseProgramStages(handle, stage, shader.GetHandle());
}

} // namespace Gfx

