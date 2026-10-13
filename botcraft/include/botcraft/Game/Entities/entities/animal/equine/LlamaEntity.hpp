#pragma once

#include "botcraft/Game/Entities/entities/animal/equine/AbstractChestedHorseEntity.hpp"

namespace Botcraft
{
    class LlamaEntity : public AbstractChestedHorseEntity
    {
    private:
        static constexpr std::array metadata_names{
            std::string_view("data_strength_id"),
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
            std::string_view("data_swag_id"),
#endif
            std::string_view("data_variant_id"),
        };
    protected:
        static constexpr int metadata_count = static_cast<int>(metadata_names.size());
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
