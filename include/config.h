#ifndef __sgl_config_h__
#define __sgl_config_h__

#include "GLFW/glfw3.h"

#ifdef _WIN64
    #pragma comment(lib, "x64/glfw3.lib")
    #pragma comment(lib, "x64/sgl.lib")
#elif _WIN32
    #pragma comment(lib, "x32/glfw3.lib")
    #pragma comment(lib, "x32/sgl.lib")
#endif  

#define _SGL_NOTHROW noexcept
#define _SGL_SAFE const noexcept
#define _SGL_TEMPLATE template<>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

#include <map>
#include <set>
#include <vector>
#include <string>
#include <stdexcept>

#include "instances.hpp"

namespace sgl
{
#define UNWRAP_VEC2(v) v.x, v.y  
#define UNWRAP_VEC3(v) v.x, v.y, v.z
#define UNWRAP_VEC4(v) v.x, v.y, v.z, v.w
#define BIND2(a, b, val) a->bind(val); b->bind(val)
#define BIND3(a, b, c, val) a->bind(val); b->bind(val); c->bind(val)

    typedef unsigned u32;
    typedef unsigned size32_t;
    typedef const void* lpc;
    typedef const char* lpcstr;
    typedef GLFWkeyfun winkey_fn;

    using glm::vec2;
    using glm::vec3;
    using glm::vec4;
    using glm::mat4;

    template<typename T> using cref = const T&;

    constexpr vec2 ZERO_VEC2{ .0f };
    constexpr vec3 ZERO_VEC3{ .0f };
    constexpr vec4 ZERO_VEC4{ ZERO_VEC3, 1.f };
    constexpr mat4 IDENTITY_MAT4{ 1.f };

    constexpr size32_t DEFAULT_BUFFER_SIZE{ 1 };
    constexpr size32_t DEFAULT_INFO_LOG_SIZE{ 1024 };
    constexpr vec4 TEXTURE_BORDER_COLOR{ ZERO_VEC4 };

    class context;
}

#endif