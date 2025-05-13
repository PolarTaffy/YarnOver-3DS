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

struct project userProjects[9];

// void clearScreens() {
//  consoleSelect(&topScreen);
//  consoleClear();

//  consoleSelect(&bottomScreen);
//  consoleClear();
// }

void initializeProjects() {
    //TODO: Actually do this properly, load from a file or something
    struct project myProj;
    myProj.row = 5;
    strcpy(myProj.name, "Sweater");
    myProj.isCreated = true;

    userProjects[0] = myProj;
}

int main(int argc, char* argv[])
{
    gfxInitDefault();
    PrintConsole topScreen, bottomScreen;
    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);
    u32 kDownOld = 0, kHeldOld = 0, kUpOld = 0; //In these variables there will be information about keys detected in the previous frame
    enum app_state state = HOME;

    int popupTimer = 0;
    int curPage = 0;
    
    //Initialize Projects
    initializeProjects();
    
    printf("\x1b[1;1HYarnOver!");

    // Main loop
    while (aptMainLoop())
    {

        // Your code goes here
        u32 kDown = hidKeysDown(); //keys that were just pressed
        u32 kHeld = hidKeysHeld(); //keys that were held
        u32 kUp = hidKeysUp(); //keys that were just released
        //Main Screen?
        
        //      ## Cursor Positioning

        // - `\x1b[y;xH` is an ANSI escape code where:
        //   - `\x1b` represents the escape character
        //   - `y` specifies the row (vertical position)
        //   - `x` specifies the column (horizontal position)
        //   - `H` is the command to set cursor position
        

        switch (state) {
            case HOME:
                
                consoleSelect(&topScreen);
                printf("\x1b[1;1HYarnOver!");
                printf("\x1b[2;1HYour personal knitting assistant.");

                consoleSelect(&bottomScreen);
                printf("\x1b[2;1HPress A to Start!");
                

                if (kDown & KEY_A) {
                    consoleSelect(&topScreen);
                    consoleClear();

                    consoleSelect(&bottomScreen);
                    consoleClear();

                    popupTimer = 30;

                    state = MENU;
                }
                
                break;
            
            case MENU:
                consoleSelect(&bottomScreen);
                if (popupTimer > 0) {
                    printf("\x1b[4;1HEntered Menu!");
                    popupTimer--;
                }
                
                
                printf("\x1b[80;HMenu Page %d!", curPage);
                
                for (int i = 0, spot = 0; i < 9; i++, spot +=2) {
                    
                    char prefix[40];
                    sprintf(prefix, "\x1b[%d;1H", spot + 6);
                    if (userProjects[i].isCreated == 0) {
                        strcat(prefix, "Empty Project");
                        printf(prefix);
                    } else {
                        strcat(prefix, userProjects[i].name);
                        printf(prefix);
                    }

                    

                }

                // printf(userProjects[0].name);

                if (kDown & KEY_A) {
                    consoleSelect(&topScreen);
                    consoleClear();

                    consoleSelect(&bottomScreen);
                    consoleClear();
                    
                    curPage = 1;

                    state = MENU;
                }

                if (kDown & KEY_B) {
                    consoleSelect(&topScreen);
                    consoleClear();

                    consoleSelect(&bottomScreen);
                    consoleClear();
                    
                    curPage = 0;

                    state = HOME;
                }

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
        //printf("\x1b[7;5H%04d; %04d", pos.dx, pos.dy);

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
