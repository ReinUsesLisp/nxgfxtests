// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include <array>
#include <functional>
#include <vector>

namespace Gfx {

class Context;
class Shader;

class ProgramPipeline {
public:
    template <typename... Ts>
    explicit ProgramPipeline(const Context& ctx, std::vector<std::reference_wrapper<const Shader>> shaders) : ctx{ctx} {
        Create();
        for (const auto& shader : shaders) {
            AttachShader(shader.get());
        }
    }
    ProgramPipeline(const ProgramPipeline&) = delete;

    ~ProgramPipeline();

    void Bind() const;

private:
    void Create();

    void AttachShader(const Shader& shader);

    const Context& ctx;
    GLuint handle{};
};

} // namespace Gfx
