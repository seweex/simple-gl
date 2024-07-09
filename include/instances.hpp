#ifndef __instances_h__
#define __instances_h__

#include <type_traits>

#define _SGL_NOTHROW noexcept
#define _SGL_SAFE const noexcept

namespace sgl 
{
    namespace detail 
    {
        class i_instance
        {
        protected:

            unsigned _handle;

        public:

            i_instance() _SGL_NOTHROW;

            unsigned handle() _SGL_SAFE;

            virtual void initialize() _SGL_NOTHROW = 0;
            virtual void destroy() _SGL_NOTHROW = 0;
            virtual void bind(bool is_using = true) _SGL_SAFE = 0;

            i_instance(const i_instance&) = delete;
            i_instance& operator=(const i_instance&) = delete;
        };

        template <typename T>
        class instance_ref
        {
            T* _ptr;

        public:

            using type = T;
            friend T;

            instance_ref(T& object) _SGL_NOTHROW : _ptr(&object)
            {
                static_assert(std::is_base_of<i_instance, T>::value, "invalid T type");
            }

            T& get() _SGL_NOTHROW { return *_ptr; }
            const T& get() _SGL_SAFE { return *_ptr; }

            T& operator*() _SGL_NOTHROW { return *_ptr; }
            const T& operator*() _SGL_SAFE { return *_ptr; }

            T* operator->() _SGL_NOTHROW { return _ptr; }
            const T* operator->() _SGL_SAFE { return _ptr; }
        };
    }
}

#endif
