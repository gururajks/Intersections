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



class event_less
{
public:
    bool operator()(const std::pair<double, int> & a, const std::pair<double, int> & b) const
    {
        if (a.first < b.first - 1.0e-9)
            return true;
        else if (a.first > b.first + 1.0e-9)
            return false;
        else if (a.second < b.second)
            return true;
        return false;
    }
};


//This is a static Helper library that does all the mathematical calculations
//It is a static library as there is no dependency and best to keep it loosely coupled
class LineLibrary {
public:
    //given two lines return a boolean if they intersect and accordingly return a point
    bool getPointOfIntersection(const LineSegment& l1, const LineSegment& l2, Vector3& poi /*output*/);
    //check if two lines are parallel
    bool isParallel(const LineSegment& l1, const LineSegment& l2);
    //given a list of line segments return a list of point of intersections
    std::vector<Vector3> getPointsOfIntersection(const std::vector<LineSegment>& lines);
    std::vector<Vector3> getEffPointsOfIntersection(std::vector<LineSegment>& lines);
    bool onSegment(Vector3 p, Vector3 q, Vector3 r);
    void deleteFromSegmentList(int lineId, std::vector<std::pair<int, LineSegment>>& sweepLine);
    std::vector<std::pair<int, LineSegment>>::iterator addIntoSegmentList(int lineId, LineSegment& line, std::vector<std::pair<int, LineSegment>>& sweepLine, float xPosition);
    void checkIntersect(std::vector<std::pair<int, LineSegment>>::iterator line1, std::vector<std::pair<int, LineSegment>>::iterator line2, std::priority_queue<Event, std::vector<Event>, cp>& pq );
    bool doIntersect(Vector3 p1, Vector3 q1, Vector3 p2, Vector3 q2);
    int orientation(Vector3 p, Vector3 q, Vector3 r);


    /*std::pair<bool, Vector3> intersect(const LineSegment & a, const LineSegment & b, bool print);
    void intersect(int a, int b, const Vector3 & I, std::vector<LineSegment> & segments, std::multimap<Vector3, int> & sweep, std::multimap<std::pair<double,int>, int,event_less> & events, bool print);
    void intersect(std::vector<LineSegment> & segments, std::vector<Vector3> & intersections, bool print);*/


};
