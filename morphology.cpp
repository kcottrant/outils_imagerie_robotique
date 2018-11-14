#include <morphology.hpp>

using namespace cv;

void
mm(Mat se, Mat ims, Mat imd, void (*pf)(uchar, uchar*))
{
  uchar minmax;
  uchar * pointeur = &minmax;
  int radius = (se.cols-1)/2;

  for(int i=0; i<imd.cols;i++)
	{
		for(int j=0;j<imd.rows;j++)
		{
      if(pf==maximum)
      {
        minmax=(uchar)0;
      }
      else
      {
        minmax=(uchar)255;
      }
			for(int k=1;k<=radius;k++)
			{
				for(int w=-k;w<k+1;w++)
				{
					if(i-k>=0 && j+w>=0 && j+w<ims.cols)
					{
						// en haut
            if(se.at<uchar>(radius-k, radius+w) == (uchar)255){
              (*pf)(ims.at<uchar>(i-k,j+w), pointeur);
            }
					}
					if(i+k>=0 && i+k<ims.rows && j+w>=0 && j+w<ims.cols)
					{
						// en bas
            if(se.at<uchar>(radius+k, radius+w) == (uchar)255){
              (*pf)(ims.at<uchar>(i+k,j+w), pointeur);
            }
					}
				}
				for(int w=-k+1;w<k;w++)
				{
					if(i+w>=0 && i+w<ims.rows && j+k>=0 && j+k<ims.cols)
					{
						// à droite
            if(se.at<uchar>(radius+w, radius+k) == (uchar)255){
              (*pf)(ims.at<uchar>(i+w,j+k), pointeur);
            }
					}
					if(i+w>=0 && i+w<ims.rows && j-k>=0 && j-k<ims.cols)
					{
						// en gauche
            if(se.at<uchar>(radius+w, radius-k) == (uchar) 255){
              (*pf)(ims.at<uchar>(i+w,j-k), pointeur);
            }
					}
				}
			}
      imd.at<uchar>(i,j)=minmax;
		}
	}
}

void
maximum(uchar val, uchar* max)
{
  if(val>*max){
    *max=val;
  }
}

void
minimum(uchar val, uchar* min)
{
  if(val<*min){
    *min=val;
  }
}
