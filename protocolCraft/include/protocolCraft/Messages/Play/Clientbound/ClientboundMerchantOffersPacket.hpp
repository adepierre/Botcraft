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

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (VarInt,      Internal::Vector<MerchantOffer, char>, VarInt,        VarInt,     bool,        bool),
            (ContainerId, Offers,                                VillagerLevel, VillagerXp, ShowProgress, CanRestock)
        );
#else
        DECLARE_FIELDS(
            (VarInt,      std::vector<MerchantOffer>, VarInt,        VarInt,     bool,        bool),
            (ContainerId, Offers,                     VillagerLevel, VillagerXp, ShowProgress, CanRestock)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(Offers);
        GETTER_SETTER(VillagerLevel);
        GETTER_SETTER(VillagerXp);
        GETTER_SETTER(ShowProgress);
        GETTER_SETTER(CanRestock);
    };
} //ProtocolCraft
#endif
