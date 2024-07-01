#include "only_compile_used_libs.h"
#include "texture.h"

void sgl::texture_i::initialize()
{
    glGenTextures(1, &_handle);
    
    bind();
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &TEXTURE_BORDER_COLOR[0]);  
    bind(0);
}

void sgl::texture_i::destroy()
{
    glDeleteTextures(1, &_handle);
    _handle = 0;
}

void sgl::texture_i::bind(bool is_using) const
{
    glBindTexture(GL_TEXTURE_2D, is_using ? _handle : 0);
}

void sgl::texture_i::smooth(bool value)
{
    bind();

    int smooth_min;
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &smooth_min);
    bool using_maipmaps = smooth_min == GL_LINEAR_MIPMAP_LINEAR || GL_LINEAR_MIPMAP_NEAREST;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, value ? GL_LINEAR : GL_NEAREST);

    if (using_maipmaps) 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, value ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_NEAREST);
    else 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, value ? GL_LINEAR : GL_NEAREST);

    bind(0);
}

void sgl::texture_i::mipmaps(bool use)
{
    bind();
    int min_filter_value;
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &min_filter_value);
    bool smooth = min_filter_value == GL_LINEAR_MIPMAP_LINEAR || GL_LINEAR;

    if (smooth)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, use ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
    else 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, use ? GL_LINEAR_MIPMAP_NEAREST : GL_NEAREST);

    bind(0);
}

void sgl::texture_i::wrapping(wrap_type type)
{
    bind(); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, type);

    bind(0);
}

void sgl::texture_i::image(size32_t width, size32_t height, color_mode format, lpc pixels, pixel_mode pxformat)
{
    bind(); 

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, pxformat, pixels);

    bind(0);
}

sgl::detail::instance_ref<sgl::texture_i> sgl::texture_i::ref()
{
    return detail::instance_ref<texture_i>(*this);
}
