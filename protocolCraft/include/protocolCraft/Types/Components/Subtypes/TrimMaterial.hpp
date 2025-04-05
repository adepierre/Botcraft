#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    namespace Components
    {
        class TrimMaterial : public NetworkType
        {
            SERIALIZED_FIELD(AssetName, std::string);
            SERIALIZED_FIELD(Ingredient, VarInt);
#if PROTOCOL_VERSION < 769 /* < 1.21.4 */
            SERIALIZED_FIELD(ItemModelIndex, float);
#endif
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
            SERIALIZED_FIELD(OverrideArmorMaterials, std::map<VarInt, std::string>);
#else
            SERIALIZED_FIELD(OverrideArmorMaterials, std::map<Identifier, std::string>);
#endif
            SERIALIZED_FIELD(Description, Chat);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
