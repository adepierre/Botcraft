#pragma once

#if PROTOCOL_VERSION > 347
#include <memory>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class Recipe : public NetworkType
    {
    public:
        virtual ~Recipe() override
        {

        }

        void SetRecipeId(const Identifier& recipe_id_)
        {
            recipe_id = recipe_id_;
        }

        void SetType(const Identifier& type_)
        {
            type = type_;
        }

        void SetData(const std::shared_ptr<RecipeTypeData> data_)
        {
            data = data_;
        }


        const Identifier& GetRecipeId() const
        {
            return recipe_id;
        }
        
        const Identifier& GetType() const
        {
            return type;
        }

        const std::shared_ptr<RecipeTypeData> GetData() const
        {
            return data;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 453
            recipe_id.Read(iter, length);
            type.Read(iter, length);
#else
            type.Read(iter, length);
            recipe_id.Read(iter, length);
#endif
            data = RecipeTypeData::CreateRecipeTypeData(type);
            data->Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 453
            recipe_id.Write(container);
            type.Write(container);
#else
            type.Write(container);
            recipe_id.Write(container);
#endif
            data->Write(container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["recipe_id"] = recipe_id.Serialize();
            output["type"] = type.Serialize();
            output["data"] = data->Serialize();

            return output;
        }

    private:
        Identifier recipe_id;
        Identifier type;
        std::shared_ptr<RecipeTypeData> data;
    };
}
#endif
