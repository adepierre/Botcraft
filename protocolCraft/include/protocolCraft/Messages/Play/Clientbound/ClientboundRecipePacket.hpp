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

        static constexpr std::string_view packet_name = "Recipe";

#if PROTOCOL_VERSION < 393 /* < 1.13 */
        DECLARE_FIELDS(
            (DiffType<RecipeState, VarInt>, RecipeBookSettings, std::vector<VarInt>, std::vector<VarInt>),
            (State,                         BookSettings,       Recipes,             ToHighlight)
        );
#else
        DECLARE_FIELDS(
            (DiffType<RecipeState, VarInt>, RecipeBookSettings, std::vector<Identifier>, std::vector<Identifier>),
            (State,                         BookSettings,       Recipes,                 ToHighlight)
        );
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
