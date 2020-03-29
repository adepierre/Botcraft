#pragma once

#if PROTOCOL_VERSION > 344
#include <memory>
#include <string>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class BrigadierProperty : public NetworkType
    {
    public:
        
        static std::shared_ptr<BrigadierProperty> CreateProperties(const std::string& parser_identifier);
    };
}
#endif
