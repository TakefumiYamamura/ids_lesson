#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define MAX_VALUE 100
#define KSIZE 3


const string windowName = "result";
int value = 0;
Mat image;
Mat grayImage;
Mat tmpImage;
Mat lapImage;
Mat resultImage;
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
  cvtColor(image, grayImage, CV_BGR2GRAY);
  image.release();

  namedWindow(windowName, CV_WINDOW_AUTOSIZE);
  const string trackbarName = "alpha";
  createTrackbar(trackbarName, windowName, &value, MAX_VALUE, onChange, NULL);
  onChange(value, NULL);

  waitKey(0);
  tmpImage.release();
  lapImage.release();
  resultImage.release();
  return 0;
}

 void onChange(int value, void* data){
   double alpha = value * 0.01;
   Laplacian(grayImage, tmpImage, CV_32FC1, KSIZE);
   convertScaleAbs(tmpImage, lapImage);
   resultImage = grayImage - alpha * lapImage;
   imshow(windowName, resultImage);
 }
