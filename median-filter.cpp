#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <list>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int compare(const void* a, const void* b)
{
	const int* x = (int*) a;
	const int* y = (int*) b;

	if (*x > *y)
		return 1;
	else if (*x < *y)
		return -1;

	return 0;
}

void
process(int radius, const char* imsname, const char* imd)
{
  (void)imd;
  Mat rgb2grey, image,image_blur;
  int mediane, taille;
  image = imread(imsname);
  cvtColor(image, rgb2grey,CV_RGB2GRAY);
  Mat image_filtre(rgb2grey.rows, rgb2grey.cols, CV_8UC1);
  vector <int> voisins;
  for(int i=0; i<rgb2grey.rows;i++)
  {
    for(int j=0;j<rgb2grey.cols;j++)
    {
      voisins.clear();
      for(int k=1;k<=radius;k++)
      {
        for(int w=-k;w<k+1;w++)
        {
          if(i-k>=0 && j+w>=0 && j+w<rgb2grey.cols)
          {
            // en haut
            voisins.push_back(rgb2grey.at<uchar>(i-k,j+w));
          }
          if(i+k>=0 && i+k<rgb2grey.rows && j+w>=0 && j+w<rgb2grey.cols)
          {
            // en bas
            voisins.push_back(rgb2grey.at<uchar>(i+k,j+w));
          }
        }
        for(int w=-k+1;w<k*2-1;w++)
        {
          if(i+w>=0 && i+w<rgb2grey.rows && j+k>=0 && j+k<rgb2grey.cols)
          {
            // à droite
            voisins.push_back(rgb2grey.at<uchar>(i+w,j+k));
          }
          if(i+w>=0 && i+w<rgb2grey.rows && j-k>=0 && j-k<rgb2grey.cols)
          {
            // en gauche
            voisins.push_back(rgb2grey.at<uchar>(i+w,j-k));
          }
        }
      }
      taille = voisins.size();
      qsort(&voisins.front(), taille, sizeof(int), compare);
      if(taille%2 == 0){
        mediane = ((voisins.at(taille/2-1))+voisins.at(taille/2))/2;
      }
      else{
        mediane = voisins.at(taille/2);
      }
      image_filtre.at<uchar>(i,j) = mediane;
    }
  }
  imwrite(imd,image_filtre);

  medianBlur(rgb2grey, image_blur, radius*2+1);

  Mat diffygris;
  subtract(image_blur,image_filtre,diffygris);

  //resultats equivalents entre la fonction opencv et notre fonction
}

void
usage (const char *s)
{
  fprintf(stderr, "Usage: %s imsname\n", s);
  exit(EXIT_FAILURE);
}

#define param 3
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(atoi(argv[1]),argv[2],argv[3]);
  return EXIT_SUCCESS;
}
