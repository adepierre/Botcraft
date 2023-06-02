#pragma once

namespace ProtocolCraft
{
    class PluginObject
    {
    public:
        virtual ~PluginObject() { }

        /// @brief Deserialize raw data into this object
        /// @param ptr Pointer to the start of the data
        /// @param length Available data, will be updated with data read
        virtual void Read(const unsigned char* ptr, unsigned long long int& length) = 0;

        /// @brief Write this object into raw data
        /// @param size Will be assigned to the data size
        /// @return A pointer to the serialized data
        virtual const unsigned char* Write(unsigned long long int& size) = 0;

        /// @brief Serialize this object into a null terminated json string
        /// @return A pointer to the start of the string
        virtual const char* Serialize() = 0;
    };
}
