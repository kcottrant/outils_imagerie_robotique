#include <iostream>
#include <cstdlib>

#include <morphology.hpp>

using namespace cv;
using namespace std;

bool image_noire(Mat image)
{
  for(int i=0;i<image.rows;i++)
  {
    for(int j=0;j<image.cols;j++)
    {
      if(image.at<uchar>(i,j)!=0)
      {
	return false;
      }
    }
  }
  return true;
}

void
process(const char* sename, const char* imsname, const char* imdname)
{
  Mat se = imread(sename);
  Mat image = imread(imsname);
  Mat seGrey,imgGrey,imgcolor;
  Mat distance(image.rows, image.cols, CV_8UC3,Scalar(0,0,0));
  Mat res(image.rows, image.cols, CV_8UC3);
  cvtColor(se, seGrey,CV_RGB2GRAY);
  cvtColor(image, imgcolor,CV_RGB2BGR);
  //  distance = imgcolor;
  cvtColor(image, imgGrey,CV_RGB2GRAY);
  while(!image_noire(imgGrey))
  {
    Mat imd(image.rows,image.cols,CV_8UC1,Scalar(0));
    mm(seGrey,imgGrey,imd,minimum);
    imgGrey = imd;
    cvtColor(imgGrey,res,CV_GRAY2BGR);
    imshow("ikoko",distance);
    waitKey(0);
    distance = distance + res; 
  }
  
  imshow("jijoi",distance);
  waitKey(0);
  (void) imdname;
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<"im-se ims imd"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 3
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], argv[2], argv[3]);
  return EXIT_SUCCESS;
}
