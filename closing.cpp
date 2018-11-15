#include <iostream>
#include <cstdlib>

#include <morphology.hpp>

using namespace cv;
using namespace std;

void
process(const char* sename, const char* imsname, const char* imdname)
{
  Mat imgGrey,seGrey;
  Mat se = imread(sename);
  Mat image = imread(imsname);
  cvtColor(se, seGrey,CV_RGB2GRAY);
  cvtColor(image, imgGrey,CV_RGB2GRAY);

  Mat imd(imgGrey.rows, imgGrey.cols, CV_8UC1);
  Mat imd_closing(imgGrey.rows, imgGrey.cols, CV_8UC1);
  // On fait d'abord une dilatation
  mm(seGrey,imgGrey,imd,maximum);
  // On fait ensuite une erosion
  mm(seGrey,imd,imd_closing,minimum);
  imwrite(imdname,imd_closing);
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
