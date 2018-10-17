#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void
process(const char* imsname)
{
  Mat image = imread(imsname,1);
  Mat rgb[3],rgb2blue,rgb2green,rgb2red,rgb2YCrCb,YCrCb2rgb,YCbCr[3];   //destination array

  //Canaux RGB
  split(image,rgb);//split source

 imshow("blue",rgb[0]); //blue channel
 waitKey(0);
 imshow("green",rgb[1]); //green channel
 waitKey(0);
 imshow("red",rgb[2]); //red channel
 waitKey(0);

 // RGB en gris
  Mat rgb2grey;
  cvtColor(image, rgb2grey,CV_RGB2GRAY);
  imshow("Rgb2grey",rgb2grey);
  waitKey(0);

  //RGB en YCBCR
  cvtColor(image,rgb2YCrCb,CV_RGB2YCrCb);
  cvtColor(rgb2YCrCb,YCrCb2rgb,CV_YCrCb2RGB);
  imshow("RGB->YCrCb->RGB",YCrCb2rgb);
  waitKey(0);

  // Canaux  Y,Cb et Cr
  split(rgb2YCrCb,YCbCr);
  imshow("Y",YCbCr[0]); //Y channel
  waitKey(0);
  imshow("Cr",YCbCr[1]); //Cr channel
  waitKey(0);
  imshow("Cb",YCbCr[2]); //Cb channel
  waitKey(0);

  //Différence entre niveau de gris et composante Y
  Mat diffygris;
  subtract(rgb2grey,YCbCr[0],diffygris);
  imshow("différence niveau gris et Y",diffygris);
  waitKey(0);
  cout << "Aucune différence entre le niveau de gris et le canal Y car le canal Y représente le niveau de gris d'une image"<< endl;

  //Différence entre niveau de gris et composante Y
  Mat diffRgbInitiale;
  subtract(image,YCrCb2rgb,diffRgbInitiale);
  imshow("différence image initiale et image RGB reconvertit",diffRgbInitiale);
  waitKey(0);
  cout << "Aucune différence entre l'image initiale et l'image RGB reconvertit car aucunes pertes d'informations lors de la conversion"<< endl;




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
