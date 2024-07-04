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

        window(size32_t width, size32_t height, lpcstr title, bool resizeable);

    public:

        friend sgl::context;

        void destroy();

        enum param : u32
        {
            depth_test = 0xb71,
            cull_face = 0xb44,
            front_face = 0xb46
        };

        void set(param pm, bool value);
        void viewport(vec2 size);

        void clear(vec3 color);
        void clear() const;

        void update();
        bool closing() const;

        void draw(program prog,
            texture tex, vertex_array vao, std::vector<u32> indices);
        void draw(program prog,
            vertex_array vao, std::vector<u32> indices);

        void draw(program prog,
            texture tex, vertex_array vao, size32_t polygons);
        void draw(program prog,
            vertex_array vao, size32_t polygons);

        double delta_time() const;
    };
}

#endif