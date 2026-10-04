#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Utilities/DynamicType.hpp"

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
    private:
        static std::shared_ptr<DebugSubscriptionData> CreateDebugSubscriptionData(const DebugSubscriptionDataType type);

        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Type, Internal::DiffType<DebugSubscriptionDataType, VarInt>);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Data, std::optional<std::shared_ptr<DebugSubscriptionData>>);

        GETTER(Type);
        GETTER(Data);

        DYNAMIC_TYPE_SETTER(Type, Data, DebugSubscriptionUpdate::CreateDebugSubscriptionData);
        // Special case to set the type and set the data to empty std::optional
        DebugSubscriptionUpdate& SetDataTypeNoData(const DebugSubscriptionDataType type);

        DECLARE_READ_WRITE_SERIALIZE;
    };

    class DebugSubscriptionEvent : public NetworkType
    {
    private:
        static std::shared_ptr<DebugSubscriptionData> CreateDebugSubscriptionData(const DebugSubscriptionDataType type);

        SERIALIZED_DYNAMIC_FIELD(DebugSubscriptionEvent, Type, Data, DebugSubscriptionData, DebugSubscriptionEvent::CreateDebugSubscriptionData, Internal::DiffType<DebugSubscriptionDataType, VarInt>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
