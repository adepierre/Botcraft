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
        SERIALIZED_FIELD(InputItem1, Slot);
#else
        SERIALIZED_FIELD(InputItem1, ItemCost);
#endif
        SERIALIZED_FIELD(OutputItem, Slot);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SERIALIZED_FIELD(InputItem2, std::optional<Slot>);
#else
        SERIALIZED_FIELD(InputItem2, std::optional<ItemCost>);
#endif
        SERIALIZED_FIELD(TradeDisabled, bool);
        SERIALIZED_FIELD(NumberOfTradesUses, int);
        SERIALIZED_FIELD(MaximumNumberOfTradeUses, int);
        SERIALIZED_FIELD(Xp, int);
        SERIALIZED_FIELD(SpecialPrice, int);
        SERIALIZED_FIELD(PriceMultiplier, float);
        SERIALIZED_FIELD(Demand, int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
