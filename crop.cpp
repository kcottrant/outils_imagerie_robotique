#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void 
process(const char* imsname,
	int i0,
	int j0,
	int h,
	int w)
{
  //crop auto
  Mat image = imread(imsname);
  Mat new_matrice(h,w,CV_8UC3);
   for(int i=0;i<h;i++)
  {
    for(int j=0;j<w;j++)
      {
	new_matrice.at<Vec3b>(i,j)=image.at<Vec3b>(i0+i,j0+j);
      }
   }

  imwrite("crop.png",new_matrice);
  imshow("crop.png",new_matrice);
  waitKey(0);
  Mat image_2 = image(Rect(j0,i0,w,h));
  imshow("crop-ocv.png",image_2);
  waitKey(0);
  imwrite("crop-ocv.png",image_2);
  Mat difference(h,w,CV_8UC3);
  subtract(new_matrice,image_2,difference);
  imshow("diff=((crop)-(crop-cv))",difference);
  waitKey(0);
}

void 
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname i0 j0 w h\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 5
int 
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1],atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atoi( argv[5]));
  // atoi(argv[4])
  return EXIT_SUCCESS;  
}
