#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
#include "protocolCraft/Types/Record.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSectionBlocksUpdatePacket : public BaseMessage<ClientboundSectionBlocksUpdatePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Section Blocks Update";

#if PROTOCOL_VERSION < 751 /* < 1.16.2 */
        DECLARE_FIELDS(
            (int,    int,    std::vector<Record>),
            (ChunkX, ChunkZ, Records)
        );
#elif PROTOCOL_VERSION < 763 /* < 1.20 */
        DECLARE_FIELDS(
            (long long int, bool,                 std::vector<short>, std::vector<int>),
            (SectionPos,    SuppressLightUpdates, Positions,          States)
        );
#else
        DECLARE_FIELDS(
            (long long int, std::vector<short>, std::vector<int>),
            (SectionPos,    Positions,          States)
        );
#endif
        DECLARE_SERIALIZE;

#if PROTOCOL_VERSION < 751 /* < 1.16.2 */
        GETTER_SETTER(ChunkX);
        GETTER_SETTER(ChunkZ);
        GETTER_SETTER(Records);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        GETTER_SETTER(SectionPos);
        GETTER_SETTER(Positions);
        GETTER_SETTER(States);
#endif
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */ && PROTOCOL_VERSION < 763 /* < 1.20 */
        GETTER_SETTER(SuppressLightUpdates);
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
            SetChunkX(ReadData<int>(iter, length));
            SetChunkZ(ReadData<int>(iter, length));
            SetRecords(ReadData<std::vector<Record>>(iter, length));
#else
            SetSectionPos(ReadData<long long int>(iter, length));
#if PROTOCOL_VERSION < 763 /* < 1.20 */
            SetSuppressLightUpdates(ReadData<bool>(iter, length));
#endif
            const std::vector<long long int> data = ReadData<std::vector<VarLong>>(iter, length);
            std::vector<short> positions(data.size());
            std::vector<int> states(data.size());
            for (size_t i = 0; i < data.size(); ++i)
            {
                positions[i] = static_cast<short>(data[i] & 0xFFFl);
                states[i] = static_cast<int>(data[i] >> 12);
            }
            SetPositions(positions);
            SetStates(states);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
            WriteData<int>(GetChunkX(), container);
            WriteData<int>(GetChunkZ(), container);
            WriteData<std::vector<Record>>(GetRecords(), container);
#else
            WriteData<long long int>(GetSectionPos(), container);
#if PROTOCOL_VERSION < 763 /* < 1.20 */
            WriteData<bool>(GetSuppressLightUpdates(), container);
#endif
            WriteData<VarInt>(static_cast<int>(GetPositions().size()), container);
            for (size_t i = 0; i < GetPositions().size(); ++i)
            {
                WriteData<VarLong>((static_cast<long long int>(GetStates()[i]) << 12) | static_cast<long long int>(GetPositions()[i]), container);
            }
#endif
        }
    };
}
