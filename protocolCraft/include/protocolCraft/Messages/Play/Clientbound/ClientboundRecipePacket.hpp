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
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x31;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x36;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x36;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x37;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x39;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Recipe";

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
            state = static_cast<RecipeState>(static_cast<int>(ReadData<VarInt>(iter, length)));
            book_settings = ReadData<RecipeBookSettings>(iter, length);

#if PROTOCOL_VERSION > 348
            recipes = ReadVector<Identifier>(iter, length);
#else
            recipes = ReadVector<int>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadData<VarInt>(i, l);
                }
            );
#endif

            if (state == RecipeState::Init)
            {
#if PROTOCOL_VERSION > 348
                to_highlight = ReadVector<Identifier>(iter, length);
#else
                to_highlight = ReadVector<int>(iter, length,
                    [](ReadIterator& i, size_t& l)
                    {
                        return ReadData<VarInt>(i, l);
                    }
                );
#endif
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(static_cast<int>(state), container);
            WriteData<RecipeBookSettings>(book_settings, container);


#if PROTOCOL_VERSION > 348

            WriteVector<Identifier>(recipes, container);
#else
            WriteVector<int>(recipes, container,
                [](const int& i, WriteContainer& c)
                {
                    WriteData<VarInt>(i, c);
                }
            );
#endif

            if (state == RecipeState::Init)
            {
#if PROTOCOL_VERSION > 348

                WriteVector<Identifier>(to_highlight, container);
#else
                WriteVector<int>(to_highlight, container,
                    [](const int& i, WriteContainer& c)
                    {
                        WriteData<VarInt>(i, c);
                    }
                );
#endif
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["state"] = state;

#if PROTOCOL_VERSION > 348
            output["recipes"] = nlohmann::json::array();
            for (const auto& r : recipes)
            {
                output["recipes"].push_back(r.Serialize());
            }
#else
            output["recipes"]= recipes;
#endif

            if (state == RecipeState::Init)
            {
#if PROTOCOL_VERSION > 348
                output["to_highlight"] = nlohmann::json::array();
                for (const auto& t : to_highlight)
                {
                    output["to_highlight"].push_back(t.Serialize());
                }
#else
                output["to_highlight"] = to_highlight;
#endif
            }

            output["book_settings"] = book_settings.Serialize();

            return output;
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
