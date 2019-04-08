// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#include <GL/glcorearb.h>

#include "gfx/context.h"
#include "gfx/vertex_array.h"

namespace Gfx {

VertexArray::VertexArray(const Context& ctx) : ctx{ctx} {
    ctx.CreateVertexArrays(1, &handle);
}

VertexArray::~VertexArray() {
    ctx.DeleteVertexArrays(1, &handle);
}

void VertexArray::Bind() const {
    ctx.BindVertexArray(handle);
}

} // namespace Gfx
