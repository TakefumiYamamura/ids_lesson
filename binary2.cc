#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

#define TRACKBAR_MAX_VALUE 255
#define THRESHOLD_MAX_VALUE 255

const string windowName = "Binary";
Mat grayImage;
void onChange(int value, void* data);

int main(int argc, char* argv[]){
  if (argc <= 1){
    cerr << "usage: binary <file>" << endl;
    return -1;
  }
  Mat image = imread(argv[1]);
  if (!image.data){
    cerr << "no such file: " << argv[1] << endl;
    return -1;
  }
  cvtColor(image, grayImage, CV_BGR2GRAY);
  image.release();
  int value = 128;
  namedWindow(windowName, CV_WINDOW_AUTOSIZE);
  threshold(grayImage, grayImage, value, THRESHOLD_MAX_VALUE, THRESH_BINARY);
  const string trackbarName = "Threshold";
  createTrackbar(trackbarName, windowName, &value, TRACKBAR_MAX_VALUE, onChange, NULL);
  imshow(windowName, grayImage);
  waitKey(0);
  grayImage.release();
  return 0;
}

void onChange(int value, void* data){
  Mat binaryImage;
  threshold(grayImage, binaryImage, value, THRESHOLD_MAX_VALUE, THRESH_BINARY);
  imshow(windowName, binaryImage);
  binaryImage.release();
}
