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
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x0B;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x0c;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x0C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x0C;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x0C;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x0B;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x0B;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x0D;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x0E;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x0D;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Edit Book";
        }

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

        void SetTitle(const std::string& title_)
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

        const bool GetSigning() const
        {
            return signing;
        }
#else        
        const std::vector<std::string>& GetPages() const
        {
            return pages;
        }

        const std::string& GetTitle() const
        {
            return title;
        }
#endif

#if PROTOCOL_VERSION > 393
        const int GetSlot() const
        {
            return slot;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 756
            book.Read(iter, length);
            signing = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 393
            slot = ReadData<VarInt>(iter, length);
#endif
#if PROTOCOL_VERSION > 755
            int pages_size = ReadData<VarInt>(iter, length);
            pages = std::vector<std::string>(pages_size);
            for (int i = 0; i < pages_size; ++i)
            {
                pages[i] = ReadData<std::string>(iter, length);
            }
            bool has_title = ReadData<bool>(iter, length);
            if (has_title)
            {
                title = ReadData<std::string>(iter, length);
            }
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 756
            book.Write(container);
            WriteData<bool>(signing, container);
#endif
#if PROTOCOL_VERSION > 393
            WriteData<VarInt>(slot, container);
#endif
#if PROTOCOL_VERSION > 755
            WriteData<VarInt>(pages.size(), container);
            for (int i = 0; i < pages.size(); ++i)
            {
                WriteData<std::string>(pages[i], container);
            }
            WriteData<bool>(!title.empty(), container);
            if (!title.empty())
            {
                WriteData<std::string>(title, container);
            }
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

#if PROTOCOL_VERSION < 756
            output["book"] = book.Serialize();
            output["signing"] = signing;
#endif
#if PROTOCOL_VERSION > 393
            output["slot"] = slot;
#endif
#if PROTOCOL_VERSION > 755
            output["pages"] = pages;

            if (!title.empty())
            {
                output["title"] = title;
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
        std::string title;
#endif
#if PROTOCOL_VERSION > 393
        int slot;
#endif

    };
} //ProtocolCraft
#endif
