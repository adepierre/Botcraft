#pragma once

#if PROTOCOL_VERSION > 451 /* > 1.13.2 */

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Item/ItemCost.hpp"
#endif

#include <optional>

namespace ProtocolCraft
{
    class MerchantOffer : public NetworkType
    {
    public:
        virtual ~MerchantOffer() override
        {

        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        void SetInputItem1(const Slot& input_item_1_)
        {
            input_item_1 = input_item_1_;
        }
#else
        void SetInputItem1(const ItemCost& input_item_1_)
        {
            input_item_1 = input_item_1_;
        }
#endif

        void SetOutputItem(const Slot& output_item_)
        {
            output_item = output_item_;
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        void SetInputItem2(const std::optional<Slot>& input_item_2_)
        {
            input_item_2 = input_item_2_;
        }
#else
        void SetInputItem2(const std::optional<ItemCost>& input_item_2_)
        {
            input_item_2 = input_item_2_;
        }
#endif

        void SetTradeDisabled(const bool trade_disabled_)
        {
            trade_disabled = trade_disabled_;
        }

        void SetNumberOfTradesUses(const int number_of_trades_uses_)
        {
            number_of_trades_uses = number_of_trades_uses_;
        }

        void SetMaximumNumberOfTradeUses(const int maximum_number_of_trade_uses_)
        {
            maximum_number_of_trade_uses = maximum_number_of_trade_uses_;
        }

        void SetXp(const int xp_)
        {
            xp = xp_;
        }

        void SetSpecialPrice(const int special_price_)
        {
            special_price = special_price_;
        }

        void SetPriceMultiplier(const float price_multiplier_)
        {
            price_multiplier = price_multiplier_;
        }

        void SetDemand(const int demand_)
        {
            demand = demand_;
        }


#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        const Slot& GetInputItem1() const
        {
            return input_item_1;
        }
#else
        const ItemCost& GetInputItem1() const
        {
            return input_item_1;
        }
#endif

        const Slot& GetOutputItem() const
        {
            return output_item;
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        const std::optional<Slot>& GetInputItem2() const
        {
            return input_item_2;
        }
#else
        const std::optional<ItemCost>& GetInputItem2() const
        {
            return input_item_2;
        }
#endif

        bool GetTradeDisabled() const
        {
            return trade_disabled;
        }

        int GetNumberOfTradesUses() const
        {
            return number_of_trades_uses;
        }

        int GetMaximumNumberOfTradeUses() const
        {
            return maximum_number_of_trade_uses;
        }

        int GetXp() const
        {
            return xp;
        }

        int GetSpecialPrice() const
        {
            return special_price;
        }

        float GetPriceMultiplier() const
        {
            return price_multiplier;
        }

        int GetDemand() const
        {
            return demand;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            input_item_1 = ReadData<Slot>(iter, length);
#else
            input_item_1 = ReadData<ItemCost>(iter, length);
#endif
            output_item = ReadData<Slot>(iter, length);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            input_item_2 = ReadOptional<Slot>(iter, length);
#else
            input_item_2 = ReadOptional<ItemCost>(iter, length);
#endif
            trade_disabled = ReadData<bool>(iter, length);
            number_of_trades_uses = ReadData<int>(iter, length);
            maximum_number_of_trade_uses = ReadData<int>(iter, length);
            xp = ReadData<int>(iter, length);
            special_price = ReadData<int>(iter, length);
            price_multiplier = ReadData<float>(iter, length);
            demand = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            WriteData<Slot>(input_item_1, container);
#else
            WriteData<ItemCost>(input_item_1, container);
#endif
            WriteData<Slot>(output_item, container);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            WriteOptional<Slot>(input_item_2, container);
#else
            WriteOptional<ItemCost>(input_item_2, container);
#endif
            WriteData<bool>(trade_disabled, container);
            WriteData<int>(number_of_trades_uses, container);
            WriteData<int>(maximum_number_of_trade_uses, container);
            WriteData<int>(xp, container);
            WriteData<int>(special_price, container);
            WriteData<float>(price_multiplier, container);
            WriteData<int>(demand, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["input_item_1"] = input_item_1;
            output["output_item"] = output_item;
            if (input_item_2.has_value())
            {
                output["input_item_2"] = input_item_2.value();
            }
            output["trade_disabled"] = trade_disabled;
            output["number_of_trades_uses"] = number_of_trades_uses;
            output["maximum_number_of_trade_uses"] = maximum_number_of_trade_uses;
            output["xp"] = xp;
            output["special_price"] = special_price;
            output["price_multiplier"] = price_multiplier;
            output["demand"] = demand;

            return output;
        }

    private:
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        Slot input_item_1;
#else
        ItemCost input_item_1;
#endif
        Slot output_item;
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        std::optional<Slot> input_item_2;
#else
        std::optional<ItemCost> input_item_2;
#endif
        bool trade_disabled = false;
        int number_of_trades_uses = 0;
        int maximum_number_of_trade_uses = 0;
        int xp = 0;
        int special_price = 0;
        float price_multiplier = 0.0f;
        int demand = 0;
    };
} // ProtocolCraft
#endif
