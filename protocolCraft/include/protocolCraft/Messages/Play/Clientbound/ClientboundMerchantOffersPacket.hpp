#pragma once

#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Trade.hpp"

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
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3 */
        static constexpr int packet_id = 0x2B;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Merchant Offers";

        virtual ~ClientboundMerchantOffersPacket() override
        {

        }

        void SetContainerId(const int container_id_)
        {
            container_id = container_id_;
        }

        void SetOffers(const std::vector<Trade>& offers_)
        {
            offers = offers_;
        }

        void SetVillagerLevel(const int villager_level_)
        {
            villager_level = villager_level_;
        }

        void SetVillagerXp(const int villager_xp_)
        {
            villager_xp = villager_xp_;
        }

        void SetShowProgress(const bool show_progress_)
        {
            show_progress = show_progress_;
        }

        void SetCanRestock(const bool can_restock_)
        {
            can_restock = can_restock_;
        }


        int GetContainerId() const
        {
            return container_id;
        }

        const std::vector<Trade>& GetOffers() const
        {
            return offers;
        }

        int GetVillagerLevel() const
        {
            return villager_level;
        }

        int GetVillagerXp() const
        {
            return villager_xp;
        }

        bool GetShowProgress() const
        {
            return show_progress;
        }

        bool GetCanRestock() const
        {
            return can_restock;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            container_id = ReadData<VarInt>(iter, length);
            offers = ReadVector<Trade, char>(iter, length);
            villager_level = ReadData<VarInt>(iter, length);
            villager_xp = ReadData<VarInt>(iter, length);
            show_progress = ReadData<bool>(iter, length);
            can_restock = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(container_id, container);
            WriteVector<Trade, char>(offers, container);
            WriteData<VarInt>(villager_level, container);
            WriteData<VarInt>(villager_xp, container);
            WriteData<bool>(show_progress, container);
            WriteData<bool>(can_restock, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;
            output["offers"] = offers;
            output["villager_level"] = villager_level;
            output["villager_xp"] = villager_xp;
            output["show_progress"] = show_progress;
            output["can_restock"] = can_restock;

            return output;
        }

    private:
        int container_id = 0;
        std::vector<Trade> offers;
        int villager_level = 0;
        int villager_xp = 0;
        bool show_progress = false;
        bool can_restock = false;

    };
} //ProtocolCraft
#endif
