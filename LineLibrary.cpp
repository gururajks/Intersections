//
// Created by Gururaj Sridhar on 2019-06-07.
//

#include<vector>
#include<queue>
#include "LineSegment.h"
#include "LineLibrary.h"
#include <algorithm>
#include<map>
#include<list>
#include<iostream>


/*
std::pair<bool, Vector3> LineLibrary::intersect(const LineSegment & a, const LineSegment & b, bool print)
{
    Vector3 ret('a', 0, 0);
    double div = (a.getStartPoint().x - a.getEndPoint().x)*(b.getStartPoint().y - b.getEndPoint().y) - (a.getStartPoint().y - a.getEndPoint().y)*(b.getStartPoint().x - b.getEndPoint().x), t;
    if (fabs(div) < 1.0e-13)
    {
        if (print) std::cout << "divisor is zero" << std::endl;
        return std::make_pair(false, ret);
    }
    ret.x = ((a.getStartPoint().x*a.getEndPoint().y - a.getStartPoint().y*a.getEndPoint().x)*(b.getStartPoint().x - b.getEndPoint().x) - (a.getStartPoint().x - a.getEndPoint().x)*(b.getStartPoint().x*b.getEndPoint().y - b.getStartPoint().y*b.getEndPoint().x)) / div;
    ret.y = ((a.getStartPoint().x*a.getEndPoint().y - a.getStartPoint().y*a.getEndPoint().x)*(b.getStartPoint().y - b.getEndPoint().y) - (a.getStartPoint().y - a.getEndPoint().y)*(b.getStartPoint().x*b.getEndPoint().y - b.getStartPoint().y*b.getEndPoint().x)) / div;
    if (print) std::cout << "found (" << ret.x << "," << ret.y << ")" << std::endl;
    //probably some of these tests are redundant
    if (fabs(a.getEndPoint().x - a.getStartPoint().x) > 1.0e-9)
    {
        t = (ret.x - a.getStartPoint().x) / (a.getEndPoint().x - a.getStartPoint().x);
        if (t < 1.0e-9 || t > 1.0 - 1.0e-9)  { if (print) std::cout << "out of bound: " << t << std::endl; return std::make_pair(false, ret); }
    }
    if (fabs(a.getEndPoint().y - a.getStartPoint().y) > 1.0e-9)
    {
        t = (ret.y - a.getStartPoint().y) / (a.getEndPoint().y - a.getStartPoint().y);
        if (t < 1.0e-9 || t > 1.0 - 1.0e-9)  { if (print) std::cout << "out of bound: " << t << std::endl; return std::make_pair(false, ret); }
    }
    if (fabs(b.getEndPoint().x - b.getStartPoint().x) > 1.0e-9)
    {
        t = (ret.x - b.getStartPoint().x) / (b.getEndPoint().x - b.getStartPoint().x);
        if (t < 1.0e-9 || t > 1.0 - 1.0e-9)  { if (print) std::cout << "out of bound: " << t << std::endl; return std::make_pair(false, ret); }
    }
    if (fabs(b.getEndPoint().y - b.getStartPoint().y) > 1.0e-9)
    {
        t = (ret.y - b.getStartPoint().y) / (b.getEndPoint().y - b.getStartPoint().y);
        if (t < 1.0e-9 || t > 1.0 - 1.0e-9)  { if (print) std::cout << "out of bound: " << t << std::endl; return std::make_pair(false, ret); }
    }
    if (print) std::cout << "intersection accepted" << std::endl;
    return std::make_pair(true, ret);
}

void LineLibrary::intersect(int a, int b, const Vector3 & I, std::vector<LineSegment> & segments, std::multimap<Vector3, int> & sweep, std::multimap<std::pair<double,int>, int,event_less> & events, bool print)
{
    //remove event of ending of old segment
    {
        int rem_end_events[2];
        rem_end_events[0] = a;
        rem_end_events[1] = b;
        for (int k = 0; k < 2; ++k)
        {
            std::pair< std::multimap<std::pair<double,int>, int,event_less>::iterator, std::multimap<std::pair<double,int>,int,event_less>::iterator > del = events.equal_range(std::make_pair(segments[rem_end_events[k]].getEndPoint().x,SEG_END)); //get all events at position of the getEndPoint()
            bool flag = false;
            for (std::multimap<std::pair<double,int>, int,event_less>::iterator it = del.first; it != del.second; ++it) //search over all events
            {
                if (it->first.second == SEG_END && it->second == rem_end_events[k]) //event is getEndPoint() of segment and segment matches current
                {
                    events.erase(it); //remove that segment
                    flag = true;
                    break; //do not expect any more
                }
            }
            if (!flag) std::cout << "Cannot find proper ending event for segment" << std::endl;
        }
    }
    //add new segment with intersection point up to getEndPoint()
    segments.push_back(LineSegment(I, segments[a].getEndPoint()));
    //add event of starting of new segment
    events.insert(std::make_pair(std::make_pair(I.x,SEG_START), (int)segments.size() - 1));
    //add event of ending of new segment
    events.insert(std::make_pair(std::make_pair(segments.back().getEndPoint().x,SEG_END),(int)segments.size() - 1));
    //change ending point for current segment
    segments[a].getEndPoint() = I;
    //add event of ending of old segment
    events.insert(std::make_pair(std::make_pair(I.x,SEG_END), a));
    //add new segment with intersection point up to getEndPoint()
    segments.push_back(LineSegment(I, segments[b].getEndPoint()));
    //add event of starting of new segment
    events.insert(std::make_pair(std::make_pair(I.x,SEG_START), (int)segments.size() - 1));
    //add event of ending of new segment
    events.insert(std::make_pair(std::make_pair(segments.back().getEndPoint().x,SEG_END), (int)segments.size() - 1));
    //change ending point for current segment
    segments[b].getEndPoint() = I;
    //add event of ending of old segment
    events.insert(std::make_pair(std::make_pair(I.x,SEG_END), b));
    if (print)
    {
        std::cout << "Number of events: " << events.size() << std::endl;
        for (std::multimap<std::pair<double, int>, int,event_less>::iterator it = events.begin(); it != events.end(); ++it)
            std::cout << "x: " << it->first.first << " type " << (it->first.second == SEG_START ? "start" : "getEndPoint()") << " segment " << it->second << std::endl;
    }
}

//find all intersection points
void LineLibrary::intersect(std::vector<LineSegment> & segments, std::vector<Vector3> & intersections, bool print)
{
    std::multimap<std::pair<double,int>,int,event_less> events;
    std::multimap<Vector3,int> sweep;

    for (int k = 0; k < (int)segments.size(); ++k)
    {
        if (segments[k].getStartPoint().x_ > segments[k].getEndPoint().x)
            std::swap(segments[k].getStartPoint(), segments[k].getEndPoint());
        events.insert(std::make_pair(std::make_pair(segments[k].getStartPoint().x_,SEG_START),k));
        events.insert(std::make_pair(std::make_pair(segments[k].getEndPoint().x_,SEG_END), k));
    }


    while (!events.empty())
    {
        std::multimap<std::pair<double,int>,int,event_less>::iterator first = events.begin();
        int t = first->first.second;
        int s = first->second;
        events.erase(first);
        if (t == SEG_START)
        {
            if( print ) std::cout << "LineSegment " << s << " start" << std::endl;
            //check if there is a line with same position
            std::multimap<Vector3, int>::iterator ins = sweep.insert(std::make_pair(segments[s].getStartPoint(), s));

            //check line (or lines above current)
            for (int dir = 0; dir <= 1; ++dir) // look up or down
            {
                if( print ) std::cout << "Looking " << (dir ? "up" : "down") << std::endl;
                std::multimap<Vector3, int>::iterator iter = ins;
                while ((dir ? ++iter : iter--) != (dir ? sweep.end() : sweep.begin())) //y is greater for next
                {
                    if (segments[s].getStartPoint() != segments[iter->second].getStartPoint()) //ignore same starting position
                    {
                        if (print) std::cout << "checking intersection" << std::endl;
                        std::pair<bool, Vector3> I = intersect(segments[s], segments[iter->second],print);
                        if (I.first)
                        {
                            I.second.letter += (char)intersections.size();
                            if( print ) std::cout << "Intersection of " << s << " and " << iter->second << " at " << I.second.letter << "(" << I.second.x << "," << I.second.y << ")" << std::endl;
                            intersections.push_back(I.second);
                            intersect(s, iter->second, I.second, segments, sweep, events,print);
                        }
                    }
                    if ((2*dir-1)*(iter->first.y - ins->first.y) > 0) //visited line is above (below) current
                        break; //stop search
                }
            }
        }
        else if (t == SEG_END)
        {
            if( print ) std::cout << "LineSegment " << s << " getEndPoint()" << std::endl;
            //remove segment from sweep
            std::pair< std::multimap<Vector3, int>::iterator, std::multimap<Vector3, int>::iterator > range = sweep.equal_range(segments[s].getStartPoint());
            if( print ) std::cout << "Range distance " << std::distance(range.first,range.second) << " sweep size " << sweep.size() << std::endl;
            std::multimap<Vector3, int>::iterator above = range.second, below = range.first;
            bool flag = false, test = true;
            if( below-- == sweep.begin() ) test = false;
            if( above == sweep.end() ) test = false;
            if( test && print ) std::cout << "Test will be performed" << std::endl;
            for (std::multimap<Vector3, int>::iterator it = range.first; it != range.second; ++it) //search over all events
            {
                if( it->second == s) //found necessery segment
                {
                    sweep.erase(it);
                    flag = true;
                    break; //do not expect any more
                }
            }
            if (!flag) std::cout << __FILE__ << ":" << __LINE__ <<  " Error: cannot find segment " << s << " in sweep" << std::endl;
            if (test)
            {
                if (print) std::cout << "test " << below->second << " with " << above->second << std::endl;
                if (segments[above->second].getStartPoint() != segments[below->second].getStartPoint())
                {
                    if (print) std::cout << "checking intersection" << std::endl;
                    std::pair<bool, Vector3> I = intersect(segments[below->second], segments[above->second],print);
                    if (I.first)
                    {
                        I.second.letter += (char)intersections.size();
                        if( print ) std::cout << "Intersection of " << below->second << " and " << above->second << " at " << I.second.letter << "(" << I.second.x << "," << I.second.y << ")" << std::endl;
                        intersections.push_back(I.second);
                        intersect(below->second, above->second, I.second, segments, sweep, events,print);
                    }
                }
                else if (print) std::cout << "skipping segments with same starting point" << std::endl;
            }
        }
    }

}


*/































