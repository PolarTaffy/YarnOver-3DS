#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include "tools.h"
#include <citro2d.h>

enum app_state {
	HOME,
	MENU,
	PROJECT,
};


int main(int argc, char* argv[])
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	u32 kDownOld = 0, kHeldOld = 0, kUpOld = 0; //In these variables there will be information about keys detected in the previous frame
	enum app_state state = HOME;

	// Main loop


	while (aptMainLoop())
	{
		

		// Your code goes here
		u32 kDown = hidKeysDown(); //keys that were just pressed
		u32 kHeld = hidKeysHeld(); //keys that were held
		u32 kUp = hidKeysUp(); //keys that were just released
		//Main Screen?
		

		switch (state) {
			case HOME:
				//Top Screen [Console]
				printf("\x1b[1;1HYarnOver!");
				printf("\x1b[2;1HPress A to Start!");

				if (kDown & KEY_A) {

					//TODO: WE need to CLEAR the console before moving on to the next thing

					state = MENU;
				}
				if (kDown & KEY_START){//if the START button is pressed.
					break; // break in order to return to hbmenu
				} 
				break;
			
			case MENU:
				printf("\x1b[4;HEntered Menu!");
				break;
			
			case PROJECT:
				printf("\x1b[4;HEntered Project Screen!");
				break;
		}

		
		//Bottom Screen

		


		if (kDown & KEY_START){//if the START button is pressed.
			break; // break in order to return to hbmenu
		} 
			
		
		kDownOld = kDown;
		kHeldOld = kHeld;
		kUpOld = kUp;

		circlePosition pos;

		//Read the CirclePad position
		hidCircleRead(&pos);

		//Print the CirclePad position
		printf("\x1b[7;5H%04d; %04d", pos.dx, pos.dy);

		hidScanInput();
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}

	UNUSED(kHeldOld);
	UNUSED(kDownOld);
	UNUSED(kUpOld);
	C2D_Fini();
	gfxExit();
	return 0;
}
