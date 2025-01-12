/*
 * Copyright (c) 2012, 2013, Joel Bodenmann aka Tectu <joel@unormal.org>
 * Copyright (c) 2012, 2013, Andrew Hannam aka inmarket
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the <organization> nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "gfx.h"

/* The handles for our two Windows */
GHandle GW1, GW2;

int main(void)
{
    gCoord		i, j;

    /* Initialize and clear the display */
    gfxInit();
    gdispClear(GFX_WHITE);

    /* Create two windows */
    {
        GWindowInit	wi;

        gwinClearInit(&wi);
        wi.show = gTrue;
        wi.x = 20;
        wi.y = 10;
        wi.width = 200;
        wi.height = 150;
        GW1 = gwinWindowCreate(0, &wi);
        wi.show = gTrue;
        wi.x = 50;
        wi.y = 190;
        wi.width = 150;
        wi.height = 100;
        GW2 = gwinWindowCreate(0, &wi);
    }

    /* Set fore- and background colors for both windows */
    gwinSetColor(GW1, GFX_BLACK);
    gwinSetBgColor(GW1, GFX_WHITE);
    gwinSetColor(GW2, GFX_WHITE);
    gwinSetBgColor(GW2, GFX_BLUE);

    /* Clear both windows - to set background color */
    gwinClear(GW1);
    gwinClear(GW2);

    gwinDrawLine(GW1, 5, 30, 150, 110);
    for (i = 5, j = 0; i < 200 && j < 150; i += 3, j += i / 20) {
        gwinDrawPixel(GW1, i, j);
    }

    /*
     * Draw two filled circles at the same coordinate
     * of each window to demonstrate the relative coordinates
     * of windows
     */
    gwinFillCircle(GW1, 20, 20, 15);
    gwinFillCircle(GW2, 20, 20, 15);

    while (1) {
        gfxSleepMilliseconds(500);
    }
}

