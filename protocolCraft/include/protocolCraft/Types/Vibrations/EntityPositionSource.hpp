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

#if PROTOCOL_VERSION > 758
        void SetYOffset(const float y_offset_)
        {
            y_offset = y_offset_;
        }
#endif


        int GetSourceEntityId() const
        {
            return source_entity_id;
        }

#if PROTOCOL_VERSION > 758
        float GetYOffset() const
        {
            return y_offset;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            source_entity_id = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION > 758
            y_offset = ReadData<float>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(source_entity_id, container);
#if PROTOCOL_VERSION > 758
            WriteData<float>(y_offset, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["source_entity_id"] = source_entity_id;
#if PROTOCOL_VERSION > 758
            output["y_offset"] = y_offset;
#endif

            return output;
        }

    private:
        int source_entity_id = 0;
#if PROTOCOL_VERSION > 758
        float y_offset = 0.0f;
#endif
    };
}
#endif
