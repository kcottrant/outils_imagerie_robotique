#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

enum {SQUARE, DIAMOND, DISK, LINE_V, DIAG_R, LINE_H, DIAG_L, CROSS, PLUS};

void
process(const int shape, const int halfsize, const char* imdname)
{
  (void) halfsize;
  (void) imdname;

  if( shape == SQUARE ){
    Mat square (halfsize*2+1,halfsize*2+1, CV_8UC1, Scalar(255));
    imwrite(imdname,square);
  }

  if(shape== LINE_V){
    Mat line_V (halfsize*2+1,halfsize*2+1, CV_8UC1, Scalar(0));
    for(int i=0;i<halfsize*2+1;i++)
    {
      line_V.at<uchar>(i,halfsize)=255;
    }
    imwrite(imdname,line_V);
  }

  if(shape== LINE_H){
    Mat line_H (halfsize*2+1,halfsize*2+1, CV_8UC1, Scalar(0));
    for(int i=0;i<halfsize*2+1;i++)
    {
      line_H.at<uchar>(halfsize,i)=255;
    }
    imwrite(imdname,line_H);
  }

  if(shape== DIAG_L){
    Mat diag_l (halfsize*2+1,halfsize*2+1, CV_8UC1, Scalar(0));
    for(int i=0;i<halfsize*2+1;i++)
    {
      diag_l.at<uchar>(i,i)=255;
    }
    imwrite(imdname,diag_l);
  }
  if(shape== DIAG_R){
    Mat diag_r (halfsize*2+1,halfsize*2+1, CV_8UC1, Scalar(0));
    for(int i=0;i<halfsize*2+1;i++)
    {
      diag_r.at<uchar>(halfsize*2-i,i)=255;
    }
    imwrite(imdname,diag_r);
  }

  if(shape== CROSS){
    Mat cross (halfsize*2+1,halfsize*2+1, CV_8UC1, Scalar(0));
    for(int i=0;i<halfsize*2+1;i++)
    {
      cross.at<uchar>(halfsize*2-i,i)=255;
    }
    for(int i=0;i<halfsize*2+1;i++)
    {
      cross.at<uchar>(i,i)=255;
    }
    imwrite(imdname,cross);
  }

  if(shape== PLUS){
    Mat plus (halfsize*2+1,halfsize*2+1, CV_8UC1, Scalar(0));
    for(int i=0;i<halfsize*2+1;i++)
    {
      plus.at<uchar>(i,halfsize)=255;
    }
    for(int i=0;i<halfsize*2+1;i++)
    {
      plus.at<uchar>(halfsize,i)=255;
    }
    imwrite(imdname,plus);
  }

  if(shape==DIAMOND)
  {
    Mat diamond (halfsize*2+1,halfsize*2+1, CV_8UC1, Scalar(0));
    int norme = halfsize;
    int norme_point=0;
    for(int i=0;i<halfsize*2+1;i++)
    {
      for(int j=0;j<halfsize*2+1;j++)
      {
        norme_point=abs(i-halfsize)+abs(j-halfsize);
        if(norme_point<=norme)
        {
          diamond.at<uchar>(i,j)=255;
        }
      }
    }
    imwrite(imdname,diamond);
  }

  if(shape==DISK)
  {
    Mat disk (halfsize*2+1,halfsize*2+1, CV_8UC1, Scalar(0));
    int norme = pow(halfsize,2);
    int norme_point=0;
    for(int i=0;i<halfsize*2+1;i++)
    {
      for(int j=0;j<halfsize*2+1;j++)
      {
        norme_point=pow(i-halfsize,2)+pow(j-halfsize,2);
        if(norme_point<=norme)
        {
          disk.at<uchar>(i,j)=255;
        }
      }
    }
    imwrite(imdname,disk);
  }
}

void
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" shape halfsize se-name"<<endl;
  exit(EXIT_FAILURE);
}

#define param 3
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]), atoi(argv[2]), argv[3]);
  return EXIT_SUCCESS;
}
