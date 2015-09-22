#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
  if (argc <= 1){
    cerr << "usage: imageInfo <file>" << endl;
    return -1;
  }
  Mat image = imread(argv[1]);
  if (!image.data){
    cerr << "no such file: " << argv[1] << endl;
    return -1;
  }
  if (image.isContinuous())
    cout << "isContinuous() = true" << endl;
  else
    cout << "isContinuous() = false" << endl;
  cout << "size of an element = " << image.elemSize() << " Bytes" << endl;
  cout << "size of a channel = " << image.elemSize1() << " Bytes" << endl;
  cout << "type = " << hex << image.type() << dec << endl;
  cout << "depth = " << hex << image.depth() << dec << endl;
  switch (image.depth()){
    case CV_8U: cout << "CV_8U" << endl; break;
    case CV_8S: cout << "CV_8S" << endl; break;
    case CV_16U: cout << "CV_16U" << endl; break;
    case CV_16S: cout << "CV_16S" << endl; break;
    case CV_32S: cout << "CV_32S" << endl; break;
    case CV_32F: cout << "CV_32F" << endl; break;
    case CV_64F: cout << "CV_64F" << endl; break;
    defalut: cout << " something else" << endl;
  }
  cout << "size of a step = " << image.step1() << endl;
  cout << "no. of channels = " << image.channels() << endl;
  cout << "no. of rows = " << image.rows << endl;
  cout << "no. of columns = " << image.cols << endl;
  namedWindow("Image", CV_WINDOW_AUTOSIZE);
  imshow("Image", image);
  waitKey(0);
  image.release();

  return 0;
}
