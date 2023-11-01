#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundChangeDifficultyPacket : public BaseMessage<ClientboundChangeDifficultyPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */ || PROTOCOL_VERSION == 393 /* 1.13 */ ||  \
      PROTOCOL_VERSION == 401 /* 1.13.1 */ || PROTOCOL_VERSION == 404 /* 1.13.2 */ ||  \
      PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 759 /* 1.19 */ || PROTOCOL_VERSION == 760 /* 1.19.1/2 */ ||  \
      PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x0B;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Change Difficulty";

        virtual ~ClientboundChangeDifficultyPacket() override
        {

        }

        void SetDifficulty(const int difficulty_)
        {
            difficulty = difficulty_;
        }

#if PROTOCOL_VERSION >= 477 /* >= 1.14 */
        void SetLocked(const bool locked_)
        {
            locked = locked_;
        }
#endif

        int GetDifficulty() const
        {
            return difficulty;
        }

#if PROTOCOL_VERSION >= 477 /* >= 1.14 */
        bool GetLocked() const
        {
            return locked;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            difficulty = ReadData<unsigned char>(iter, length);
#if PROTOCOL_VERSION >= 477 /* >= 1.14 */
            locked = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<unsigned char>((unsigned char)difficulty, container);
#if PROTOCOL_VERSION >= 477 /* >= 1.14 */
            WriteData<bool>(locked, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["difficulty"] = difficulty;
#if PROTOCOL_VERSION >= 477 /* >= 1.14 */
            output["locked"] = locked;
#endif

            return output;
        }

    private:
        int difficulty = 0;

#if PROTOCOL_VERSION >= 477 /* >= 1.14 */
        bool locked = false;
#endif
    };
} //ProtocolCraft
