#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    class ClientboundRegistryDataPacket : public BaseMessage<ClientboundRegistryDataPacket>
    {
    public:
        static constexpr int packet_id = 0x05;

        static constexpr std::string_view packet_name = "Registry Data";

        virtual ~ClientboundRegistryDataPacket() override
        {

        }

        void SetRegistryHolder(const NBT::Value& registry_holder_)
        {
            registry_holder = registry_holder_;
        }

        const NBT::Value& GetRegistryHolder() const
        {
            return registry_holder;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            registry_holder = ReadData<NBT::UnnamedValue>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<NBT::UnnamedValue>(registry_holder, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["registry_holder"] = registry_holder;

            return output;
        }

    private:
        NBT::Value registry_holder;
    };
} //ProtocolCraft
#endif
