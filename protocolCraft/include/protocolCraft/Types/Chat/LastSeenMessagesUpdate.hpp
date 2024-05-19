#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once


#include "protocolCraft/NetworkType.hpp"

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include <vector>

#include "protocolCraft/Types/Chat/LastSeenMessagesEntry.hpp"
#endif

namespace ProtocolCraft
{
    class LastSeenMessagesUpdate : public NetworkType
    {
    public:
        virtual ~LastSeenMessagesUpdate() override
        {

        }


#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        void SetLastSeen(const std::vector<LastSeenMessagesEntry>& last_seen_)
        {
            last_seen = last_seen_;
        }

        void SetLastReceived(const std::optional<LastSeenMessagesEntry>& last_received_)
        {
            last_received = last_received_;
        }
#else
        void SetOffset(const int offset_)
        {
            offset = offset_;
        }

        void SetAcknowledged(const std::bitset<20>& acknowledged_)
        {
            acknowledged = acknowledged_;
        }
#endif


#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        const std::vector<LastSeenMessagesEntry>& GetLastSeen() const
        {
            return last_seen;
        }

        const std::optional<LastSeenMessagesEntry>& GetLastReceived() const
        {
            return last_received;
        }
#else
        int GetOffset() const
        {
            return offset;
        }

        const std::bitset<20>& GetAcknowledged() const
        {
            return acknowledged;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            last_seen = ReadData<std::vector<LastSeenMessagesEntry>>(iter, length);
            last_received = ReadData<std::optional<LastSeenMessagesEntry>>(iter, length);
#else
            offset = ReadData<VarInt>(iter, length);
            acknowledged = ReadData<std::bitset<20>>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            WriteData<std::vector<LastSeenMessagesEntry>>(last_seen, container);
            WriteData<std::optional<LastSeenMessagesEntry>>(last_received, container);
#else
            WriteData<VarInt>(offset, container);
            WriteData<std::bitset<20>>(acknowledged, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            output["last_seen"] = last_seen;
            if (last_received.has_value())
            {
                output["last_received"] = last_received.value();
            }
#else
            output["offset"] = offset;
            output["acknowledged"] = acknowledged.to_string();
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        std::vector<LastSeenMessagesEntry> last_seen;
        std::optional<LastSeenMessagesEntry> last_received;
#else
        int offset = 0;
        std::bitset<20> acknowledged;
#endif
    };
} // ProtocolCraft
#endif
