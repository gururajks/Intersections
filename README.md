# Intersections
Get Point of Intersections. Give a set of lines, it generates the list of point of intersections.

* CMake Version - 3.14.5
* GCC - 4.2.1

_If you have a different CMake version and a different gcc (please make sure both of them are compatible with each other), 
Edit CMakeLists.txt `cmake_minimum_required(VERSION 3.14)` to the version you have in your system_ 

##Sweep Line Algorithm 
https://en.wikipedia.org/wiki/Bentley%E2%80%93Ottmann_algorithm

### LINUX/OSX

CMAKE Build Instructions
Inside the source/root folder (Intersections) in this case

```
$ cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../Intersections
$ make
$ ./Intersections 
```

CATCH Unit Test Build Instructions
* In main.cpp there is a macro `RUN_TESTS` .. uncomment that and rebuild the project and execute it to run tests again.



### Windows
It is best to download CMake GUI and point the source code and the build folder
Click Configure
Click Generate for the project to be built for appropriate Visual Studio version you have. 
