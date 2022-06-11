#pragma once

#if PROTOCOL_VERSION > 711
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundJigsawGeneratePacket : public BaseMessage<ServerboundJigsawGeneratePacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x0F;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x0F;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x0E;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x0E;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x10;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Jigsaw Generate";
        }

        virtual ~ServerboundJigsawGeneratePacket() override
        {

        }
        
        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }

        void SetLevels(const int levels_)
        {
            levels = levels_;
        }

        void SetKeepJigsaws(const bool keep_jigsaws_)
        {
            keep_jigsaws = keep_jigsaws_;
        }

        const NetworkPosition GetPos() const
        {
            return pos;
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
            pos.Read(iter, length);
            levels = ReadData<VarInt>(iter, length);
            keep_jigsaws = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            pos.Write(container);
            WriteData<VarInt>(levels, container);
            WriteData<bool>(keep_jigsaws, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["pos"] = pos.Serialize();
            output["levels"] = levels;
            output["keep_jigsaws"] = keep_jigsaws;

            return output;
        }

    private:
        NetworkPosition pos;
        int levels;
        bool keep_jigsaws;
    };
} //ProtocolCraft
#endif