// the main routine makes the window, and then runs an even loop
// until the window is closed
#include <windows.h>
#include <iostream>
#include <ctime>

#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <Fl/Fl_Value_Slider.H>
#include <Fl/Fl_Button.h>
#include <Fl/Fl_Light_Button.h>
#include <Fl/Fl_Choice.h>
#include <FL/Fl_Box.h>

#include "MyGlWindow.h"


Fl_Group* widgets;


long lastRedraw;
int frameRate = 60;


void idleCB(void* w)
{
	MyGlWindow * win = (MyGlWindow *)w;
	if (clock() - lastRedraw > CLOCKS_PER_SEC / frameRate) {
		lastRedraw = clock();
		win->update();
	}
	win->redraw();
}

int main()
{
	Fl::scheme("none");
	int width = 1024;
	int height = 768;
	Fl_Double_Window* wind = new Fl_Double_Window(100, 100, width, height, "Helix Jump");

	wind->begin();		// put widgets inside of the window

	widgets = new Fl_Group(0, 0, 800, 800);
	widgets->begin();

	MyGlWindow* gl = new MyGlWindow(10, 10, width - 20, height - 50);
	Fl::add_idle((void(*)(void*)) idleCB, gl);  //

	widgets->end();
	Fl_Group::current()->resizable(widgets);

	wind->end();


	wind->show();	// this actually opens the window


	Fl::run();
	delete wind;

	return 1;
}

