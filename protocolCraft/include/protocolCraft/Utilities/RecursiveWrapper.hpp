#pragma once

#include <memory>


namespace ProtocolCraft
{
    namespace Internal
    {
        /// @brief Template magic to have a full type instead of an incomplete one as required for example by std::variant
        /// @tparam T Any incomplete class we want to wrap
        template<typename T>
        class RecursiveWrapper
        {
        public:
            RecursiveWrapper() = delete;
            ~RecursiveWrapper() = default;

            RecursiveWrapper(const RecursiveWrapper& r) noexcept
            {
                p = std::make_unique<T>(*r.p);
            }

            RecursiveWrapper(RecursiveWrapper&& r) noexcept
            {
                p = std::move(r.p);
            }

            RecursiveWrapper(const T& r) noexcept
            {
                p = std::make_unique<T>(r);
            }

            RecursiveWrapper(T&& r) noexcept
            {
                p = std::make_unique<T>(std::move(r));
            }

            const T& get() const noexcept
            {
                return *p.get();
            }

            T& get() noexcept
            {
                return *p.get();
            }

            RecursiveWrapper& operator=(const RecursiveWrapper& other) noexcept
            {
                p = std::make_unique<T>(*other.p);
                return *this;
            }

            RecursiveWrapper& operator=(RecursiveWrapper&& other) noexcept
            {
                p = std::move(other.p);
                return *this;
            }

        private:
            std::unique_ptr<T> p;
        };
    }
}
