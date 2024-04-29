#pragma once

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#include "protocolCraft/NetworkType.hpp"

#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/GlobalPos.hpp"

namespace ProtocolCraft
{
    class CommonPlayerSpawnInfo : public NetworkType
    {
    public:
        virtual ~CommonPlayerSpawnInfo() override
        {

        }


        void SetDimension(const Identifier& dimension_)
        {
            dimension = dimension_;
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        void SetDimensionType(const Identifier& dimension_type_)
        {
            dimension_type = dimension_type_;
        }
#else
        void SetDimensionType(const int dimension_type_)
        {
            dimension_type = dimension_type_;
        }
#endif

        void SetSeed(const long long int seed_)
        {
            seed = seed_;
        }

        void SetGameType(const unsigned char game_type_)
        {
            game_type = game_type_;
        }

        void SetPreviousGameType(const unsigned char previous_game_type_)
        {
            previous_game_type = previous_game_type_;
        }

        void SetIsDebug(const bool is_debug_)
        {
            is_debug = is_debug_;
        }

        void SetIsFlat(const bool is_flat_)
        {
            is_flat = is_flat_;
        }

        void SetLastDeathLocation(const std::optional<GlobalPos>& last_death_location_)
        {
            last_death_location = last_death_location_;
        }

        void SetPortalCooldown(const int portal_cooldown_)
        {
            portal_cooldown = portal_cooldown_;
        }


#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        const Identifier& GetDimensionType() const
        {
            return dimension_type;
        }
#else
        int GetDimensionType() const
        {
            return dimension_type;
        }
#endif

        const Identifier& GetDimension() const
        {
            return dimension;
        }
        
        long long int GetSeed() const
        {
            return seed;
        }

        unsigned char GetGameType() const
        {
            return game_type;
        }

        unsigned char GetPreviousGameType() const
        {
            return previous_game_type;
        }

        bool GetIsDebug() const
        {
            return is_debug;
        }

        bool GetIsFlat() const
        {
            return is_flat;
        }

        const std::optional<GlobalPos>& GetLastDeathLocation() const
        {
            return last_death_location;
        }

        int GetPortalCooldown() const
        {
            return portal_cooldown;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            dimension_type = ReadData<Identifier>(iter, length);
#else
            dimension_type = ReadData<VarInt>(iter, length);
#endif
            dimension = ReadData<Identifier>(iter, length);
            seed = ReadData<long long int>(iter, length);
            game_type = ReadData<unsigned char>(iter, length);
            previous_game_type = ReadData<unsigned char>(iter, length);
            is_debug = ReadData<bool>(iter, length);
            is_flat = ReadData<bool>(iter, length);
            last_death_location = ReadOptional<GlobalPos>(iter, length);
            portal_cooldown = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            WriteData<Identifier>(dimension_type, container);
#else
            WriteData<VarInt>(dimension_type, container);
#endif
            WriteData<Identifier>(dimension, container);
            WriteData<long long int>(seed, container);
            WriteData<unsigned char>(game_type, container);
            WriteData<unsigned char>(previous_game_type, container);
            WriteData<bool>(is_debug, container);
            WriteData<bool>(is_flat, container);
            WriteOptional<GlobalPos>(last_death_location, container);
            WriteData<VarInt>(portal_cooldown, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["dimension_type"] = dimension_type;
            output["dimension"] = dimension;
            output["seed"] = seed;
            output["game_type"] = game_type;
            output["previous_game_type"] = previous_game_type;
            output["is_debug"] = is_debug;
            output["is_flat"] = is_flat;
            if (last_death_location.has_value())
            {
                output["last_death_location"] = last_death_location.value();
            }
            output["portal_cooldown"] = portal_cooldown;

            return output;
        }

    private:
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        Identifier dimension_type;
#else
        int dimension_type = 0;
#endif
        Identifier dimension;
        long long int seed = 0;
        unsigned char game_type = 0;
        unsigned char previous_game_type = 0;
        bool is_debug = false;
        bool is_flat = false;
        std::optional<GlobalPos> last_death_location;
        int portal_cooldown = 0;

    };
}
#endif
