// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#include "gfx/context.h"
#include "gfx/framebuffer.h"
#include "gfx/texture.h"

namespace Gfx {

Framebuffer::Framebuffer(const Context& ctx) : ctx{ctx} {
    ctx.CreateFramebuffers(1, &handle);
}

Framebuffer::~Framebuffer() {
    ctx.DeleteFramebuffers(1, &handle);
}

void Framebuffer::Bind() const {
    ctx.BindFramebuffer(GL_FRAMEBUFFER, handle);
}

void Framebuffer::DrawBind() const {
    ctx.BindFramebuffer(GL_DRAW_FRAMEBUFFER, handle);
}

void Framebuffer::ReadBind() const {
    ctx.BindFramebuffer(GL_READ_FRAMEBUFFER, handle);
}

void Framebuffer::AttachColor(const Texture& texture, int index, int level) const {
    ctx.NamedFramebufferTexture(handle, GL_COLOR_ATTACHMENT0 + index, texture.GetHandle(), level);
}

void Framebuffer::AttachDepth(const Texture& texture, int level) const {
    ctx.NamedFramebufferTexture(handle, GL_DEPTH_ATTACHMENT, texture.GetHandle(), level);
}

void Framebuffer::AttachStencil(const Texture& texture, int level) const {
    ctx.NamedFramebufferTexture(handle, GL_STENCIL_ATTACHMENT, texture.GetHandle(), level);
}

void Framebuffer::AttachDepthStencil(const Texture& texture, int level) const {
    ctx.NamedFramebufferTexture(handle, GL_DEPTH_STENCIL_ATTACHMENT, texture.GetHandle(), level);
}

} // namespace Gfx
