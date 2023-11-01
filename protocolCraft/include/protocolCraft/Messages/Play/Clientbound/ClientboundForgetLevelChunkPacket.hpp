#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/Types/ChunkPos.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundForgetLevelChunkPacket : public BaseMessage<ClientboundForgetLevelChunkPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x1F;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Forget Level Chunk";

        virtual ~ClientboundForgetLevelChunkPacket() override
        {

        }

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        void SetX(const int x_)
        {
            x = x_;
        }

        void SetZ(const int z_)
        {
            z = z_;
        }
#else
        void SetPos(const ChunkPos& pos_)
        {
            pos = pos_;
        }
#endif

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        int GetX() const
        {
            return x;
        }

        int GetZ() const
        {
            return z;
        }
#else
        const ChunkPos& GetPos() const
        {
            return pos;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            x = ReadData<int>(iter, length);
            z = ReadData<int>(iter, length);
#else
            pos = ReadData<ChunkPos>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            WriteData<int>(x, container);
            WriteData<int>(z, container);
#else
            WriteData<ChunkPos>(pos, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
            output["x"] = x;
            output["z"] = z;
#else
            output["pos"] = pos;
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        int x = 0;
        int z = 0;
#else
        ChunkPos pos;
#endif
    };
} //ProtocolCraft
