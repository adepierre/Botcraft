#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include <memory>
#include <optional>

namespace ProtocolCraft
{
    enum class DebugSubscriptionDataType
    {
        None = -1,
        DedicatedServerTickTime,
        Bees,
        Brains,
        Breezes,
        GoalSelectors,
        EntityPaths,
        EntityBlockIntersections,
        BeeHives,
        Pois,
        RedstoneWireOrientations,
        VillageSections,
        Raids,
        Structures,
        GameEventListeners,
        NeighborUpdates,
        GameEvents,
        NUM_DEBUG_SUBSCRIPTION_DATA_TYPES
    };

    class DebugSubscriptionData;

    class DebugSubscriptionUpdate : public NetworkType
    {
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(DataType, DebugSubscriptionDataType);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Data, std::optional<std::shared_ptr<DebugSubscriptionData>>);

        GETTER(DataType);
        GETTER(Data);

        DebugSubscriptionUpdate& SetDataType(const DebugSubscriptionDataType data_type_);
        DebugSubscriptionUpdate& SetDataTypeNoData(const DebugSubscriptionDataType data_type_);

        DECLARE_READ_WRITE_SERIALIZE;
    };

    class DebugSubscriptionEvent : public NetworkType
    {
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(DataType, DebugSubscriptionDataType);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Data, std::shared_ptr<DebugSubscriptionData>);

        GETTER(DataType);
        GETTER(Data);

        DebugSubscriptionEvent& SetDataType(const DebugSubscriptionDataType data_type_);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
