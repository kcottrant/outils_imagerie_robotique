#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(int sigma_s, int sigma_c, const char* imsname, const char* imd)
{
  Mat rgb2grey;
  Mat image = imread(imsname);
  cvtColor(image, rgb2grey,CV_RGB2GRAY);
  Mat image_bilaterale(rgb2grey.rows, rgb2grey.cols, CV_8UC1);
  float Gc [256];
  float x = sqrt(-2*pow(sigma_s,2)*log(0.01));
  //cout<<x<<endl;
  //cout<<sigma_c<<endl;
  //printf("%f",x);
  int taille_spaciale = round(x);
  //cout<<taille_spaciale<<endl;
  float Gs [taille_spaciale*2];
  float num, den;
  int radius = taille_spaciale;
  float argG,ratio;

  //calcul de Gc
  for(int i=0; i<256; i++)
  {
    Gc[i] =  exp(-pow((float)i,2)/(2*sigma_c));
  }
  //calcul de Gs
  for(int i = 0; i<taille_spaciale;i++)
  {
    Gs[i] = exp(-pow((float)i,2)/(2*sigma_s));
  }

  for(int i=0; i<rgb2grey.rows;i++)
  {
    for(int j=0;j<rgb2grey.cols;j++)
    {
      num = 0.0;
      den = 0.0;
      //cout<<"*******************"<<endl;
      for(int k=1;k<=radius;k++)
      {
        for(int w=-k;w<k+1;w++)
        {
          if(i-k>=0 && j+w>=0 && j+w<rgb2grey.cols)
          {
            // en haut
            argG =Gs[abs(i-abs(i-k)) + abs(j-(j+w))]*Gc[abs(rgb2grey.at<uchar>(i,j)-rgb2grey.at<uchar>(i-k,j+w))];
            //cout<<argG<<endl;
            num = num + argG*rgb2grey.at<uchar>(i-k,j+w);
            //cout<<num<<endl;
            //cout<<(int)rgb2grey.at<uchar>(i-k,j+w)<<endl;
            den = den+argG;
          }
          if(i+k>=0 && i+k<rgb2grey.rows && j+w>=0 && j+w<rgb2grey.cols)
          {
            // en bas
            argG =Gs[abs(i-(i+k)) + abs(j-(j+w))]*Gc[abs(rgb2grey.at<uchar>(i,j)-rgb2grey.at<uchar>(i+k,j+w))];
            num = num + argG*(int)rgb2grey.at<uchar>(i+k,j+w);
            den = den+argG;
          }
        }
        for(int w=-k+1;w<k*2-1;w++)
        {
          if(i+w>=0 && i+w<rgb2grey.rows && j+k>=0 && j+k<rgb2grey.cols)
          {
            // à droite
            argG =Gs[abs(i-(i+w)) + abs(j-(j+k))]*Gc[abs(rgb2grey.at<uchar>(i,j)-rgb2grey.at<uchar>(i+w,j+k))];
            num = num + argG*(int)rgb2grey.at<uchar>(i+w,j+k);
            den = den+argG;
          }
          if(i+w>=0 && i+w<rgb2grey.rows && j-k>=0 && j-k<rgb2grey.cols)
          {
            // en gauche
            argG =Gs[abs(i-(i+w)) + abs(j-abs(j-k))]*Gc[abs(rgb2grey.at<uchar>(i,j)-rgb2grey.at<uchar>(i+w,j-k))];
            num = num + argG*(int)rgb2grey.at<uchar>(i+w,j-k);
            den = den+argG;
          }
        }

      }
      //cout<<num<<endl;
      ratio = num/den;
      //cout<<ratio<<endl;
      image_bilaterale.at<uchar>(i,j) = ratio;
    }
  }
  imshow("hi", image_bilaterale);
  waitKey(0);
  (void)imd;
}

void
usage (const char *s)
{
  fprintf(stderr, "Usage: %s imsname\n", s);
  exit(EXIT_FAILURE);
}

#define param 4
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]),atoi(argv[2]), argv[3], argv[4] );
  return EXIT_SUCCESS;
}
