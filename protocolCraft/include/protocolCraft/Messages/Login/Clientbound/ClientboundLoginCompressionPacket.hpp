#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundLoginCompressionPacket : public BaseMessage<ClientboundLoginCompressionPacket>
    {
    public:
        static constexpr int packet_id = 0x03;
        static constexpr std::string_view packet_name = "Login Compression";

        virtual ~ClientboundLoginCompressionPacket() override
        {

        }

        void SetCompressionThreshold(const int compression_threshold_)
        {
            compression_threshold = compression_threshold_;
        }

        int GetCompressionThreshold() const
        {
            return compression_threshold;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            compression_threshold = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(compression_threshold, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["compression_threshold"] = compression_threshold;

            return output;
        }

    private:
        int compression_threshold;
    };
} //ProtocolCraft
