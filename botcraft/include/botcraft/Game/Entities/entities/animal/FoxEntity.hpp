#if PROTOCOL_VERSION > 404
#pragma once

#include "botcraft/Game/Entities/entities/animal/AnimalEntity.hpp"

namespace Botcraft
{
    class FoxEntity : public AnimalEntity
    {
    protected:
        static constexpr int metadata_count = 4;
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AnimalEntity::metadata_count + AnimalEntity::hierarchy_metadata_count;

    public:
        FoxEntity();
        virtual ~FoxEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataTypeId() const;
        char GetDataFlagsId() const;
        const std::optional<ProtocolCraft::UUID>& GetDataTrustedId0() const;
        const std::optional<ProtocolCraft::UUID>& GetDataTrustedId1() const;

        void SetDataTypeId(const int data_type_id);
        void SetDataFlagsId(const char data_flags_id);
        void SetDataTrustedId0(const std::optional<ProtocolCraft::UUID>& data_trusted_id_0);
        void SetDataTrustedId1(const std::optional<ProtocolCraft::UUID>& data_trusted_id_1);

    };
}
#endif
