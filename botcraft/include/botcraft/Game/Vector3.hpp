#pragma once

#include <ostream>
#include <cassert>

#include <nlohmann/json.hpp>

#include "protocolCraft/Types/NetworkPosition.hpp"

namespace Botcraft
{
    template <typename T>
    struct Vector3
    {
        Vector3()
        {
            x = T(0);
            y = T(0);
            z = T(0);
        }

        Vector3(const T& x_, const T& y_, const T& z_)
        {
            x = x_;
            y = y_;
            z = z_;
        }

        Vector3(const ProtocolCraft::NetworkPosition& position)
        {
            x = position.GetX();
            y = position.GetY();
            z = position.GetZ();
        }

        Vector3(const Vector3<int>& position)
        {
            x = position.x;
            y = position.y;
            z = position.z;
        }

        T x;
        T y;
        T z;

        Vector3 operator+(const Vector3 &a) const
        {
            return Vector3(a.x + x, a.y + y, a.z + z);
        }

        Vector3 operator-(const Vector3 &a) const
        {
            return Vector3(x - a.x, y - a.y, z - a.z);
        }

        const bool operator==(const Vector3 &a) const
        {
            return (x == a.x) && (y == a.y) && (z == a.z);
        }

        const bool operator!=(const Vector3 &a) const
        {
            return (x != a.x) || (y != a.y) || (z != a.z);
        }

        const bool operator<(const Vector3 &a) const
        {
            return (x < a.x) ||
                (x == a.x && y < a.y) ||
                (x == a.x && y == a.y && z < a.z);
        }

        Vector3 operator*(const T d) const
        {
            return Vector3(x * d, y * d, z * d);
        }

        Vector3 operator-(const T d) const
        {
            return Vector3(x - d, y - d, z - d);
        }

        Vector3 operator+(const T d) const
        {
            return Vector3(x + d, y + d, z + d);
        }

        Vector3 operator/(const T d) const
        {
            return Vector3(x / d, y / d, z / d);
        }

        const double dot(const Vector3 &v) const
        {
            double output = 0.0;
            output += x * v.x;
            output += y * v.y;
            output += z * v.z;
            return output;
        }

        T& operator[] (const int i)
        {
            assert(i > -1);
            assert(i < 3);
            switch (i)
            {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            case 2:
                return z;
                break;
            }
            // This doesn't happen
            return x;
        }

        const T& operator[] (const int i) const
        {
            assert(i > -1);
            assert(i < 3);
            switch (i)
            {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            case 2:
                return z;
                break;
            }
            // This doesn't happen
            return x;
        }

        void Normalize()
        {
            double norm = sqrt(x * x + y * y + z * z);
            x /= norm;
            y /= norm;
            z /= norm;
        }

        friend std::ostream& operator << (std::ostream &o, const Vector3 &vec)
        {
            o << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
            return o;
        }

        const nlohmann::json Serialize() const
        {
            return nlohmann::json({ x, y, z });
        }

        const ProtocolCraft::NetworkPosition ToNetworkPosition() const
        {
            ProtocolCraft::NetworkPosition output;
            output.SetX(x);
            output.SetY(y);
            output.SetZ(z);

            return output;
        }
    };
    typedef Vector3<int> Position;
} // Botcraft

namespace std
{
    template <typename T>
    struct hash<Botcraft::Vector3<T> > 
    {
        inline size_t operator()(const Botcraft::Vector3<T> &v) const
        {
            std::hash<T> hasher;
            size_t value = hasher(v.x);
            value ^= hasher(v.y) + 0x9e3779b9 + (value << 6) + (value >> 2);
            value ^= hasher(v.z) + 0x9e3779b9 + (value << 6) + (value >> 2);
            return value;
        }
    };
}