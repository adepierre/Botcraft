#pragma once

#include "protocolCraft/NetworkType.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Utilities/CustomType.hpp"

#include <map>
#endif

namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    enum class RecipeBookType
    {
        Crafting,
        Furnace,
        BlastFurnace,
        Smoker,
        NUM_RECIPEBOOKTYPE
    };
#endif

    class RecipeBookSettings : public NetworkType
    {
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    public:
        struct TypeSettings
        {
            bool open = false;
            bool filtering = false;
        };
    private:
        using THIS = RecipeBookSettings;

        std::map<RecipeBookType, TypeSettings> ReadStates(ReadIterator& iter, size_t& length) const
        {
            std::map<RecipeBookType, TypeSettings> output;

            for (int i = 0; i < static_cast<int>(RecipeBookType::NUM_RECIPEBOOKTYPE); ++i)
            {
                const bool b1 = ReadData<bool>(iter, length);
                const bool b2 = ReadData<bool>(iter, length);
                if (b1 || b2)
                {
                    output[static_cast<RecipeBookType>(i)] = TypeSettings{ b1, b2 };
                }
            }

            return output;
    }

        void WriteStates(const std::map<RecipeBookType, TypeSettings>& states, WriteContainer& container) const
        {
            for (int i = 0; i < static_cast<int>(RecipeBookType::NUM_RECIPEBOOKTYPE); ++i)
            {
                TypeSettings written_values;
                if (auto it = states.find(static_cast<RecipeBookType>(i)); it != states.end())
                {
                    written_values = it->second;
                }
                WriteData<bool>(written_values.open, container);
                WriteData<bool>(written_values.filtering, container);
            }
        }

        std::optional<Json::Value> SerializeStates(const std::map<RecipeBookType, TypeSettings>& states) const
        {
            Json::Value output;

            for (const auto& [k, v] : states)
            {
                output[std::to_string(static_cast<int>(k))] = {
                    { "open", v.open },
                    { "filtering", v.filtering }
                };
            }

            return output;
        }
#endif

#if PROTOCOL_VERSION < 768 /* < 1.21.2*/
        SERIALIZED_FIELD(IsGuiOpen, bool);
        SERIALIZED_FIELD(IsFilteringCraftable, bool);
#endif
#if PROTOCOL_VERSION > 356 /* > 1.12.2 */ && PROTOCOL_VERSION < 768 /* < 1.21.2*/
        SERIALIZED_FIELD(IsFurnaceGuiOpen, bool);
        SERIALIZED_FIELD(IsFurnaceFilteringOpen, bool);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */ && PROTOCOL_VERSION < 768 /* < 1.21.2*/
        SERIALIZED_FIELD(IsBlastingFurnaceGuiOpen, bool);
        SERIALIZED_FIELD(IsBlastingFurnaceFilteringCraftable, bool);
        SERIALIZED_FIELD(IsSmokerGuiOpen, bool);
        SERIALIZED_FIELD(IsSmokerFilteringCraftable, bool);
#endif

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        SERIALIZED_FIELD(States, Internal::CustomType<std::map<RecipeBookType, TypeSettings>, &THIS::ReadStates, &THIS::WriteStates, &THIS::SerializeStates>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
