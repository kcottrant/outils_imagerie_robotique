#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(int h,int s,int v ,const char* imsname,const char* imdsname)
{
  Mat image,hsv[3],imgHsv,ajouthsv[3],newimage,hsv2rgb;
  image = imread(imsname);
  cvtColor(image,imgHsv,CV_BGR2HSV);
  // composantes h, s, v
  split(imgHsv,hsv);
  imshow("h",hsv[0]); //h channel
  waitKey(0);
  imshow("s",hsv[1]); //s channel
  waitKey(0);
  imshow("v",hsv[2]); //v channel
  waitKey(0);

  add(hsv[0],h,ajouthsv[0]);
  add(hsv[1],s,ajouthsv[1]);
  add(hsv[2],v,ajouthsv[2]);

  merge(ajouthsv,3,newimage);
  cvtColor(newimage,hsv2rgb,CV_HSV2BGR);
  imwrite(imdsname,hsv2rgb);

  (void) imdsname;
}

void
usage (const char *s)
{
  fprintf(stderr, "Usage: %s imsname\n", s);
  exit(EXIT_FAILURE);
}

#define param 5
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),argv[4],argv[5]);
  return EXIT_SUCCESS;
}
