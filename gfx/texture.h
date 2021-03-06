// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include <optional>

#include <GL/glcorearb.h>

namespace Gfx {

class Context;

class Texture {
public:
    Texture(const Context& ctx, GLenum target, GLenum format, GLsizei levels, GLsizei width,
            std::optional<GLsizei> height = {}, std::optional<GLsizei> depth = {});
    Texture(const Texture& original_texture, GLenum target, GLenum format, int min_level,
            int num_levels, int min_layer, int num_layers);
    Texture(const Texture&) = delete;
    ~Texture();

    void BindTexture(int index = 0) const;

    void Upload(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type,
                const void* pixels) const;
    void Upload(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
                GLenum format, GLenum type, const void* pixels) const;
    void Upload(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width,
                GLsizei height, GLsizei depth, GLenum format, GLenum type,
                const void* pixels) const;

    GLuint64 GetBindlessHandle() const;

    GLuint GetHandle() const {
        return handle;
    }

private:
    const Context& ctx;
    GLuint handle{};
};

} // namespace Gfx
