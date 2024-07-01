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

        void initialize() override;
        void destroy() override;

        int compile(lpcstr source) const;
        std::string log() const;
        
        shader ref();

    private:

        type _type;

        shader_i(type tp);

        void bind(bool = true) const override;
    };
}

#endif