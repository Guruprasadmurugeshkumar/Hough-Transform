#pragma once


#ifndef HOUGHTRANSFORMATION_H
#define HOUGHTRANSFORMATION_H

#include <iostream>
#include <stdlib.h>
#include<vector>
#include "Image.h"

using namespace std;

int accu_w;
int accu_h;
int img_w;
int img_h;
unsigned int* accu;

vector<pair<pair<int, int>, pair<int, int> > > Lines;

vector<pair<pair<int, int>, pair<int, int> > >::iterator it;


vector<pair<int, int>> line;

vector<pair<int, int>>::iterator ite;

void Dotransform(Image<float>&,ImageRGB&,const string&);

#endif
