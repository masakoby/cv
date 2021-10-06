#include "kb_random.h"
#include <stdlib.h>

int kb::getRandomNumbers(int number, int* buf, int max_num)
{
	if (number > max_num)
		return -1;

	for (int i = 0; i < number; i++) {
		while (1) {
			int a = rand() % max_num;

			int flag_same = 0;
			for (int k = 0; k < i; k++) {
				if (a == buf[k]) {
					flag_same = 1;
					break;
				}
			}
			if (flag_same == 0) {
				buf[i] = a;
				break;
			}
		}
	}
	return 0;
}

std::vector<int> kb::getRandomNumbers(int num)
{
	std::vector<int> v1;
	v1.resize(num, -1);


	for (int i = 0; i < num; i++) {
		int a = rand() % (num);
		if (v1[a] < 0) {
			v1[a] = i;
		}
		else {
			for (int ii = 0; ii < num; ii++) {
				int b = (a + ii) % num;
				if (v1[b] < 0) {
					v1[b] = i;
					break;
				}
			}
		}
	}
	return v1;
}
