#include "vertex_array.h"
#include "program.h"
#include "texture.h"

#include "window.h"

sgl::window::window(size32_t width, size32_t height, lpcstr title, bool resizeable)
{
    glfwWindowHint(GLFW_RESIZABLE, resizeable);

    _gl_window = glfwCreateWindow(width, height, title, 0, 0);
    glfwMakeContextCurrent(_gl_window);
}

void sgl::window::destroy()
{
    glfwDestroyWindow(_gl_window);
}

void sgl::window::set(param pm, bool value)
{
    if (value) glEnable(pm);
    else glDisable(pm);
}

void sgl::window::viewport(vec2 size)
{
    glViewport(0, 0, UNWRAP_VEC2(size));
}

void sgl::window::clear(vec3 color)
{
    glClearColor(UNWRAP_VEC3(color), 1.f);
    clear();
}

void sgl::window::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void sgl::window::update()
{
    glfwSwapBuffers(_gl_window);
    glfwPollEvents();
}

bool sgl::window::closing() const
{
    return glfwWindowShouldClose(_gl_window);
}

void sgl::window::draw(program prog, texture tex, vertex_array vao, std::vector<u32> indices)
{
    BIND3(prog, tex, vao, 1);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);
    BIND3(prog, tex, vao, 0);
}

void sgl::window::draw(program prog, vertex_array vao, std::vector<u32> indices)
{
    BIND2(prog, vao, 1);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);
    BIND2(prog, vao, 0);
}

void sgl::window::draw(program prog, texture tex, vertex_array vao, size32_t polygons)
{
    BIND3(prog, tex, vao, 1);
    glDrawArrays(GL_TRIANGLES, 0, polygons);
    BIND3(prog, tex, vao, 0);
}

void sgl::window::draw(program prog, vertex_array vao, size32_t polygons)
{
    BIND2(prog, vao, 1);
    glDrawArrays(GL_TRIANGLES, 0, polygons);
    BIND2(prog, vao, 0);
}