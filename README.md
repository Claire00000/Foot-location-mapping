# Foot-location-mapping
The file is used to calculate mapping between 3D world and image coordinates.
Before running code, please make sure that you have installed OpenCV 3.0 on your computer. 
The calibration parameters, 3 dimension points in real world, and 2 dimension pixels need to be specified in the file.
The file takes in 2 number corresponding to x and y, and outputs 3D coordinates in the world.

The order to run it looks like:
mkdir build
cd build
g++ ../map_coordinates.cpp -o map_coordinates.out 'pkg-config --cflag --libs opencv'
./map_coordinates.out 322 128
