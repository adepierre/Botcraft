#include "protocolCraft/Utilities/GZip.hpp"
#include "protocolCraft/BinaryReadWrite.hpp"

#include <stdexcept>

#if USE_COMPRESSION
#include <zlib.h>
#endif

namespace ProtocolCraft
{
    std::vector<unsigned char> ExtractGZip(ReadIterator& iter, size_t& length)
    {
#if USE_COMPRESSION
        unsigned long size_to_decompress = static_cast<unsigned long>(length);

        std::vector<unsigned char> decompressed_data(size_to_decompress);
        decompressed_data.reserve(size_to_decompress);

        z_stream strm;
        memset(&strm, 0, sizeof(strm));
        strm.next_in = const_cast<unsigned char*>(&(*iter));
        strm.avail_in = size_to_decompress;
        strm.next_out = decompressed_data.data();
        strm.avail_out = static_cast<unsigned int>(decompressed_data.size());

        int res = inflateInit2(&strm, 16 + MAX_WBITS); // 16 + MAX_WBITS to set zlib to gzip mode
        if (res != Z_OK)
        {
            throw std::runtime_error("inflateInit failed: " + std::string(strm.msg));
        }

        while (true)
        {
            if (strm.total_out >= decompressed_data.size())
            {
                decompressed_data.resize(decompressed_data.size() + length / 2);
            }
            strm.next_out = decompressed_data.data() + strm.total_out;
            strm.avail_out = decompressed_data.size() - strm.total_out;

            res = inflate(&strm, Z_SYNC_FLUSH);
            if (res == Z_STREAM_END)
            {
                break;
            }
            else if (res != Z_OK)
            {
                inflateEnd(&strm);
                throw std::runtime_error("Inflate decompression failed: " + std::string(strm.msg));
            }
        }

        if (inflateEnd(&strm) != Z_OK)
        {
            throw std::runtime_error("inflateEnd failed: " + std::string(strm.msg));
        }

        iter += strm.total_in;
        length -= strm.total_in;
        decompressed_data.resize(strm.total_out);

        return decompressed_data;
#else
        throw std::runtime_error("ProtocolCraft compiled without GZIP support");
#endif
    }
}
