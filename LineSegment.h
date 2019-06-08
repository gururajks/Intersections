//
// Created by Gururaj Sridhar on 2019-06-07.
//
#pragma once
#include"Vector3.h"

class Vector3;
class LineSegment
{
public:
    LineSegment() = delete;
    ~LineSegment() = default;
    LineSegment(const Vector3& pt1, const Vector3& pt2);
    inline Vector3 getStartPoint() const {return startPoint_;}
    inline Vector3 getEndPoint() const {return endPoint_;}
    inline double getSlope() const {return slope_;}

    LineSegment(LineSegment& other) = default;
    LineSegment(const LineSegment& other) = default;
    LineSegment(LineSegment&& other) = default;

private:
    double slope_;
    Vector3 startPoint_;
    Vector3 endPoint_;
};

