#pragma once

#if PROTOCOL_VERSION > 451
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Trade.hpp"

namespace ProtocolCraft
{
    class TradeList : public BaseMessage<TradeList>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x27;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x28;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Trade List";
        }

        void SetWindowId(const int window_id_)
        {
            window_id = window_id_;
        }

        void SetSize(const char size_)
        {
            size = size_;
        }

        void SetTrades(const std::vector<Trade>& trades_)
        {
            trades = trades_;
        }

        void SetVillagerLevel(const int villager_level_)
        {
            villager_level = villager_level_;
        }

        void SetExperience(const int experience_)
        {
            experience = experience_;
        }

        void SetIsRegularVillager(const bool is_regular_villager_)
        {
            is_regular_villager = is_regular_villager_;
        }

        void SetCanRestock(const bool can_restock_)
        {
            can_restock = can_restock_;
        }


        const int GetWindowId() const
        {
            return window_id;
        }

        const char GetSize() const
        {
            return size;
        }

        const std::vector<Trade>& GetTrades() const
        {
            return trades;
        }

        const int GetVillagerLevel() const
        {
            return villager_level;
        }

        const int GetExperience() const
        {
            return experience;
        }

        const bool GetIsRegularVillager() const
        {
            return is_regular_villager;
        }

        const bool GetCanRestock() const
        {
            return can_restock;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            window_id = ReadVarInt(iter, length);
            size = ReadData<char>(iter, length);
            trades = std::vector<Trade>(size);
            for (int i = 0; i < size; ++i)
            {
                trades[i].Read(iter, length);
            }
            villager_level = ReadVarInt(iter, length);
            experience = ReadVarInt(iter, length);
            is_regular_villager = ReadData<bool>(iter, length);
            can_restock = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(window_id, container);
            WriteData<char>(size, container);
            for (int i = 0; i < size; ++i)
            {
                trades[i].Write(container);
            }
            WriteVarInt(villager_level, container);
            WriteVarInt(experience, container);
            WriteData<bool>(is_regular_villager, container);
            WriteData<bool>(can_restock, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["window_id"] = picojson::value((double)window_id);
            object["size"] = picojson::value((double)size);
            object["trades"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["trades"].get<picojson::array>();
            for (int i = 0; i < size; ++i)
            {
                array.push_back(trades[i].Serialize());
            }
            object["villager_level"] = picojson::value((double)villager_level);
            object["experience"] = picojson::value((double)experience);
            object["is_regular_villager"] = picojson::value(is_regular_villager);
            object["can_restock"] = picojson::value(can_restock);

            return value;
        }

    private:
        int window_id;
        char size;
        std::vector<Trade> trades;
        int villager_level;
        int experience;
        bool is_regular_villager;
        bool can_restock;

    };
} //ProtocolCraft
#endif
