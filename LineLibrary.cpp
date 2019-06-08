//
// Created by Gururaj Sridhar on 2019-06-07.
//

#include<vector>
#include "LineSegment.h"
#include "LineLibrary.h"

bool LineLibrary::isParallel(const LineSegment &l1, const LineSegment &l2)
{
    return l1.getSlope() == l2.getSlope();
}

bool LineLibrary::getPointOfIntersection(const LineSegment& l1, const LineSegment& l2, Vector3& pointOfIntersection)
{
    if(isParallel(l1, l2)) return false;

    double poi_x = (l2.getStartPoint().y_ - l1.getStartPoint().y_ +
                 l1.getSlope() * l1.getStartPoint().x_ - l2.getSlope() * l2.getStartPoint().x_) / (l1.getSlope() - l2.getSlope());
    double poi_y = l1.getSlope() * (poi_x - l1.getStartPoint().x_) + l1.getStartPoint().y_;
    pointOfIntersection.x_ = poi_x;
    pointOfIntersection.y_ = poi_y;

    return true;
}

std::vector<Vector3> LineLibrary::getPointsOfIntersection(const std::vector<LineSegment>& lines)
{
    std::vector<Vector3> pointOfIntersections;
    for(int i = 0 ; i < lines.size(); i++)
    {
        for(int j = i + 1; j < lines.size(); j++)
        {
            Vector3 pointOfIntersection(0.0f, 0.0f, 0.0f);
            if(LineLibrary::getPointOfIntersection(lines[i], lines[j], pointOfIntersection))
                pointOfIntersections.push_back(pointOfIntersection);
        }
    }
    return pointOfIntersections;
}