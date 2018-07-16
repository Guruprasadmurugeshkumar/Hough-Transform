/*
 Hough transform is one of the edge detecting algorithms used in image processing it can be used for detecting lines, circles and other geoemtrical shapes. the generalized hough transform is used in the detection of arbitary shapes
 this program is developed for the implementation of the hough transform for detecting lines
 this program uses the sobel edge detector for detecting the edges and then the hough transform for detecting the lines
 this is the main program definition -  the control is transferred to the sub programs but is controlled by this program


 AUTHOR :: Guru Prasad Murugesh kumar ; STUDENT INDEX : 289031
 University :: POlitechnika warszawa
 Faculty : Mechatronics - Photonics Engineering
 Course - Title : Numerical Methods in Optical Techniques
*/

#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

#include "Image.h"
#include "MONO.h"
#include "sobeloperator.h"
#include "gaussian_filter.h"
#include "Houghtransformation.h"

using namespace std ;


bool info = true;

Image<float> tmp(800,600);


int _tmain(int argc, _TCHAR* argv[])
{

	string img_name = "images/image";

	cout << "    Loading image from file: \"" << img_name << ".bmp\"..." << endl;
	ImageRGB img_rgb;
	if (!img_rgb.Load(img_name + ".bmp")) {
		cerr << "    Could not load image!" << endl;
		info = false;
	}

	tmp = convert_to_mono(img_rgb,img_name, info);

	if (info == false) {
		return 0;
	}

	string img2_name = "images/image_mono";

	tmp = gaussblur(tmp,img2_name,info);

	if (info == false) {
		return 0;
	}
	
	string img3_name = "images/image_mono_gauss";

	tmp = sobel_edge_detector(tmp,img3_name,info);

	if (info == false) {
		return 0;
	}

	string img4_name = "images/image_mono_gauss_sobel";

	Dotransform(tmp,img_rgb,img4_name);

	return 0;
}


// end of the program
