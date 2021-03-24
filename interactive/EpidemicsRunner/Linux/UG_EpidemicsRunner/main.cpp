//http://www.youtube.com/user/thecplusplusguy
//Thanks for the typed in code to Tapit85
#include <gtk/gtk.h>
#include <string>
#include "widget1.h"
#include <iostream>

int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *window, *notebook, *label, *label2,*label3,*hbox1;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "UG EpidemicsRunner");
	notebook = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_BOTTOM);

	ug::epi::SEIRDWidget<ug::epi::util::WidgetTab::Interactive> seird_widget_interactive;
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), seird_widget_interactive.widget, seird_widget_interactive.name_widget); //represents GUI tab of the interactive SEIRD model
	//gtk_notebook_append_page(GTK_NOTEBOOK(notebook), seird_widget_interactive2.widget, seird_widget_interactive2.name_widget);
	std::cout<<"Address:"<<&seird_widget_interactive<<"\n";
	
	/*
	for(int i = 0; i < 5; i += 1)
	{
		hbox1=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
		std::string s = "Label1.";
		s += static_cast<char>(49+i);
		label = gtk_label_new(s.c_str());
		
		s = "Page ";
		s += static_cast<char>(49+i);
		label2 = gtk_label_new(s.c_str());
		gtk_box_pack_start(GTK_BOX(hbox1),label,0,0,0);
		label3 = gtk_label_new("label3");
		gtk_box_pack_start(GTK_BOX(hbox1),label3,0,0,0);	
		

		//gtk_container_add(GTK_CONTAINER(win),vbox);			
		//gtk_notebook_append_page(GTK_NOTEBOOK(notebook), label, label2);
		gtk_notebook_append_page(GTK_NOTEBOOK(notebook), hbox1, label2);
	}
	*/
	gtk_container_add(GTK_CONTAINER(window), notebook);


	gtk_widget_show_all(window);
	gtk_main();
	std::cout<<"Programm ended\n";
	return 0;
}
