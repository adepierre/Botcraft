#pragma once

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

#include <optional>

namespace ProtocolCraft
{
    class PackedRegistryEntry : public NetworkType
    {
    public:
        virtual ~PackedRegistryEntry() override
        {

        }


        void SetId(const Identifier& id__)
        {
            id_ = id__;
        }

        void SetData(const std::optional<NBT::Value>& data_)
        {
            data = data_;
        }


        const Identifier& GetId_() const
        {
            return id_;
        }

        const std::optional<NBT::Value>& GetData() const
        {
            return data;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<Identifier>(iter, length);
            data = ReadData<std::optional<NBT::Value>, std::optional<NBT::UnnamedValue>>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Identifier>(id_, container);
            WriteData<std::optional<NBT::Value>, std::optional<NBT::UnnamedValue>>(data, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id"] = id_;
            if (data.has_value())
            {
                output["data"] = data.value();
            }

            return output;
        }

    private:
        Identifier id_;
        std::optional<NBT::Value> data;
    };
}
#endif
