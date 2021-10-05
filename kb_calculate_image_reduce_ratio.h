#pragma once


namespace kb
{
	//	基準の画像サイズ（画像の縦もしくは横のピクセル数）に従って、画像を縮小する倍率を計算する
	//	縮小の必要がなければ、ー１を返す。
	inline double calculate_image_reduce_ratio(int width_reduced, int width, int height)
	{
		float w1 = sqrt((float)width * (float)height);
		float w2 = width_reduced;
		if (w2 < w1) {
			return (w2 / w1);
		}
		else {
			return -1.0;
		}
	}
};