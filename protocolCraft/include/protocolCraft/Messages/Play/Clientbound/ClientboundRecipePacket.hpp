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

#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
        void SetRecipes(const std::vector<Identifier>& recipes_)
#else
        void SetRecipes(const std::vector<int>& recipes_)
#endif
        {
            recipes = recipes_;
        }

#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
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


        RecipeState GetState() const
        {
            return state;
        }

#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
        const std::vector<Identifier>& GetRecipes() const
#else
        const std::vector<int>& GetRecipes() const
#endif
        {
            return recipes;
        }

#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
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

#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
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
#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
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


#if PROTOCOL_VERSION > 348 /* > 1.12.2 */

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
#if PROTOCOL_VERSION > 348 /* > 1.12.2 */

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

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["state"] = state;
            output["recipes"]= recipes;

            if (state == RecipeState::Init)
            {
                output["to_highlight"] = to_highlight;
            }

            output["book_settings"] = book_settings;

            return output;
        }

    private:
        RecipeState state;
#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
        std::vector<Identifier> recipes;
#else
        std::vector<int> recipes;
#endif
#if PROTOCOL_VERSION > 348 /* > 1.12.2 */
        std::vector<Identifier> to_highlight;
#else
        std::vector<int> to_highlight;
#endif
        RecipeBookSettings book_settings;

    };
} //ProtocolCraft
