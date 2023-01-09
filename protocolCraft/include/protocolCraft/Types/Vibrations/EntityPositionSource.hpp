#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/Types/Vibrations/PositionSource.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class EntityPositionSource : public PositionSource
    {
    public:
        virtual ~EntityPositionSource() override
        {

        }

        void SetSourceEntityId(const int source_entity_id_)
        {
            source_entity_id = source_entity_id_;
        }


        int GetSourceEntityId() const
        {
            return source_entity_id;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            source_entity_id = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(source_entity_id, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["source_entity_id"] = source_entity_id;

            return output;
        }

    private:
        int source_entity_id;
    };
}
#endif
