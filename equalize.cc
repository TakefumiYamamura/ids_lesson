#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;


#define BASE           2.0
#define RATIO          32.0
#define HISTOGRAM_SIZE 256
#define TRACKBAR_HALF  128
#define TRACKBAR_MAX   (TRACKBAR_HALF * 2)


Mat grayImage;
Mat equalizeImage;
const string windowName = "Result";
int trackbarEqualize = TRACKBAR_HALF;
// unsigned char lookUpTable[TRACKBAR_MAX + 1][HISTOGRAM_SIZE];
unsigned char lookUpTable[HISTOGRAM_SIZE];

void changeHist() {
  Mat lookUpTableMatrix(HISTOGRAM_SIZE, 1, CV_8U, lookUpTable[trackbarEqualize]);
  // Mat resultImage;
  LUT(grayImage, lookUpTableMatrix, equalizeImage);
  imshow(windowName, equalizeImage);
  lookUpTableMatrix.release();
  equalizeImage.release();
}

int main(int argc, char* argv[]){
  if(argc <= 1){
    cerr << "usage: equalizeCV <file>" << endl;
    return -1;
  }
  Mat image = imread(argv[1]);
  if(!image.data){
    cerr << "no such file:" << argv[1] << endl;
    return -1;
  }


  cvtColor(image, grayImage, CV_BGR2GRAY);
  image.release();

  // equalizeHist(grayImage, equalizeImage);
  float max = 0.0;
  float min = 999999.0;

  for (int row = 0; row < grayImage.rows; ++row)
  {
    for (int col = 0; col < grayImage.cols; ++col)
    {
      if(max > grayImage.at<float>(row, col)){
        unsigned char max_val = grayImage.at<uchar>(row, col);
      }
      if(min < grayImage.at<float>(row, col)){
        unsigned char min_val = grayImage.at<uchar>(row, col);
      }
    }
  }
  for (int orgVal = 0; orgVal < HISTOGRAM_SIZE; ++orgVal)
  {
    float a, b;
    a = (255.0)/(max - min);
    b = min;
    int newVal = round((a * (orgVal- min) + min ));
    if (newVal < 0)
    {
      newVal = 0;
    }
    if(newVal > (HISTOGRAM_SIZE-1)){
      newVal = (HISTOGRAM_SIZE-1);
    }
    lookUpTable[orgVal] = (unsigned char)newVal;
  }

  changeHist();

  const string windowNameGray = "Gray";
  namedWindow(windowNameGray, CV_WINDOW_AUTOSIZE);
  imshow(windowNameGray, grayImage);
  const string windowNameEqualize = "Equalize";
  namedWindow(windowNameEqualize, CV_WINDOW_AUTOSIZE);
  imshow(windowNameEqualize, equalizeImage);
  waitKey(0);
  grayImage.release();
  equalizeImage.release();
}
