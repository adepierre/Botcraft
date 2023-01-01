#if PROTOCOL_VERSION < 759
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundAddPaintingPacket : public BaseMessage<ClientboundAddPaintingPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x04;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x04;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x04;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x04;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x03;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x03;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x03;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x03;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Add Painting";
        }

        virtual ~ClientboundAddPaintingPacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }

        void SetUuid(const UUID& uuid_)
        {
            uuid = uuid_;
        }

        void SetPos(const NetworkPosition pos_)
        {
            pos = pos_;
        }

        void SetDirection(const char direction_)
        {
            direction = direction_;
        }

#if PROTOCOL_VERSION < 353
        void SetTitle(const std::string title_)
        {
            title = title_;
        }
#else
        void SetMotive(const int motive_)
        {
            motive = motive_;
        }
#endif



        const int GetId_() const
        {
            return id_;
        }

        const UUID& GetUuid() const
        {
            return uuid;
        }

        const NetworkPosition GetPos() const
        {
            return pos;
        }

        const char GetDirection() const
        {
            return direction;
        }

#if PROTOCOL_VERSION < 353
        const std::string GetTitle() const
        {
            return title;
        }
#else
        const int GetMotive() const
        {
            return motive;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<VarInt>(iter, length);
            uuid = ReadData<UUID>(iter, length);
#if PROTOCOL_VERSION < 353
            title = ReadData<std::string>(iter, length);
#else
            motive = ReadData<VarInt>(iter, length);
#endif
            pos = ReadData<NetworkPosition>(iter, length);
            direction = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(id_, container);
            WriteData<UUID>(uuid, container);
#if PROTOCOL_VERSION < 353
            WriteData<std::string>(title, container);
#else
            WriteData<VarInt>(motive, container);
#endif
            WriteData<NetworkPosition>(pos, container);
            WriteData<char>(direction, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["id_"] = id_;
            output["uuid"] = uuid;
#if PROTOCOL_VERSION < 353
            output["title"] = title;
#else
            output["motive"] = motive;
#endif
            output["pos"] = pos.Serialize();
            output["direction"] = direction;

            return output;
        }

    private:
        int id_;
        UUID uuid;
        NetworkPosition pos;
        char direction;
#if PROTOCOL_VERSION < 353
        std::string title;
#else
        int motive;
#endif

    };
} //ProtocolCraft
#endif
