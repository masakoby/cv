#include "kb_sort.h"
#include <map>

int kb::sort(std::vector<int>& vvalues, std::vector<int>& vidx, int order)
{
	int num = vvalues.size();
	
	if (order == 0) {
		std::multimap<int, int, std::less<float>> mm;
		for (int k = 0; k < num; k++) {
			mm.insert(std::make_pair(vvalues[k], k));
		}

		std::multimap<int, int, std::less<float>>::iterator it = mm.begin();
		for (; it != mm.end(); it++) {
			vidx.push_back(it->second);
		}
	}
	else {
		std::multimap<int, int, std::greater<float>> mm;
		for (int k = 0; k < num; k++) {
			mm.insert(std::make_pair(vvalues[k], k));
		}

		std::multimap<int, int, std::greater<float>>::iterator it = mm.begin();
		for (; it != mm.end(); it++) {
			vidx.push_back(it->second);
		}

	}

	return 0;
}

int kb::sort(std::vector<std::string>& vvalues, std::vector<int>& vidx, int order)
{
	int num = vvalues.size();

	if (order == 0) {
		std::multimap<std::string, int, std::less<>> mm;
		for (int k = 0; k < num; k++) {
			mm.insert(std::make_pair(vvalues[k], k));
		}

		std::multimap<std::string, int, std::less<>>::iterator it = mm.begin();
		for (; it != mm.end(); it++) {
			vidx.push_back(it->second);
		}
	}
	else {
		std::multimap<std::string, int, std::greater<>> mm;
		for (int k = 0; k < num; k++) {
			mm.insert(std::make_pair(vvalues[k], k));
		}

		std::multimap<std::string, int, std::greater<>>::iterator it = mm.begin();
		for (; it != mm.end(); it++) {
			vidx.push_back(it->second);
		}

	}

	return 0;
}
