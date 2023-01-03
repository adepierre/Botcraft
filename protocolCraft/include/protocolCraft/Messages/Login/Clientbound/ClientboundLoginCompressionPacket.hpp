#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundLoginCompressionPacket : public BaseMessage<ClientboundLoginCompressionPacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x03;
        }

        virtual const std::string GetName() const override
        {
            return "Login Compression";
        }

        virtual ~ClientboundLoginCompressionPacket() override
        {

        }

        void SetCompressionThreshold(const int compression_threshold_)
        {
            compression_threshold = compression_threshold_;
        }

        const int GetCompressionThreshold() const
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["compression_threshold"] = compression_threshold;

            return output;
        }

    private:
        int compression_threshold;
    };
} //ProtocolCraft
