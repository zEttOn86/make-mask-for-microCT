/*
* Output histogram csv file
* 
* @auther tozawa
* @hitory
* 20171030
*/

#include "naricommon.h"
#include "nariinfocontroller.h"
#include "narivectorpp.h"
#include "naricaseinfo.h"
#include "ip/naridistance.h"
#include "other/narimhd.h"
#include "naristring.h"
#include "naritimer.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include "raw_io.h"
#include "ItkImageIO.h"
typedef unsigned char IMG;


void main(int argc, char **argv)
{
	
	if (argc != 3) {
		printf("Usage: exe, InputMhd(.mhd), OutputDir, (Image type is only unsigned char)\n");
		exit(1);
	}
	
	std::vector<IMG> img;
	
	ImageIO<3> mhdi;
	mhdi.Read(img, argv[1]);
	int xe = mhdi.Size(0);
	int ye = mhdi.Size(1);
	int ze = mhdi.Size(2);
	/*read_vector(img, std::string(argv[1]));
	int xe = atoi(argv[2]);
	int ye = atoi(argv[3]);
	int ze = atoi(argv[4]);*/
	//unsigned long long se = xe*ye*ze;
	//unsigned long long se = mhdi.NumOfPixels();
	unsigned long long se = (unsigned long long)xe*(unsigned long long)ye*(unsigned long long)ze;
	std::cout << argv[1] << " ";
	std::cout << xe << " " << ye << " " << ze << " " << se;
	std::vector<unsigned long long> hist(UCHAR_MAX + 1);
	
	//Vote histogram
	for (unsigned long long s = 0; s < se; s++) {
		//std::cout << img[s] << s <<" ";
		hist[img[s]]+=1;
	}
	//Output csv
	std::ofstream ofs(std::string(argv[2]) + "/result.csv");
	std::cout << "output csv file" << std::endl;
	ofs << "value,frequency" << std::endl;
	for (int i = 0; i < UCHAR_MAX+1; i++) {
		ofs << i << "," << hist[i] << std::endl;
	}
	//Old coding
	//std::cout << "test" << "\n";
	//Copy Img
	//std::vector<IMG> temp(se, 0);
	//for (int s = 0; s < se; s++) {
	//	temp[s] = img[s];
	//}
	//std::cout << "temp" << "\n";
	//int max = *std::max_element(temp.begin(), temp.end());
	//int min = *std::min_element(temp.begin(), temp.end());
	//std::cout << max << " "<<min << std::endl;
	//std::vector<int> hist( max+1);
	//std::vector<int> _hist(std::abs(min) +1);
	//
	////Vote histogram
	//for (int s = 0; s < se; s++) {
	//	if (temp[s] >= 0) hist[temp[s]]++;
	//	else _hist[std::abs(temp[s])]++;
	//}
	//
	////Output csv file
	//std::ofstream ofs(std::string(argv[2]) + "/result.csv");
	//std::cout << "output csv file" << std::endl;
	//ofs << "value,frequency" << std::endl;
	//for (int i = std::abs(min); i > 0; i--) {
	//	ofs << -i << "," << _hist[i] << std::endl;
	//}
	//for (int i = 0; i <= max; i++) {
	//	ofs << i << "," << hist[i] << std::endl;
	//}
}