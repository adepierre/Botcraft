#pragma once
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/KnownPack.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundSelectKnownPacksPacket : public BaseMessage<ClientboundSelectKnownPacksPacket>
    {
    public:
        static constexpr int packet_id = 0x0E;
        static constexpr std::string_view packet_name = "Select Known Packs";

        virtual ~ClientboundSelectKnownPacksPacket() override
        {

        }


        void SetKnownPacks(const std::vector<KnownPack>& known_packs_)
        {
            known_packs = known_packs_;
        }


        const std::vector<KnownPack>& GetKnownPacks() const
        {
            return known_packs;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            known_packs = ReadVector<KnownPack>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVector<KnownPack>(known_packs, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["known_packs"] = known_packs;

            return output;
        }

    private:
        std::vector<KnownPack> known_packs;
    };
} // ProtocolCraft
#endif
