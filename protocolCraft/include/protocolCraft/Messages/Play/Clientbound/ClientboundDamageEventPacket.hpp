#if PROTOCOL_VERSION > 761

#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 356
#include "protocolCraft/Types/Chat/Chat.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundDamageEventPacket : public BaseMessage<ClientboundDamageEventPacket>
    {
    public:
#if PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 763 // 1.20
        static constexpr int packet_id = 0x18;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Damage Event";

        virtual ~ClientboundDamageEventPacket() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetSourceTypeId(const int source_type_id_)
        {
            source_type_id = source_type_id_;
        }

        void SetSourceCauseId(const int source_cause_id_)
        {
            source_cause_id = source_cause_id_;
        }

        void SetSourceDirectId(const int source_direct_id_)
        {
            source_direct_id = source_direct_id_;
        }

        void SetSourcePosition(const std::optional<std::array<double, 3>>& source_position_)
        {
            source_position = source_position_;
        }


        int GetEntityId() const
        {
            return entity_id;
        }

        int GetSourceTypeId() const
        {
            return source_type_id;
        }

        int GetSourceCauseId() const
        {
            return source_cause_id;
        }

        int GetSourceDirectId() const
        {
            return source_direct_id;
        }

        const std::optional<std::array<double, 3>>& GetSourcePosition() const
        {
            return source_position;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadData<VarInt>(iter, length);
            source_type_id = ReadData<VarInt>(iter, length);
            source_cause_id = ReadData<VarInt>(iter, length) - 1;
            source_direct_id = ReadData<VarInt>(iter, length) - 1;
            source_position = ReadOptional<std::array<double, 3>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    std::array<double, 3> output;
                    output[0] = ReadData<double>(i, l);
                    output[1] = ReadData<double>(i, l);
                    output[2] = ReadData<double>(i, l);
                    return output;
                }
            );
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity_id, container);
            WriteData<VarInt>(source_type_id, container);
            WriteData<VarInt>(source_cause_id + 1, container);
            WriteData<VarInt>(source_direct_id + 1, container);
            WriteOptional<std::array<double, 3>>(source_position, container,
                [](const std::array<double, 3>& v, WriteContainer& c)
                {
                    WriteData<double>(v[0], c);
                    WriteData<double>(v[1], c);
                    WriteData<double>(v[2], c);
                }
            );
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["entity_id"] = entity_id;
            output["source_type_id"] = source_type_id;
            output["source_cause_id"] = source_cause_id;
            output["source_direct_id"] = source_direct_id;
            if (source_position.has_value())
            {
                output["source_position"] = source_position.value();
            }


            return output;
        }

    private:
        int entity_id = 0;
        int source_type_id = 0;
        int source_cause_id = 0;
        int source_direct_id = 0;
        std::optional<std::array<double, 3>> source_position;
    };
} //ProtocolCraft
#endif
