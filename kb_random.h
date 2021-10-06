#include <vector>

#pragma once

namespace kb
{
	//	特徴点のマッチングでRANSACを行う際に使用する関数
	//	　number=5だとサイズ５の配列を用意する
	//　	　[*,*,*,*,*]
	//	　最大値(max_num-1)として、値にかぶりなしで、
	//	　numberで指定したサイズの配列を取得する関数
	//
	//	初期化はどこかで呼んでも良い
	//	srand( (unsigned)time( NULL ) );
	//
	int getRandomNumbers(
		int number, 
		int* buf,
		int max_num
	);

	std::vector<int> getRandomNumbers(int num);

};

//	以下の情報もあるので、修正の必要もありそうだ。
//
// http://vivi.dyndns.org/tech/cpp/random.html
//これまで広く使用されてきた rand() による乱数生成には以下の問題点がある。
//生成される範囲が[0, 32767] と狭い
//rand() % N は一様では無い
//周期があまり長くない
//乱数生成アルゴリズムが固定（通常は線形合同法）
//正規分布など、一様でない乱数生成が面倒
//rand() で生成される値の範囲は[0, 32767] と狭い。15ビットしかない。
//(rand() << 15) + rand() とすれば、30ビット乱数にすることは可能だが、スマートではないし、 
//生成アルゴリズムの関係で、乱数に偏りが出る場合がある。
//

