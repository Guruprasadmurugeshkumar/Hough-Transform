#include "Image.h"

#include <windows.h>

bool _Private::_LoadBMP(const std::string& p_path, std::vector<unsigned char>& p_data, unsigned int& w, unsigned int& h)
{
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;
	DWORD bytesread;
	bool ok = true;

	HANDLE file = ::CreateFileA(p_path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	ok = file != INVALID_HANDLE_VALUE;
	if (ok) ok = ::ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) != 0;
	if (ok) ok = ::ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) != 0;
	if (ok) ok = bmpheader.bfType == 'MB';
	if (ok) ok = bmpinfo.biCompression == BI_RGB;
	if (ok) ok = bmpinfo.biBitCount == 24;

	if (ok) {
		w = bmpinfo.biWidth;
		h = abs(bmpinfo.biHeight);
		p_data.resize(w*h * 3);

		::SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
		ok = ::ReadFile(file, p_data.data(), p_data.size(), &bytesread, NULL) != 0;
	}

	::CloseHandle(file);
	return ok;
}

bool _Private::_SaveBMP(const std::string& p_path, const std::vector<unsigned char>& p_data, unsigned int w, unsigned int h)
{
	bool ok = true;
	DWORD byteswritten = 0;

	// Some basic bitmap parameters  
	unsigned long headers_size = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	unsigned long pixel_data_size = h * w * 3;
	if (pixel_data_size != p_data.size()) return false;

	BITMAPINFOHEADER bmpinfo = { 0 };

	bmpinfo.biSize = sizeof(BITMAPINFOHEADER);	// Set the size 
	bmpinfo.biBitCount = 24;					// Bit count 
	bmpinfo.biClrImportant = 0;					// Use all colors
	bmpinfo.biClrUsed = 0;						// Use as many colors according to bits per pixel  
	bmpinfo.biCompression = BI_RGB;				// Store as uncompressed
	bmpinfo.biHeight = h;						// Set the height in pixels  
	bmpinfo.biWidth = w;						// Width of the Image in pixels  
	bmpinfo.biPlanes = 1;						// Default number of planes  
	bmpinfo.biSizeImage = pixel_data_size;		// Calculate the image size in bytes  

	BITMAPFILEHEADER bmpheader = { 0 };
	bmpheader.bfType = 'MB';
	bmpheader.bfOffBits = headers_size;					// Offset to the RGB data   
	bmpheader.bfSize = headers_size + pixel_data_size;	// Total size of image including size of headers

	// Create the file in disk to write  
	HANDLE file = ::CreateFileA(p_path.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	ok = file != INVALID_HANDLE_VALUE;
 
	if (ok) ok = ::WriteFile(file, &bmpheader, sizeof(bmpheader), &byteswritten, NULL) != 0;		// Write the File header 
	if (ok) ok = ::WriteFile(file, &bmpinfo, sizeof(bmpinfo), &byteswritten, NULL) != 0;			// Write the bitmap info header 
	if (ok) ok = ::WriteFile(file, p_data.data(), bmpinfo.biSizeImage, &byteswritten, NULL) != 0;	// Write the RGB Data  

	::CloseHandle(file);
	return ok;
}

ImageRGB::ImageRGB(unsigned int width, unsigned int height)
{
	w = width;
	h = height;
	pixels.resize(w*h);
}

bool ImageRGB::Load(const std::string& p_path)
{
	std::vector<unsigned char> buffer;
	if (_Private::_LoadBMP(p_path, buffer, w, h)) {
		if (buffer.size() != w*h*3) return false;
		pixels.resize(w*h);
		for (unsigned int i = 0; i < w*h; ++i) {
			pixels[i].R = buffer[3 * i];
			pixels[i].G = buffer[3 * i + 1];
			pixels[i].B = buffer[3 * i + 2];
		}
		return true;
	}
	return false;
}

bool ImageRGB::Save(const std::string& p_path) const
{
	std::vector<unsigned char> buffer(w*h*3);
	for (unsigned int i = 0; i < w*h; ++i) {
		buffer[3 * i] = pixels[i].R;
		buffer[3 * i + 1] = pixels[i].G;
		buffer[3 * i + 2] = pixels[i].B;
	}
	return _Private::_SaveBMP(p_path, buffer, w, h);
}
