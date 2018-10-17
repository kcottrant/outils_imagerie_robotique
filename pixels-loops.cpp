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
  Mat outImg, outImg2, outImg3,outImg4;
  Size size(10240,10240);
  resize(image, outImg, size);
  cout << "largeur : "<< outImg.size().width << endl;
  cout << "longueur : "<<outImg.size().height << endl;
  // Operateur at
  double t  =(double) getTickCount();
  for(int i=0;i<outImg.size().width;i++)
  {
    for(int j=0;j<outImg.size().height;j++)
    {
      for( int g=0;g<3;g++)
	{
	  outImg.at<Vec3b>(i,j).val[g]=(1.0/64)*outImg.at<Vec3b>(i,j).val[g]*64+64/2;
	}   
    }
  }
  t = ((double)getTickCount() - t)/getTickFrequency();
  cout << "temps écoulé (at)(en s) : "<< t << endl;
  
  // Iterator
  resize(image, outImg2, size);
  Mat_<Vec3b>::iterator it, itEnd;
  t  =(double) getTickCount();
  for( it = outImg2.begin<Vec3b>(), itEnd = outImg2.end<Vec3b>(); it != itEnd; ++it)
  {  
    (*it)[0] = (1.0/64)*(*it)[0]*64+64/2;
    (*it)[1] = (1.0/64)*(*it)[1]*64+64/2;
    (*it)[2] = (1.0/64)*(*it)[2]*64+64/2;
  }
  t = ((double)getTickCount() - t)/getTickFrequency();
  cout << "temps écoulé (iterator) : (en s) "<< t << endl;

  // Opération matricielle
  resize(image,outImg3,size);
  t  =(double) getTickCount();
  Mat multiplication(outImg3.rows,outImg3.cols,CV_32FC3);
  Mat division(outImg3.rows,outImg3.cols,CV_32FC3);
  Mat resultat(outImg3.rows,outImg3.cols,CV_32FC3);
  divide(outImg3,64.0,division);
  multiply(division,64.0,multiplication);
  add(multiplication,32.0,resultat);
  // approximations du aux arrondis 
  t = ((double)getTickCount() - t)/getTickFrequency();
  cout << "temps écoulé (operation matricielle)(en s) : "<< t << endl;

  // Pointeurs
  resize(image,outImg4,size);
  t  =(double) getTickCount();
  for (int y = 0; y < outImg4.rows; ++y)
    {
      Vec3b* row_ptr = outImg4.ptr<Vec3b>(y);
      for (int x = 0; x < outImg4.cols; ++x,++row_ptr)
	{
	 row_ptr->val[0] = (1.0/64)*row_ptr->val[0]*64+64/2;
	 row_ptr->val[1] = (1.0/64)*row_ptr->val[1]*64+64/2;
	 row_ptr->val[2] = (1.0/64)*row_ptr->val[2]*64+64/2;
	}
    }
  t = ((double)getTickCount() - t)/getTickFrequency();
  cout << "temps écoulé (pointeurs)(en s) : "<< t << endl;
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