/*-------------------------------------------------------------------------------------------------*/



bool LineLibrary::isParallel(const LineSegment &l1, const LineSegment &l2)
{
    return l1.getSlope() == l2.getSlope();
}


/*
 * Get point of intersection
 */
bool LineLibrary::getPointOfIntersection(const LineSegment& l1, const LineSegment& l2, Vector3& pointOfIntersection)
{

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
            if(doIntersect(lines[i].getStartPoint(), lines[i].getEndPoint(),
                    lines[j].getStartPoint(), lines[j].getEndPoint()))
            {
                getPointOfIntersection(lines[i], lines[j], pointOfIntersection);
                pointOfIntersections.push_back(pointOfIntersection);
            }
        }
    }
    return pointOfIntersections;
}

/*********************************************************************************************************/




// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool LineLibrary::onSegment(Vector3 p, Vector3 q, Vector3 r)
{
    return (q.x_ <= std::max(p.x_, r.x_) && q.x_ >= std::min(p.x_, r.x_) &&
        q.y_ <= std::max(p.y_, r.y_) && q.y_ >= std::min(p.y_, r.y_));
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int LineLibrary::orientation(Vector3 p, Vector3 q, Vector3 r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (q.y_ - p.y_) * (r.x_ - q.x_) -
              (q.x_ - p.x_) * (r.y_ - q.y_);

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool LineLibrary::doIntersect(Vector3 p1, Vector3 q1, Vector3 p2, Vector3 q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    return (o4 == 0 && onSegment(p2, q1, q2));
}




void LineLibrary::checkIntersect(std::vector<std::pair<int, LineSegment>>::iterator line1, std::vector<std::pair<int, LineSegment>>::iterator line2, std::priority_queue<Event, std::vector<Event>, cp>& pq )
{
    if(doIntersect(line1->second.getStartPoint(), line1->second.getEndPoint(), line2->second.getStartPoint(), line2->second.getEndPoint()))
    {
        Vector3 poi(0.0, 0.0, 0.0);
        getPointOfIntersection(line1->second, line2->second, poi);
        Event e(poi, Event::EventType::CROSS, 0);
        e.crossOver.first = line1->first;
        e.crossOver.second = line2->first;
        pq.push(e);
    }

}


std::vector<std::pair<int, LineSegment>>::iterator LineLibrary::addIntoSegmentList(int lineId, LineSegment& line, std::vector<std::pair<int, LineSegment>>& sweepLine, float xPosition)
{
    std::vector<std::pair<int, LineSegment>>::iterator insertedIter = sweepLine.end();
    for(auto iter = sweepLine.begin(); iter != sweepLine.end(); iter++)
    {
        auto sweepPoint = iter->second;
        int y = sweepPoint.getSlope() * xPosition + sweepPoint.getIntercept();
        int cy = line.getSlope() * xPosition + line.getIntercept();
        if(cy < y)
        {
            sweepLine.insert(iter, std::make_pair(lineId, line));
            insertedIter = iter;
        }
    }
    return insertedIter;
}

void LineLibrary::deleteFromSegmentList(int lineId, std::vector<std::pair<int, LineSegment>>& sweepLine)
{
    auto iter = std::find_if(sweepLine.begin(), sweepLine.end(), [lineId](std::pair<int, LineSegment> item){
       return (item.first == lineId);
    });
    if(iter != sweepLine.end())
    {
        sweepLine.erase(iter);
    }
}

/*
 * Use a line to sweep from left to right and get the POI
 */
std::vector<Vector3> LineLibrary::getEffPointsOfIntersection(std::vector<LineSegment>& lines)
{
    std::vector<Vector3> pointOfIntersections;
    std::sort(lines.begin(), lines.end(), [](LineSegment& line1, LineSegment& line2) {
        return line1.getStartPoint().x_ < line2.getStartPoint().x_;
    });
    std::priority_queue<Event, std::vector<Event>, cp> pq;
    std::map<int , LineSegment> segmentMap;
    std::vector<std::pair<int, LineSegment>> sweepLine;
    std::cout<<"Reached1"<<std::endl;

    int lineId = 0;
    for(auto& line : lines)
    {
        pq.emplace(line.getStartPoint(), Event::EventType::BEGIN, lineId);
        pq.emplace(line.getEndPoint(), Event::EventType::END, lineId);
        segmentMap[lineId] = line;
        lineId++;
    }
    while(!pq.empty())
    {
        std::cout<<"Reached2"<<std::endl;
        auto topValue = pq.top();
        pq.pop();
        std::cout<<"Reached2.5"<<std::endl;
        std::cout<<topValue.event_<<std::endl;
        if(topValue.event_ == Event::EventType::BEGIN)
        {
            std::cout<<"Reached3"<<std::endl;
            auto iter = addIntoSegmentList(topValue.lineId_, segmentMap[topValue.lineId_], sweepLine, topValue.point_.x_);
            std::cout<<"Reached4"<<std::endl;

            //check the predecessor for the intersection
            auto prevIter = iter - 1;
            if(iter != sweepLine.begin() )
            {
                checkIntersect(prevIter, iter, pq);
            }
            std::cout<<"Reached5"<<std::endl;
            //check the successor for intersections
            auto nextIter = iter + 1;
            if(nextIter != sweepLine.end())
            {
                checkIntersect(nextIter, iter, pq);
            }
            std::cout<<"Reached6"<<std::endl;
        }
        if(topValue.event_ == Event::EventType::END)
        {
            std::cout<<"Reached7"<<std::endl;
            //check the intersection of pred and suc of this line
            //check the successor for intersections
            int lineId = topValue.lineId_;
            auto iter = std::find_if(sweepLine.begin(), sweepLine.end(), [lineId](std::pair<int, LineSegment>& item) {
               return item.first == lineId;
            });
            //check the successor for intersections
            auto nextIter = iter + 1;
            if(nextIter != sweepLine.end())
            {
                checkIntersect(nextIter, iter,  pq);
            }
            //delete the segment from the segment map
            deleteFromSegmentList(topValue.lineId_, sweepLine);
        }
        if(topValue.event_ == Event::EventType::CROSS)
        {
            std::cout<<"Reached8"<<std::endl;
            pointOfIntersections.push_back(topValue.point_);

            int firstLine = topValue.crossOver.first;
            int secondLine = topValue.crossOver.second;
            for(int i = 0 ; i < sweepLine.size(); i++)
            {

            }

            //swap the crossOver in the sweep line

        }
    }

    return pointOfIntersections;
}


