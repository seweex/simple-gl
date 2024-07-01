#include "only_compile_used_libs.h"
#include "context.hpp"
#include "buffer.h"
#include "texture.h"
#include "program.h"

sgl::context::context(u32 mj, u32 mn, bool compat)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mj);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mn);
    glfwWindowHint(GLFW_OPENGL_PROFILE, compat? GLFW_OPENGL_COMPAT_PROFILE : GLFW_OPENGL_CORE_PROFILE);
}

sgl::context::~context()
{
    glfwTerminate();

    for(auto& inst : _instances) {
        inst->destroy();
        delete inst;
    }
}

sgl::window sgl::context::make(size32_t width, size32_t height, lpcstr title, bool resizeable)
{
    sgl::window wnd{width, height, title, resizeable};
    gladLoadGL();
    glViewport(0, 0, width, height);

    return wnd;
}

sgl::shader sgl::context::make(shader_i::type type)
{
    shader_i * obj = new shader_i{type};
    obj->initialize();
    _instances.insert(obj);

    return obj->ref();
}
