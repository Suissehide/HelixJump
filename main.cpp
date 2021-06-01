// the main routine makes the window, and then runs an even loop
// until the window is closed
#include <windows.h>
#include <iostream>
#include <ctime>

#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl_Double_Window.h>
#include <Fl/Fl.h>
#include <Fl/Fl_Value_Slider.H>
#include <Fl/Fl_Button.h>
#include <Fl/Fl_Light_Button.h>
#include <Fl/Fl_Choice.h>
#include <FL/Fl_Box.h>

Fl_Group* widgets;

int main()
{
	Fl::scheme("gtk+");
	int width = 1280;
	int height = 720;
	Fl_Double_Window* win = new Fl_Double_Window(100, 100, width, height, "Helix Jump");

	win->begin();

	widgets = new Fl_Group(0, 0, 800, 800);
	widgets->begin();

	widgets->end();
	Fl_Group::current()->resizable(widgets);

	win->end();
	win->show();

	Fl::run();
	delete win;

	return 1;
}