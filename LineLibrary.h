//
// Created by Gururaj Sridhar on 2019-06-07.
//
#pragma once
#include<vector>
#include<queue>
#include "Vector3.h"
#include<map>
class Vector3;
class LineSegment;

class Event
{
public:
    enum EventType {
        BEGIN,
        END,
        CROSS
    };
    Event(Vector3 point, EventType event, int lineId) : point_(point), event_(event), lineId_(lineId) {}
    Vector3 point_;
    EventType event_;
    int lineId_;
    std::pair<int, int> crossOver;
};


class cp
{
public:
    bool operator()(const Event& lhs, const Event& rhs)
    {
        return lhs.point_.x_ > rhs.point_.x_;
    }
};

//This is a  Helper library that does all the mathematical calculations
class LineLibrary {
public:
    //given two lines return a boolean if they intersect and accordingly return a point
    bool getPointOfIntersection(const LineSegment& l1, const LineSegment& l2, Vector3& poi /*output*/);
    //check if two lines are parallel
    bool isParallel(const LineSegment& l1, const LineSegment& l2);
    bool doIntersect(Vector3 p1, Vector3 q1, Vector3 p2, Vector3 q2);
    float orientation(Vector3 a, Vector3 b, Vector3 c);
    bool onSegment(Vector3 p, Vector3 q, Vector3 r);
    //given a list of line segments return a list of point of intersections
    std::vector<Vector3> getPointsOfIntersection(const std::vector<LineSegment>& lines);

    //Uses Line sweep algorithm
    std::vector<Vector3> getEfficientPointsOfIntersection(std::vector<LineSegment>& lines);


    void deleteFromSweepLine(int lineId, std::vector<std::pair<int, LineSegment>> &sweepLine);
    std::vector<std::pair<int, LineSegment>>::iterator addSegmentIntoSweepLine(int lineId, const LineSegment &line,
                                                                               std::vector<std::pair<int, LineSegment>> &sweepLine,
                                                                               float xPosition);

    void checkIntersect(std::vector<std::pair<int, LineSegment>>::iterator line1,
                        std::vector<std::pair<int, LineSegment>>::iterator line2,
                        std::priority_queue<Event, std::vector<Event>, cp>& pq,
                        float xPosition );


};
