#pragma once

#if PROTOCOL_VERSION > 385

#if PROTOCOL_VERSION > 755
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
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x0c;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x0B;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x0E;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Edit Book";

        virtual ~ServerboundEditBookPacket() override
        {

        }

#if PROTOCOL_VERSION < 756
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

#if PROTOCOL_VERSION > 393
        void SetSlot(const int slot_)
        {
            slot = slot_;
        }
#endif


#if PROTOCOL_VERSION < 756
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

#if PROTOCOL_VERSION > 393
        int GetSlot() const
        {
            return slot;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 756
            book = ReadData<Slot>(iter, length);
            signing = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 393
            slot = ReadData<VarInt>(iter, length);
#endif
#if PROTOCOL_VERSION > 755
            pages = ReadVector<std::string>(iter, length);
            title = ReadOptional<std::string>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 756
            WriteData<Slot>(book, container);
            WriteData<bool>(signing, container);
#endif
#if PROTOCOL_VERSION > 393
            WriteData<VarInt>(slot, container);
#endif
#if PROTOCOL_VERSION > 755
            WriteVector<std::string>(pages, container);
            WriteOptional<std::string>(title, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 756
            output["book"] = book;
            output["signing"] = signing;
#endif
#if PROTOCOL_VERSION > 393
            output["slot"] = slot;
#endif
#if PROTOCOL_VERSION > 755
            output["pages"] = pages;

            if (title.has_value())
            {
                output["title"] = title.value();
            }
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 756
        Slot book;
        bool signing;
#else
        std::vector<std::string> pages;
        std::optional<std::string> title;
#endif
#if PROTOCOL_VERSION > 393
        int slot;
#endif

    };
} //ProtocolCraft
#endif
