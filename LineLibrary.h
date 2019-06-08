//
// Created by Gururaj Sridhar on 2019-06-07.
//
#pragma once
#include<vector>

class Vector3;
class LineSegment;

//This is a static Helper library that does all the mathematical calculations
//It is a static library as there is no dependency and best to keep it loosely coupled
class LineLibrary {
public:
    //given two lines return a boolean if they intersect and accordingly return a point
    static bool getPointOfIntersection(const LineSegment& l1, const LineSegment& l2, Vector3& poi /*output*/);
    //check if two lines are parallel
    static bool isParallel(const LineSegment& l1, const LineSegment& l2);
    //given a list of line segments return a list of point of intersections
    static std::vector<Vector3> getPointsOfIntersection(const std::vector<LineSegment>& lines);
};
