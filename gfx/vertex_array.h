// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include <GL/glcorearb.h>

namespace Gfx {

class Context;

class VertexArray {
public:
    VertexArray(const Context& ctx);
    VertexArray(const VertexArray&) = delete;
    ~VertexArray();

    void Bind() const;

    GLuint GetHandle() const {
        return handle;
    }

private:
    const Context& ctx;
    GLuint handle{};
};

} // namespace Gfx
