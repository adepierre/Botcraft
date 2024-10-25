#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/MerchantOffer.hpp"

namespace ProtocolCraft
{
    class ClientboundMerchantOffersPacket : public BaseMessage<ClientboundMerchantOffersPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Merchant Offers";

        SERIALIZED_FIELD(ContainerId, VarInt);
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        SERIALIZED_FIELD(Offers, Internal::Vector<MerchantOffer, char>);
#else
        SERIALIZED_FIELD(Offers, std::vector<MerchantOffer>);
#endif
        SERIALIZED_FIELD(VillagerLevel, VarInt);
        SERIALIZED_FIELD(VillagerXp, VarInt);
        SERIALIZED_FIELD(ShowProgress, bool);
        SERIALIZED_FIELD(CanRestock, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
