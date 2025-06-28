#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

#include <optional>

namespace ProtocolCraft
{
    template<typename T>
    class Holder : public NetworkType
    {
    public:
        Holder() = default;

        template <typename U>
        Holder(const Holder<U>& other)
        {
            id = other.GetId();
            if (other.GetValue().has_value())
            {
                value = static_cast<T>(other.GetValue().value());
            }
        }

        virtual ~Holder()
        {

        }


        int GetId() const
        {
            return id;
        }

        const std::optional<T>& GetValue() const
        {
            return value;
        }


        auto& SetId(const int id_)
        {
            id = id_;
            return *this;
        }

        auto& SetValue(const std::optional<T>& value_)
        {
            value = value_;
            return *this;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id = ReadData<VarInt>(iter, length);
            if (id == 0)
            {
                value = ReadData<T>(iter, length);
            }
            else
            {
                id -= 1;
                value = std::optional<T>();
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            if (value.has_value())
            {
                WriteData<VarInt>(0, container);
                WriteData<T>(value.value(), container);
            }
            else
            {
                WriteData<VarInt>(id + 1, container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            if (value.has_value())
            {
                output["value"] = value.value();
            }
            else
            {
                output["id"] = id;
            }

            return output;
        }

    private:
        int id = 0;
        std::optional<T> value;

    };
}
#endif
