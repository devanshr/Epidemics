#pragma once

#ifdef linux
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#endif

#include <string>

#include <vtkVersion.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartXY.h>
#include <vtkTable.h>
#include <vtkPlot.h>
#include <vtkFloatArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkPen.h>

namespace ug{
	namespace epi{
	
	#ifdef linux
	
		class Button{
			public:
			const int x0;
			const int y0;
			const int x1;
			const int y1;
			bool (*f)();
			Button(int* p1[2], int p2[2]:x0(p1[0]),y0(p1[1]),x1(p2[0]),y1(p2[1]){
			
			}
			
			bool observe(int p1[2], int p2[2]){
				if (p1[0]<=x1 && p1[0]>=x0 && p1[1]<=y1 && p1[1]>=y0){
					return f();
				}
			}
		
		}
	
		class ModelRunner{
			private:
			Display *dis;
			int screen;
			Window win;
			GC gc;
			const char* program_name="UG Epidemics ModelRunner";
			int resX=1920;
			int resY=1080;
			void init_x() {
				/* get the colors black and white (see section for details) */
				unsigned long black,white;

				/* use the information from the environment variable DISPLAY 
				   to create the X connection:
				*/	
				dis=XOpenDisplay((char *)0);
			   	screen=DefaultScreen(dis);
				black=BlackPixel(dis,screen),	/* get color black */
				white=WhitePixel(dis, screen);  /* get color white */

				/* once the display is initialized, create the window.
				   This window will be have be 200 pixels across and 300 down.
				   It will have the foreground white and background black
				*/
			   	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	
					resX, resY, 5, 0, 0xffffff);

				/* here is where some properties of the window can be set.
				   The third and fourth items indicate the name which appears
				   at the top of the window and the name of the minimized window
				   respectively.
				*/
				XSetStandardProperties(dis,win,program_name,"HI!",None,NULL,0,NULL);

				/* this routine determines which types of input are allowed in
				   the input.  see the appropriate section for details...
				*/
				XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);

				/* create the Graphics Context */
				gc=XCreateGC(dis, win, 0,0);        

				/* here is another routine to set the foreground and background
				   colors _currently_ in use in the window.
				*/
				XSetBackground(dis,gc,white);
				XSetForeground(dis,gc,black);

				/* clear the window and bring it on top of the other windows */
				XClearWindow(dis, win);
				XMapRaised(dis, win);
			}

			void close_x() {
				XFreeGC(dis, gc);
				XDestroyWindow(dis,win);
				XCloseDisplay(dis);				
			}		
			public:
			
			void run(){
				init_x();
				XEvent event;		/* the XEvent declaration !!! */
				KeySym key;		/* a dealie-bob to handle KeyPress Events */	
				char text[255];		/* a char buffer for KeyPress Events */
				const char* text1="Hey";
			
				/* look for events forever... */
				while(1) {		
					/* get the next event and stuff it into our event variable.
					   Note:  only events we set the mask for are detected!
					*/
					XDrawString(dis,win,gc,50,50, text1, strlen(text1));
					XNextEvent(dis, &event);
				
					if (event.type==Expose && event.xexpose.count==0) {
					/* the window was exposed redraw it! */
						//redraw();
					}
					if (event.type==KeyPress&&
					    XLookupString(&event.xkey,text,255,&key,0)==1) {
					/* use the XLookupString routine to convert the invent
					   KeyPress data into regular text.  Weird but necessary...
					*/
						if (text[0]=='q') {
							close_x();
						}
						printf("You pressed the %c key!\n",text[0]);
					}
					if (event.type==ButtonPress) {
					/* tell where the mouse Button was Pressed */
						printf("You pressed a button at (%i,%i)\n",
							event.xbutton.x,event.xbutton.y);
					}
				}			
			
			}
		
		};
	
	#endif
	
	}
}
