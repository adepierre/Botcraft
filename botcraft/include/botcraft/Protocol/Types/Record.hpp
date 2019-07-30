#pragma once

#include <string>

#include "botcraft/Protocol/NetworkType.hpp"

namespace Botcraft
{
    class Record : public NetworkType
    {
    public:
        void SetHorizontalPosition(const unsigned char h)
        {
            horizontal_position = h;
        }
        
        void SetYCoordinate(const unsigned char y)
        {
            y_coordinate = y;
        }
        
        void SetBlockId(const int i)
        {
            block_id = i;
        }
    
    
        const unsigned char GetHorizontalPosition() const
        {
            return horizontal_position;
        }
        
        const unsigned char GetYCoordinate() const
        {
            return y_coordinate;
        }
        
        const int GetBlockId() const
        {
            return block_id;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            horizontal_position = ReadData<unsigned char>(iter, length);
            y_coordinate = ReadData<unsigned char>(iter, length);
            block_id = ReadVarInt(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<unsigned char>(horizontal_position, container);
            WriteData<unsigned char>(y_coordinate, container);
            WriteVarInt(block_id, container);
        }

    private:
        unsigned char horizontal_position;
        unsigned char y_coordinate;
        int block_id;
    };
}