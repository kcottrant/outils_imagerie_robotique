#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int
_find(int p, int* roots)
{
  while(roots[p] != p)
    p = roots[p];
  return p;
}

int
_union(int r0, int r1, int* roots)
{
  if(r0 == r1) return r0;
  if(r0 == -1) return r1;
  if(r1 == -1) return r0;
  if(r0 <  r1){
    roots[r1] = r0;
    return r0;
  }else{
    roots[r0] = r1;
    return r1;  
  }
}

int
_add(int p, int r, int* roots)
{
  if(r==-1) 
    roots[p] = p;
  else 
    roots[p] = r;
  return roots[p];
}

void 
process(const char* imsname,const char* regname,const char* colorname)
{
  (void) colorname;
  (void) regname;
  Mat ims = imread(imsname);

  Mat carte_label(ims.rows,ims.cols,CV_8UC1);
  Mat carte_color(ims.rows,ims.cols,CV_8UC3,Scalar(0,0,0));
  
  if(!ims.data){
    cerr<<"Image not found, exit"<<endl;
    exit(EXIT_FAILURE);
  }

  cvtColor(ims, ims, CV_BGR2GRAY);
 
  int* roots = new int[ims.total()];
  int  rows  = ims.rows;
  int  cols  = ims.cols;
  int p      = 0;
  int r      = -1;
  uchar* ps  = ims.data;
  
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      r = -1;

      if( j>0 && (*(ps-1) == (*ps)) )
	r = _union( _find(p-1, roots), r, roots);

      if( (i>0 && j>0) && (*(ps-1-cols) == (*ps)) ) 
	r = _union( _find(p-1-cols, roots), r, roots);

      if( i>0 && (*(ps-cols) == (*ps)) ) 
	r = _union(_find(p-cols, roots), r, roots);

      if( (j<(cols-1) && i>0) && (*(ps+1-cols) == (*ps)) )
	r = _union(_find(p+1-cols, roots), r, roots);

      r = _add(p, r, roots);

      p++; 
      ps++; 
    }
  }

  for(p=0; p<rows*cols; p++){ 
    roots[p] = _find(p, roots);
  }
  
  int l=0;
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      int p = i*cols+j;
      if(roots[p] == p)
	roots[p] = l++;
      else
	roots[p] = roots[roots[p]];
    }
  }
  // carte labélisée
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      int p = i*cols+j;
      carte_label.at<uchar>(i,j)=roots[p];
    }
  }
  // Définition d'un tableu de couleurs
  Vec3b couleurs[l];
   srand(time(NULL));
    for(int c=1;c<=l;c++)
    {
        int B = rand() % 256;
	int G = rand() % 256;
	int R= rand() % 256;
	Vec3b vect(B,G,R);
	couleurs[c]=vect;
    }
  // carte colorée
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      for(int c=1;c<=l;c++)
      {
        if(carte_label.at<uchar>(i,j)==c)
        {
	  carte_color.at<Vec3b>(i,j)=couleurs[c];
	}
      }
    }
  }

  imwrite(regname,carte_label);
  imwrite(colorname,carte_color);
  cout<<"labeling: "<< l << " components detected"<<endl;
  delete [] roots;
}

void 
usage (const char *s)
{
  std::cerr<<"Usage: "<<s<<" ims"<<std::endl;
  exit(EXIT_FAILURE);
}

#define param 3
int 
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1],argv[2],argv[3]);
  return EXIT_SUCCESS;  
}

