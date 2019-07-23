#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"

namespace Botcraft
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
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        int threshold;
    };
} //Botcraft