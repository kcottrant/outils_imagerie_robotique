#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>

#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;
VideoCapture cap;
Mat frame;
int  alpha_slider;
bool boucle; 

static void on_trackbar( int i_track, void* )
{

  alpha_slider = i_track;
  cap.set(CV_CAP_PROP_POS_FRAMES,alpha_slider);
  boucle = true;
}

void
process(const char* vidname)
{
  cap.open(vidname);
  double nb_frame = cap.get(CV_CAP_PROP_FRAME_COUNT);
  double fps = cap.get(CV_CAP_PROP_FPS);
  int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  cout << "nombre de frames: "<< nb_frame<<"\nfps: "<<fps <<"\nwidth: "<<width<<"\nheight: "<<height<<endl;
  namedWindow("Video",1);
  createTrackbar("slide bar","Video",&alpha_slider,nb_frame,on_trackbar);
  for(alpha_slider=0;alpha_slider<nb_frame;alpha_slider++)
  {
    if(boucle)
      {
	boucle = false;
	cout << "go to frame number : "<<alpha_slider-1<<endl;
      }
    Point coin(10,20);
    cap.read(frame);
    if(!frame.data)
      break;
    else
    {
      if(alpha_slider<1000){
	ostringstream str;
	str << "frame  number : "<< alpha_slider;
	putText(frame,str.str(),coin,FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA); 
      }      
      imshow("Video",frame);
      
      //on_trackbar( alpha_slider, 0 );
      }
    
    if(waitKey(30)>=0)
      break;
  }
 
  (void) vidname;
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
  alpha_slider=0;
  boucle=false;
  process(argv[1]);
  return EXIT_SUCCESS;  
}
