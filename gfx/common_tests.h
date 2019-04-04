// Copyright 2019 nxgfxtests
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include <functional>

#include "common/test_list.h"
#include "gfx/context.h"
#include "gfx/shader.h"

namespace Gfx {

class Context;
class Shader;

using SetupCallback = std::function<void(const Context&, const Shader&)>;

bool SinglePixelTest(const char* pixel_shader_glsl, float expected_value,
                     SetupCallback callback = {});

} // namespace Gfx
