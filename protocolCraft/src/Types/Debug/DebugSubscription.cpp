#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "protocolCraft/Types/Debug/DebugSubscription.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionData.hpp"
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

#include "protocolCraft/Types/Debug/DebugSubscriptionDataBeeInfo.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataBrainDump.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataBreezeInfo.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataEmpty.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataEntityBlockIntersection.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataGameEventInfo.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataGameEventListenerInfo.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataGoalInfo.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataHiveInfo.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataNeighbor.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataOrientation.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataPathInfo.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataPoiInfo.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataRaids.hpp"
#include "protocolCraft/Types/Debug/DebugSubscriptionDataStructures.hpp"

namespace ProtocolCraft
{
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataBeeInfo);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataBrainDump);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataBreezeInfo);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataEmpty);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataEntityBlockIntersection);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataGameEventInfo);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataGameEventListenerInfo);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataGoalInfo);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataHiveInfo);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataNeighbor);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataOrientation);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataPathInfo);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataPoiInfo);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataRaids);
    DEFINE_NETWORK_TYPE(DebugSubscriptionDataStructures);

    // Subtypes
    DEFINE_NETWORK_TYPE(BoundingBox);
    DEFINE_NETWORK_TYPE(DebugGoal);
    DEFINE_NETWORK_TYPE(DebugStructureInfo);
    DEFINE_NETWORK_TYPE(DebugStructureInfoPiece);
    DEFINE_NETWORK_TYPE(Node);
    DEFINE_NETWORK_TYPE(Path);
    DEFINE_NETWORK_TYPE(PathDebugData);

    namespace
    {
        std::shared_ptr<DebugSubscriptionData> DebugSubscriptionDataFactory(const DebugSubscriptionDataType debug_subscription_data_type_)
        {
            if (debug_subscription_data_type_ <= DebugSubscriptionDataType::None || debug_subscription_data_type_ >= DebugSubscriptionDataType::NUM_DEBUG_SUBSCRIPTION_DATA_TYPES)
            {
                throw std::runtime_error("Unable to create debug subscription data with id: " + std::to_string(static_cast<int>(debug_subscription_data_type_)) + ".");
            }

            switch (debug_subscription_data_type_)
            {
            case DebugSubscriptionDataType::DedicatedServerTickTime:
                return std::make_shared<DebugSubscriptionDataEmpty>();
            case DebugSubscriptionDataType::Bees:
                return std::make_shared<DebugSubscriptionDataBeeInfo>();
            case DebugSubscriptionDataType::Brains:
                return std::make_shared<DebugSubscriptionDataBrainDump>();
            case DebugSubscriptionDataType::Breezes:
                return std::make_shared<DebugSubscriptionDataBreezeInfo>();
            case DebugSubscriptionDataType::GoalSelectors:
                return std::make_shared<DebugSubscriptionDataGoalInfo>();
            case DebugSubscriptionDataType::EntityPaths:
                return std::make_shared<DebugSubscriptionDataPathInfo>();
            case DebugSubscriptionDataType::EntityBlockIntersections:
                return std::make_shared<DebugSubscriptionDataEntityBlockIntersection>();
            case DebugSubscriptionDataType::BeeHives:
                return std::make_shared<DebugSubscriptionDataHiveInfo>();
            case DebugSubscriptionDataType::Pois:
                return std::make_shared<DebugSubscriptionDataPoiInfo>();
            case DebugSubscriptionDataType::RedstoneWireOrientations:
                return std::make_shared<DebugSubscriptionDataOrientation>();
            case DebugSubscriptionDataType::VillageSections:
                return std::make_shared<DebugSubscriptionDataEmpty>();
            case DebugSubscriptionDataType::Raids:
                return std::make_shared<DebugSubscriptionDataRaids>();
            case DebugSubscriptionDataType::Structures:
                return std::make_shared<DebugSubscriptionDataStructures>();
            case DebugSubscriptionDataType::GameEventListeners:
                return std::make_shared<DebugSubscriptionDataGameEventListenerInfo>();
            case DebugSubscriptionDataType::NeighborUpdates:
                return std::make_shared<DebugSubscriptionDataNeighbor>();
            case DebugSubscriptionDataType::GameEvents:
                return std::make_shared<DebugSubscriptionDataGameEventInfo>();
            default:
                // Should never happen
                throw std::runtime_error("Unable to create debug subscription data with id: " + std::to_string(static_cast<int>(debug_subscription_data_type_)) + ".");
                break;
            }

            // Should never happen
            throw std::runtime_error("Unable to create debug subscription data with id: " + std::to_string(static_cast<int>(debug_subscription_data_type_)) + ".");
            return nullptr;
        }
    }

    DebugSubscriptionUpdate& DebugSubscriptionUpdate::SetDataType(const DebugSubscriptionDataType data_type_)
    {
        DataType = data_type_;
        Data = DebugSubscriptionDataFactory(DataType);

        return *this;
    }

    DebugSubscriptionUpdate& DebugSubscriptionUpdate::SetDataTypeNoData(const DebugSubscriptionDataType data_type_)
    {
        DataType = data_type_;
        Data = std::nullopt;

        return *this;
    }

    void DebugSubscriptionUpdate::ReadImpl(ReadIterator& iter, size_t& length)
    {
        DataType = ReadData<DebugSubscriptionDataType, VarInt>(iter, length);
        const bool has_data = ReadData<bool>(iter, length);
        if (has_data)
        {
            Data = DebugSubscriptionDataFactory(DataType);
            Data.value()->Read(iter, length);
        }
    }

    void DebugSubscriptionUpdate::WriteImpl(WriteContainer& container) const
    {
        WriteData<DebugSubscriptionDataType, VarInt>(DataType, container);
        WriteData<bool>(Data.has_value(), container);
        if (Data.has_value() && Data.value() != nullptr)
        {
            Data.value()->Write(container);
        }
    }

    Json::Value DebugSubscriptionUpdate::SerializeImpl() const
    {
        Json::Value output;

        output[std::string(field_name<DataType_index>)] = static_cast<int>(DataType);
        if (Data.has_value())
        {
            output[std::string(field_name<Data_index>)] = Data == nullptr ? Json::Object() : Data.value()->Serialize();
        }

        return output;
    }


    DebugSubscriptionEvent& DebugSubscriptionEvent::SetDataType(const DebugSubscriptionDataType data_type_)
    {
        DataType = data_type_;
        Data = DebugSubscriptionDataFactory(DataType);

        return *this;
    }

    void DebugSubscriptionEvent::ReadImpl(ReadIterator& iter, size_t& length)
    {
        DataType = ReadData<DebugSubscriptionDataType, VarInt>(iter, length);
        Data = DebugSubscriptionDataFactory(DataType);
        if (Data != nullptr)
        {
            Data->Read(iter, length);
        }
    }

    void DebugSubscriptionEvent::WriteImpl(WriteContainer& container) const
    {
        WriteData<DebugSubscriptionDataType, VarInt>(DataType, container);
        if (Data != nullptr)
        {
            Data->Write(container);
        }
    }

    Json::Value DebugSubscriptionEvent::SerializeImpl() const
    {
        Json::Value output;

        output[std::string(field_name<DataType_index>)] = static_cast<int>(DataType);
        output[std::string(field_name<Data_index>)] = Data == nullptr ? Json::Object() : Data->Serialize();

        return output;
    }
}
#endif
