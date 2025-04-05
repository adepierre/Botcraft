#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

#include <optional>

namespace ProtocolCraft
{
    template<typename T, typename U>
    class Either : public NetworkType
    {
    public:
        virtual ~Either()
        {

        }


        const std::optional<T>& GetLeft() const
        {
            return left;
        }

        const std::optional<T>& GetRight() const
        {
            return right;
        }


        auto& SetLeft(const std::optional<T>& left_)
        {
            left = left_;
            if (left.has_value())
            {
                right = std::nullopt;
            }
            return *this;
        }

        auto& SetRight(const std::optional<T>& right_)
        {
            right = right_;
            if (right.has_value())
            {
                left = std::nullopt;
            }
            return *this;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            const bool is_left = ReadData<bool>(iter, length);
            if (is_left)
            {
                left = ReadData<T>(iter, length);
                right = std::nullopt;
            }
            else
            {
                left = std::nullopt;
                right = ReadData<U>(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(left.has_value(), container);
            if (left.has_value())
            {
                WriteData<T>(left.value(), container);
            }
            else // Right should have a value
            {
                WriteData<U>(right.value(), container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            if (left.has_value())
            {
                output["left"] = left.value();
            }
            else if (right.has_value())
            {
                output["right"] = right.value();
            }

            return output;
        }

    private:
        std::optional<T> left;
        std::optional<U> right;

    };
}
#endif
