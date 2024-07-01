#ifndef __instances_h__
#define __instances_h__

#include <type_traits>

namespace sgl 
{
    namespace detail 
    {
        class i_instance
        {
        protected:

            unsigned _handle;

        public:

            i_instance();

            unsigned handle() const noexcept;

            virtual void initialize() = 0;
            virtual void destroy() = 0;
            virtual void bind(bool is_using = true) const = 0;

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

            instance_ref() : _ptr(nullptr) {}
            instance_ref(T& object) : _ptr(&object) 
            {
                static_assert(std::is_base_of<i_instance, T>::value, "invalid T type");
            }

            T& get() {return *_ptr;}
            const T& get() const {return *_ptr;}

            T& operator*() {return *_ptr;}
            const T& operator*() const {return *_ptr;}

            T* operator->() {return _ptr;}
            const T* operator->() const {return _ptr;}
        };
    }
}

#endif
