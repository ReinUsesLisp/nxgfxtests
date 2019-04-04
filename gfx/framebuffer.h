// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include <GL/glcorearb.h>

namespace Gfx {

class Context;
class Texture;

class Framebuffer {
public:
    Framebuffer(const Context& ctx);
    Framebuffer(const Framebuffer&) = delete;
    ~Framebuffer();

    void Bind() const;
    void DrawBind() const;
    void ReadBind() const;

    void AttachColor(const Texture& texture, int index = 0, int level = 0) const;
    void AttachDepth(const Texture& texture, int level) const;
    void AttachStencil(const Texture& texture, int level) const;
    void AttachDepthStencil(const Texture& texture, int level) const;

    GLuint GetHandle() const {
        return handle;
    }

private:
    const Context& ctx;
    GLuint handle{};
};

} // namespace Gfx
