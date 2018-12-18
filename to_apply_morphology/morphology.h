/*
* @auther tozawa
* @history 
* 20171114 çÇë¨âªî≈Çí«â¡
* 20171106
*/

#pragma once
typedef long long T_TYPE;
namespace morphology {

	template<class T1>
	int dilation(const std::vector<T1> &imgI, const T_TYPE xe, const T_TYPE ye, const T_TYPE ze, const int m, std::vector<T1> &imgR)
	{
		if (xe, ye, ze <= 0 || m < 3 || m % 2 == 0) {
			std::cout << "input positive value or Filter size is only odd";
			return -1;
		}
		int hm = m / 2;
		int mm = m*m*m;
		std::vector<T1> stock(mm);
		//Raster scan
		//for (r = 0; r < repetition; r++) {
		for (T_TYPE z = 0; z < ze; z++) {
			for (T_TYPE y = 0; y < ye; y++) {
				for (T_TYPE x = 0; x < xe; x++) {
					T_TYPE s = xe*(z*ye + y) + x;
					int t = 0;
					//Filtering
					for (T_TYPE k = -hm; k <= hm; k++) {
						for (T_TYPE j = -hm; j <= hm; j++) {
							for (T_TYPE i = -hm; i <= hm; i++) {
								T_TYPE ss = xe*(std::max((T_TYPE)0, std::min(ze - 1, z + k))*ye
									+ std::max((T_TYPE)0, std::min(ye - 1, y + j)))
									+ std::max((T_TYPE)0, std::min(xe - 1, x + i));
								stock.at(t) = imgI.at(ss);
								t++;
							}
						}
					}
					imgR.at(s) = *std::max_element(stock.begin(), stock.end());
				}
			}
		}
		//}
		return 0;
	}

	template<class T1>
	int faster_dilation(const std::vector<T1> &imgI, const T_TYPE xe, const T_TYPE ye, const T_TYPE ze, const int radius, std::vector<T1> &imgR)
	{
		if (xe, ye, ze <= 0 || radius <= 0) {
			std::cout << "Input value is only positive";
			return -1;
		}
		int hm = radius;
		T_TYPE se = xe*ye*ze;
		std::vector<T1> temp(se);
		std::vector<T1> stock(2 * hm + 1);

		for (T_TYPE z = 0; z < ze; z++) {
			for (T_TYPE y = 0; y < ye; y++) {
				for (T_TYPE x = 0; x < xe; x++) {
					T_TYPE s = xe*(z*ye + y) + x;
					int t = 0;
					for (T_TYPE k = -hm; k <= hm; k++) {// z
						T_TYPE ss = xe*(std::max((T_TYPE)0, std::min(ze - 1, z + k))*ye
							+ std::max((T_TYPE)0, std::min(ye - 1, y)))
							+ std::max((T_TYPE)0, std::min(xe - 1, x));
						stock.at(t) = imgI.at(ss);
						t++;
					}
					imgR.at(s) = *std::max_element(stock.begin(), stock.end());
				}
			}
		}
		for (T_TYPE z = 0; z < ze; z++) {
			for (T_TYPE y = 0; y < ye; y++) {
				for (T_TYPE x = 0; x < xe; x++) {
					T_TYPE s = xe*(z*ye + y) + x;
					int t = 0;
					for (T_TYPE k = -hm; k <= hm; k++) {// y
						T_TYPE ss = xe*(std::max((T_TYPE)0, std::min(ze - 1, z))*ye
							+ std::max((T_TYPE)0, std::min(ye - 1, y + k)))
							+ std::max((T_TYPE)0, std::min(xe - 1, x));
						stock.at(t) = imgR.at(ss);
						t++;
					}
					temp.at(s) = *std::max_element(stock.begin(), stock.end());
				}
			}
		}
		for (T_TYPE z = 0; z < ze; z++) {
			for (T_TYPE y = 0; y < ye; y++) {
				for (T_TYPE x = 0; x < xe; x++) {
					T_TYPE s = xe*(z*ye + y) + x;
					int t = 0;
					for (T_TYPE k = -hm; k <= hm; k++) {// x
						T_TYPE ss = xe*(std::max((T_TYPE)0, std::min(ze - 1, z))*ye
							+ std::max((T_TYPE)0, std::min(ye - 1, y)))
							+ std::max((T_TYPE)0, std::min(xe - 1, x+k));
						stock.at(t) = temp.at(ss);
						t++;
					}
					imgR.at(s) = *std::max_element(stock.begin(), stock.end());
				}
			}
		}

		return 0;
	}

