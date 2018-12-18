/*
* This implementaion use itk
* Otsu method
* VS2012
* Reference : "http://pynote.hatenablog.com/entry/2017/07/31/233616"
* @auther tozawa
* @history
* 20171110 For short
* 20171106 ‘å’Ã‚Ì2’l‰»
* 20171102
*/

#include "ItkImageIO.h"
#include <numeric>

typedef short IMG;
typedef int IN_TYPE;
template<class T, class T1>
double mean(const T start, const T end, const T numOfHist, std::vector<T1> &temp)
{
	double sum = 0.;
	for (T i = start; i <= end; i++) {
		sum += temp.at(i) * (double)i;
	}
	sum /= (double)numOfHist;
	return sum;
}
void main(int argc, char **argv)
{
	if (argc != 3) {
		std::cerr << "Usage : " << std::endl;
		std::cerr << argv[0] << " inputFile(.mhd) outputFileName(.mhd)" << std::endl;
		exit(1);
	}
	const char * inputFileName = argv[1];
	const char * outputFileName = argv[2];
	const unsigned char NDims = 3;

	std::vector<IMG> img;
	ImageIO<NDims> mhdi;
	mhdi.Read(img, inputFileName);
	IN_TYPE xe = mhdi.Size(0);
	IN_TYPE ye = mhdi.Size(1);
	IN_TYPE ze = mhdi.Size(2);
	IN_TYPE se = xe*ze*ye;
	std::cout << xe << " " << ye << " " << ze << " " << se<<std::endl;
	
	int max = *std::max_element(img.begin(), img.end());
	int min = *std::min_element(img.begin(), img.end());
	std::cout << "max, min " << max << " " << min << std::endl;
	
	// Vote bins
	std::vector<IN_TYPE> hist(max-min+1);
	for (IN_TYPE s = 0; s < se; s++) {
		hist.at(img.at(s) + std::abs(min))++;
	}

	// Calc Inter class variance
	int th = 0;
	double myu1, myu2, maxSigma, squared_sigma_b;
	myu1 = myu2 = maxSigma = squared_sigma_b = 0.;
	IN_TYPE n1 = 0, n2 = 0;
	for (IN_TYPE i = 0; i < max - min + 1; i++) {
		std::cout << i << "th hist : " << hist.at(i) << std::endl;
		
		n1 = std::accumulate(hist.begin(), hist.begin() + i, 0);
		myu1 = mean(0, i, n1, hist);
		//std::cout << "voxel " << n1 << std::endl;
		n2 = std::accumulate(hist.begin() + i, hist.end(), 0);
		myu2 = mean(i, max, n2, hist);

		// calc sigma b
		squared_sigma_b = (double)n1*(double)n2*(myu1 - myu2)*(myu1 - myu2);
		if (maxSigma < squared_sigma_b) {
			th = i;
			maxSigma = squared_sigma_b;
		}
	}
	std::cout << "Threshold " << th+min << std::endl;
	// binary image
	th += min;
	std::vector<unsigned char> mask(se);
	std::cout << "before thre" << std::endl;
	for (IN_TYPE s = 0; s < se; s++)
		if (img.at(s) >= th) mask.at(s) = UCHAR_MAX;
	std::cout << "after thre" << std::endl;

	mhdi.Write(mask, outputFileName);

}