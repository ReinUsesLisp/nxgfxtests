// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include <GL/glcorearb.h>

namespace Gfx {

class Context;

class Buffer {
public:
    explicit Buffer(const Context& ctx, GLenum usage = GL_STATIC_DRAW);
    Buffer(const Buffer&) = delete;
    ~Buffer();

    void Resize(GLsizeiptr size) const;

    void InvalidateUpload(GLsizeiptr size, const void* data) const;

    void Upload(GLintptr offset, GLsizeiptr size, const void* data) const;

    void BindAsUniform(GLuint index) const;

    GLuint GetHandle() const {
        return handle;
    }

private:
    const Context& ctx;
    GLuint handle{};
    GLenum usage{};
};

} // namespace Gfx