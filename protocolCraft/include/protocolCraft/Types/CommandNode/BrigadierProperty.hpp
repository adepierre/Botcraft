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
        virtual ~BrigadierProperty() override;

#if PROTOCOL_VERSION < 759
        static std::shared_ptr<BrigadierProperty> CreateProperties(const Identifier& parser_identifier);
#else
        static std::shared_ptr<BrigadierProperty> CreateProperties(const int parser_id);
#endif
    };
}
#endif
