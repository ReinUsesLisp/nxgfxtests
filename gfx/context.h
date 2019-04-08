// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include <cstddef>

#include <EGL/egl.h>
#include <GL/glcorearb.h>

namespace Gfx {

class Context {
public:
    enum class Profile {
        OpenGL_Core,
        OpenGL_Compatibility,
    };

    explicit Context(Profile profile, int major, int minor);
    ~Context();

    void SwapBuffers() const;

    constexpr std::size_t GetWidth() const {
        return 1280;
    }

    constexpr std::size_t GetHeight() const {
        return 720;
    }

    PFNGLGETERRORPROC GetError;

    PFNGLCLEARCOLORPROC ClearColor;
    PFNGLPOINTSIZEPROC PointSize;

    PFNGLCLEARPROC Clear;
    PFNGLDRAWARRAYSPROC DrawArrays;

    PFNGLREADPIXELSPROC ReadPixels;

    PFNGLGENTEXTURESPROC GenTextures;
    PFNGLCREATETEXTURESPROC CreateTextures;
    PFNGLDELETETEXTURESPROC DeleteTextures;
    PFNGLTEXTUREVIEWPROC TextureView;
    PFNGLTEXTURESTORAGE1DPROC TextureStorage1D;
    PFNGLTEXTURESTORAGE2DPROC TextureStorage2D;
    PFNGLTEXTURESTORAGE3DPROC TextureStorage3D;
    PFNGLTEXTURESUBIMAGE1DPROC TextureSubImage1D;
    PFNGLTEXTURESUBIMAGE2DPROC TextureSubImage2D;
    PFNGLTEXTURESUBIMAGE3DPROC TextureSubImage3D;
    PFNGLBINDTEXTUREUNITPROC BindTextureUnit;
    PFNGLGETTEXTUREHANDLEARBPROC GetTextureHandle;
    PFNGLMAKETEXTUREHANDLERESIDENTARBPROC MakeTextureHandleResident;

    PFNGLCREATEBUFFERSPROC CreateBuffers;
    PFNGLDELETEBUFFERSPROC DeleteBuffers;
    PFNGLNAMEDBUFFERDATAPROC NamedBufferData;
    PFNGLNAMEDBUFFERSUBDATAPROC NamedBufferSubData;
    PFNGLBINDBUFFERBASEPROC BindBufferBase;

    PFNGLCREATESHADERPROGRAMVPROC CreateShaderProgramv;
    PFNGLDELETEPROGRAMPROC DeleteProgram;
    PFNGLGETPROGRAMIVPROC GetProgramiv;
    PFNGLGETPROGRAMINFOLOGPROC GetProgramInfoLog;
    PFNGLPROGRAMUNIFORM1FPROC ProgramUniform1f;
    PFNGLPROGRAMUNIFORM1IPROC ProgramUniform1i;
    PFNGLPROGRAMUNIFORM1UI64ARBPROC ProgramUniform1ui64;

    PFNGLCREATEPROGRAMPIPELINESPROC CreateProgramPipelines;
    PFNGLDELETEPROGRAMPIPELINESPROC DeleteProgramPipelines;
    PFNGLBINDPROGRAMPIPELINEPROC BindProgramPipeline;
    PFNGLUSEPROGRAMSTAGESPROC UseProgramStages;

    PFNGLCREATEVERTEXARRAYSPROC CreateVertexArrays;
    PFNGLDELETEVERTEXARRAYSPROC DeleteVertexArrays;
    PFNGLBINDVERTEXARRAYPROC BindVertexArray;

    PFNGLCREATEFRAMEBUFFERSPROC CreateFramebuffers;
    PFNGLDELETEFRAMEBUFFERSPROC DeleteFramebuffers;
    PFNGLBINDFRAMEBUFFERPROC BindFramebuffer;
    PFNGLNAMEDFRAMEBUFFERTEXTUREPROC NamedFramebufferTexture;

private:
    void InitializeFunctionPointers();

    template <typename PFN>
    void GetProc(PFN& pfn, const char* function_name);

    EGLDisplay display{};
    EGLContext context{};
    EGLSurface surface{};
};

} // namespace Gfx
