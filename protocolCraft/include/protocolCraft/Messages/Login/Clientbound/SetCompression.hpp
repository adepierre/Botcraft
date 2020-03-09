#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SetCompression : public BaseMessage<SetCompression>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x03;
        }

        virtual const std::string GetName() const override
        {
            return "Set Compression";
        }

        void SetThreshold(const int threshold_)
        {
            threshold = threshold_;
        }

        const int GetThreshold() const
        {
            return threshold;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            threshold = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(threshold, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["threshold"] = picojson::value((double)threshold);

            return value;
        }

    private:
        int threshold;
    };
} //ProtocolCraft