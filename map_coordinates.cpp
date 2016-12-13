#include <opencv2/opencv.hpp>
#include <iostream>
#include <cassert>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "stdlib.h"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/optflow.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/tracking.hpp"
#include "opencv2/ximgproc/seeds.hpp"
#include <opencv2/ximgproc.hpp>
#include "opencv2/video/background_segm.hpp"
#include "opencv2/bgsegm.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/video.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/video/tracking.hpp"
#include <sys/stat.h>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;



int main(int argc, char **argv){
    int point_count = 4; //the points that are available to use to calculate mapping matrix
    vector<Point2f> pts_im(point_count);
    vector<Point3f> pts_wd(point_count);
    vector<Point2f> pts_out(1);
    vector<Point2f> pts_wd_test(1);
    pts_im[0] = cv::Point2f(333,122); //points in image
    pts_im[1] = cv::Point2f(425,138);
    pts_im[2] = cv::Point2f(639,153);
    pts_im[3] = cv::Point2f(240,136);
    //pts_im[4] = cv::Point2f(138,52);
    //pts_im[5] = cv::Point2f(123,51);
    //pts_im[6] = cv::Point2f(92,49);
    //pts_im[7] = cv::Point2f(992,55);
    //pts_im[8] = cv::Point2f();
    //pts_im[9] = cv::Point2f();
    //pts_im[10] = cv::Point2f(); x,
    pts_wd[0] = cv::Point3f(0,0,0);  //points in physical world
    pts_wd[1] = cv::Point3f(0.1397,0.4699,0);
    pts_wd[2] = cv::Point3f(0.1397,1.4732,0);
    pts_wd[3] = cv::Point3f(0.2731,-0.3048,0);
    //pts_wd[4] = cv::Point3f(-4.6990,-2.3971,0);
    //pts_wd[5] = cv::Point3f(-4.6196,-2.6448,0);
    //pts_wd[6] = cv::Point3f(-4.6958,-2.6448,0);
    //pts_wd[7] = cv::Point3f(-4.9911,6.1341,0);
    //pts_wd[8] = cv::Point3f();
    //pts_wd[9] = cv::Point3f();
    //pts_wd[10] = cv::Point3f();

    double aa[3][3]={{490.874, 0., 637.900},{0,490.210,358.650},{0,0,1}};  //calibration parameters
    Mat cameraMatrix = Mat(3, 3, CV_64F,aa);

    double cc[3][3]={{490.874, 0., 637.900},{0,490.210,358.650},{0,0,1}};
    Mat intrinsics = Mat(3, 3, CV_64F,cc);
    Mat rvec, tvec;
    vector<int> inliers;
    Mat distCoeffs = Mat::zeros(4, 1, CV_32FC1);
    //double bb[5][1]= {{-2.484045e-01},{1.0144540877e-01},{0},{0},{-2.614560230472e-02}};
    //Mat distCoeffs = Mat(5, 1, CV_64F,bb);
    solvePnPRansac(pts_wd, pts_im, cameraMatrix, distCoeffs, rvec, tvec, false, 500, 0.5f, 0.99, inliers, CV_ITERATIVE);
    Mat rotationMatrix;
    Rodrigues(rvec,rotationMatrix);
    Mat uvPoint = cv::Mat::ones(3,1,cv::DataType<double>::type);
    uvPoint.at<double>(0,0) = atoi(argv[1]);
    uvPoint.at<double>(1,0) = atoi(argv[2]);
    cv::Mat tempMat, tempMat2;
    double s, zConst = 0;
    tempMat = rotationMatrix.inv() * intrinsics.inv() * uvPoint;
    tempMat2 = rotationMatrix.inv() * tvec;
    s = zConst + tempMat2.at<double>(2,0);
    s /= tempMat.at<double>(2,0);
    cv::Mat wcPoint = rotationMatrix.inv() * (s * intrinsics.inv() * uvPoint - tvec);
    Point3f realPoint(wcPoint.at<double>(0, 0), wcPoint.at<double>(1, 0), wcPoint.at<double>(2, 0));  
    cout<<realPoint<<endl;   
    return 0;
}
