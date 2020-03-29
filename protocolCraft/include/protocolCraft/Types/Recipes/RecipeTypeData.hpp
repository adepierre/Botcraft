#pragma once

#if PROTOCOL_VERSION > 347
#include <memory>
#include <string>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class RecipeTypeData : public NetworkType
    {
    public:
        
        static std::shared_ptr<RecipeTypeData> CreateRecipeTypeData(const std::string& recipe_type);
    };
}
#endif
