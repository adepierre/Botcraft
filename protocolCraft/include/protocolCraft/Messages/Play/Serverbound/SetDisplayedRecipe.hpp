#pragma once

#if PROTOCOL_VERSION > 736
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SetDisplayedRecipe : public BaseMessage<SetDisplayedRecipe>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2 or 1.16.3
            return 0x1E;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Displayed Recipe";
        }

        void SetRecipeID(const Identifier& recipe_id_)
        {
            recipe_id = recipe_id_;
        }


        const Identifier& GetRecipeID() const
        {
            return recipe_id;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            recipe_id = ReadString(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteString(recipe_id, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["recipe_id"] = picojson::value(recipe_id);

            return value;
        }

    private:
        Identifier recipe_id;
    };
} //ProtocolCraft
#endif