#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/MerchantOffer.hpp"

namespace ProtocolCraft
{
    class ClientboundMerchantOffersPacket : public BaseMessage<ClientboundMerchantOffersPacket>
    {
    public:
#if   PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x26;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x2D;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Merchant Offers";

        DECLARE_FIELDS_TYPES(VarInt,      std::vector<MerchantOffer>, VarInt,        VarInt,     bool,        bool);
        DECLARE_FIELDS_NAMES(ContainerId, Offers,                     VillagerLevel, VillagerXp, ShowProgress, CanRestock);
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
