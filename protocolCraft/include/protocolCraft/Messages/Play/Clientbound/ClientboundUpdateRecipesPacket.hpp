#pragma once

#if PROTOCOL_VERSION > 347
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Recipes/Recipe.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateRecipesPacket : public BaseMessage<ClientboundUpdateRecipesPacket>
    {
    public:
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x54;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x5A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x5B;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x5A;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x5A;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x65;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x66;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x67;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x6A;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x69;
#elif PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x6D;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Update Recipes";

        virtual ~ClientboundUpdateRecipesPacket() override
        {

        }


        void SetRecipes(const std::vector<Recipe>& recipes_)
        {
            recipes = recipes_;
        }


        const std::vector<Recipe>& GetRecipes() const
        {
            return recipes;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            recipes = ReadVector<Recipe>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVector<Recipe>(recipes, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["recipes"] = recipes;

            return output;
        }

    private:
        std::vector<Recipe> recipes;

    };
} //ProtocolCraft
#endif
