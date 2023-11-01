#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include <vector>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class LastSeenMessagesEntry : public NetworkType
    {
    public:
        virtual ~LastSeenMessagesEntry() override
        {

        }


#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        void SetProfileId(const UUID& profile_id_)
        {
            profile_id = profile_id_;
        }
#else
        void SetId(const int id_)
        {
            id = id_;
        }
#endif

        void SetLastSignature(const std::vector<unsigned char>& last_signature_)
        {
            last_signature = last_signature_;
        }
    

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        const UUID& GetProfileId() const
        {
            return profile_id;
        }
#else
        int GetId() const
        {
            return id;
        }
#endif

        const std::vector<unsigned char>& GetLastSignature() const
        {
            return last_signature;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            profile_id = ReadData<UUID>(iter, length);
            last_signature = ReadVector<unsigned char>(iter, length);
#else
            id = ReadData<VarInt>(iter, length) - 1;
            if (id == -1)
            {
                last_signature = ReadByteArray(iter, length, 256);
            }
            else
            {
                last_signature.clear();
            }
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            WriteData<UUID>(profile_id, container);
            WriteVector<unsigned char>(last_signature, container);
#else
            WriteData<VarInt>(id + 1, container);
            if (last_signature.size() > 0)
            {
                WriteByteArray(last_signature, container);
            }
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
            output["profile_id"] = profile_id;
#else
            output["id"] = id;
#endif
            output["last_signature"] = "Vector of " + std::to_string(last_signature.size()) + " unsigned char";

            return output;
        }

    private:
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        UUID profile_id = {};
#else
        int id = 0;
#endif
        std::vector<unsigned char> last_signature;
    };
} // ProtocolCraft
#endif
