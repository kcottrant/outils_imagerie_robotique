#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(const char* imsname)
{
  Mat image = imread(imsname);
  //image.convertTo(image, CV_32FC3);
  // RGB en gris
  Mat rgb2grey,dst,difference;
  float histo_normalise[256]={0},histo_cumule[256]={0};
  cvtColor(image, rgb2grey,CV_BGR2GRAY);
  //rgb2grey.convertTo(rgb2grey, CV_8UC1);
  Mat eq(rgb2grey.rows,rgb2grey.cols,CV_8UC1);
  float histo[256]={0};
  int intensite_max=0;
  for(int i=0; i<rgb2grey.rows;i++)
  {
    for(int j=0;j<rgb2grey.cols;j++)
    {
        int valeur = rgb2grey.at<uchar>(i,j);
        histo[valeur]=histo[valeur]+1;
        if(valeur>intensite_max)
        {
          intensite_max = valeur;
        }
    }
  }

  float total_pixel = rgb2grey.cols*rgb2grey.rows;

  for(int i=0; i<256;i++)
  {
    cout << histo[i] << endl;
    histo_normalise[i]=histo[i]/total_pixel;
  }
  cout <<"histo  0 " << histo[100] << endl;
  cout <<"histo normalisé 0 " << histo_normalise[100] << endl;
  // Calcul de l'histogramme cumulé
  histo_cumule[0]=histo_normalise[0];
  for(int i=1; i<256;i++)
  {
    histo_cumule[i]=histo_cumule[i-1]+histo_normalise[i];

  }
  cout <<"histo cumule 0 " << histo_cumule[100] << endl;

  for(int i=0; i<rgb2grey.rows;i++)
  {
    for(int j=0;j<rgb2grey.cols;j++)
    {

      eq.at<uchar>(i,j)=intensite_max*histo_cumule[rgb2grey.at<uchar>(i,j)];
    }
  }
  // Calcul de l'intensité maximale

  imwrite("eq.png",eq);

 equalizeHist(rgb2grey, dst);
 imwrite("eq-ocv.png",dst);
 subtract(eq,dst,difference);
 imshow("d",difference);
 imwrite("diff.png",difference);

}

void
usage (const char *s)
{
  fprintf(stderr, "Usage: %s imsname\n", s);
  exit(EXIT_FAILURE);
}

#define param 1
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1]);
  return EXIT_SUCCESS;
}
