#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include <mutex>
#include <vector>

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#include <deque>

#include "protocolCraft/Types/Chat/LastSeenMessagesEntry.hpp"
#else
#include <array>
#endif

#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"

namespace Botcraft
{
    class LastSeenMessagesTracker
    {
    public:
        LastSeenMessagesTracker();
        ~LastSeenMessagesTracker();

        std::mutex& GetMutex();

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        const std::vector<unsigned char>& GetLastSignature() const;
        void SetLastSignature(const std::vector<unsigned char>& last_signature_sent_);

        void AddSeenMessage(const std::vector<unsigned char>& signature, const ProtocolCraft::UUID& sender);

        ProtocolCraft::LastSeenMessagesUpdate GetLastSeenMessagesUpdate() const;
#else
        /// @brief Get both a vector of previous messages signatures and the LastSeenMessagesUpdate object
        /// @return A pair with both items
        std::pair<std::vector<std::vector<unsigned char>>, ProtocolCraft::LastSeenMessagesUpdate> GetLastSeenMessagesUpdate();

        void AddSeenMessage(const std::vector<unsigned char>& signature);

        int GetOffset() const;
        int GetAndResetOffset();
#endif

    private:
        std::mutex mutex;
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        std::vector<unsigned char> last_signature_sent;
        std::deque<ProtocolCraft::LastSeenMessagesEntry> last_seen;
#else
        /// @brief Circular buffer to store previously seen message signatures
        std::array<std::vector<unsigned char>, 20> last_seen_signatures;
        size_t tail;
        int offset;
#endif
    };
}
#endif