#include <iostream>
#include "LineLibrary.h"
#include "Vector3.h"
#include "LineSegment.h"
#define RUN_TESTS
#define CATCH_CONFIG_MAIN
#include "catch.hpp"



#ifndef RUN_TESTS

int main() {

    std::vector<LineSegment> lines = {
            LineSegment(Vector3(1.0, 1.0, 0.0), Vector3(4.0, 4.0, 0.0)),
            LineSegment(Vector3(2.0, 4.0, 0.0), Vector3(6.0, 1.0, 0.0)),
            LineSegment(Vector3(5.0, 4.0, 0.0), Vector3(13.5,2.7, 0.0)),
            LineSegment(Vector3(5.0, 5.0, 0.0), Vector3(9.0, 1.0, 0.0)),
            LineSegment(Vector3(7.0, 4.7, 0.0), Vector3(12.5, 1.5, 0.0)),
            LineSegment(Vector3(10.0, 1.5, 0.0), Vector3(12.5, 5.0, 0.0))};

    auto pointOfIntersections = LineLibrary::getPointsOfIntersection(lines);

    std::for_each(pointOfIntersections.begin(), pointOfIntersections.end(), [](const Vector3& poi){
       std::cout<<"x:"<<poi.x_<<"   y:"<<poi.y_<<"   z:"<<poi.z_<<std::endl;
    });

    return 0;
}

#else

TEST_CASE("Get Slope", "[getSlop()]")
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
    LineSegment l3(Vector3(5.0, 5.0, 0.0), Vector3(9.0, 1.0, 0.0));
    LineSegment l4(Vector3(7.0, 4.7, 0.0), Vector3(12.5, 1.5, 0.0));
    //REQUIRE(LineLibrary::getPointsOfIntersection(l3, l4))
}

TEST_CASE("Testing points of Intersection", "[POIs]")
{
    std::vector<LineSegment> lines = {
            LineSegment(Vector3(1.0, 1.0, 0.0), Vector3(4.0, 4.0, 0.0)),
            LineSegment(Vector3(2.0, 4.0, 0.0), Vector3(6.0, 1.0, 0.0)),
            LineSegment(Vector3(5.0, 4.0, 0.0), Vector3(13.5,2.7, 0.0))};
    auto pointsOfIntersection = LineLibrary::getPointsOfIntersection(lines);

}


#endif
