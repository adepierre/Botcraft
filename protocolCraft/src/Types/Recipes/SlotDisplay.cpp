#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Recipes/SlotDisplay.hpp"

#include "protocolCraft/Types/Recipes/CompositeSlotDisplay.hpp"
#include "protocolCraft/Types/Recipes/ItemSlotDisplay.hpp"
#include "protocolCraft/Types/Recipes/ItemStackSlotDisplay.hpp"
#include "protocolCraft/Types/Recipes/SlotDisplayDataEmpty.hpp"
#include "protocolCraft/Types/Recipes/SmithingTrimDemoSlotDisplay.hpp"
#include "protocolCraft/Types/Recipes/TagSlotDisplay.hpp"
#include "protocolCraft/Types/Recipes/WithRemainderSlotDisplay.hpp"

#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

namespace ProtocolCraft
{
    DEFINE_NETWORK_TYPE(CompositeSlotDisplay);
    DEFINE_NETWORK_TYPE(ItemSlotDisplay);
    DEFINE_NETWORK_TYPE(ItemStackSlotDisplay);
    DEFINE_NETWORK_TYPE(SlotDisplayDataEmpty);
    DEFINE_NETWORK_TYPE(SmithingTrimDemoSlotDisplay);
    DEFINE_NETWORK_TYPE(TagSlotDisplay);
    DEFINE_NETWORK_TYPE(WithRemainderSlotDisplay);

    SlotDisplay& SlotDisplay::SetType(const SlotDisplaysDataType type)
    {
        if (type <= SlotDisplaysDataType::None || type >= SlotDisplaysDataType::NUM_SLOT_DISPLAYS_DATA_TYPES)
        {
            throw std::runtime_error("Unable to create SlotDisplaysData with id: " + std::to_string(static_cast<int>(type)) + ".");
        }
        Type = type;

        switch (Type)
        {
        case SlotDisplaysDataType::Empty:
        case SlotDisplaysDataType::AnyFuel:
            Data = std::make_shared<SlotDisplayDataEmpty>();
            break;
        case SlotDisplaysDataType::Item:
            Data = std::make_shared<ItemSlotDisplay>();
            break;
        case SlotDisplaysDataType::ItemStack:
            Data = std::make_shared<ItemStackSlotDisplay>();
            break;
        case SlotDisplaysDataType::Tag:
            Data = std::make_shared<TagSlotDisplay>();
            break;
        case SlotDisplaysDataType::SmithingTrim:
            Data = std::make_shared<SmithingTrimDemoSlotDisplay>();
            break;
        case SlotDisplaysDataType::WithRemainder:
            Data = std::make_shared<WithRemainderSlotDisplay>();
            break;
        case SlotDisplaysDataType::Composite:
            Data = std::make_shared<CompositeSlotDisplay>();
            break;
        default:
            // This should not happen
            throw std::runtime_error("Unable to create SlotDisplaysData with id: " + std::to_string(static_cast<int>(Type)) + ".");
            Data = nullptr;
            break;
        }
        return *this;
    }


    void SlotDisplay::ReadImpl(ReadIterator& iter, size_t& length)
    {
        SetType(ReadData<SlotDisplaysDataType, VarInt>(iter, length));
        if (GetData() != nullptr)
        {
            GetData()->Read(iter, length);
        }
    }

    void SlotDisplay::WriteImpl(WriteContainer& container) const
    {
        WriteData<SlotDisplaysDataType, VarInt>(GetType(), container);
        if (GetData() != nullptr)
        {
            GetData()->Write(container);
        }
    }

    Json::Value SlotDisplay::SerializeImpl() const
    {
        Json::Value output;

        output[std::string(field_name<Type_index>)] = GetType();
        output[std::string(field_name<Data_index>)] = GetData() == nullptr ? Json::Object() : GetData()->Serialize();

        return output;
    }
}
#endif
