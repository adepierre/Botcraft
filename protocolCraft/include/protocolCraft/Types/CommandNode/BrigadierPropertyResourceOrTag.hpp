#pragma once

#if PROTOCOL_VERSION > 344
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyResourceOrTag : public BrigadierProperty
    {
    public:
        virtual ~BrigadierPropertyResourceOrTag()
        {

        }


        void SetRegistry(const Identifier& registry_)
        {
            registry = registry_;
        }
        
        
        const Identifier& GetRegistry() const
        {
            return registry;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            registry.Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            registry.Write(container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["registry"] = registry.Serialize();

            return output;
        }

    private:
        Identifier registry;
    };
}
#endif