	template<class T1>
	int erosion(const std::vector<T1> &imgI, const T_TYPE xe, const T_TYPE ye, const T_TYPE ze, const int m,  std::vector<T1> &imgR)
	{
		if (xe, ye, ze <= 0 || m < 3 || m % 2 == 0 ) {
			std::cout << "input positive value or Filter size is only odd";
			return -1;
		}
		int hm = m / 2;
		int mm = m*m*m;
		std::vector<T1> stock(mm);
		//Raster scan
		//for (r = 0; r < repetition; r++) {
			for (T_TYPE z = 0; z < ze; z++) {
				for (T_TYPE y = 0; y < ye; y++) {
					for (T_TYPE x = 0; x < xe; x++) {
						T_TYPE s = xe*(z*ye + y) + x;
						int t = 0;
						//Filtering
						for (T_TYPE k = -hm; k <= hm; k++) {
							for (T_TYPE j = -hm; j <= hm; j++) {
								for (T_TYPE i = -hm; i <= hm; i++) {
									T_TYPE ss = xe*(std::max((T_TYPE)0, std::min(ze - 1, z + k))*ye
										+ std::max((T_TYPE)0, std::min(ye - 1, y + j)))
										+ std::max((T_TYPE)0, std::min(xe - 1, x + i));
									stock.at(t) = imgI.at(ss);
									t++;
								}
							}
						}
						imgR.at(s) = *std::min_element(stock.begin(), stock.end());
					}
				}
			}
		//}
		return 0;
	}

	template<class T1>
	int faster_erosion(const std::vector<T1> &imgI, const T_TYPE xe, const T_TYPE ye, const T_TYPE ze, const int radius, std::vector<T1> &imgR)
	{
		if (xe, ye, ze <= 0 || radius <= 0) {
			std::cout << "Input value is only positive";
			return -1;
		}
		int hm = radius;
		T_TYPE se = xe*ye*ze;
		std::vector<T1> temp(se);
		std::vector<T1> stock(2 * hm + 1);

		for (T_TYPE z = 0; z < ze; z++) {
			for (T_TYPE y = 0; y < ye; y++) {
				for (T_TYPE x = 0; x < xe; x++) {
					T_TYPE s = xe*(z*ye + y) + x;
					int t = 0;
					for (T_TYPE k = -hm; k <= hm; k++) {// z
						T_TYPE ss = xe*(std::max((T_TYPE)0, std::min(ze - 1, z + k))*ye
							+ std::max((T_TYPE)0, std::min(ye - 1, y)))
							+ std::max((T_TYPE)0, std::min(xe - 1, x));
						stock.at(t) = imgI.at(ss);
						t++;
					}
					imgR.at(s) = *std::min_element(stock.begin(), stock.end());
				}
			}
		}
		for (T_TYPE z = 0; z < ze; z++) {
			for (T_TYPE y = 0; y < ye; y++) {
				for (T_TYPE x = 0; x < xe; x++) {
					T_TYPE s = xe*(z*ye + y) + x;
					int t = 0;
					for (T_TYPE k = -hm; k <= hm; k++) {// y
						T_TYPE ss = xe*(std::max((T_TYPE)0, std::min(ze - 1, z))*ye
							+ std::max((T_TYPE)0, std::min(ye - 1, y + k)))
							+ std::max((T_TYPE)0, std::min(xe - 1, x));
						stock.at(t) = imgR.at(ss);
						t++;
					}
					temp.at(s) = *std::min_element(stock.begin(), stock.end());
				}
			}
		}
		for (T_TYPE z = 0; z < ze; z++) {
			for (T_TYPE y = 0; y < ye; y++) {
				for (T_TYPE x = 0; x < xe; x++) {
					T_TYPE s = xe*(z*ye + y) + x;
					int t = 0;
					for (T_TYPE k = -hm; k <= hm; k++) {// x
						T_TYPE ss = xe*(std::max((T_TYPE)0, std::min(ze - 1, z))*ye
							+ std::max((T_TYPE)0, std::min(ye - 1, y)))
							+ std::max((T_TYPE)0, std::min(xe - 1, x+k));
						stock.at(t) = temp.at(ss);
						t++;
					}
					imgR.at(s) = *std::min_element(stock.begin(), stock.end());
				}
			}
		}
		return 0;
	}
}