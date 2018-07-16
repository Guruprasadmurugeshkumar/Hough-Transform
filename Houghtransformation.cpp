/* this is the hough transform function for calculating the detected lines in an image.
   the lines are calculated and stored in the hough space using an accumulator and then
   recalculated and drawn on the image
   
   Input: 
          edge detected image : img_hough
		  colour image to store result : result
		  name of the file to be stored : img_name

   output:
          accumulator and the resultant image stored at the location of the specified directory

   return value:
                none
   */


#include "Houghtransformation.h"

#include "Image.h"

#include <cmath>

#include <iostream>

#include <stdlib.h>

#include <string.h>


#define DEG2RAD 0.017453293f

using namespace std;


void Dotransform(Image<float>& img_hough,ImageRGB& result,const string& img_data){

	int h = img_hough.h;
	int w = img_hough.w;

	int img_w = w;
	int img_h = h;

	float cosine[180];
	float sine[180];

	// look_up table calculation

	for (int u = 0; u < 180; u++) { 
		cosine[u] = cos(u*DEG2RAD);
		sine[u] = sin(u*DEG2RAD);
	}

	// accumulator height, width calculation
	double hough_h = (int)round((sqrt(2.0) * (double)(h>w ? h : w)) / 2.0);

	double accu_h = hough_h * 2;

	double accu_w = 180; // accumulator width pre-determined

	int thres = round(accu_h / 7); // Any changes to the denominator value affects the final result

	// accumulator declaration

	Image<float> accu(accu_w, accu_h);

	int center_x = w / 2;

	int center_y = h / 2;

	// accumulator initialisation
	for (int u = 0; u < accu_h; u++) {
		for (int v = 0; v < accu_w; v++) {
			accu.At(u, v) = 0.0;
		}
	}

	//calculation of polar co-ordinate parameter r, theta

	for (int x = 0; x<w; x++) {
		for (int y = 0; y<h; y++) {

			if (img_hough.At(x, y) > 0) {

				for (int t = 0; t<180; t++) {

					double r = (((x - center_x) * cosine[t]) + ((y - center_y) * sine[t])); // calculation of r-value
					int rvalue = (int)(round(r + hough_h));
					accu.At(t, rvalue)++; // incrementing the accumulator value

				}

			}

		}

	}
	// saving the accumulator
	cout << "    Saving hough_accumulator image..." << endl;
	if (!accu.Save(img_data + "_accu.bmp")) {
		cerr << "    Could not save image!" << endl;
		return;
	}

	// generating lines from the accumulator

	for (int r = 0; r < accu_h; r++) {

		for (int t = 0; t < accu_w; t++) {
			if (r == 0 || t == 0 || r >= 1130 || t >= 179) {
				continue;
			}
			else {
				if ((int)accu.At(t, r) >= thres) {

					int max = (int)accu.At(t, r);

					// calculation of local maxima in the accumulator

					for (int ii = -1; ii < 2; ii++) {
						for (int jj = -1; jj < 2; jj++) {
							int m = accu.At(t + ii, r + jj);
							if (max < m) {
								max = m;
							}
						}
					}
					if (max >(int)accu.At(t, r)) {
						continue;
					}

					int x1, y1, x2, y2;

					x1 = y1 = x2 = y2 = 0;

					int r2 = round(r - hough_h);

					// calculation of co-ordinates of the lines

					if (t >= 45 && t <= 135) {

						for (x1 = 1; x1 < img_w; x1++) {

							y1 = (int)round(((r2 - ((x1 - (center_x)) * cosine[t])) / (sine[t])) + center_y);

							if (y1 < 0) {
								y1 = y1 * -1;
							}

							if ((x1 > 799) || (y1 > 599)) {
								continue;
							}
							else {
								result.At(x1, y1).R = 0.0; // drawing the lines on the image
								result.At(x1, y1).G = 0.0;
								result.At(x1, y1).B = 255.0;
							}
						}
					}

					else {

						for (y1 = 1; y1 < (img_h - 1); y1++) {

							x1 = (int)round(((r2 - ((y1 - (center_y)) * sine[t])) / (cosine[t])) + center_x);

							if (x1 < 0) {
								x1 = x1 * -1;
							}

							if ((x1 > 799) || (y1 > 599)) {
								continue;
							}
							else {
								result.At(x1, y1).R = 0.0; // drawing the lines on the image
								result.At(x1, y1).G = 0.0;
								result.At(x1, y1).B = 255.0;
							}
						}
					}
				}
			}
		}
	}
	// saving the final image
	cout << "    Saving Final image..." << endl;
	if (!result.Save(img_data + "_res.bmp")) {
		cerr << "    Could not save image!" << endl;
		return;
	}
	return;

	}

