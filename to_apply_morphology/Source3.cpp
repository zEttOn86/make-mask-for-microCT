/*
* This implementation use itk
* Dilation & Erosion
* @auther tozawa
* @history
* 20171114
*/

#include "ItkImageIO.h"
#include "morphology.h"
typedef unsigned char IMG;
typedef long long IN_TYPE;

int main(int argc, char **argv)
{
	if (argc != 4) {
		std::cerr << "Usage : " << std::endl;
		std::cerr << argv[0] << " inputFile(.mhd) outputFileName(.mhd) ksize//radius" << std::endl;
		exit(1);
	}
	const char * inputFileName = argv[1];
	const char * outputFileName = argv[2];
	const unsigned char NDims = 3;
	const int radius = atoi(argv[3]);

	std::vector<IMG> img;
	ImageIO<NDims> mhdi;
	mhdi.Read(img, inputFileName);
	IN_TYPE xe = mhdi.Size(0);
	IN_TYPE ye = mhdi.Size(1);
	IN_TYPE ze = mhdi.Size(2);
	IN_TYPE se = xe*ze*ye;
	std::cout << xe << " " << ye << " " << ze << " " << se << std::endl;

	std::vector<IMG> out(se);
	if (morphology::dilation(img, xe, ye, ze, radius, out) != 0) {
		std::cerr << "Morphology failure" << std::endl;
		exit(-1);
	}
	mhdi.Write(out, outputFileName);

	return 0;
}