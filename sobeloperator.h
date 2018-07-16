#pragma once
#ifndef SOBELOPERATOR_H
#define SOBELOPERATOR_H
#include "Image.h"
using namespace std;

// declaration of the image files
Image<float> Xdir_image(800, 600);
Image<float> Ydir_image(800, 600);
Image<float> grad_image(800, 600);
//Image<float> ang_image(800, 600);

// declaration of the kernel
float Ydkernel[3][3] = { { 1,2,1 },{ 0,0,0 },{ -1,-2,-1 } };
float Xdkernel[3][3] = { { 1,0,-1 },{ 2,0,-2 },{ 1,0,-1 } };


Image<float> sobel_edge_detector(Image<float>&,const string&,bool&);

#endif
