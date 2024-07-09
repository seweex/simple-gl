#include "only_compile_used_libs.h"
#include "vertex_array.h"
#include "program.h"
#include "texture.h"
#include "window.h"

using namespace sgl;

window::window(size32_t width, size32_t height, lpcstr title, bool resizeable) _SGL_NOTHROW
    : 
    _time_curr{},
    _time_prev{}
{
    glfwWindowHint(GLFW_RESIZABLE, resizeable);

    _gl_window = glfwCreateWindow(width, height, title, 0, 0);
    glfwMakeContextCurrent(_gl_window);
}

void window::destroy() _SGL_NOTHROW
{
    glfwDestroyWindow(_gl_window);
}

void window::key_callback(winkey_fn func) _SGL_NOTHROW
{
    glfwSetKeyCallback(_gl_window, func);
}

void window::set(param pm, bool value) _SGL_NOTHROW
{
    if (value) glEnable(pm);
    else glDisable(pm);
}

void window::viewport(vec2 size) _SGL_NOTHROW
{
    glViewport(0, 0, static_cast<int>(size.x), static_cast<int>(size.y));
}

void window::clear(vec3 color) _SGL_NOTHROW
{
    glClearColor(UNWRAP_VEC3(color), 1.f);
    clear();
}

void window::clear() _SGL_NOTHROW
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void window::update() _SGL_NOTHROW
{
    _time_prev = _time_curr;
    _time_curr = glfwGetTime();

    glfwSwapBuffers(_gl_window);
    glfwPollEvents();
}

bool window::closing() _SGL_SAFE
{
    return glfwWindowShouldClose(_gl_window);
}

void window::draw(program prog, std::vector<texture> texs, vertex_array vao, std::vector<u32> indices) 
{
    std::vector<u32> texsHandlers;
    texsHandlers.reserve(texs.size());

    for (auto& tex : texs)
        texsHandlers.push_back(tex->handle());

    BIND2(prog, vao, 1);
    glBindTextures(0, static_cast<int>(texs.size()), &texsHandlers[0]);
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, &indices[0]);
    BIND2(prog, vao, 0);
}

void window::draw(program prog, vertex_array vao, std::vector<u32> indices)
{
    BIND2(prog, vao, 1);
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, &indices[0]);
    BIND2(prog, vao, 0);
}

void window::draw(program prog, std::vector<texture> texs, vertex_array vao, size32_t polygons, size32_t first)
{
    std::vector<u32> texsHandlers;
    texsHandlers.reserve(texs.size());

    for (auto& tex : texs)
        texsHandlers.push_back(tex->handle());

    BIND2(prog, vao, 1);
    glBindTextures(0, static_cast<int>(texs.size()), &texsHandlers[0]);
    glDrawArrays(GL_TRIANGLES, first, polygons * 3);
    BIND2(prog, vao, 0);
}

void window::draw(program prog, vertex_array vao, size32_t polygons, size32_t first)
{
    BIND2(prog, vao, 1);
    glDrawArrays(GL_TRIANGLES, first, polygons * 3);
    BIND2(prog, vao, 0);
}

double window::delta_time() _SGL_SAFE
{
    return _time_curr - _time_prev;
}
