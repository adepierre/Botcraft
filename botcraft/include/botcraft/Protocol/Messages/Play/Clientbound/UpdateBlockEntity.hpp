#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"
#include "botcraft/Game/Vector3.hpp"
#include "botcraft/NBT/NBT.hpp"
#include "botcraft/Version.hpp"

namespace Botcraft
{
    class UpdateBlockEntity : public BaseMessage<UpdateBlockEntity>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x09;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x09;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x09;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Block Entity";
        }

        const Position& GetLocation() const
        {
            return location;
        }

        const unsigned char GetAction() const
        {
            return action;
        }

        const std::shared_ptr<NBT> GetNBTData() const
        {
            return nbt_data;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            location = ReadPosition(iter, length);
            action = ReadData<unsigned char>(iter, length);
            nbt_data = std::shared_ptr<NBT>(new NBT);
            nbt_data->Read(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        Position location;
        unsigned char action;
        std::shared_ptr<NBT> nbt_data;
    };
} //Botcraft