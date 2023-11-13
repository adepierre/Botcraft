#if PROTOCOL_VERSION > 759 /* > 1.19 */

#include "botcraft/Network/LastSeenMessagesTracker.hpp"

namespace Botcraft
{
    LastSeenMessagesTracker::LastSeenMessagesTracker()
    {
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        tail = 0;
        offset = 0;
#endif
    }

    LastSeenMessagesTracker::~LastSeenMessagesTracker()
    {

    }

    std::mutex& LastSeenMessagesTracker::GetMutex()
    {
        return mutex;
    }

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
    const std::vector<unsigned char>& LastSeenMessagesTracker::GetLastSignature() const
    {
        return last_signature_sent;
    }

    void LastSeenMessagesTracker::SetLastSignature(const std::vector<unsigned char>& last_signature_sent_)
    {
        last_signature_sent = last_signature_sent_;
    }

    void LastSeenMessagesTracker::AddSeenMessage(const std::vector<unsigned char>& signature, const ProtocolCraft::UUID& sender)
    {
        std::scoped_lock<std::mutex> lock_messages(mutex);

        ProtocolCraft::LastSeenMessagesEntry entry;
        entry.SetLastSignature(signature);
        entry.SetProfileId(sender);

        // Remove old messages from the same player
        int index = 0;
        while (index < last_seen.size())
        {
            if (last_seen[index].GetProfileId() == sender)
            {
                last_seen.erase(last_seen.begin() + index);
            }
            else
            {
                index += 1;
            }
        }

        // Push new header in front
        last_seen.push_front(entry);

        // Limit the size to 5 messages
        while (last_seen.size() > 5)
        {
            last_seen.pop_back();
        }
    }

    ProtocolCraft::LastSeenMessagesUpdate LastSeenMessagesTracker::GetLastSeenMessagesUpdate() const
    {
        ProtocolCraft::LastSeenMessagesUpdate last_seen_messages_update;
        last_seen_messages_update.SetLastSeen({ last_seen.begin(), last_seen.begin() + std::min(static_cast<int>(last_seen.size()), 5) });
        return last_seen_messages_update;
    }
#else
    std::pair<std::vector<std::vector<unsigned char>>, ProtocolCraft::LastSeenMessagesUpdate> LastSeenMessagesTracker::GetLastSeenMessagesUpdate()
    {
        std::scoped_lock<std::mutex> lock_messages(mutex);
        std::pair<std::vector<std::vector<unsigned char>>, ProtocolCraft::LastSeenMessagesUpdate> output;
        output.second.SetOffset(GetAndResetOffset());

        output.first.reserve(last_seen_signatures.size());
        std::bitset<20> bitset;
        for (size_t i = 0; i < last_seen_signatures.size(); ++i)
        {
            const size_t index = (tail + i) % last_seen_signatures.size();
            if (last_seen_signatures[index].empty())
            {
                continue;
            }
            bitset.set(i, true);
            output.first.push_back(last_seen_signatures[index]);
        }
        output.second.SetAcknowledged(bitset);

        return output;
    }

    void LastSeenMessagesTracker::AddSeenMessage(const std::vector<unsigned char>& signature)
    {
        last_seen_signatures[tail] = signature;
        tail = (tail + 1) % last_seen_signatures.size();
        offset += 1;
    }

    int LastSeenMessagesTracker::GetOffset() const
    {
        return offset;
    }
    
    int LastSeenMessagesTracker::GetAndResetOffset()
    {
        const int current_offset = offset;
        offset = 0;
        return current_offset;
    }
#endif
}
#endif
