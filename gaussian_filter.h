#pragma once
#ifndef GAUSSIAN_FILTER_H
#define GAUSSIAN_FILTER_H

#include<iostream>
#include "Image.h"

using namespace std;

//declaration of gaussian kernel
//float gausskernel[5][5] = { { 2,4,5,4,2 },{ 4,9,12,9,4 },{ 5,12,15,12,5 },{ 4,9,12,9,4 },{ 2,4,5,4,2 } };
float gausskernel[3][3] = { {0.107035,0.113092,0.107035},{0.113092,0.119491,0.113092},{ 0.107035,0.113092,0.107035 } };
//declaration of images
Image<float> image_gauss(800, 600);
Image<float> gaussian_image(800, 600);

Image<float> gaussblur(Image<float>&,const string&,bool&);

#endif
