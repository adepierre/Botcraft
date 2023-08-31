#if PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundAddPaintingPacket : public BaseMessage<ClientboundAddPaintingPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */ || PROTOCOL_VERSION == 393 /* 1.13 */ ||  \
      PROTOCOL_VERSION == 401 /* 1.13.1 */ || PROTOCOL_VERSION == 404 /* 1.13.2 */ ||  \
      PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x03;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Add Painting";

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

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }

        void SetDirection(const char direction_)
        {
            direction = direction_;
        }

#if PROTOCOL_VERSION < 353 /* < 1.13 */
        void SetTitle(const std::string& title_)
        {
            title = title_;
        }
#else
        void SetMotive(const int motive_)
        {
            motive = motive_;
        }
#endif



        int GetId_() const
        {
            return id_;
        }

        const UUID& GetUuid() const
        {
            return uuid;
        }

        const NetworkPosition& GetPos() const
        {
            return pos;
        }

        char GetDirection() const
        {
            return direction;
        }

#if PROTOCOL_VERSION < 353 /* < 1.13 */
        const std::string& GetTitle() const
        {
            return title;
        }
#else
        int GetMotive() const
        {
            return motive;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<VarInt>(iter, length);
            uuid = ReadData<UUID>(iter, length);
#if PROTOCOL_VERSION < 353 /* < 1.13 */
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
#if PROTOCOL_VERSION < 353 /* < 1.13 */
            WriteData<std::string>(title, container);
#else
            WriteData<VarInt>(motive, container);
#endif
            WriteData<NetworkPosition>(pos, container);
            WriteData<char>(direction, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["id_"] = id_;
            output["uuid"] = uuid;
#if PROTOCOL_VERSION < 353 /* < 1.13 */
            output["title"] = title;
#else
            output["motive"] = motive;
#endif
            output["pos"] = pos;
            output["direction"] = direction;

            return output;
        }

    private:
        int id_ = 0;
        UUID uuid = {};
        NetworkPosition pos;
        char direction = 0;
#if PROTOCOL_VERSION < 353 /* < 1.13 */
        std::string title;
#else
        int motive = 0;
#endif

    };
} //ProtocolCraft
#endif
