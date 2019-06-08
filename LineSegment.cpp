//
// Created by Gururaj Sridhar on 2019-06-07.
//

#include "LineSegment.h"
#include <limits>
#include "Vector3.h"

LineSegment::LineSegment(const Vector3& pt1, const Vector3& pt2) : startPoint_(pt1), endPoint_(pt2)
{
    //vertical lines .. slope is max
    if(endPoint_.x_ == startPoint_.x_)
        slope_ = std::numeric_limits<double>::max();
    else
        slope_ = (endPoint_.y_ - startPoint_.y_) / (endPoint_.x_ -  startPoint_.x_);
}
