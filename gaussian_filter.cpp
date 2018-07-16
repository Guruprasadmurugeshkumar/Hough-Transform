/* function for gaussian filter- this filter is used for the smoothing operation of the image
   The kernel is calculated previously outside the program and is declared with the pre-determined values
   Input: 
          monochrome image : img_gauss
          name of the file to be stored : img_name
		  a variable to test exceptions : info
   output:
          the resultant image stored at the location of the specified directory

   return value :  
                 filtered image
   */

#include<iostream>
#include "Image.h"
#include "gaussian_filter.h"

using namespace std;

//Gaussian blur function:

Image<float> gaussblur(Image<float>& image_gauss, const string& img_name, bool& info) {
	float sum = 0;
	float var = 0;

	for (unsigned int u = 0; u < image_gauss.w; ++u) {
		for (unsigned int v = 0; v < image_gauss.h; ++v) {
			if (u == 0 || v == 0 || u >= 799 || v >= 599) {
				var = image_gauss.At(u, v);
				gaussian_image.At(u, v) = var;
			}
			else {
				gaussian_image.At(u, v) = ((image_gauss.At(u - 1, v - 1)*gausskernel[0][0]) + (image_gauss.At(u - 1, v)*gausskernel[0][1]) + (image_gauss.At(u - 1, v + 1)*gausskernel[0][2]) + (image_gauss.At(u, v - 1)*gausskernel[1][0]) + (image_gauss.At(u, v)*gausskernel[1][1]) + (image_gauss.At(u, v + 1)*gausskernel[1][2]) + (image_gauss.At(u + 1, v - 1)*gausskernel[2][0]) + (image_gauss.At(u + 1, v)*gausskernel[2][1]) + (image_gauss.At(u + 1, v + 1)*gausskernel[2][2]));
			}
		}
	}

	cout << "    Saving Gauss image..." << endl;
	if (!gaussian_image.Save(img_name + "_gauss.bmp")) {
		cerr << "    Could not save image!" << endl;
		info = false;
	}
	return gaussian_image;
}
