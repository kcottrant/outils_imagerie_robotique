#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void 
process(const char* imsname, const char* imdname)
{
  Mat image = imread(imsname,1);
  if(image.data==NULL)
    printf("Image non valide \n");
  else
    {
      imshow(imsname, image);
      waitKey(0);
      (void) imdname;
      int width = image.size().width;
      int height = image.size().height;
      printf("widht : %i \nheight : %i \n",width,height);
  
      // Creation d'une image
      Mat new_image(100,200,CV_8UC3,cv::Scalar(255, 0, 255));
      imshow("New image",new_image);
      waitKey(0);
      imwrite(imdname,new_image);
    } 
 
} 

void 
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" imsname imdname\n"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 2
int 
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1], argv[2]);

  return EXIT_SUCCESS;  
}
