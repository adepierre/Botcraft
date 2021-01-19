#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    enum class UnlockRecipesAction
    {
        Init = 0,
        Add = 1,
        Remove = 2
    };

    class UnlockRecipes : public BaseMessage<UnlockRecipes>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x31;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x34;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x36;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x37;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x36;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x35;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Unlock Recipes";
        }

        void SetAction(const int action_)
        {
            action = action_;
        }

        void SetCraftingBookOpen(const bool crafting_book_open_)
        {
            crafting_book_open = crafting_book_open_;
        }

        void SetCraftingRecipeBookFilterActive(const bool crafting_recipe_book_filter_active_)
        {
            crafting_recipe_book_filter_active = crafting_recipe_book_filter_active_;
        }

#if PROTOCOL_VERSION > 356
        void SetSmeltingRecipeBookOpen(const bool smelting_recipe_book_open_)
        {
            smelting_recipe_book_open = smelting_recipe_book_open_;
        }

        void SetSmeltingRecipeBookFilterActive(const bool smelting_recipe_book_filter_active_)
        {
            smelting_recipe_book_filter_active = smelting_recipe_book_filter_active_;
        }
#endif

#if PROTOCOL_VERSION > 736
        void SetBlastFurnaceRecipeBookOpen(const bool smelting_recipe_book_open_)
        {
            blast_furnace_recipe_book_open = smelting_recipe_book_open_;
        }

        void SetBlastFurnaceRecipeBookFilterActive(const bool smelting_recipe_book_filter_active_)
        {
            blast_furnace_recipe_book_filter_active = smelting_recipe_book_filter_active_;
        }

        void SetSmokerRecipeBookOpen(const bool smelting_recipe_book_open_)
        {
            smoker_recipe_book_open = smelting_recipe_book_open_;
        }

        void SetSmokerRecipeBookFilterActive(const bool smelting_recipe_book_filter_active_)
        {
            smoker_recipe_book_filter_active = smelting_recipe_book_filter_active_;
        }
#endif

        void SetArraySize1(const int array_size_1_)
        {
            array_size_1 = array_size_1_;
        }

#if PROTOCOL_VERSION > 348
        void SetRecipeIds1(const std::vector<Identifier>& recipe_ids_1_)
#else
        void SetRecipeIds1(const std::vector<int>& recipe_ids_1_)
#endif
        {
            recipe_ids_1 = recipe_ids_1_;
        }

        void SetArraySize2(const int array_size_2_)
        {
            array_size_2 = array_size_2_;
        }

#if PROTOCOL_VERSION > 348
        void SetRecipeIds2(const std::vector<Identifier>& recipe_ids_2_)
#else
        void SetRecipeIds2(const std::vector<int>& recipe_ids_2_)
#endif
        {
            recipe_ids_2 = recipe_ids_2_;
        }


        const int GetAction() const
        {
            return action;
        }

        const bool GetCraftingBookOpen() const
        {
            return crafting_book_open;
        }

        const bool GetCraftingRecipeBookFilterActive() const
        {
            return crafting_recipe_book_filter_active;
        }

#if PROTOCOL_VERSION > 356
        const bool GetSmeltingRecipeBookOpen() const
        {
            return smelting_recipe_book_open;
        }

        const bool GetSmeltingRecipeBookFilterActive() const
        {
            return smelting_recipe_book_filter_active;
        }
#endif

#if PROTOCOL_VERSION > 736
        const bool GetBlastFurnaceRecipeBookOpen() const
        {
            return blast_furnace_recipe_book_open;
        }

        const bool GetBlastFurnaceRecipeBookFilterActive() const
        {
            return blast_furnace_recipe_book_filter_active;
        }

        const bool GetSmokerRecipeBookOpen() const
        {
            return smelting_recipe_book_open;
        }

        const bool GetSmokerFurnaceRecipeBookFilterActive() const
        {
            return smoker_recipe_book_filter_active;
        }
#endif

        const int GetArraySize1() const
        {
            return array_size_1;
        }

#if PROTOCOL_VERSION > 348
        const std::vector<Identifier>& GetRecipeIds1() const
#else
        const std::vector<int>& GetRecipeIds1() const
#endif
        {
            return recipe_ids_1;
        }

        const int GetArraySize2() const
        {
            return array_size_2;
        }

#if PROTOCOL_VERSION > 348
        const std::vector<Identifier>& GetRecipeIds2() const
#else
        const std::vector<int>& GetRecipeIds2() const
