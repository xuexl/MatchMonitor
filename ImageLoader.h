#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include<opencv2/core/core.hpp>

class ImageLoader
{
public:
    ImageLoader();
    
    cv::Mat imgRead(const char* f);
    
};

#endif // IMAGELOADER_H
