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
    float x_ = 0.0;
    float y_ = 0.0;
    float z_ = 0.0;
};

#endif //INTERSECTIONS_VECTOR3_H
