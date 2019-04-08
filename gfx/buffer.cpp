// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#include <GL/glcorearb.h>

#include "gfx/buffer.h"
#include "gfx/context.h"

namespace Gfx {

Buffer::Buffer(const Context& ctx, GLenum usage) : ctx{ctx}, usage{usage} {
    ctx.CreateBuffers(1, &handle);
}

Buffer::~Buffer() {
    ctx.DeleteBuffers(1, &handle);
}

void Buffer::Resize(GLsizeiptr size) const {
    ctx.NamedBufferData(handle, size, nullptr, usage);
}

void Buffer::InvalidateUpload(GLsizeiptr size, const void* data) const {
    ctx.NamedBufferData(handle, size, data, usage);
}

void Buffer::Upload(GLintptr offset, GLsizeiptr size, const void* data) const {
    ctx.NamedBufferSubData(handle, offset, size, data);
}

void Buffer::BindAsUniform(GLuint index) const {
    ctx.BindBufferBase(GL_UNIFORM_BUFFER, index, handle);
}

} // namespace Gfx
