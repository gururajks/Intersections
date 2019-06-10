//
// Created by Gururaj Sridhar on 2019-06-07.
//
#pragma once
#include"Vector3.h"

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

    LineSegment(LineSegment& other)
    {
        startPoint_ = Vector3(other.getStartPoint().x_, other.getStartPoint().y_, other.getStartPoint().z_);
        slope_ = other.getSlope();
        endPoint_ = Vector3(other.getEndPoint().x_, other.getEndPoint().y_, other.getEndPoint().z_);
        intercept_ = other.getIntercept();
    }

    LineSegment(const LineSegment& other)
    {
        startPoint_ = Vector3(other.getStartPoint().x_, other.getStartPoint().y_, other.getStartPoint().z_);
        slope_ = other.getSlope();
        endPoint_ = Vector3(other.getEndPoint().x_, other.getEndPoint().y_, other.getEndPoint().z_);
        intercept_ = other.getIntercept();
    }


private:
    double slope_;
    Vector3 startPoint_;
    Vector3 endPoint_;
    double intercept_;
};

