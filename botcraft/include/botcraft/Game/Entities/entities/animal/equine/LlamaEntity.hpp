#pragma once

#include "botcraft/Game/Entities/entities/animal/equine/AbstractChestedHorseEntity.hpp"

namespace Botcraft
{
    class LlamaEntity : public AbstractChestedHorseEntity
    {
    protected:
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static constexpr int metadata_count = 3;
#else
        static constexpr int metadata_count = 2;
#endif
        static const std::array<std::string, metadata_count> metadata_names;
        static constexpr int hierarchy_metadata_count = AbstractChestedHorseEntity::metadata_count + AbstractChestedHorseEntity::hierarchy_metadata_count;

    public:
        LlamaEntity();
        virtual ~LlamaEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();


        virtual ProtocolCraft::Json::Value Serialize() const override;

        // Metadata stuff
        virtual void SetMetadataValue(const int index, const std::any& value) override;

        int GetDataStrengthId() const;
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        int GetDataSwagId() const;
#endif
        int GetDataVariantId() const;

        void SetDataStrengthId(const int data_strength_id);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        void SetDataSwagId(const int data_swag_id);
#endif
        void SetDataVariantId(const int data_variant_id);

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
