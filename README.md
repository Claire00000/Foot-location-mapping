# Foot-location-mapping
1. Project aim: 
The project is to detect feet location in Surveillance Videos and map the location in frames to 3D coordinates. This part is mainly about the preprocessing of the frames and coordinates mapping between image points and 3D coordinates. The camera to use is GoPro 3 or 4. 

2. Calibration
Please refer to the instruction here about the process of calibration. (with detailed explanation and instruction)

http://www.theeminentcodfish.com/gopro-calibration/ 

After finishing calibration, you can get two core information: Intrinsic Matrix and Distortion Coefficients. You need to input them in the file map_coordinates.cpp

3. Get Point Pairs in image and 3D world

You get Intrinsic matrix after calibration, however, you still need Extrinsic Matrix to calculate transforming matrix. You need at least 4 pairs of points to calculate. Please choose one point as original point(one that is easy to measure both in image and in 3D world), select at least 4 corner points in image, and find the Matrix based on them. 

The image is made up of pixels, and we can represent coordinates in image with pixel number. There is an easy way to selet points from image and get the coordinates with matlab. You can just use the order "imshow("the path to your image")", and select interest points in prompted window. For coordinates in 3D world, you need to measure it based on the origin point you chose just now. The units doesn't matter as long as you keep them the same for all calculations.

4. Run program
The file "map_coordinates.cpp" is used to calculate mapping between 3D world and image coordinates.
Before running code, please make sure that you have installed OpenCV 3.0 and g++ on your computer. 

You need to first input the point pairs number you select, and the point pairs coordinates. For the image one, there are two numbers and for the real world coordinates, there are three numbers -- x,y,z. 

You also need to input the Intrinsic Matrix and Distortion Coefficients as instructed. 

After you finish all the steps above, you can run the program. Just input the number of x and y coordinates in image. The order is:

mkdir build
cd build
g++ ../map_coordinates.cpp -o map_coordinates.out 'pkg-config --cflag --libs opencv'
./map_coordinates.out 322 128
