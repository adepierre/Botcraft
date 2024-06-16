#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"

#include <optional>

namespace ProtocolCraft
{
    template<typename T>
    class Filterable : public NetworkType
    {
    public:
        virtual ~Filterable()
        {

        }


        const T& GetRaw() const
        {
            return raw;
        }

        const std::optional<T>& GetFiltered() const
        {
            return filtered;
        }


        auto& SetRaw(const T& raw_)
        {
            raw = raw_;
            return *this;
        }

        auto& SetFiltered(const std::optional<T>& filtered_)
        {
            filtered = filtered_;
            return *this;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            raw = ReadData<T>(iter, length);
            filtered = ReadData<std::optional<T>>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<T>(raw, container);
            WriteData<std::optional<T>>(filtered, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;


            output["raw"] = raw;
            if (filtered.has_value())
            {
                output["filtered"] = filtered.value();
            }

            return output;
        }

    private:
        T raw;
        std::optional<T> filtered;

    };
}
#endif
