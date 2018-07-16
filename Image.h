#pragma once

#include <string>
#include <vector>

/** @class PixelRGB
* @brief Defines 3-channel pixel
*/
struct PixelRGB
{
	/// Red channel value
	unsigned char R;
	/// Green channel value
	unsigned char G;
	/// Blue channel value
	unsigned char B;
};

/** @group _Private
* @brief Internal private definitions. Do not use directly.
*/
namespace _Private
{
	template <typename PixelType>
	struct _PixelTraits
	{
		enum { CHANNELS = 1 };
		typedef PixelType ValueType;
		typedef PixelType PixelType;
	};

	template <>
	struct _PixelTraits<PixelRGB>
	{
		enum { CHANNELS = 3 };
		typedef unsigned char ValueType;
		typedef PixelRGB PixelType;
	};

	bool _LoadBMP(const std::string& p_path, std::vector<unsigned char>& p_data, unsigned int& w, unsigned int& h);
	bool _SaveBMP(const std::string& p_path, const std::vector<unsigned char>& p_data, unsigned int w, unsigned int h);
}

/** @class ImageBase
* @brief Base image structure. Stores image buffer and dimensions
* \tparam PixelT Type of pixel
*/
template <typename PixelT>
struct ImageBase
{
	/// Number of image channels (1 and 3-channel images are supported)
	enum { CHANNELS = _Private::_PixelTraits<PixelT>::CHANNELS };
	/// Type of the pixel data
	typedef typename _Private::_PixelTraits<PixelT>::ValueType ValueType;
	/// Type of the pixel
	typedef typename _Private::_PixelTraits<PixelT>::PixelType PixelType;

	/// Image height
	unsigned int h;
	/// Image width
	unsigned int w;
	/// Image buffer
	std::vector<PixelType> pixels;
};

/** @class Image
* @brief Provides basic image functionality: loading and saving from file
* \tparam DataT Type of pixel data
*/
template <typename DataT>
struct Image : public ImageBase<DataT>
{
	/// @brief Default constructor
	Image() {}
	
	/// @brief Constructor
	/// [in] image width
	/// [in] image height
	Image(unsigned int width, unsigned int height) 
	{
		w = width;
		h = height;
		pixels.resize(w*h);
	}
	
	/// @brief Virtual destructor
	virtual ~Image() {}

	/// @brief Loads image data from BMP file
	/// [in] path to BMP file
	/// @return status (success or failure)
	virtual bool Load(const std::string& p_path)
	{
		std::vector<unsigned char> buffer;
		return (_Private::_LoadBMP(p_path, buffer, w, h) && FillImage<PixelType>(buffer));
	}

	/// @brief Save image data to BMP file
	/// [in] path to BMP file
	/// @return status (success or failure)
	virtual bool Save(const std::string& p_path) const
	{
		std::vector<unsigned char> buffer;
		return (FillBuffer<PixelType>(buffer) && _Private::_SaveBMP(p_path, buffer, w, h));
	}

	/// @brief Gives access to a single pixel
	/// [in] horizontal pixel coordinate (x, column)
	/// [in] vertical pixel coordinate (y, row)
	/// @return value of the requested pixel
	PixelType& At(unsigned int u, unsigned int v) { return pixels[w*v + u]; }

	/// @brief Gives read only access to a single pixel
	/// [in] horizontal pixel coordinate (x, column)
	/// [in] vertical pixel coordinate (y, row)
	/// @return value of the requested pixel
	const PixelType& At(unsigned int u, unsigned int v) const { return pixels[w*v + u]; }

private:
	template <typename PixelT>
	bool FillImage(const std::vector<unsigned char>& p_buffer)
	{
		if (p_buffer.size() != w*h*3) return false;
		pixels.resize(w*h);
		for (unsigned int i = 0; i < w*h; ++i) {
			pixels[i] = typename _Private::_PixelTraits<PixelType>::ValueType(((double)p_buffer[3 * i] + (double)p_buffer[3 * i + 1] + (double)p_buffer[3 * i + 2]) / 3.0);
		}
		return true;
	}

	template <typename PixelT>
	bool FillBuffer(std::vector<unsigned char>& p_buffer) const
	{
		p_buffer.resize(w*h*3);
		for (unsigned int i = 0; i < w*h; ++i) {
			p_buffer[3 * i] = p_buffer[3 * i + 1] = p_buffer[3 * i + 2] = (unsigned char)pixels[i];
		}
		return true;
	}

	template <>
	bool FillImage<PixelRGB>(const std::vector<unsigned char>& p_buffer) { return false; }

	template <>
	bool FillBuffer<PixelRGB>(std::vector<unsigned char>& p_buffer) const { return false; }
};

/** @class ImageRGB
* @brief Defines 3-channel RGB image which stores 8-bit data
*/
struct ImageRGB : public Image<PixelRGB>
{
	/// Default constructor
	ImageRGB() {}

	/// @brief Constructor
	/// [in] image width
	/// [in] image height
	ImageRGB(unsigned int width, unsigned int height);

	/// @brief Virtual destructor
	virtual ~ImageRGB() override{}

	/// @brief Loads image data from BMP file
	/// [in] path to BMP file
	/// @return status (success or failure)
	virtual bool Load(const std::string& p_path) override;

	/// @brief Saves image data to BMP file
	/// [in] path to BMP file
	/// @return status (success or failure)
	virtual bool Save(const std::string& p_path) const override;

	/// @brief Converts RGB image to monochrome with desired pixel data type
	/// \tparam DataT Pixel data type
	/// [in] placeholder for the converted image (will be overwritten!)
	template <typename DataT>
	void Convert(Image<DataT>& p_img_mono) const
	{
		p_img_mono.w = w;
		p_img_mono.h = h;
		p_img_mono.pixels.resize(w*h);
		for (unsigned int i = 0; i < w*h; ++i) {
			p_img_mono.pixels[i] = DataT(((double)pixels[i].R + (double)pixels[i].G + (double)pixels[i].B) / 3.0);
		}
	}
};
