#ifndef PUBLIC_TYPE_H
#define PUBLIC_TYPE_H
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <math.h>
#include <cstdlib>
#include <QImage>
using namespace cv;
using namespace std;

int const arraynum = 200;
typedef struct MatArray
{
    int counter;
    Mat Frame[arraynum];
};


#endif // PUBLIC_TYPE_H
