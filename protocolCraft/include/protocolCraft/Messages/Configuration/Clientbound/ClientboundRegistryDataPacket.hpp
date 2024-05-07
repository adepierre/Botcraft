#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
#include "protocolCraft/Types/NBT/NBT.hpp"
#else
#include "protocolCraft/Types/PackedRegistryEntry.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <vector>
#endif


namespace ProtocolCraft
{
    class ClientboundRegistryDataPacket : public BaseMessage<ClientboundRegistryDataPacket>
    {
    public:
#if   PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x07;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Registry Data";

        virtual ~ClientboundRegistryDataPacket() override
        {

        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        void SetRegistryHolder(const NBT::Value& registry_holder_)
        {
            registry_holder = registry_holder_;
        }
#else
        void SetRegistry(const Identifier& registry_)
        {
            registry = registry_;
        }

        void SetEntries(const std::vector<PackedRegistryEntry>& entries_)
        {
            entries = entries_;
        }
#endif


#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        const NBT::Value& GetRegistryHolder() const
        {
            return registry_holder;
        }
#else
        const Identifier& GetRegistry() const
        {
            return registry;
        }

        const std::vector<PackedRegistryEntry>& GetEntries() const
        {
            return entries;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            registry_holder = ReadData<NBT::UnnamedValue>(iter, length);
#else
            registry = ReadData<Identifier>(iter, length);
            entries = ReadVector<PackedRegistryEntry>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            WriteData<NBT::UnnamedValue>(registry_holder, container);
#else
            WriteData<Identifier>(registry, container);
            WriteVector<PackedRegistryEntry>(entries, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            output["registry_holder"] = registry_holder;
#else
            output["registry"] = registry;
            output["entries"] = entries;
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        NBT::Value registry_holder;
#else
        Identifier registry;
        std::vector<PackedRegistryEntry> entries;
#endif
    };
} //ProtocolCraft
#endif
