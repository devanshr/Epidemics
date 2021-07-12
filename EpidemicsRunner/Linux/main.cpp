//http://www.youtube.com/user/thecplusplusguy
//Thanks for the typed in code to Tapit85
#include <gtk/gtk.h>
#include <string>
#include "widgets/seird_widget.h"
#include "widgets/seird_pde_widget.h"
#include "widgets/seird_pde_editor_widget.h"
#include <iostream>
#include <clocale>


int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);
	std::setlocale(LC_NUMERIC,"C");
	GtkWidget *window, *notebook;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "UG EpidemicsRunner");
	gtk_window_set_icon_from_file(GTK_WINDOW(window), "resources/icon.png", NULL);
	notebook = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_BOTTOM);
	ug::epi::SEIRDWidget seird_widget;
	ug::epi::SEIRDPDEWidget seird_pde_widget;
	ug::epi::SEIRDPDE_EDITORWidget seird_pde_editor_widget;

	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), seird_widget.get_widget(),seird_widget.get_name()); //represents GUI tab of the interactive SEIRD model
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), seird_pde_widget.get_widget(),seird_pde_widget.get_name()); //represents GUI tab of the interactive SEIRD model
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), seird_pde_editor_widget.get_widget(),seird_pde_editor_widget.get_name()); //represents GUI tab of the interactive SEIRD model
	

	//gtk_notebook_append_page(GTK_NOTEBOOK(notebook), seird_widget_interactive2.widget, seird_widget_interactive2.name_widget);
	
	 gtk_container_add(GTK_CONTAINER(window), notebook);


	//gtk_widget_show(window);
	gtk_widget_show_all(window);
	
	gtk_main();
	std::cout<<"Programm ended\n";
	return 0;
}
