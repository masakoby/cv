#include "kb_tube2vidx.h"

int kb::tube2vidx(
	std::vector< double>& circum,
	int num_circum,
	std::vector< int >& vidx
)
{
	int num1 = circum.size() / (3*num_circum);
	for (int i = 0; i < num1 - 1; i++) {
		int i0 = i * num_circum;
		int i1 = (i + 1) * num_circum;
		for (int ii = 0; ii < num_circum; ii++) {
			int ii1 = (ii + 1) % num_circum;

			vidx.push_back(i0 + ii);
			vidx.push_back(i0 + ii1);
			vidx.push_back(i1 + ii);

			vidx.push_back(i1 + ii);
			vidx.push_back(i0 + ii1);
			vidx.push_back(i1 + ii1);
		}
	}



	return 0;
}
