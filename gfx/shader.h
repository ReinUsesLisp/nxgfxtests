// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include <GL/glcorearb.h>

#include <string>

namespace Gfx {

class Context;

class Shader {
public:
    enum class Type {
        Vertex,
        Hull,
        Domain,
        Geometry,
        Pixel,
        Compute,
    };

    explicit Shader(const Context& ctx, Type type, const std::string& code);
    Shader(const Shader&) = delete;
    ~Shader();

    GLuint GetHandle() const {
        return handle;
    }

    Type GetType() const {
        return type;
    }

private:
    const Context& ctx;
    Type type{};
    GLuint handle{};
};

template <Shader::Type TYPE>
class ShaderSpecialized : public Shader {
public:
    explicit ShaderSpecialized(const Context& ctx, const std::string& code)
        : Shader(ctx, TYPE, code) {}
    explicit ShaderSpecialized(const Context& ctx, const char* code)
        : ShaderSpecialized(ctx, std::string(code)) {}
};

using VertexShader = ShaderSpecialized<Shader::Type::Vertex>;
using HullShader = ShaderSpecialized<Shader::Type::Hull>;
using DomainShader = ShaderSpecialized<Shader::Type::Domain>;
using GeometryShader = ShaderSpecialized<Shader::Type::Geometry>;
using PixelShader = ShaderSpecialized<Shader::Type::Pixel>;
using ComputeShader = ShaderSpecialized<Shader::Type::Compute>;

} // namespace Gfx
