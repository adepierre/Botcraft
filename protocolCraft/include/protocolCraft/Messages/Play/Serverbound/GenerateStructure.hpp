#pragma once

#if PROTOCOL_VERSION > 711
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class GenerateStructure : public BaseMessage<GenerateStructure>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x0F;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x0F;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Digging";
        }
        
        void SetLocation(const NetworkPosition& pos)
        {
            location = pos;
        }

        void SetLevels(const int levels_)
        {
            levels = levels_;
        }

        void SetKeepJigsaws(const bool keep_jigsaws_)
        {
            keep_jigsaws = keep_jigsaws_;
        }

        const NetworkPosition GetLocation() const
        {
            return location;
        }

        const int GetLevels() const
        {
            return levels;
        }

        const bool GetKeepJigsaws() const
        {
            return keep_jigsaws;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            location.Read(iter, length);
            levels = ReadVarInt(iter, length);
            keep_jigsaws = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            location.Write(container);
            WriteVarInt(levels, container);
            WriteData<bool>(keep_jigsaws, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["location"] = location.Serialize();
            object["levels"] = picojson::value((double)levels);
            object["keep_jigsaws"] = picojson::value(keep_jigsaws);

            return value;
        }

    private:
        NetworkPosition location;
        int levels;
        bool keep_jigsaws;
    };
} //ProtocolCraft
#endif