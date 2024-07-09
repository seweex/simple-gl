#ifndef __window_h__
#define __window_h__

#include "config.h"
#include "vertex_array.h"
#include "texture.h"
#include "program.h"

namespace sgl
{
    class window
    {
        GLFWwindow* _gl_window;

        double _time_prev;
        double _time_curr;

        window(size32_t width, size32_t height, lpcstr title, bool resizeable) _SGL_NOTHROW;

    public:

        friend sgl::context;

        enum param : u32
        {
            depth_test = 0xb71,
            cull_face = 0xb44,
            front_face = 0xb46
        };

        void destroy() _SGL_NOTHROW;

        void key_callback(winkey_fn func) _SGL_NOTHROW;
        void set(param pm, bool value) _SGL_NOTHROW;
        void viewport(vec2 size) _SGL_NOTHROW;

        void clear(vec3 color) _SGL_NOTHROW;
        void clear() _SGL_NOTHROW;

        void update() _SGL_NOTHROW;
        bool closing() _SGL_SAFE;

        void draw(program prog,
            std::vector<texture> texs, vertex_array vao, std::vector<u32> indices);
        void draw(program prog,
            vertex_array vao, std::vector<u32> indices);

        void draw(program prog,
            std::vector<texture> texs, vertex_array vao, size32_t polygons, size32_t first = 0);
        void draw(program prog,
            vertex_array vao, size32_t polygons, size32_t first = 0);

        double delta_time() _SGL_SAFE;
    };
}

#endif