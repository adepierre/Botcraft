#include "botcraft/Game/Physics/AABB.hpp"

#include <algorithm>

namespace Botcraft
{
    AABB::AABB(const Vector3<double>& center_, const Vector3<double>& half_size_)
    {
        center = center_;
        half_size = half_size_;
    }

    AABB::~AABB()
    {

    }

    Vector3<double> AABB::GetMin() const
    {
        return center - half_size;
    }

    Vector3<double> AABB::GetMax() const
    {
        return center + half_size;
    }

    const Vector3<double>& AABB::GetCenter() const
    {
        return center;
    }

    const Vector3<double>& AABB::GetHalfSize() const
    {
        return half_size;
    }

    bool AABB::Collide(const AABB& b) const
    {
        bool x = std::abs(center.x - b.center.x) <= (half_size.x + b.half_size.x);
        bool y = std::abs(center.y - b.center.y) <= (half_size.y + b.half_size.y);
        bool z = std::abs(center.z - b.center.z) <= (half_size.z + b.half_size.z);

        return x && y && z;
    }

    bool AABB::Intersect(const Vector3<double>& origin, const Vector3<double>& direction) const
    {
        double tmin = -std::numeric_limits<float>::max();
        double tmax = std::numeric_limits<float>::max();

        Vector3<double> t1 = center - half_size - origin;
        Vector3<double> t2 = center + half_size - origin;

        for (int i = 0; i < 3; ++i)
        {
            if (direction[i] != 0.0)
            {
                double ti1 = t1[i] / direction[i];
                double ti2 = t2[i] / direction[i];

                tmin = std::max(tmin, std::min(ti1, ti2));
                tmax = std::min(tmax, std::max(ti1, ti2));
            }
        }

        return tmin <= tmax;
    }

    void AABB::Inflate(const double d)
    {
        half_size += d;
    }

    void AABB::Translate(const Vector3<double>& t)
    {
        center += t;
    }

    bool AABB::operator<(const AABB& other) const
    {
        return center < other.center ||
            (center == other.center && half_size < other.half_size);
    }

    bool AABB::operator==(const AABB& other) const
    {
        return center == other.center && half_size == other.half_size;
    }
} // Botcraft
