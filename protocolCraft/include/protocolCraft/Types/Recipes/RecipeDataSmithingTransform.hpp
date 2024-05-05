#pragma once

#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Types/Recipes/RecipeData.hpp"
#include "protocolCraft/Types/Recipes/Ingredient.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class RecipeDataSmithingTransform : public RecipeData
    {
    public:
        virtual ~RecipeDataSmithingTransform() override
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

        void SetResult(const Slot& result_)
        {
            result = result_;
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

        const Slot& GetResult() const
        {
            return result;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            template_ = ReadData<Ingredient>(iter, length);
            base = ReadData<Ingredient>(iter, length);
            addition = ReadData<Ingredient>(iter, length);
            result = ReadData<Slot>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Ingredient>(template_, container);
            WriteData<Ingredient>(base, container);
            WriteData<Ingredient>(addition, container);
            WriteData<Slot>(result, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["template"] = template_;
            output["base"] = base;
            output["addition"] = addition;
            output["result"] = result;

            return output;
        }

    private:
        Ingredient template_;
        Ingredient base;
        Ingredient addition;
        Slot result;
    };
}
#endif
