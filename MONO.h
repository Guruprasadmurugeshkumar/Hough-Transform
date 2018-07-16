#pragma once

#ifndef MONO_H
#define MONO_H

#include <iostream>
#include <stdlib.h>
#include "Image.h"

using namespace std;

Image<float> convert_to_mono(ImageRGB&,const string&, bool&);

#endif
