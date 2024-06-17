#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include <vector>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class LastSeenMessagesEntry : public NetworkType
    {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (UUID,      std::vector<unsigned char>),
            (ProfileId, LastSignature)
        );
        DECLARE_READ_WRITE_SERIALIZE;
#else
        DECLARE_FIELDS(
            (VarInt, std::optional<std::vector<unsigned char>>),
            (Id,     LastSignature)
        );
        DECLARE_SERIALIZE;
#endif


#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        GETTER_SETTER(ProfileId);
#else
        GETTER_SETTER(Id);
#endif
        GETTER_SETTER(LastSignature);

    protected:
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetId(ReadData<VarInt>(iter, length) - 1);
            if (GetId() == -1)
            {
                SetLastSignature(ReadByteArray(iter, length, 256));
            }
            else
            {
                SetLastSignature({});
            }
        }
#endif

#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(GetId() + 1, container);
            if (GetLastSignature().has_value())
            {
                WriteByteArray(GetLastSignature().value(), container);
            }
        }
#endif
    };
} // ProtocolCraft
#endif
