#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
#pragma once

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
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS_TYPES(Slot,       Slot,       std::optional<Slot>, bool,          int,                int,                      int, int,          float,           int);
        DECLARE_FIELDS_NAMES(InputItem1, OutputItem, InputItem2,          TradeDisabled, NumberOfTradesUses, MaximumNumberOfTradeUses, Xp,  SpecialPrice, PriceMultiplier, Demand);
#else
        DECLARE_FIELDS_TYPES(ItemCost,       Slot,       std::optional<ItemCost>, bool,          int,                int,                      int, int,          float,           int);
        DECLARE_FIELDS_NAMES(InputItem1,     OutputItem, InputItem2,              TradeDisabled, NumberOfTradesUses, MaximumNumberOfTradeUses, Xp,  SpecialPrice, PriceMultiplier, Demand);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(InputItem1);
        GETTER_SETTER(OutputItem);
        GETTER_SETTER(InputItem2);
        GETTER_SETTER(TradeDisabled);
        GETTER_SETTER(NumberOfTradesUses);
        GETTER_SETTER(MaximumNumberOfTradeUses);
        GETTER_SETTER(Xp);
        GETTER_SETTER(SpecialPrice);
        GETTER_SETTER(PriceMultiplier);
        GETTER_SETTER(Demand);
    };
} // ProtocolCraft
#endif
