#pragma once

#include <vector>
#include <string>
#include <memory>

namespace Botcraft
{
    namespace Renderer
    {
        struct IMatrix;

        class Transformation
        {
        public:
            virtual void ApplyTransformation(IMatrix& m) const = 0;
            virtual const std::string Print() const = 0;
        };

        class Translation : public Transformation
        {
        public:
            Translation(const float x_ = 0.0f, const float y_ = 0.0f, const float z_ = 0.0f);
            virtual void ApplyTransformation(IMatrix& m) const override;

            const virtual std::string Print() const override;

            float x;
            float y;
            float z;
        };

        class Rotation : public Transformation
        {
        public:
            Rotation(const float axis_x_ = 0.0f, const float axis_y_ = 0.0f, const float axis_z_ = 0.0f, const float deg_angle_ = 0.0f);
            virtual void ApplyTransformation(IMatrix& m) const override;

            const virtual std::string Print() const override;

            float axis_x;
            float axis_y;
            float axis_z;
            float deg_angle;
        };

        class Scale : public Transformation
        {
        public:
            Scale(const float axis_x_ = 1.0f, const float axis_y_ = 1.0f, const float axis_z_ = 1.0f);
            virtual void ApplyTransformation(IMatrix& m) const override;

            const virtual std::string Print() const override;

            float axis_x;
            float axis_y;
            float axis_z;
        };

        typedef std::shared_ptr<Transformation> TransformationPtr;
        typedef std::shared_ptr<Scale> ScalePtr;

        struct FaceTransformation
        {
            std::vector<ScalePtr> scales;
            std::vector<TransformationPtr> rotations;
            std::vector<TransformationPtr> translations;

            //Textures transformations
            //Steps of 90° (0, 90°, 180°, 270°)
            unsigned char rotation = 0;

            //In 1/16th of the image
            float offset_x1 = 0;
            float offset_y1 = 0;
            float offset_x2 = 16;
            float offset_y2 = 16;
        };
    } // Renderer
} // Botcraft
