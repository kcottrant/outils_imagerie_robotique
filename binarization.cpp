#include <iostream>
#include <cstdlib>

#include <morphology.hpp>

using namespace cv;
using namespace std;

void
process(int thmin, int thmax,const char* sename, const char* imsname)
{
  (void) imsname;
  Mat image = imread(sename);
  Mat gear;
  Mat image2(image.rows,image.cols,CV_8UC1,Scalar(0));
  cvtColor(image, gear,CV_RGB2GRAY);
  for(int i=0;i<gear.rows;i++)
  {
    for(int j=0; j<gear.cols; j++)
    {
      if(gear.at<uchar>(i,j)>=thmin && gear.at<uchar>(i,j)<=thmax)
      {
	image2.at<uchar>(i,j)=255;
      }
      else
      {
	image2.at<uchar>(i,j)=0;
      }
    }
  }
  imwrite(imsname,image2);
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<"im-se ims imd"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 4
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]),atoi(argv[2]), argv[3], argv[4]);
  return EXIT_SUCCESS;
}
