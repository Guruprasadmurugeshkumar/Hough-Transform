/*  this function is an implementation of the edge detector to detect the edges - Sobel operator
    the kernel used for detecting the edges is defined with pre-determined values
	the resultant image is binarised before saving 
Input: 
	   filtered image : img_mono
	   name of the file to be stored : img_name
	   a variable to catch exceptions: info
output: 
      resultant image stored at the location of the specified directory
return value:
      edge detected image which is binarised
*/

#include<iostream>
#include "Image.h"
#include "sobeloperator.h"

Image<float> sobel_edge_detector(Image<float>& image_mono,const string& img_name,bool& info)
{
	float var;

	for (unsigned int u = 0; u < image_mono.w; ++u) {
		for (unsigned int v = 0; v < image_mono.h; ++v) {
			if (u == 0 || v == 0 || u >= 799 || v >= 599) {
				Xdir_image.At(u, v) = 0.0;
				Ydir_image.At(u, v) = 0.0;
			}
			else {
				Xdir_image.At(u, v) = ((image_mono.At(u - 1, v - 1)*Xdkernel[0][0]) + (image_mono.At(u - 1, v)*Xdkernel[0][1]) + (image_mono.At(u - 1, v + 1)*Xdkernel[0][2]) + (image_mono.At(u, v - 1)*Xdkernel[1][0]) + (image_mono.At(u, v)*Xdkernel[1][1]) + (image_mono.At(u, v + 1)*Xdkernel[1][2]) + (image_mono.At(u + 1, v - 1)*Xdkernel[2][0]) + (image_mono.At(u + 1, v)*Xdkernel[2][1]) + (image_mono.At(u + 1, v + 1)*Xdkernel[2][2]));
				Ydir_image.At(u, v) = ((image_mono.At(u - 1, v - 1) * Ydkernel[0][0]) + (image_mono.At(u - 1, v) * Ydkernel[0][1]) + (image_mono.At(u - 1, v + 1)*Ydkernel[0][2]) + (image_mono.At(u, v - 1)*Ydkernel[1][0]) + (image_mono.At(u, v)*Ydkernel[1][1]) + (image_mono.At(u, v + 1)*Ydkernel[1][2]) + (image_mono.At(u + 1, v - 1)*Ydkernel[2][0]) + (image_mono.At(u + 1, v)*Ydkernel[2][1]) + (image_mono.At(u + 1, v + 1)*Ydkernel[2][2]));
			}
		}
	}

	cout << "    Binarising the image...." << endl;

	for (unsigned int u = 0; u < grad_image.w; ++u) {
		for (unsigned int v = 0; v < grad_image.h; ++v) {
			grad_image.At(u, v) = sqrt((Xdir_image.At(u, v) * Xdir_image.At(u, v)) + (Ydir_image.At(u, v) * Ydir_image.At(u, v)));

			if (grad_image.At(u, v) > 100) {
				grad_image.At(u, v) = 255;
			}
			else {
				grad_image.At(u, v) = 0;
			}
		}
	}
	
	cout << "    Saving  sobel image..." << endl;
	if (!grad_image.Save(img_name + "_sobel.bmp")) {
		cerr << "    Could not save image!" << endl;
		info =  false;
	}

	return grad_image;
}
