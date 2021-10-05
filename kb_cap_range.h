#pragma once

namespace kb
{

	//	最大・最小値が上限・下限を超えてないかチェックし、超えていた場合、
	//	上限値と下限値を設定する
	int cap_range(double range[2], double width, double range_out[2]);

};
