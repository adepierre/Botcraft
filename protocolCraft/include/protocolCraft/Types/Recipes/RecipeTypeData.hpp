#pragma once

#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#include <memory>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class RecipeTypeData : public NetworkType
    {
    public:
        virtual ~RecipeTypeData() override;
        
        static std::shared_ptr<RecipeTypeData> CreateRecipeTypeData(const Identifier& recipe_type);
    };
}
#endif
