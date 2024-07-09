#ifndef __texture_h__
#define __texture_h__

#include "config.h"

namespace sgl
{
    class texture_i : public detail::i_instance
    {
        texture_i() _SGL_NOTHROW = default;

    public:

        friend context;

        enum color_mode : u32
        {
            rgb = 0x1907,
            rgba = 0x1908,
            depth_component = 0x1902,
            depth_stencil = 0x84F9,
            stencil_index = 0x1901
        };

        enum pixel_mode : u32
        {
            unsigned_byte = 0x1401,
            unsigned_short = 0x1403,
            unsigned_int = 0x1405,
            glfloat = 0x1406,
            byte = 0x1400,
            glshort = 0x1402
        };

        enum wrap_type : u32
        {
            clamp_to_edge = 0x812F,
            clamp_to_border = 0x812D,
            mirrored_repeat = 0x8370,
            repeat = 0x2901
        };

        void initialize() _SGL_NOTHROW override;
        void destroy() _SGL_NOTHROW override;
        void bind(bool is_using = true) _SGL_SAFE override;

        void smooth(bool value) _SGL_NOTHROW;
        void mipmaps(bool use) _SGL_NOTHROW;
        void wrapping(wrap_type type) _SGL_NOTHROW;

        void image(
            size32_t width, size32_t height,
            color_mode format, lpc pixels, 
            pixel_mode pxformat = unsigned_byte) _SGL_NOTHROW;

        detail::instance_ref<texture_i> ref() _SGL_NOTHROW;
    };

    typedef detail::instance_ref<texture_i> texture;
}

#endif