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

C2D_TextBuf g_staticBuf;
C2D_Text g_HomeText[3];

int main(int argc, char* argv[])
{
	//Initialize libraries
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	//Create Screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT); //Create top screen
	//C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT); //Create bottom screen

	//Configure initial state and keys
	u32 kDownOld = 0, kHeldOld = 0, kUpOld = 0; //In these variables there will be information about keys detected in the previous frame
	enum app_state state = HOME;

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();

		//Get inputs
		u32 kDown = hidKeysDown(); //keys that were just pressed
		u32 kHeld = hidKeysHeld(); //keys that were held
		u32 kUp = hidKeysUp(); //keys that were just released

		switch (state) {
			case HOME:
				// Initialize home screen scene
				g_staticBuf = C2D_TextBufNew(4096);
				C2D_TextParse(&g_HomeText[0], g_staticBuf, "Welcome to YarnOver!");
				C2D_TextOptimize(&g_HomeText[0]);

				//Begin Rendering Home
				C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
				C2D_TargetClear(top, C2D_Color32(0x68, 0xB0, 0xD8, 0xFF));
				C2D_SceneBegin(top);
				
				
				//Draw static text strings
				C2D_DrawText(&g_HomeText[0], 0, 8.0f, 8.0f, 0.5f, .5f, .5f);

				
				if (kDown & KEY_A) {

					//TODO: WE need to CLEAR the console before moving on to the next thing

					state = MENU;
				}
				break;
			
			case MENU:
				// printf("\x1b[4;HEntered Menu!");
				break;
			
			case PROJECT:
				// printf("\x1b[4;HEntered Project Screen!");
				break;
		}




		
		//TODO: Render the scene!
		C3D_FrameEnd(0);

		//Exit
		if (kDown & KEY_START){//if the START button is pressed.
			break; // break in order to return to hbmenu
		} 
					
		//Manage the controls
		kDownOld = kDown;
		kHeldOld = kHeld;
		kUpOld = kUp;

		
	}

	//Delete TextBuffers
	C2D_TextBufDelete(g_staticBuf);

	

	UNUSED(kHeldOld);
	UNUSED(kDownOld);
	UNUSED(kUpOld);
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
