#pragma once

#if PROTOCOL_VERSION > 347
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"

namespace ProtocolCraft
{
    class RecipeTypeDataNone : public RecipeTypeData
    {
    public:
        virtual ~RecipeTypeDataNone() override
        {

        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {

        }

        virtual void WriteImpl(WriteContainer& container) const override
        {

        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            return output;
        }

    private:
    };
}
#endif
