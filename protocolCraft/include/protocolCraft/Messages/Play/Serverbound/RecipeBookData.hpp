#pragma once

#if PROTOCOL_VERSION < 737
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    enum class RecipeBookDataType
    {
        DisplayedRecipe = 0,
        RecipeBookStates = 1
    };

    // Was Crafting Book Data in 1.12.2
    class RecipeBookData : public BaseMessage<RecipeBookData>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x17;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x1B;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x1D;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x1D;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x1E;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Recipe Book Data";
        }

        void SetType(const int type_)
        {
            type = type_;
        }

#if PROTOCOL_VERSION > 375
        void SetRecipeId(const Identifier& recipe_id_)
#else
        void SetRecipeId(const int recipe_id_)
#endif
        {
            recipe_id = recipe_id_;
        }

        void SetCraftingRecipeBookOpen(const bool crafting_recipe_book_open_)
        {
            crafting_recipe_book_open = crafting_recipe_book_open_;
        }

        void SetCraftingRecipeFilterActive(const bool crafting_recipe_filter_active_)
        {
            crafting_recipe_filter_active = crafting_recipe_filter_active_;
        }

#if PROTOCOL_VERSION > 358
        void SetSmeltingRecipeBookOpen(const bool smelting_recipe_book_open_)
        {
            smelting_recipe_book_open = smelting_recipe_book_open_;
        }

        void SetSmeltingRecipeFilterActive(const bool smelting_recipe_filter_active_)
        {
            smelting_recipe_filter_active = smelting_recipe_filter_active_;
        }
#endif

#if PROTOCOL_VERSION > 450
        void SetBlastingRecipeBookOpen(const bool blasting_recipe_book_open_)
        {
            blasting_recipe_book_open = blasting_recipe_book_open_;
        }

        void SetBlastingRecipeFilterActive(const bool blasting_recipe_filter_active_)
        {
            blasting_recipe_filter_active = blasting_recipe_filter_active_;
        }

        void SetSmokingRecipeBookOpen(const bool smoking_recipe_book_open_)
        {
            smoking_recipe_book_open = smoking_recipe_book_open_;
        }

        void SetSmokingRecipeFilterActive(const bool smoking_recipe_filter_active_)
        {
            smoking_recipe_filter_active = smoking_recipe_filter_active_;
        }
#endif

        const int GetType() const
        {
            return type;
        }

#if PROTOCOL_VERSION > 375
        const Identifier& GetRecipeId() const
#else
        const int GetRecipeId() const
#endif
        {
            return recipe_id;
        }

        const bool GetCraftingRecipeBookOpen() const
        {
            return crafting_recipe_book_open;
        }

        const bool GetCraftingRecipeFilterActive() const
        {
            return crafting_recipe_filter_active;
        }

#if PROTOCOL_VERSION > 358
        const bool GetSmeltingRecipeBookOpen() const
        {
            return smelting_recipe_book_open;
        }

        const bool GetSmeltingRecipeFilterActive() const
        {
            return smelting_recipe_filter_active;
        }
#endif

#if PROTOCOL_VERSION > 450
        const bool GetBlastingRecipeBookOpen() const
        {
            return blasting_recipe_book_open;
        }

        const bool GetBlastingRecipeFilterActive() const
        {
            return blasting_recipe_filter_active;
        }

        const bool GetSmokingRecipeBookOpen() const
        {
            return smoking_recipe_book_open;
        }

        const bool GetSmokingRecipeFilterActive() const
        {
            return smoking_recipe_filter_active;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            type = ReadVarInt(iter, length);
            switch ((RecipeBookDataType)type)
            {
            case RecipeBookDataType::DisplayedRecipe:
#if PROTOCOL_VERSION > 375
                recipe_id = ReadString(iter, length);
#else
                recipe_id = ReadVarInt(iter, length);
#endif
                break;
            case RecipeBookDataType::RecipeBookStates:
                crafting_recipe_book_open = ReadData<bool>(iter, length);
                crafting_recipe_filter_active = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 358
                smelting_recipe_book_open = ReadData<bool>(iter, length);
                smelting_recipe_filter_active = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 450
                blasting_recipe_book_open = ReadData<bool>(iter, length);
                blasting_recipe_filter_active = ReadData<bool>(iter, length);
                smoking_recipe_book_open = ReadData<bool>(iter, length);
                smoking_recipe_filter_active = ReadData<bool>(iter, length);
#endif
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(type, container);
            switch ((RecipeBookDataType)type)
            {
            case RecipeBookDataType::DisplayedRecipe:
#if PROTOCOL_VERSION > 375
                WriteString(recipe_id, container);
#else
                WriteVarInt(recipe_id, container);
#endif
                break;
            case RecipeBookDataType::RecipeBookStates:
                WriteData<bool>(crafting_recipe_book_open, container);
                WriteData<bool>(crafting_recipe_filter_active, container);
#if PROTOCOL_VERSION > 358
                WriteData<bool>(smelting_recipe_book_open, container);
                WriteData<bool>(smelting_recipe_filter_active, container);
#endif
#if PROTOCOL_VERSION > 450
                WriteData<bool>(blasting_recipe_book_open, container);
                WriteData<bool>(blasting_recipe_filter_active, container);
                WriteData<bool>(smoking_recipe_book_open, container);
                WriteData<bool>(smoking_recipe_filter_active, container);
#endif
                break;
            default:
                break;
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["type"] = picojson::value((double)type);
            switch ((RecipeBookDataType)type)
            {
            case RecipeBookDataType::DisplayedRecipe:
#if PROTOCOL_VERSION > 375
                object["recipe_id"] = picojson::value(recipe_id);
#else
                object["recipe_id"] = picojson::value((double)recipe_id);
#endif
                break;
            case RecipeBookDataType::RecipeBookStates:
                object["crafting_recipe_book_open"] = picojson::value(crafting_recipe_book_open);
                object["crafting_recipe_filter_active"] = picojson::value(crafting_recipe_filter_active);
#if PROTOCOL_VERSION > 358
                object["smelting_recipe_book_open"] = picojson::value(smelting_recipe_book_open);
                object["smelting_recipe_filter_active"] = picojson::value(smelting_recipe_filter_active);
#endif
#if PROTOCOL_VERSION > 450
                object["blasting_recipe_book_open"] = picojson::value(blasting_recipe_book_open);
                object["blasting_recipe_filter_active"] = picojson::value(blasting_recipe_filter_active);
                object["smoking_recipe_book_open"] = picojson::value(smoking_recipe_book_open);
                object["smoking_recipe_filter_active"] = picojson::value(smoking_recipe_filter_active);
#endif
                break;
            default:
                break;
            }

            return value;
        }

    private:
        int type;
#if PROTOCOL_VERSION > 375
        Identifier recipe_id;
#else
        int recipe_id;
#endif
        bool crafting_recipe_book_open;
        bool crafting_recipe_filter_active;
#if PROTOCOL_VERSION > 358
        bool smelting_recipe_book_open;
        bool smelting_recipe_filter_active;
#endif
#if PROTOCOL_VERSION > 450
        bool blasting_recipe_book_open;
        bool blasting_recipe_filter_active;
        bool smoking_recipe_book_open;
        bool smoking_recipe_filter_active;
#endif

    };
} //ProtocolCraft
#endif