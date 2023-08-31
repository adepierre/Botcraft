#pragma once

#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"

namespace ProtocolCraft
{
    class RecipeTypeDataSmithingTrim : public RecipeTypeData
    {
    public:
        virtual ~RecipeTypeDataSmithingTrim() override
        {

        }

        void SetTemplate(const Ingredient& template__)
        {
            template_ = template__;
        }

        void SetBase(const Ingredient& base_)
        {
            base = base_;
        }

        void SetAddition(const Ingredient& addition_)
        {
            addition = addition_;
        }


        const Ingredient& GetTemplate() const
        {
            return template_;
        }

        const Ingredient& GetBase() const
        {
            return base;
        }

        const Ingredient& GetAddition() const
        {
            return addition;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            template_ = ReadData<Ingredient>(iter, length);
            base = ReadData<Ingredient>(iter, length);
            addition = ReadData<Ingredient>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Ingredient>(template_, container);
            WriteData<Ingredient>(base, container);
            WriteData<Ingredient>(addition, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["template"] = template_;
            output["base"] = base;
            output["addition"] = addition;

            return output;
        }

    private:
        Ingredient template_;
        Ingredient base;
        Ingredient addition;
    };
}
#endif
