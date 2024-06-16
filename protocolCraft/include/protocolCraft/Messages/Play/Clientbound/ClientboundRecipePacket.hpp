#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Recipes/RecipeBookSettings.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    enum class RecipeState
    {
        Init = 0,
        Add = 1,
        Remove = 2
    };

    class ClientboundRecipePacket : public BaseMessage<ClientboundRecipePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x31;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x36;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x36;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x3F;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x41;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Recipe";

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS_TYPES(DiffType<RecipeState, VarInt>, RecipeBookSettings, std::vector<VarInt>, std::vector<VarInt>);
        DECLARE_FIELDS_NAMES(State,                         BookSettings,       Recipes,             ToHighlight);
#else
        DECLARE_FIELDS_TYPES(DiffType<RecipeState, VarInt>, RecipeBookSettings, std::vector<Identifier>, std::vector<Identifier>);
        DECLARE_FIELDS_NAMES(State,                         BookSettings,       Recipes,                 ToHighlight);
#endif

        GETTER_SETTER(State);
        GETTER_SETTER(BookSettings);
        GETTER_SETTER(Recipes);
        GETTER_SETTER(ToHighlight);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetState(ReadData<RecipeState, VarInt>(iter, length));
            SetBookSettings(ReadData<RecipeBookSettings>(iter, length));
            SetRecipes(ReadData<std::tuple_element_t<static_cast<size_t>(FieldsEnum::Recipes), typename Internal::SerializedType<FieldsTuple>::serialization_type>>(iter, length));

            if (GetState() == RecipeState::Init)
            {
                SetToHighlight(ReadData<std::tuple_element_t<static_cast<size_t>(FieldsEnum::ToHighlight), typename Internal::SerializedType<FieldsTuple>::serialization_type>>(iter, length));
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<RecipeState, VarInt>(GetState(), container);
            WriteData<RecipeBookSettings>(GetBookSettings(), container);

            WriteData<std::tuple_element_t<static_cast<size_t>(FieldsEnum::Recipes), typename Internal::SerializedType<FieldsTuple>::serialization_type>>(GetRecipes(), container);

            if (GetState() == RecipeState::Init)
            {
                WriteData<std::tuple_element_t<static_cast<size_t>(FieldsEnum::ToHighlight), typename Internal::SerializedType<FieldsTuple>::serialization_type>>(GetToHighlight(), container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::State)])] = GetState();
            output[std::string(json_names[static_cast<size_t>(FieldsEnum::Recipes)])] = GetRecipes();

            if (GetState() == RecipeState::Init)
            {
                output[std::string(json_names[static_cast<size_t>(FieldsEnum::ToHighlight)])] = GetToHighlight();
            }

            output[std::string(json_names[static_cast<size_t>(FieldsEnum::BookSettings)])] = GetBookSettings();

            return output;
        }
    };
} //ProtocolCraft
