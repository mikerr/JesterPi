#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <xf86drm.h>
#include <xf86drmMode.h>
#include <gbm.h>
#include <EGL/egl.h>
#include <GL/gl.h>
#include <fcntl.h>

#include <FTGL/ftgl.h>

#include <termios.h>
#include <linux/input.h>

#include "input.h"
#include "menu.h"

extern FTGLfont *font;
extern void swap_buffers();

char menu[20][80];



// normalize 0,0 to -1,-1
// normalize 200,200 to 1,1
float x_to_gl(int x) {
	float fx;

  	fx = x / 100.0f;
  	fx--;

	return fx;
}
float y_to_gl(int y) {
	float fy;

  	fy = (200 - y) / 100.0f;
  	fy--;

	return fy;
}

void setPos (int x,int y) {
	float fx,fy;

  	fx = x_to_gl(x);
  	fy = y_to_gl(y);
  	glRasterPos2f(fx,fy);
}

void set_menuitems (int submenu) {

for (int i =0;i<20;i++)
	strcpy(menu[i],"");

switch (submenu) {
	case 0:
		strcpy(menu[0] , "TV Central");
		strcpy(menu[1] , "Now Playing");
		strcpy(menu[2] , "Watch Live Tv");
		strcpy(menu[3] , "Inside Tivo");
		strcpy(menu[4] , "Channel Highlights");
		strcpy(menu[5] , "Pick Programmes to Record");
		strcpy(menu[6] , "Messages and Setup");
		break;
	case 1:
		strcpy(menu[0] , "Now Playing");
		strcpy(menu[1] , "The Gadget Show");
		strcpy(menu[2] , "Miller's Crossing");
		strcpy(menu[3] , "Cold Case");
		strcpy(menu[4] , "Paris Underground ");
		strcpy(menu[5] , "Gattaca");
		strcpy(menu[6] , "Doctor Who");
		break;
	case 2:
		strcpy(menu[0] , "Watch Live Tv");
		strcpy(menu[1] , "Watch Live Tv");
		break;
	case 3:
		strcpy(menu[0] , "Inside Tivo");
		strcpy(menu[1] , "Inside Tivo");
		break;
	case 4:
		strcpy(menu[0] , "Channel Highlights");
		strcpy(menu[1] , "Channel Highlights");
		break;
	case 5:
		strcpy(menu[0] , "Pick Programmes to Record");
		strcpy(menu[1] , "Search By Title");
		strcpy(menu[2] , "Search Using WishLists");
		strcpy(menu[3] , "Tivo Suggestions");
		strcpy(menu[4] , "Record By Time or Channel");
		strcpy(menu[5] , "Season Pass Manager");
		strcpy(menu[6] , "To Do List");
		break;
	case 6:
		strcpy(menu[0] , "Messages and Setup");
		strcpy(menu[1] , "TiVo Messages");
		strcpy(menu[2] , "My Preferences");
		strcpy(menu[3] , "Recorder & Network Setup");
		strcpy(menu[4] , "System Information");
		strcpy(menu[5] , "Troubleshooting");
		strcpy(menu[6] , "System Reset");
		strcpy(menu[7] , "Standby");
		break;
	}

}
int draw_menu (int selection)
{
        glClear(GL_COLOR_BUFFER_BIT);

	//highlight selected item
        float x,y;
        y = selection * 20;
	y = y_to_gl(y);

	x = x_to_gl(50);
	glColor3f(0,0,1); // blue
	glRectf(x,y + 0.15,0.7,y - 0.04);

	// draw menu items
	for (int m = 1; m < 10 ; m++) {
	        glColor3f(1,1,1); // white
		setPos(50,m * 20);
		ftglSetFontFaceSize(font,80,80);
    		ftglRenderFont(font,menu[m], FTGL_RENDER_ALL);
	}
    	swap_buffers();
}
