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
            registry = ReadData<Identifier>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<Identifier>(registry, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["registry"] = registry.Serialize();

            return output;
        }

    private:
        Identifier registry;
    };
}
#endif
