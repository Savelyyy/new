# Version comparison

The input data for the project is a list of binary packages of 2 branches. In my case, p10 and p9.
This project creates three files.

The received package lists are compared and a JSON file is output in which:

1)all packages that are in the 1st, but not in the 2nd branch

2)all packages that are in the 2nd, but not in the 1st branch

3)all packages whose version-release is greater in the 1st than in the 2nd branch

# Using

To install and run the project, you need Cmake (version 3.0) and nlohmann/json.hpp library.
```sh
apt-get install cmake
apt-get install nlohmann-json-devel
```
Build the project using Cmake
```sh
Cmake /"the path to the CMakeLists.txt"
make
```

Run task_1_2_3
```sh
./task_1_2_3
```
# Result
As a result, 3 files are created with all the necessary information.

difference1.json

difference2.json

difference3.json
