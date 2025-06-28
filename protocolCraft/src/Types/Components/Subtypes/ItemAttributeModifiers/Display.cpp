#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

#include "protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/ItemAttributeModifiersDisplay.hpp"

#include "protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/DefaultDisplay.hpp"
#include "protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/HiddenDisplay.hpp"
#include "protocolCraft/Types/Components/Subtypes/ItemAttributeModifiers/OverrideDisplay.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        DEFINE_NETWORK_TYPE(DefaultDisplay);
        DEFINE_NETWORK_TYPE(HiddenDisplay);
        DEFINE_NETWORK_TYPE(OverrideDisplay);

        ItemAttributeModifiersDisplay& ItemAttributeModifiersDisplay::SetType(const ItemAttributeModifiersDisplayType type)
        {
            if (type <= ItemAttributeModifiersDisplayType::None || type >= ItemAttributeModifiersDisplayType::NUM_DISPLAY_TYPES)
            {
                throw std::runtime_error("Unable to create ItemAttributeModifiersDisplayData with id: " + std::to_string(static_cast<int>(type)) + ".");
            }
            Type = type;

            switch (Type)
            {
            case ItemAttributeModifiersDisplayType::Default:
                Data = std::make_shared<DefaultDisplay>();
                break;
            case ItemAttributeModifiersDisplayType::Hidden:
                Data = std::make_shared<HiddenDisplay>();
                break;
            case ItemAttributeModifiersDisplayType::Override:
                Data = std::make_shared<OverrideDisplay>();
                break;
            default:
                // This should not happen
                throw std::runtime_error("Unable to create ItemAttributeModifiersDisplayData with id: " + std::to_string(static_cast<int>(Type)) + ".");
                Data = nullptr;
                break;
            }
            return *this;
        }


        void ItemAttributeModifiersDisplay::ReadImpl(ReadIterator& iter, size_t& length)
        {
            SetType(ReadData<ItemAttributeModifiersDisplayType, VarInt>(iter, length));
            if (GetData() != nullptr)
            {
                GetData()->Read(iter, length);
            }
        }

        void ItemAttributeModifiersDisplay::WriteImpl(WriteContainer& container) const
        {
            WriteData<ItemAttributeModifiersDisplayType, VarInt>(GetType(), container);
            if (GetData() != nullptr)
            {
                GetData()->Write(container);
            }
        }

        Json::Value ItemAttributeModifiersDisplay::SerializeImpl() const
        {
            Json::Value output;

            output[std::string(field_name<Type_index>)] = Type;
            output[std::string(field_name<Data_index>)] = Data == nullptr ? Json::Object() : Data->Serialize();

            return output;
        }
    }
}
#endif
