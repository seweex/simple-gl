#ifndef __shader_h__
#define __shader_h__

#include "config.h"

namespace sgl
{
    class shader_i : public detail::i_instance
    {
    public:

        friend context;

        enum type : u32
        {
            vertex = 0x8B31,
            fragment = 0x8B30,
            geometry = 0x8DD9,
            compute = 0x91B9
        };

        void initialize() _SGL_NOTHROW override;
        void destroy() _SGL_NOTHROW override;

        int compile(lpcstr source) _SGL_NOTHROW;
        std::string log() _SGL_SAFE;
        
        detail::instance_ref<shader_i> ref() _SGL_NOTHROW;

    private:

        type _type;

        shader_i(type tp) _SGL_NOTHROW;

        void bind(bool = true) _SGL_SAFE override;
    };

    typedef detail::instance_ref<shader_i> shader;
}

#endif