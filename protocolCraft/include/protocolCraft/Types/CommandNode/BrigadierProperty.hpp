#pragma once

#if PROTOCOL_VERSION > 344
#include <memory>
#include <string>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class BrigadierProperty : public NetworkType
    {
    public:
        
        static std::shared_ptr<BrigadierProperty> CreateProperties(const Identifier& parser_identifier);
    };
}
#endif
