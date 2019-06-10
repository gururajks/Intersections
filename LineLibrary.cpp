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


bool LineLibrary::isParallel(const LineSegment &l1, const LineSegment &l2)
{
    return l1.getSlope() == l2.getSlope();
}


/*
 * Get point of intersection
 */
bool LineLibrary::getPointOfIntersection(const LineSegment& l1, const LineSegment& l2, Vector3& pointOfIntersection)
{
    if(isParallel(l1, l2) || !doIntersect(l1.getStartPoint(), l1.getEndPoint(), l2.getStartPoint(), l2.getEndPoint())) return false;
    double poi_x = (l2.getStartPoint().y_ - l1.getStartPoint().y_ +
                 l1.getSlope() * l1.getStartPoint().x_ - l2.getSlope() * l2.getStartPoint().x_) / (l1.getSlope() - l2.getSlope());
    double poi_y = l1.getSlope() * (poi_x - l1.getStartPoint().x_) + l1.getStartPoint().y_;
    pointOfIntersection.x_ = poi_x;
    pointOfIntersection.y_ = poi_y;
    return true;
}


/*
* O(n2) algorithm
*/
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

//check if they are co-linear
bool LineLibrary::onSegment(Vector3 a, Vector3 b, Vector3 c)
{
    return (b.x_ <= std::max(a.x_, c.x_) && b.x_ >= std::min(a.x_, c.x_) &&
        b.y_ <= std::max(a.y_, c.y_) && b.y_ >= std::min(a.y_, c.y_));
}


int LineLibrary::orientation(Vector3 a, Vector3 b, Vector3 c)
{
    int val = (b.y_ - a.y_) * (c.x_ - b.x_) -
              (b.x_ - a.x_) * (c.y_ - b.y_);

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


void LineLibrary::checkIntersect(std::vector<std::pair<int, LineSegment>>::iterator line1, std::vector<std::pair<int, LineSegment>>::iterator line2, std::priority_queue<Event, std::vector<Event>, cp>& pq, float xPosition)
{
    if(doIntersect(line1->second.getStartPoint(), line1->second.getEndPoint(), line2->second.getStartPoint(), line2->second.getEndPoint()))
    {
        Vector3 poi(0.0, 0.0, 0.0);
        getPointOfIntersection(line1->second, line2->second, poi);
        //only events to the right of the cross over will be added
        //only events are added once
		if (poi.x_ > xPosition)
		{
			Event e(poi, Event::EventType::CROSS, 0);
			e.crossOver.first = line1->first;
			e.crossOver.second = line2->first;
			pq.push(e);
		}        
    }

}

//
std::vector<std::pair<int, LineSegment>>::iterator LineLibrary::addSegmentIntoSweepLine(int lineId, const LineSegment &line,
                                                                                        std::vector<std::pair<int, LineSegment>> &sweepLine,
                                                                                        float xPosition)
{
	int cy = line.getSlope() * xPosition + line.getIntercept();
    std::vector<std::pair<int, LineSegment>>::iterator insertedIter = sweepLine.end();	
	bool inserted = false;
    for(auto iter = sweepLine.begin(); iter != sweepLine.end(); iter++)
    {
        auto sweepPoint = iter->second;
		//calculate the slope at that xposition and get the y so that it gets inserted in the right position
        int y = sweepPoint.getSlope() * xPosition + sweepPoint.getIntercept();        
        if(cy < y)
        {
			insertedIter = sweepLine.insert(iter, std::make_pair(lineId, line));
			inserted = true;
			break;
        }
    }
	if (sweepLine.empty())
	{
		insertedIter = sweepLine.insert(sweepLine.begin(), std::make_pair(lineId, line));
	}
	else if (!inserted)
	{
		insertedIter = sweepLine.insert(sweepLine.begin() + sweepLine.size(), std::make_pair(lineId, line));
	}
    return insertedIter;
}

void LineLibrary::deleteFromSweepLine(int lineId, std::vector<std::pair<int, LineSegment>> &sweepLine)
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
 * This algorithm is based on Bentley Ottomon Algorithm of sweep lines
 * http://www.itseng.org/research/papers/topics/VLSI_Physical_Design_Automation/Physical_Verification/DRC/Geometric_Intersection_Problems/1979-Bentley.pdf
 */
std::vector<Vector3> LineLibrary::getEfficientPointsOfIntersection(std::vector<LineSegment>& lines)
{
    std::vector<Vector3> pointOfIntersections;	
    std::priority_queue<Event, std::vector<Event>, cp> pq;
    std::map<int , LineSegment*> segmentMap;
    std::vector<std::pair<int, LineSegment>> sweepLine;

    int lineId = 0;
    for(auto& line : lines)
    {
        pq.emplace(line.getStartPoint(), Event::EventType::BEGIN, lineId);
        pq.emplace(line.getEndPoint(), Event::EventType::END, lineId);
        segmentMap[lineId] = &line;
        lineId++;
    }
    while(!pq.empty())
    {
        auto topValue = pq.top();
        pq.pop();
        if(topValue.event_ == Event::EventType::BEGIN)
        {
            auto iter = addSegmentIntoSweepLine(topValue.lineId_, *segmentMap[topValue.lineId_], sweepLine,
                                                topValue.point_.x_);

            //check the predecessor for the intersection
            
            if(iter != sweepLine.begin() )
            {
				auto prevIter = iter - 1;
                checkIntersect(prevIter, iter, pq, topValue.point_.x_);
            }
            //check the successor for intersections
            auto nextIter = iter + 1;
            if(nextIter != sweepLine.end())
            {
                checkIntersect(nextIter, iter, pq, topValue.point_.x_);
            }
        }
        if(topValue.event_ == Event::EventType::END)
        {
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
                checkIntersect(nextIter, iter,  pq, topValue.point_.x_);
            }
            //delete the segment from the segment map
            deleteFromSweepLine(topValue.lineId_, sweepLine);
        }
		//cross over event
        if(topValue.event_ == Event::EventType::CROSS)
        {
            pointOfIntersections.push_back(topValue.point_);

            int firstLine = topValue.crossOver.first;
            int secondLine = topValue.crossOver.second;
			int firstLineIndex = 0;
			int secondLineIndex = 0;
            for(int i = 0 ; i < sweepLine.size(); i++)
            {
				if (sweepLine[i].first == firstLine)  firstLineIndex = i;
				if (sweepLine[i].first == secondLine)  secondLineIndex = i;
            }
			std::swap(sweepLine[firstLineIndex], sweepLine[secondLineIndex]);

            //swap the crossOver in the sweep line
			//check if the swapped neigbors have any further crossovers 
			if(firstLineIndex > 0)
				checkIntersect(sweepLine.begin() + firstLineIndex - 1, sweepLine.begin() + firstLineIndex, pq, topValue.point_.x_);
			if (secondLineIndex < sweepLine.size() - 1)
				checkIntersect(sweepLine.begin() + secondLineIndex + 1, sweepLine.begin() + secondLineIndex, pq, topValue.point_.x_);
        }
    }

    return pointOfIntersections;
}


