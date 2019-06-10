//
// Created by Gururaj Sridhar on 2019-06-07.
//

#ifndef INTERSECTIONS_VECTOR3_H
#define INTERSECTIONS_VECTOR3_H

class Vector3
{
public:
    Vector3() = delete;
    Vector3(float x, float y, float z) : x_(x), y_(y), z_(z) {}

    Vector3(Vector3& other) : x_(other.x_) , y_(other.y_), z_(other.z_)
    {
    }

    Vector3(const Vector3& other)  : x_(other.x_) , y_(other.y_), z_(other.z_)
    {
    }

    Vector3& operator=(Vector3& other)
    {
        if(this == &other)
            return *this;
        this->x_ = other.x_;
        this->y_ = other.y_;
        this->z_ = other.z_;
        return *this;
    }

    Vector3& operator=(const Vector3& other)
    {
        if(this == &other)
            return *this;
        this->x_ = other.x_;
        this->y_ = other.y_;
        this->z_ = other.z_;
        return *this;
    }

    bool operator==(Vector3& other) const
    {
        return this->x_ == other.x_ && this->y_ == other.y_ && this->z_ == other.z_;
    }

    bool operator != (Vector3& other) const
    {
        return this->x_ != other.x_ || this->y_ != other.y_ || this->z_ != other.z_;
    }

    bool operator==(const Vector3& other) const
    {
        return this->x_ == other.x_ && this->y_ == other.y_ && this->z_ == other.z_;
    }

    float x_ = 0.0;
    float y_ = 0.0;
    float z_ = 0.0;
};

#endif //INTERSECTIONS_VECTOR3_H
