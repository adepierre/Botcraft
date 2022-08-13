#pragma once

#if PROTOCOL_VERSION > 471
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetChunkCacheRadiusPacket : public BaseMessage<ClientboundSetChunkCacheRadiusPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x41;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x42;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x41;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x41;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x4A;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x4A;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x49;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x4C;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Chunk Cache Radius";
        }

        virtual ~ClientboundSetChunkCacheRadiusPacket() override
        {

        }

        void SetRadius(const int radius_)
        {
            radius = radius_;
        }


        const int GetRadius() const
        {
            return radius;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            radius = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(radius, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["radius"] = radius;

            return output;
        }

    private:
        int radius;

    };
} //ProtocolCraft
#endif
