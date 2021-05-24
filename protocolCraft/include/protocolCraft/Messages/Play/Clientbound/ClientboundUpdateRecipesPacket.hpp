#pragma once

#if PROTOCOL_VERSION > 347
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Recipes/Recipe.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateRecipesPacket : public BaseMessage<ClientboundUpdateRecipesPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x54;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x5A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x5B;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x5A;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x5A;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Recipes";
        }

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
            const int recipes_size = ReadVarInt(iter, length);
            recipes = std::vector<Recipe>(recipes_size);
            for (int i = 0; i < recipes_size; ++i)
            {
                recipes[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(recipes.size(), container);
            for (int i = 0; i < recipes.size(); ++i)
            {
                recipes[i].Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["recipes"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["recipes"].get<picojson::array>();

            for (int i = 0; i < recipes.size(); ++i)
            {
                array.push_back(recipes[i].Serialize());
            }

            return value;
        }

    private:
        std::vector<Recipe> recipes;

    };
} //ProtocolCraft
#endif
