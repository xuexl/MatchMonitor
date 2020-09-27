#include "ImageLoader.h"

#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv; 

ImageLoader::ImageLoader()
{
    
}

cv::Mat ImageLoader::imgRead(const char* f)
{
    Mat imgMat = cv::imread(f);

    cvtColor(imgMat, imgMat, COLOR_BGR2GRAY);
    cvtColor(imgMat, imgMat, COLOR_GRAY2RGB);
    
    return imgMat;
}
