
#pragma once

namespace kb
{
	//	Ô`—Î`Â
	void makeTemparaturePalette0(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);

	//	Ô`—Î`Â`•
	void makeTemparaturePalette(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);
	//	”’`Ô`—Î`Â`•
	void makeTemparaturePalette2(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);
	void makeTemparaturePalette3(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);
	//	Ô`‰©`—Î
	void makeTemparaturePalette4(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);

	//	Ô`•`Â‚ÌƒpƒŒƒbƒg
	void makeRedAndBluePalette(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);
	//	Ô`”’`Â‚ÌƒpƒŒƒbƒg
	void makeRedAndBluePalette2(int tone_number, unsigned char* prr, unsigned char* pgg, unsigned char* pbb);

	//	ƒ‰ƒ“ƒ_ƒ€ƒJƒ‰\ƒpƒŒƒbƒgì¬
	void random_color_palette(int index, unsigned char* rr, unsigned char* gg, unsigned char* bb);
	//	ƒ‰ƒ“ƒ_ƒ€ƒJƒ‰\ƒpƒŒƒbƒgì¬
	//		buffer number = 256
	void random_color_palette(unsigned char* rr, unsigned char* gg, unsigned char* bb);


};

