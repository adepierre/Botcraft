#pragma once

#if PROTOCOL_VERSION > 347
#include <memory>
#include <string>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Recipes/RecipeTypeData.hpp"

namespace ProtocolCraft
{
    class Recipe : public NetworkType
    {
    public:
        void SetRecipeId(const Identifier& recipe_id_)
        {
            recipe_id = recipe_id_;
        }

        void SetType(const std::string& type_)
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
        
        const std::string& GetType() const
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
            recipe_id = ReadString(iter, length);
            type = ReadString(iter, length);
#else
            type = ReadString(iter, length);
            recipe_id = ReadString(iter, length);
#endif
            data = RecipeTypeData::CreateRecipeTypeData(type);
            data->Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 578
            WriteString(recipe_id, container);
            WriteString(type, container);
#else
            WriteString(type, container);
            WriteString(recipe_id, container);
#endif
            data->Write(container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["recipe_id"] = picojson::value(recipe_id);
            object["type"] = picojson::value(type);
            object["data"] = data->Serialize();

            return value;
        }

    private:
        Identifier recipe_id;
        std::string type;
        std::shared_ptr<RecipeTypeData> data;
    };
}
#endif
