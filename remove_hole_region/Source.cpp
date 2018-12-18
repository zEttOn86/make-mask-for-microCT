/*
* This implementaion use itk and mist
* Build on VS2012
* Remove hole on each axial
* @auther tozawa
* @history 
* 20171110
* 20171109
* 20171108
*/
#include <iostream>
#include "ItkImageIO.h"
//#include "ip/narilabeling.h"
#include <mist/mist.h>
#include <mist/filter/labeling.h>
typedef unsigned char IMG;
typedef int T_TYPE;
typedef long long LL_TYPE;

void main(int argc, char **argv)
{
	if (argc != 3) {
		std::cerr << "Usage :\n";
		std::cerr << argv[0] << " inputFile(.mhd) outFile(.mhd)" << std::endl;
		exit(1);
	}
	
	std::vector<IMG> img;
	ImageIO<3> mhdi;
	mhdi.Read(img, argv[1]);
	T_TYPE xe = mhdi.Size(0);
	T_TYPE ye = mhdi.Size(1);
	T_TYPE ze = mhdi.Size(2);
	LL_TYPE se = (LL_TYPE)xe*(LL_TYPE)ye*(LL_TYPE)ze;
	std::cout << xe << " " << ye << " " << ze << " " << se << "\n";

	// Remove hole region using mist
	std::cout << "Remove hole region on each axial\n";
	std::vector<IMG> out(se);
	mist::array2<IMG> for_remove_hole(xe, ye);
	for (T_TYPE k = 0; k < ze; k++) 
	{
		for (T_TYPE j = 0; j < ye; j++) 
			for (T_TYPE i = 0; i < xe; i++) 
				for_remove_hole(i, j) = img.at((LL_TYPE)xe*((LL_TYPE)k*(LL_TYPE)ye + (LL_TYPE)j) + (LL_TYPE)i);
		
		mist::remove_hole_region(for_remove_hole, for_remove_hole);
		
		for (T_TYPE j = 0; j < ye; j++)
			for (T_TYPE i = 0; i < xe; i++)
				out.at((LL_TYPE)xe*((LL_TYPE)k*(LL_TYPE)ye + (LL_TYPE)j) + (LL_TYPE)i) = for_remove_hole(i, j);
	}
		
	//Output Image
	mhdi.Write(out, argv[2]);
}