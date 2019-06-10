//
// Created by Gururaj Sridhar on 2019-06-07.
//
#pragma once

#include "Vector3.h"

class Vector3;
class LineSegment
{
public:
    LineSegment() {}
    ~LineSegment() = default;
    LineSegment(const Vector3& pt1, const Vector3& pt2);
    inline Vector3 getStartPoint() const {return startPoint_;}
    inline Vector3 getEndPoint() const {return endPoint_;}
    inline double getSlope() const {return slope_;}
    inline double getIntercept() const { return intercept_; }

    LineSegment& operator=(LineSegment& other);
    LineSegment& operator=(const LineSegment& other);
    LineSegment(LineSegment& other);
    LineSegment(const LineSegment& other);

private:
    double slope_;
    Vector3 startPoint_;
    Vector3 endPoint_;
    double intercept_;
};

