#pragma once

#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundSetStructureBlockPacket : public BaseMessage<ServerboundSetStructureBlockPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x2C;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */ || PROTOCOL_VERSION == 761 /* 1.19.3 */ ||  \
      PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x2D;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Structure Block";

        virtual ~ServerboundSetStructureBlockPacket() override
        {

        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }

        void SetUpdateType(const int update_type_)
        {
            update_type = update_type_;
        }

        void SetMode(const int mode_)
        {
            mode = mode_;
        }

        void SetName_(const std::string& name__)
        {
            name_ = name__;
        }

        void SetOffset(const NetworkPosition& offset_)
        {
            offset = offset_;
        }

        void SetSizeX(const NetworkPosition& size_)
        {
            size = size_;
        }

        void SetMirror(const int mirror_)
        {
            mirror = mirror_;
        }

        void SetRotation(const int rotation_)
        {
            rotation = rotation_;
        }

        void SetData(const std::string& data_)
        {
            data = data_;
        }

        void SetIntegrity(const float integrity_)
        {
            integrity = integrity_;
        }

        void SetSeed(const long long int seed_)
        {
            seed = seed_;
        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }


        const NetworkPosition& GetPos() const
        {
            return pos;
        }

        int GetUpdateType() const
        {
            return update_type;
        }

        int GetMode() const
        {
            return mode;
        }

        const std::string& GetName_() const
        {
            return name_;
        }

        const NetworkPosition& GetOffset() const
        {
            return offset;
        }

        const NetworkPosition& GetSize() const
        {
            return size;
        }

        int GetMirror() const
        {
            return mirror;
        }

        int GetRotation() const
        {
            return rotation;
        }

        const std::string& GetData() const
        {
            return data;
        }

        float GetIntegrity() const
        {
            return integrity;
        }

        long long int GetSeed() const
        {
            return seed;
        }

        char GetFlags() const
        {
            return flags;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            pos = ReadData<NetworkPosition>(iter, length);
            update_type = ReadData<VarInt>(iter, length);
            mode = ReadData<VarInt>(iter, length);
            name_ = ReadData<std::string>(iter, length);
            offset.SetX(ReadData<char>(iter, length));
            offset.SetY(ReadData<char>(iter, length));
            offset.SetZ(ReadData<char>(iter, length));
            size.SetX(ReadData<char>(iter, length));
            size.SetY(ReadData<char>(iter, length));
            size.SetZ(ReadData<char>(iter, length));
            mirror = ReadData<VarInt>(iter, length);
            rotation = ReadData<VarInt>(iter, length);
            data = ReadData<std::string>(iter, length);
            integrity = ReadData<float>(iter, length);
            seed = ReadData<VarLong>(iter, length);
            flags = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<NetworkPosition>(pos, container);
            WriteData<VarInt>(update_type, container);
            WriteData<VarInt>(mode, container);
            WriteData<std::string>(name_, container);
            WriteData<char>(offset.GetX(), container);
            WriteData<char>(offset.GetY(), container);
            WriteData<char>(offset.GetZ(), container);
            WriteData<char>(size.GetX(), container);
            WriteData<char>(size.GetY(), container);
            WriteData<char>(size.GetZ(), container);
            WriteData<VarInt>(mirror, container);
            WriteData<VarInt>(rotation, container);
            WriteData<std::string>(data, container);
            WriteData<float>(integrity, container);
            WriteData<VarLong>(seed, container);
            WriteData<char>(flags, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["pos"] = pos;
            output["update_type"] = update_type;
            output["mode"] = mode;
            output["name_"] = name_;
            output["offset"] = offset;
            output["size"] = size;
            output["mirror"] = mirror;
            output["rotation"] = rotation;
            output["data"] = data;
            output["integrity"] = integrity;
            output["seed"] = seed;
            output["flags"] = flags;

            return output;
        }

    private:
        NetworkPosition pos;
        int update_type = 0;
        int mode = 0;
        std::string name_;
        NetworkPosition offset;
        NetworkPosition size;
        int mirror = 0;
        int rotation = 0;
        std::string data;
        float integrity = 0.0f;
        long long int seed = 0;
        char flags = 0;

    };
} //ProtocolCraft
#endif
