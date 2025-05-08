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

C2D_TextBuf home_staticBuffer;
C2D_Text g_HomeText[3];
C2D_Text g_MenuText[5];
enum app_state state;

void initializeLibraries() {
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	state = HOME;
}

int main(int argc, char* argv[])
{
	initializeLibraries();
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT); //Create top screen
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT); //Create bottom screen
	
	
	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		//Get inputs
		u32 kDown = hidKeysDown(); //keys that were just pressed
		u32 kHeld = hidKeysHeld(); //keys that were held
		u32 kUp = hidKeysUp(); //keys that were just released
		UNUSED(kHeld);
		UNUSED(kUp);
		
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		switch (state) {
			case HOME:
				// Initialize home screen scene
				home_staticBuffer = C2D_TextBufNew(4096); 
				C2D_TextParse(&g_HomeText[0], home_staticBuffer, "YarnOver!");
				C2D_TextParse(&g_HomeText[1], home_staticBuffer, "Your Pocket Knitting Assistant");
				C2D_TextParse(&g_HomeText[2], home_staticBuffer, "Press A to start!");
				C2D_TextOptimize(&g_HomeText[0]); 
				C2D_TextOptimize(&g_HomeText[1]); 
				C2D_TextOptimize(&g_HomeText[2]); 
				
				//-------------------------------TOP SCREEN (HOME)
				
				C2D_TargetClear(top, C2D_Color32(0x68, 0xB0, 0xD8, 0xFF));
				C2D_SceneBegin(top);
				//Draw static text strings
				C2D_DrawText(&g_HomeText[0], 0, 10.5f, 12.0f, 1.0f, 2.0f, 2.0f); //text, flags, x, y, z, scaleX, scaleY
				C2D_DrawText(&g_HomeText[1], 0, 8.0f, 60.0f + 10.0f, 0.5f, .7f, .7f);

				//-------------------------------BOTTOM SCREEN (HOME)
				C2D_TargetClear(bottom, C2D_Color32(0x64, 0xB0, 0xD1, 0xFE));
				C2D_SceneBegin(bottom);
				//Draw text strings
				C2D_DrawText(&g_HomeText[2], 0, BOT_WIDTH/2 - (g_HomeText[2].width / 2), BOT_HEIGHT/2, 0.0f, 0.8f, 0.8f);
	

				
				if (kDown & KEY_A) {

					// TODO: WE need to CLEAR the console before moving on to the next thing
					// C2D_TextBufClear(home_staticBuffer);
					C2D_TargetClear(top, C2D_Color32(0x68, 0xB0, 0xD8, 0xFF));
					C2D_TargetClear(bottom, C2D_Color32(0x64, 0xB0, 0xD1, 0xFE));
					state = MENU;
				}

				break;
			
			case MENU:

				

				if (kDown & KEY_B) {
					C2D_TargetClear(top, C2D_Color32(0x02, 0x42, 0xA8, 0xFC));
					C2D_TargetClear(bottom, C2D_Color32(0x21, 0xB3, 0xD5, 0xFA));
					state = HOME;
				}

				break;
			
			case PROJECT:
				// printf("\x1b[4;HEntered Project Screen!");
				break;
		}

		C3D_FrameEnd(0);
		C2D_TextBufDelete(home_staticBuffer); //we delete the buffer to avoid memory leaks
		home_staticBuffer = NULL;

		//Exit
		if (kDown & KEY_START){//if the START button is pressed.
			break; // break in order to return to hbmenu
		} 
		
	}

	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
