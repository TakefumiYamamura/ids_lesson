#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define MAX_VALUE 3

const string windowName = "result";
int value = 0;
Mat image;
void onChange(int value, void* data);

int main(int argc, char* argv[]){
if (argc < 2){
cerr << "usage: sharpening <sourceFile>" << endl;
return -1;
 }
 image = imread(argv[1]);
 if (!image.data){
 cerr << "no such file: " << argv[1] << endl;
 return -1;
 }

 const string windowOriginal = "Original";
 namedWindow(windowOriginal, CV_WINDOW_AUTOSIZE);
 imshow(windowOriginal, image);

 Mat grayImage;
 cvtColor(image, grayImage, CV_BGR2GRAY);
 float m[3][3] = {{-1, -1, -1}, {-1, 9, -1}, {-1, -1, -1}};
 Mat kernel(3, 3, CV_32F, m);
 Mat tmpImage1;
 filter2D(grayImage, tmpImage1, CV_32FC1, kernel);
 convertScaleAbs(tmpImage1, grayImage);
 const string windowFilter2D = "filter2D";
 namedWindow(windowFilter2D, CV_WINDOW_AUTOSIZE);
 imshow(windowFilter2D, grayImage);


 namedWindow(windowName, CV_WINDOW_AUTOSIZE);
 const string trackbarName = "ksize";
 createTrackbar(trackbarName, windowName, &value, MAX_VALUE, onChange, NULL);
 onChange(value, NULL);

 waitKey(0);
 image.release();
 tmpImage1.release();
 grayImage.release();
 return 0;
 }


 void onChange(int value, void* data){
 int alpha = value*2 + 1;
 Mat tmpImage2;
 Mat lapImage;
 Mat resultImage;
 Laplacian(image, tmpImage2, CV_32FC1, alpha);
 convertScaleAbs(tmpImage2, lapImage);
 resultImage = image - lapImage;
 imshow(windowName, resultImage);
 tmpImage2.release();
 lapImage.release();
 resultImage.release();
 }