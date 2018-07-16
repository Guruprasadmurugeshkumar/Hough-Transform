/* this funstion takes an image with three color channels (RGB) and converts it into a monochromatic image
   Input: 
          RGB image : img_rgb
          name of the file to be stored : img_name
		  a variable to test exceptions : info
   output:
          the resultant image stored at the location of the specified directory

   return value :  
                 monochrome image
*/



#include "Image.h"
#include "MONO.h"

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;


Image<float> convert_to_mono(ImageRGB& img_rgb,const string& img_name, bool& info)
{

	cout << "    Converting RGB image to monochrome floating point image..." << endl;
	Image<float> img_mono;
	img_rgb.Convert(img_mono);

	cout << "    Saving monochrome image..." << endl;
	if (!img_mono.Save(img_name + "_mono.bmp")) {
		cerr << "    Could not save image!" << endl;
		info = false;
	}
	return img_mono;
}
