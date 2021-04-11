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
            compression_threshold = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(compression_threshold, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["compression_threshold"] = picojson::value((double)compression_threshold);

            return value;
        }

    private:
        int compression_threshold;
    };
} //ProtocolCraft