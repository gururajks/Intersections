//
// Created by Gururaj Sridhar on 2019-06-07.
//

#include "LineSegment.h"
#include <limits>
#include "Vector3.h"

/*
 * Calculate the slope when the line is constructed
 */
LineSegment::LineSegment(const Vector3& pt1, const Vector3& pt2) : startPoint_(pt1), endPoint_(pt2)
{
    //vertical lines .. slope is max
    if(endPoint_.x_ == startPoint_.x_)
        slope_ = std::numeric_limits<double>::max();
    else
        slope_ = (endPoint_.y_ - startPoint_.y_) / (endPoint_.x_ -  startPoint_.x_);
    intercept_ = -(slope_ * startPoint_.x_) + startPoint_.y_;
}


LineSegment& LineSegment::operator=(LineSegment& other)
{
    if(this == &other)
        return *this;
    slope_ = other.getSlope();
    intercept_ = other.getIntercept();
    startPoint_ = other.getStartPoint();
    endPoint_ = other.getEndPoint();
    return *this;
}

LineSegment& LineSegment::operator=(const LineSegment& other)
{
    if(this == &other)
        return *this;
    slope_ = other.getSlope();
    intercept_ = other.getIntercept();
    startPoint_ = other.getStartPoint();
    endPoint_ = other.getEndPoint();
    return *this;
}

LineSegment::LineSegment(LineSegment& other) : LineSegment(other.getStartPoint(), other.getEndPoint())
{
    slope_ = other.getSlope();
    intercept_ = other.getIntercept();
}

LineSegment::LineSegment(const LineSegment& other) : LineSegment(other.getStartPoint(), other.getEndPoint())
{
    slope_ = other.getSlope();
    intercept_ = other.getIntercept();
}
