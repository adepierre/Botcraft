#pragma once

#if PROTOCOL_VERSION > 385 /* > 1.12.2 */

#if PROTOCOL_VERSION > 755 /* > 1.17 */
#include <vector>
#include <string>
#endif

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft
{
    class ServerboundEditBookPacket : public BaseMessage<ServerboundEditBookPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x0c;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */ || PROTOCOL_VERSION == 735 /* 1.16 */ ||  \
      PROTOCOL_VERSION == 736 /* 1.16.1 */ || PROTOCOL_VERSION == 751 /* 1.16.2 */ ||  \
      PROTOCOL_VERSION == 753 /* 1.16.3 */ || PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x11;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Edit Book";

        virtual ~ServerboundEditBookPacket() override
        {

        }

#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
        void SetBook(const Slot& book_)
        {
            book = book_;
        }

        void SetSigning(const bool signing_)
        {
            signing = signing_;
        }
#else
        void SetPages(const std::vector<std::string>& pages_)
        {
            pages = pages_;
        }

        void SetTitle(const std::optional<std::string>& title_)
        {
            title = title_;
        }
#endif

#if PROTOCOL_VERSION > 393 /* > 1.13 */
        void SetSlot(const int slot_)
        {
            slot = slot_;
        }
#endif


#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
        const Slot& GetBook() const
        {
            return book;
        }

        bool GetSigning() const
        {
            return signing;
        }
#else        
        const std::vector<std::string>& GetPages() const
        {
            return pages;
        }

        const std::optional<std::string>& GetTitle() const
        {
            return title;
        }
#endif

#if PROTOCOL_VERSION > 393 /* > 1.13 */
        int GetSlot() const
        {
            return slot;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
            book = ReadData<Slot>(iter, length);
            signing = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 393 /* > 1.13 */
            slot = ReadData<VarInt>(iter, length);
#endif
#if PROTOCOL_VERSION > 755 /* > 1.17 */
            pages = ReadVector<std::string>(iter, length);
            title = ReadOptional<std::string>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
            WriteData<Slot>(book, container);
            WriteData<bool>(signing, container);
#endif
#if PROTOCOL_VERSION > 393 /* > 1.13 */
            WriteData<VarInt>(slot, container);
#endif
#if PROTOCOL_VERSION > 755 /* > 1.17 */
            WriteVector<std::string>(pages, container);
            WriteOptional<std::string>(title, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
            output["book"] = book;
            output["signing"] = signing;
#endif
#if PROTOCOL_VERSION > 393 /* > 1.13 */
            output["slot"] = slot;
#endif
#if PROTOCOL_VERSION > 755 /* > 1.17 */
            output["pages"] = pages;

            if (title.has_value())
            {
                output["title"] = title.value();
            }
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 756 /* < 1.17.1 */
        Slot book;
        bool signing = false;
#else
        std::vector<std::string> pages;
        std::optional<std::string> title;
#endif
#if PROTOCOL_VERSION > 393 /* > 1.13 */
        int slot = 0;
#endif

    };
} //ProtocolCraft
#endif
