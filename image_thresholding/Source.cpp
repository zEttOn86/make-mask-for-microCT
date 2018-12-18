/*
* This implementaion use itk
* Image Thresholding
* @auther tozawa
* @history
* 20171113
*/
#include <iostream>
#include "ItkImageIO.h"

typedef unsigned char IMG;
typedef long long IN_TYPE;
void main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Usage:" << std::endl;
		std::cerr << argv[0] << " inputFile(.mhd) outFile(.mhd) Threshold" << std::endl;
		exit(1);
	}
	const char * inputFileName = argv[1];
	const char * outputFileName = argv[2];
	const int threshold = atoi(argv[3]);
	
	std::vector<IMG> img;
	ImageIO<3> mhdi;
	mhdi.Read(img, inputFileName);
	IN_TYPE xe = mhdi.Size(0);
	IN_TYPE ye = mhdi.Size(1);
	IN_TYPE ze = mhdi.Size(2);
	IN_TYPE se = xe*ye*ze;
	std::cout << xe << " " << ye << " " << ze << " " << se << std::endl;

	// binary image
	std::vector<IMG> mask(se);
	for (IN_TYPE s = 0; s < se; s++) {
		if (img.at(s) >= threshold) mask.at(s) = UCHAR_MAX;
	}
	std::cout << "After threshold" << std::endl;
	mhdi.Write(mask, outputFileName);
}