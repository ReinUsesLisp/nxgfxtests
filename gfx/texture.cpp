// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#include <cassert>
#include <optional>

#include "gfx/context.h"
#include "gfx/texture.h"

namespace Gfx {

Texture::Texture(const Context& ctx, GLenum target, GLenum format, GLsizei levels, GLsizei width,
                 std::optional<GLsizei> height, std::optional<GLsizei> depth)
    : ctx{ctx} {
    ctx.CreateTextures(target, 1, &handle);
    if (depth) {
        assert(height);
        ctx.TextureStorage3D(handle, levels, format, width, *height, *depth);
    } else if (height) {
        ctx.TextureStorage2D(handle, levels, format, width, *height);
    } else {
        ctx.TextureStorage1D(handle, levels, format, width);
    }
}

Texture::Texture(const Texture& original_texture, GLenum target, GLenum format, int min_level,
                 int num_levels, int min_layer, int num_layers)
    : ctx{original_texture.ctx} {
    ctx.GenTextures(1, &handle);
    ctx.TextureView(handle, target, original_texture.handle, format, min_level, num_levels,
                    min_layer, num_layers);
}

Texture::~Texture() {
    ctx.DeleteTextures(1, &handle);
}

void Texture::Bind(int index) const {
    ctx.BindTextureUnit(index, handle);
}

} // namespace Gfx