#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddPlayerPacket : public BaseMessage<ClientboundAddPlayerPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x05;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x05;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x05;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x05;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x04;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x04;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x04;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Add Player";
        }

        virtual ~ClientboundAddPlayerPacket() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetPlayerId(const UUID& player_id_)
        {
            player_id = player_id_;
        }

        void SetX(const double x_)
        {
            x = x_;
        }

        void SetY(const double y_)
        {
            y = y_;
        }

        void SetZ(const double z_)
        {
            z = z_;
        }

        void SetYRot(const Angle yRot_)
        {
            yRot = yRot_;
        }

        void SetXRot(const Angle xRot_)
        {
            xRot = xRot_;
        }

#if PROTOCOL_VERSION < 550
        void SetRawMetadata(const std::vector<unsigned char> raw_metadata_)
        {
            raw_metadata = raw_metadata_;
        }
#endif


        const int GetEntityId() const
        {
            return entity_id;
        }

        const UUID& GetPlayerId() const
        {
            return player_id;
        }

        const double GetX() const
        {
            return x;
        }

        const double GetY() const
        {
            return y;
        }

        const double GetZ() const
        {
            return z;
        }

        const Angle GetYRot() const
        {
            return yRot;
        }

        const Angle GetXRot() const
        {
            return xRot;
        }

#if PROTOCOL_VERSION < 550
        const std::vector<unsigned char>& GetRawMetadata() const
        {
            return raw_metadata;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadData<VarInt>(iter, length);
            player_id = ReadData<UUID>(iter, length);
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            yRot = ReadData<Angle>(iter, length);
            xRot = ReadData<Angle>(iter, length);
#if PROTOCOL_VERSION < 550
            raw_metadata = ReadByteArray(iter, length, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity_id, container);
            WriteData<UUID>(player_id, container);
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<Angle>(yRot, container);
            WriteData<Angle>(xRot, container); 
#if PROTOCOL_VERSION < 550
                WriteByteArray(raw_metadata, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["entity_id"] = entity_id;
            output["player_id"] = player_id;
            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["yRot"] = yRot;
            output["xRot"] = xRot;
#if PROTOCOL_VERSION < 550
            output["raw_metadata"] = "Vector of " + std::to_string(raw_metadata.size()) + " unsigned char";
#endif

            return output;
        }

    private:
        int entity_id;
        UUID player_id;
        double x;
        double y;
        double z;
        Angle yRot;
        Angle xRot;
#if PROTOCOL_VERSION < 550
        std::vector<unsigned char> raw_metadata;
#endif

    };
} //ProtocolCraft