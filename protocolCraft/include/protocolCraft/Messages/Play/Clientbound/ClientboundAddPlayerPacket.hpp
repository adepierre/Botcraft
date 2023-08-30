#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddPlayerPacket : public BaseMessage<ClientboundAddPlayerPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 || PROTOCOL_VERSION == 393 ||  \
      PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 ||  \
      PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754 || PROTOCOL_VERSION == 755 ||  \
      PROTOCOL_VERSION == 756 || PROTOCOL_VERSION == 757 ||  \
      PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 759 || PROTOCOL_VERSION == 760 ||  \
      PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x03;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Add Player";

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


        int GetEntityId() const
        {
            return entity_id;
        }

        const UUID& GetPlayerId() const
        {
            return player_id;
        }

        double GetX() const
        {
            return x;
        }

        double GetY() const
        {
            return y;
        }

        double GetZ() const
        {
            return z;
        }

        Angle GetYRot() const
        {
            return yRot;
        }

        Angle GetXRot() const
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

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

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
        int entity_id = 0;
        UUID player_id = {};
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        Angle yRot = 0;
        Angle xRot = 0;
#if PROTOCOL_VERSION < 550
        std::vector<unsigned char> raw_metadata;
#endif

    };
} //ProtocolCraft
