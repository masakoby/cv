#pragma once

namespace kb
{
    //  
    //  rgb[0]=b
    //  rgb[1]=g
    //  rgb[2]=r
    //  hsv[0]=v
    //  hsv[1]=s
    //  hsv[2]=h
    inline void rgb2hsv(unsigned char rgb[3], unsigned char hsv[3])
	{
        int r = rgb[2], g = rgb[1], b = rgb[0];
        int  h, s=0, v, vmin;

        v = vmin = r;
        if (v < g) v = g;
        if (v < b) v = b;
        if (vmin > g) vmin = g;
        if (vmin > b) vmin = b;

        int diff = v - vmin;
        if (diff == 0) {
            
            hsv[0] = v;
            hsv[1] = 0;
            hsv[2] = 0;
            return;
        }

        hsv[0] = v;
        hsv[1] = (unsigned char)( 255 * diff / v );

        if (v == r)
            h = 60*(g - b) / diff;
        else if (v == g)
            h = 60*(b - r) / diff + 120;
        else
            h = 60*(r - g) / diff + 240;

        if (h < 0) h += 360;

        hsv[2] = h/2;
	}
};
