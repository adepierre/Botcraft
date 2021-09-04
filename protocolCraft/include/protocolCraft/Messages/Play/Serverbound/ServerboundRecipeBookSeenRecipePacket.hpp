#pragma once

#if PROTOCOL_VERSION > 736
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ServerboundRecipeBookSeenRecipePacket : public BaseMessage<ServerboundRecipeBookSeenRecipePacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x1F;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x1F;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Recipe Book Seen Recipe";
        }

        virtual ~ServerboundRecipeBookSeenRecipePacket() override
        {

        }

        void SetRecipe(const Identifier& recipe_)
        {
            recipe = recipe_;
        }


        const Identifier& GetRecipe() const
        {
            return recipe;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            recipe.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            recipe.Write(container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["recipe"] = recipe.Serialize();

            return output;
        }

    private:
        Identifier recipe;
    };
} //ProtocolCraft
#endif