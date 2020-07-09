#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class UpdateStructureBlock : public BaseMessage<UpdateStructureBlock>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x25;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x28;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x28;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x29;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Structure Block";
        }

        void SetLocation(const NetworkPosition& location_)
        {
            location = location_;
        }

        void SetAction(const int action_)
        {
            action = action_;
        }

        void SetMode(const int mode_)
        {
            mode = mode_;
        }

        void SetName_(const std::string& name__)
        {
            name_ = name__;
        }

        void SetOffsetX(const char offset_x_)
        {
            offset_x = offset_x_;
        }

        void SetOffsetY(const char offset_y_)
        {
            offset_y = offset_y_;
        }

        void SetOffsetZ(const char offset_z_)
        {
            offset_z = offset_z_;
        }

        void SetSizeX(const char size_x_)
        {
            size_x = size_x_;
        }

        void SetSizeY(const char size_y_)
        {
            size_y = size_y_;
        }

        void SetSizeZ(const char size_z_)
        {
            size_z = size_z_;
        }

        void SetMirror(const int mirror_)
        {
            mirror = mirror_;
        }

        void SetRotation(const int rotation_)
        {
            rotation = rotation_;
        }

        void SetMetadata(const std::string& metadata_)
        {
            metadata = metadata_;
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


        const NetworkPosition& GetLocation() const
        {
            return location;
        }

        const int GetAction() const
        {
            return action;
        }

        const int GetMode() const
        {
            return mode;
        }

        const std::string& GetName_() const
        {
            return name_;
        }

        const char GetOffsetX() const
        {
            return offset_x;
        }

        const char GetOffsetY() const
        {
            return offset_y;
        }

        const char GetOffsetZ() const
        {
            return offset_z;
        }

        const char GetSizeX() const
        {
            return size_x;
        }

        const char GetSizeY() const
        {
            return size_y;
        }

        const char GetSizeZ() const
        {
            return size_z;
        }

        const int GetMirror() const
        {
            return mirror;
        }

        const int GetRotation() const
        {
            return rotation;
        }

        const std::string& GetMetadata() const
        {
            return metadata;
        }

        const float GetIntegrity() const
        {
            return integrity;
        }

        const long long int GetSeed() const
        {
            return seed;
        }

        const char GetFlags() const
        {
            return flags;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            location.Read(iter, length);
            action = ReadVarInt(iter, length);
            mode = ReadVarInt(iter, length);
            name_ = ReadString(iter, length);
            offset_x = ReadData<char>(iter, length);
            offset_y = ReadData<char>(iter, length);
            offset_z = ReadData<char>(iter, length);
            size_x = ReadData<char>(iter, length);
            size_y = ReadData<char>(iter, length);
            size_z = ReadData<char>(iter, length);
            mirror = ReadVarInt(iter, length);
            rotation = ReadVarInt(iter, length);
            metadata = ReadString(iter, length);
            integrity = ReadData<float>(iter, length);
            seed = ReadVarLong(iter, length);
            flags = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            location.Write(container);
            WriteVarInt(action, container);
            WriteVarInt(mode, container);
            WriteString(name_, container);
            WriteData<char>(offset_x, container);
            WriteData<char>(offset_y, container);
            WriteData<char>(offset_z, container);
            WriteData<char>(size_x, container);
            WriteData<char>(size_y, container);
            WriteData<char>(size_z, container);
            WriteVarInt(mirror, container);
            WriteVarInt(rotation, container);
            WriteString(metadata, container);
            WriteData<float>(integrity, container);
            WriteVarLong(seed, container);
            WriteData<char>(flags, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["location"] = location.Serialize();
            object["action"] = picojson::value((double)action);
            object["mode"] = picojson::value((double)mode);
            object["name_"] = picojson::value(name_);
            object["offset_x"] = picojson::value((double)offset_x);
            object["offset_y"] = picojson::value((double)offset_y);
            object["offset_z"] = picojson::value((double)offset_z);
            object["size_x"] = picojson::value((double)size_x);
            object["size_y"] = picojson::value((double)size_y);
            object["size_z"] = picojson::value((double)size_z);
            object["mirror"] = picojson::value((double)mirror);
            object["rotation"] = picojson::value((double)rotation);
            object["metadata"] = picojson::value(metadata);
            object["integrity"] = picojson::value((double)integrity);
            object["seed"] = picojson::value((double)seed);
            object["flags"] = picojson::value((double)flags);

            return value;
        }

    private:
        NetworkPosition location;
        int action;
        int mode;
        std::string name_;
        char offset_x;
        char offset_y;
        char offset_z;
        char size_x;
        char size_y;
        char size_z;
        int mirror;
        int rotation;
        std::string metadata;
        float integrity;
        long long int seed;
        char flags;

    };
} //ProtocolCraft
#endif