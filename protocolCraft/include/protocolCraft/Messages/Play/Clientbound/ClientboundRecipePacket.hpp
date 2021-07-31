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
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x39;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Recipe";
        }

        virtual ~ClientboundRecipePacket() override
        {

        }

        void SetState(const RecipeState state_)
        {
            state = state_;
        }

#if PROTOCOL_VERSION > 348
        void SetRecipes(const std::vector<Identifier>& recipes_)
#else
        void SetRecipes(const std::vector<int>& recipes_)
#endif
        {
            recipes = recipes_;
        }

#if PROTOCOL_VERSION > 348
        void SetToHighlight(const std::vector<Identifier>& to_highlight_)
#else
        void SetToHighlight(const std::vector<int>& to_highlight_)
#endif
        {
            to_highlight = to_highlight_;
        }

        void SetBookSettings(const RecipeBookSettings& book_settings_)
        {
            book_settings = book_settings_;
        }


        const RecipeState GetState() const
        {
            return state;
        }

#if PROTOCOL_VERSION > 348
        const std::vector<Identifier>& GetRecipes() const
#else
        const std::vector<int>& GetRecipes() const
#endif
        {
            return recipes;
        }

#if PROTOCOL_VERSION > 348
        const std::vector<Identifier>& GetToHighlight() const
#else
        const std::vector<int>& GetToHighlight() const
#endif
        {
            return to_highlight;
        }

        const RecipeBookSettings& GetBookSettings() const
        {
            return book_settings;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            state = (RecipeState)(int)ReadData<VarInt>(iter, length);
            book_settings.Read(iter, length);
            int recipes_size = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION > 348
            recipes = std::vector<Identifier>(recipes_size);
#else
            recipes = std::vector<int>(recipes_size);
#endif
            for (int i = 0; i < recipes_size; ++i)
            {
#if PROTOCOL_VERSION > 348
                recipes[i].Read(iter, length);
#else
                recipes[i] = ReadData<VarInt>(iter, length);
#endif
            }
            if (state == RecipeState::Init)
            {
                int to_highlight_size = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION > 348
                to_highlight = std::vector<Identifier>(to_highlight_size);
#else
                to_highlight = std::vector<int>(to_highlight_size);
#endif
                for (int i = 0; i < to_highlight_size; ++i)
                {
#if PROTOCOL_VERSION > 348
                    to_highlight[i].Read(iter, length);
#else
                    to_highlight[i] = ReadData<VarInt>(iter, length);
#endif
                }
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>((int)state, container);
            book_settings.Write(container);
            WriteData<VarInt>(recipes.size(), container);
            for (int i = 0; i < recipes.size(); ++i)
            {
#if PROTOCOL_VERSION > 348
                recipes[i].Write(container);
#else
                WriteData<VarInt>(recipes[i], container);
#endif
            }
            if (state == RecipeState::Init)
            {
                WriteData<VarInt>(to_highlight.size(), container);
                for (int i = 0; i < to_highlight.size(); ++i)
                {
#if PROTOCOL_VERSION > 348
                    to_highlight[i].Write(container);
#else
                    WriteData<VarInt>(to_highlight[i], container);
#endif
                }
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["state"] = picojson::value((double)state);

            object["recipes"] = picojson::value(picojson::array_type, false);
            picojson::array& array_recipes = object["recipes"].get<picojson::array>();

            for (int i = 0; i < recipes.size(); ++i)
            {
#if PROTOCOL_VERSION > 348
                array_recipes.push_back(recipes[i].Serialize());
#else
                array_recipes.push_back(picojson::value((double)recipes[i]));
#endif
            }

            if (state == RecipeState::Init)
            {
                object["to_highlight"] = picojson::value(picojson::array_type, false);
                picojson::array& array_to_highlight = object["to_highlight"].get<picojson::array>();

                for (int i = 0; i < to_highlight.size(); ++i)
                {
#if PROTOCOL_VERSION > 348
                    array_to_highlight.push_back(to_highlight[i].Serialize());
#else
                    array_to_highlight.push_back(picojson::value((double)to_highlight[i]));
#endif
                }
            }

            object["book_settings"] = book_settings.Serialize();

            return value;
        }

    private:
        RecipeState state;
#if PROTOCOL_VERSION > 348
        std::vector<Identifier> recipes;
#else
        std::vector<int> recipes;
#endif
#if PROTOCOL_VERSION > 348
        std::vector<Identifier> to_highlight;
#else
        std::vector<int> to_highlight;
#endif
        RecipeBookSettings book_settings;

    };
} //ProtocolCraft