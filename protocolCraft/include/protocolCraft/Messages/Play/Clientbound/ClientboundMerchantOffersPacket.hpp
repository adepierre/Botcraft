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

        DECLARE_FIELDS(
            (VarInt,      std::vector<MerchantOffer>, VarInt,        VarInt,     bool,        bool),
            (ContainerId, Offers,                     VillagerLevel, VillagerXp, ShowProgress, CanRestock)
        );
        DECLARE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(Offers);
        GETTER_SETTER(VillagerLevel);
        GETTER_SETTER(VillagerXp);
        GETTER_SETTER(ShowProgress);
        GETTER_SETTER(CanRestock);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetContainerId(ReadData<VarInt>(iter, length));
#if PROTOCOL_VERSION < 759 /* < 1.19 */
            // Special case, the size is a char instead of a varint
            SetOffers(ReadVector<MerchantOffer, char>(iter, length, ReadData<MerchantOffer>));
#else
            SetOffers(ReadData<std::vector<MerchantOffer>>(iter, length));
#endif
            SetVillagerLevel(ReadData<VarInt>(iter, length));
            SetVillagerXp(ReadData<VarInt>(iter, length));
            SetShowProgress(ReadData<bool>(iter, length));
            SetCanRestock(ReadData<bool>(iter, length));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetContainerId(), container);
#if PROTOCOL_VERSION < 759 /* < 1.19 */
            // Special case, the size is a char instead of a varint
            WriteVector<MerchantOffer, char>(GetOffers(), container, WriteData<MerchantOffer>);
#else
            WriteData<std::vector<MerchantOffer>>(GetOffers(), container);
#endif
            WriteData<VarInt>(GetVillagerLevel(), container);
            WriteData<VarInt>(GetVillagerXp(), container);
            WriteData<bool>(GetShowProgress(), container);
            WriteData<bool>(GetCanRestock(), container);
        }
    };
} //ProtocolCraft
#endif
