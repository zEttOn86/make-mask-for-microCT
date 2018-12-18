/*
* This implementaion use itk
* Otsu method
* VS2012
* @auther tozawa
* @history
* 20171106 ‘å’Ã‚Ì2’l‰»
* 20171102
*/

#include "ItkImageIO.h"
#include <numeric>

typedef unsigned char IMG;
typedef long long T_TYPE;

template<class T0, class T1, class T2>
double mean(const T0 start, const T0 end, const T1 numOfHist, std::vector<T2> &temp)
{
	double sum = 0.;
	for (T0 i = start; i <= end; i++) {
		sum += temp.at(i) * (double)i;
	}
	sum /= (double)numOfHist;
	return sum;
}
void main(int argc, char **argv)
{

	if (argc != 3) {
		printf("Usage: exe, InputMhd(.mhd), OutputMhd(.mhd), (Image type is only unsigned char)\n");
		exit(1);
	}

	std::vector<IMG> img;

	ImageIO<3> mhdi;
	mhdi.Read(img, argv[1]);
	T_TYPE xe = mhdi.Size(0);
	T_TYPE ye = mhdi.Size(1);
	T_TYPE ze = mhdi.Size(2);
	T_TYPE se = xe*ye*ze;
	std::cout << xe << " " << ye << " " << ze << " " << se << std::endl;
	std::vector<unsigned long long> hist(UCHAR_MAX + 1);
	//Vote bins
	for (T_TYPE s = 0; s < se; s++) {
		//std::cout << img[s] << s <<" ";
		hist.at(img.at(s)) += 1;
	}
	// Calc Inter class variance
	int th = 0;
	double myu1, myu2, max, squared_sigma_b;
	myu1 = myu2 = max = squared_sigma_b = 0.;
	T_TYPE n1 = 0, n2 = 0;
	for (int i = 0; i < UCHAR_MAX + 1; i++) {
		std::cout << i << "th hist : " << hist[i] << std::endl;
		//myu1 = mean(0, i);
		n1 = std::accumulate(hist.begin(), hist.begin() + i, 0);
		myu1 = mean(0, i, n1, hist);
		//myu2 = mean(i, UCHAR_MAX);
		n2 = std::accumulate(hist.begin() + i, hist.end(), 0);
		myu2 = mean(i, UCHAR_MAX, n2, hist);

		// calc sigma b
		squared_sigma_b = (double)n1*(double)n2*(myu1 - myu2)*(myu1 - myu2);
		if (max < squared_sigma_b) {
			th = i;
			max = squared_sigma_b;
		}
	}
	std::cout << "Threshold " << th << std::endl;
	// binary image
	std::vector<IMG> mask(se);
	std::cout << "before thre" << std::endl;
	for (T_TYPE s = 0; s < se; s++)
		if (img.at(s) >= th) mask.at(s) = UCHAR_MAX;
	std::cout << "after thre" << std::endl;

	mhdi.Write(mask, argv[2]);
}