#include <iostream>
#include "LineLibrary.h"
#include "Vector3.h"
#include "LineSegment.h"
//#define RUN_TESTS



#ifndef RUN_TESTS

int main() {

    std::vector<LineSegment> lines = {
            LineSegment(Vector3(1.0, 1.0, 0.0), Vector3(4.0, 4.0, 0.0)),
            LineSegment(Vector3(2.0, 1.0, 0.0), Vector3(2.0, 4.0, 0.0))};

    /*
     * ,
            LineSegment(Vector3(5.0, 4.0, 0.0), Vector3(13.5,2.7, 0.0)),
            LineSegment(Vector3(5.0, 5.0, 0.0), Vector3(9.0, 1.0, 0.0)),
            LineSegment(Vector3(7.0, 4.7, 0.0), Vector3(12.5, 1.5, 0.0)),
            LineSegment(Vector3(10.0, 1.5, 0.0), Vector3(12.5, 5.0, 0.0))
     *
     */

    LineLibrary lineLib;
    //This is an inefficient algorithm that goes in O(n2)
    //this is to compare and test the algorithm
    /*auto pointOfIntersections = lineLib.getPointsOfIntersection(lines);
    std::for_each(pointOfIntersections.begin(), pointOfIntersections.end(), [](const Vector3& poi){
       std::cout<<"x:"<<poi.x_<<"   y:"<<poi.y_<<"   z:"<<poi.z_<<std::endl;
    });*/

    std::cout << "-----"<<std::endl;
    //This is an efficient algorithm that goes in O(nlogn)
    auto points = lineLib.getEfficientPointsOfIntersection(lines);
    std::for_each(points.begin(), points.end(), [](const Vector3& poi) {
        std::cout << "x:" << poi.x_ << "   y:" << poi.y_ << "   z:" << poi.z_ << std::endl;
    });

    return 0;
}

#else

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE("Get Slope", "[getSlope()]")
{
    LineSegment l(Vector3(5.0, 5.0, 0.0), Vector3(9.0, 9.0, 0.0));
    REQUIRE(l.getSlope() == 1);
    LineSegment l1(Vector3(5.0, 5.0, 0.0), Vector3(5.0, 9.0, 0.0));
    REQUIRE(l1.getSlope() == std::numeric_limits<double>::max());
}

TEST_CASE("Testing isParallel()", "[isParallel()]")
{
    LineSegment l1(Vector3(1.0, 1.0, 0.0), Vector3(4.0, 4.0, 0.0));
    LineSegment l2(Vector3(2.0, 2.0, 0.0), Vector3(3.0, 3.0, 0.0));
    REQUIRE(LineLibrary::isParallel(l1, l2) == true);

    LineSegment l3(Vector3(5.0, 5.0, 0.0), Vector3(9.0, 1.0, 0.0));
    LineSegment l4(Vector3(7.0, 4.7, 0.0), Vector3(12.5, 1.5, 0.0));
    REQUIRE(LineLibrary::isParallel(l3, l4) == false);
}

TEST_CASE("Testing point of Intersection", "[POI]")
{
    LineSegment l1(Vector3(2.0, 2.0, 0.0), Vector3(6.0, 6.0, 0.0));
    LineSegment l2(Vector3(2.0, 6.0, 0.0), Vector3(12.0, -4.0, 0.0));
    Vector3 poi(0.0,0.0,0.0);
    REQUIRE(LineLibrary::getPointOfIntersection(l1, l2, poi) == true);
    REQUIRE(poi == Vector3(4.0, 4.0, 0.0));
}


#endif
