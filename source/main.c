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

struct project {
    char name[20];
    int row;
    bool isCreated;
};

struct project userProjects[18];
struct project* curProject;
PrintConsole topScreen, bottomScreen;

void clearConsoles() {
    consoleSelect(&topScreen);
    consoleClear();
    consoleSelect(&bottomScreen);
    consoleClear();
}

void initializeProjects() {
    //TODO: Actually do this properly, load from a file or something
    struct project myProj;
    myProj.row = 5;
    strcpy(myProj.name, "Sweater");
    myProj.isCreated = true;

    userProjects[0] = myProj;
}

void displayMenu(int curPage) {
	int maxDisplayItems = 9;
	int pgoffset = curPage * maxDisplayItems;
	for (int i = pgoffset; i < pgoffset + maxDisplayItems; i++) {

	}
	//print items
	for (int i = pgoffset, spot = 0; i < pgoffset + maxDisplayItems; i++, spot +=2) {
		
		char prefix[40];
		sprintf(prefix, "\x1b[%d;4H", spot + 6);
		if (userProjects[i].isCreated == 0) {
			strcat(prefix, "Empty Project");
			printf(prefix);
		} else {
			strcat(prefix, userProjects[i].name);
			printf(prefix);
		}

	}
}

void setCurrentProject(int projIndex) {
	curProject = &userProjects[projIndex];
}

int main(int argc, char* argv[])
{
    gfxInitDefault();
    
    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);
    u32 kDownOld = 0, kHeldOld = 0, kUpOld = 0; //In these variables there will be information about keys detected in the previous frame
    enum app_state state = HOME;

    int popupTimer = 0;
    int curPage = 0;
	int selectionIndex = 0;
    
    //Initialize Projects
    initializeProjects();
    
    printf("\x1b[1;1HYarnOver!");

    // Main loop
    while (aptMainLoop())
    {
        u32 kDown = hidKeysDown(); //keys that were just pressed
        u32 kHeld = hidKeysHeld(); //keys that were held
        u32 kUp = hidKeysUp(); //keys that were just released

        clearConsoles();
        switch (state) {
            case HOME:
                consoleSelect(&topScreen);
                printf("\x1b[1;1HYarnOver!");
                printf("\x1b[2;1HYour personal knitting assistant.");

                consoleSelect(&bottomScreen);
                printf("\x1b[2;1HPress A to Start!");

                if (kDown & KEY_A) {
                    popupTimer = 300;
					curPage = 0;
                    state = MENU;
                }
                break;
            
            case MENU:
                consoleSelect(&bottomScreen);
                if (popupTimer > 0) {
                    printf("\x1b[4;1HEntered Menu!");
                    popupTimer--;
                }
                displayMenu(curPage);

                printf("\x1b[80;HMenu Page %d!", curPage);

				
                //TODO: Change these into a switch statement ?
                if (kDown & KEY_A) {
                    //TODO: Set selectionIndex to current cursor selection
					setCurrentProject(selectionIndex);
                    state = PROJECT;
                }
				if (kDown & KEY_DRIGHT) {
					if (curPage < 4) { curPage++;}
                    state = MENU;
                }
				if (kDown & KEY_DLEFT) {
					if (curPage > 0) {curPage--;}
                    state = MENU;
                }
                if (kDown & KEY_B) {                    
                    curPage = 0;
                    state = HOME;
                }

                break;
            

            case PROJECT:
				consoleSelect(&bottomScreen);
                printf("\x1b[4;HEntered Project Screen!");

				consoleSelect(&topScreen);
				printf(curProject->name);

                break;
        }

        if (kDown & KEY_START){//if the START button is pressed.
            break; // break in order to return to hbmenu
        } 
        
        kDownOld = kDown;
        kHeldOld = kHeld;
        kUpOld = kUp;

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
