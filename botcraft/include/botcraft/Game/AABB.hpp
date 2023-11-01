#pragma once

#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    class AABB
    {
    public:
        AABB(const Vector3<double>& center_, const Vector3<double>& half_size_);
        ~AABB();
        const Vector3<double> GetMin() const;
        const Vector3<double> GetMax() const;
        const Vector3<double>& GetCenter() const;
        const Vector3<double>& GetHalfSize() const;
        
        //Return whether or not these two AABB collides
        const bool Collide(const AABB& b) const;

        //Return the fraction (between 0 and 1) of the speed
        //that can be performed without collision with the given
        //AABB
        const double SweptCollide(const Vector3<double>& speed, const AABB& b, Vector3<double>& normal) const;

        const bool Intersect(const Vector3<double>& origin, const Vector3<double>& direction) const;

        bool operator<(const AABB& other) const;
        bool operator==(const AABB& other) const;

        template <typename T>
        friend AABB operator+(AABB box, const Vector3<T>& offset)
        {
            box.center.x += offset.x;
            box.center.y += offset.y;
            box.center.z += offset.z;

            return box;
        }


    private:
        Vector3<double> center;
        Vector3<double> half_size;
    };
} // Botcraft