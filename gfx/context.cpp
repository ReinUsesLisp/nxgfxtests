// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#include <switch.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "gfx/context.h"

namespace Gfx {

constexpr EGLint FramebufferAttributeList[] = {EGL_RENDERABLE_TYPE,
                                               EGL_OPENGL_BIT,
                                               EGL_RED_SIZE,
                                               8,
                                               EGL_GREEN_SIZE,
                                               8,
                                               EGL_BLUE_SIZE,
                                               8,
                                               EGL_ALPHA_SIZE,
                                               8,
                                               EGL_DEPTH_SIZE,
                                               24,
                                               EGL_STENCIL_SIZE,
                                               8,
                                               EGL_NONE};

constexpr EGLint GetProfile(Context::Profile profile) {
    switch (profile) {
    case Context::Profile::OpenGL_Core:
        return EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR;
    case Context::Profile::OpenGL_Compatibility:
        return EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR;
    }
    std::abort();
}

Context::Context(Profile profile, int major, int minor) {
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    assert(display);

    eglInitialize(display, nullptr, nullptr);

    const EGLint result = eglBindAPI(EGL_OPENGL_API);
    assert(result == EGL_TRUE);

    EGLConfig config;
    EGLint num_configs;
    eglChooseConfig(display, FramebufferAttributeList, &config, 1, &num_configs);
    assert(num_configs > 0);

    surface = eglCreateWindowSurface(display, config, nwindowGetDefault(), nullptr);
    assert(surface);

    const EGLint context_attr_list[] = {EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,
                                        GetProfile(profile),
                                        EGL_CONTEXT_MAJOR_VERSION_KHR,
                                        major,
                                        EGL_CONTEXT_MINOR_VERSION_KHR,
                                        minor,
                                        EGL_NONE};
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attr_list);
    assert(context);

    eglMakeCurrent(display, surface, surface, context);

    InitializeFunctionPointers();
}

Context::~Context() {
    eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(display, context);
    eglDestroySurface(display, surface);
    eglTerminate(display);
}

void Context::SwapBuffers() const {
    eglSwapBuffers(display, surface);
}

void Context::InitializeFunctionPointers() {
    GetProc(GetError, "glGetError");

    GetProc(ClearColor, "glClearColor");
    GetProc(PointSize, "glPointSize");

    GetProc(Clear, "glClear");
    GetProc(DrawArrays, "glDrawArrays");

    GetProc(ReadPixels, "glReadPixels");

    GetProc(GenTextures, "glGenTextures");
    GetProc(CreateTextures, "glCreateTextures");
    GetProc(DeleteTextures, "glDeleteTextures");
    GetProc(TextureView, "glTextureView");
    GetProc(TextureStorage1D, "glTextureStorage1D");
    GetProc(TextureStorage2D, "glTextureStorage2D");
    GetProc(TextureStorage3D, "glTextureStorage3D");
    GetProc(TextureSubImage1D, "glTextureSubImage1D");
    GetProc(TextureSubImage2D, "glTextureSubImage2D");
    GetProc(TextureSubImage3D, "glTextureSubImage3D");
    GetProc(BindTextureUnit, "glBindTextureUnit");
    GetProc(GetTextureHandle, "glGetTextureHandleARB");
    GetProc(MakeTextureHandleResident, "glMakeTextureHandleResidentARB");

    GetProc(CreateBuffers, "glCreateBuffers");
    GetProc(DeleteBuffers, "glDeleteBuffers");
    GetProc(NamedBufferData, "glNamedBufferData");
    GetProc(NamedBufferSubData, "glNamedBufferSubData");
    GetProc(BindBufferBase, "glBindBufferBase");

    GetProc(CreateShaderProgramv, "glCreateShaderProgramv");
    GetProc(DeleteProgram, "glDeleteProgram");
    GetProc(GetProgramiv, "glGetProgramiv");
    GetProc(GetProgramInfoLog, "glGetProgramInfoLog");
    GetProc(ProgramUniform1f, "glProgramUniform1f");
    GetProc(ProgramUniform1i, "glProgramUniform1i");
    GetProc(ProgramUniform1ui, "glProgramUniform1ui");
    GetProc(ProgramUniform1ui64, "glProgramUniform1ui64ARB");

    GetProc(CreateProgramPipelines, "glCreateProgramPipelines");
    GetProc(DeleteProgramPipelines, "glDeleteProgramPipelines");
    GetProc(BindProgramPipeline, "glBindProgramPipeline");
    GetProc(UseProgramStages, "glUseProgramStages");

    GetProc(CreateVertexArrays, "glCreateVertexArrays");
    GetProc(DeleteVertexArrays, "glDeleteVertexArrays");
    GetProc(BindVertexArray, "glBindVertexArray");

    GetProc(CreateFramebuffers, "glCreateFramebuffers");
    GetProc(DeleteFramebuffers, "glDeleteFramebuffers");
    GetProc(BindFramebuffer, "glBindFramebuffer");
    GetProc(NamedFramebufferTexture, "glNamedFramebufferTexture");
}

template <typename PFN>
void Context::GetProc(PFN& pfn, const char* function_name) {
    pfn = reinterpret_cast<PFN>(eglGetProcAddress(function_name));
    if (pfn == nullptr) {
        fprintf(stderr, "Failed to get OpenGL proc \"%s\"\n", function_name);
        std::abort();
    }
}

} // namespace Gfx