#endif
        {
            return recipe_ids_2;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            action = ReadVarInt(iter, length);
            crafting_book_open = ReadData<bool>(iter, length);
            crafting_recipe_book_filter_active = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 356
            smelting_recipe_book_open = ReadData<bool>(iter, length);
            smelting_recipe_book_filter_active = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 736
            blast_furnace_recipe_book_open = ReadData<bool>(iter, length);
            blast_furnace_recipe_book_filter_active = ReadData<bool>(iter, length);
            smoker_recipe_book_open = ReadData<bool>(iter, length);
            smoker_recipe_book_filter_active = ReadData<bool>(iter, length);
#endif
            array_size_1 = ReadVarInt(iter, length);
#if PROTOCOL_VERSION > 348
            recipe_ids_1 = std::vector<Identifier>(array_size_1);
#else
            recipe_ids_1 = std::vector<int>(array_size_1);
#endif
            for (int i = 0; i < array_size_1; ++i)
            {
#if PROTOCOL_VERSION > 348
                recipe_ids_1[i] = ReadString(iter, length);
#else
                recipe_ids_1[i] = ReadVarInt(iter, length);
#endif
            }
            if ((UnlockRecipesAction)action == UnlockRecipesAction::Init)
            {
                array_size_2 = ReadVarInt(iter, length);
#if PROTOCOL_VERSION > 348
                recipe_ids_2 = std::vector<Identifier>(array_size_2);
#else
                recipe_ids_2 = std::vector<int>(array_size_2);
#endif
                for (int i = 0; i < array_size_2; ++i)
                {
#if PROTOCOL_VERSION > 348
                    recipe_ids_2[i] = ReadString(iter, length);
#else
                    recipe_ids_2[i] = ReadVarInt(iter, length);
#endif
                }
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(action, container);
            WriteData<bool>(crafting_book_open, container);
            WriteData<bool>(crafting_recipe_book_filter_active, container);
#if PROTOCOL_VERSION > 356
            WriteData<bool>(smelting_recipe_book_open, container);
            WriteData<bool>(smelting_recipe_book_filter_active, container);
#endif
#if PROTOCOL_VERSION > 736
            WriteData<bool>(blast_furnace_recipe_book_open, container);
            WriteData<bool>(blast_furnace_recipe_book_filter_active, container);
            WriteData<bool>(smoker_recipe_book_open, container);
            WriteData<bool>(smoker_recipe_book_filter_active, container);
#endif
            WriteVarInt(array_size_1, container);
            for (int i = 0; i < array_size_1; ++i)
            {
#if PROTOCOL_VERSION > 348
                WriteString(recipe_ids_1[i], container);
#else
                WriteVarInt(recipe_ids_1[i], container);
#endif
            }
            if ((UnlockRecipesAction)action == UnlockRecipesAction::Init)
            {
                WriteVarInt(array_size_2, container);
                for (int i = 0; i < array_size_2; ++i)
                {
#if PROTOCOL_VERSION > 348
                    WriteString(recipe_ids_2[i], container);
#else
                    WriteVarInt(recipe_ids_2[i], container);
#endif
                }
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["action"] = picojson::value((double)action);
            object["crafting_book_open"] = picojson::value((double)crafting_book_open);
            object["crafting_recipe_book_filter_active"] = picojson::value((double)crafting_recipe_book_filter_active);
#if PROTOCOL_VERSION > 356
            object["smelting_recipe_book_open"] = picojson::value(smelting_recipe_book_open);
            object["smelting_recipe_book_filter_active"] = picojson::value(smelting_recipe_book_filter_active);
#endif
#if PROTOCOL_VERSION > 736
            object["smelting_recipe_book_open"] = picojson::value(blast_furnace_recipe_book_open);
            object["smelting_recipe_book_filter_active"] = picojson::value(blast_furnace_recipe_book_filter_active);
            object["smelting_recipe_book_open"] = picojson::value(smoker_recipe_book_open);
            object["smelting_recipe_book_filter_active"] = picojson::value(smoker_recipe_book_filter_active);
#endif
            object["array_size_1"] = picojson::value((double)array_size_1);

            object["recipe_ids_1"] = picojson::value(picojson::array_type, false);
            picojson::array& array1 = object["recipe_ids_1"].get<picojson::array>();

            for (int i = 0; i < array_size_1; ++i)
            {
#if PROTOCOL_VERSION > 348
                array1.push_back(picojson::value(recipe_ids_1[i]));
#else
                array1.push_back(picojson::value((double)recipe_ids_1[i]));
#endif
            }

            if ((UnlockRecipesAction)action == UnlockRecipesAction::Init)
            {
                object["array_size_2"] = picojson::value((double)array_size_2);
                object["recipe_ids_2"] = picojson::value(picojson::array_type, false);
                picojson::array& array2 = object["recipe_ids_2"].get<picojson::array>();

                for (int i = 0; i < array_size_2; ++i)
                {
#if PROTOCOL_VERSION > 348
                    array2.push_back(picojson::value(recipe_ids_2[i]));
#else
                    array2.push_back(picojson::value((double)recipe_ids_2[i]));
#endif
                }
            }

            return value;
        }

    private:
        int action;
        bool crafting_book_open;
        bool crafting_recipe_book_filter_active;
#if PROTOCOL_VERSION > 356
        bool smelting_recipe_book_open;
        bool smelting_recipe_book_filter_active;
#endif
#if PROTOCOL_VERSION > 736
        bool blast_furnace_recipe_book_open;
        bool blast_furnace_recipe_book_filter_active;
        bool smoker_recipe_book_open;
        bool smoker_recipe_book_filter_active;
#endif
        int array_size_1;
#if PROTOCOL_VERSION > 348
        std::vector<Identifier> recipe_ids_1;
#else
        std::vector<int> recipe_ids_1;
#endif
        int array_size_2;
#if PROTOCOL_VERSION > 348
        std::vector<Identifier> recipe_ids_2;
#else
        std::vector<int> recipe_ids_2;
#endif

    };
} //ProtocolCraft