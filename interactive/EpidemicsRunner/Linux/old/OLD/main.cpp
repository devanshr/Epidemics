//http://www.youtube.com/user/thecplusplusguy
//Thanks for the typed in code to Tapit85
#include <gtk/gtk.h>
#include <string>
// #include "widget1.h"
#include "widge2.h"
#include <iostream>



int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *window, *notebook, *label, *label2,*label3,*hbox1,*parameter_input_widget;
	// window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkBuilder      *builder; 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "Glades/SEIRD.glade", NULL);
    gtk_builder_connect_signals(builder, window);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    GtkSpinButton *spin_alpha;

	// GtkWidget* label0 = GTK_WIDGET(gtk_builder_get_object(builder, "label_alpha"));
	// GtkAdjustment *adjustment0;
	// adjustment0 = gtk_adjustment_new (0.00000003, 0.0, 1, 0.0000001, 0.1, 0.0);								
	// parameter_input_widget = GTK_WIDGET(gtk_builder_get_object(builder, "spin_alpha"));
	// spin_alpha = GTK_SPIN_BUTTON(parameter_input_widget);
	// gtk_spin_button_set_adjustment(spin_alpha, adjustment0);
	// gtk_spin_button_set_digits(spin_alpha,3);

	// g_signal_connect (spin_alpha, "value-changed",  G_CALLBACK (alpha_value_changed_callback), this);  
    g_object_unref(builder);


	g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "UG EpidemicsRunner");

	notebook = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_BOTTOM);

	ug::epi::SEIRDWidget<ug::epi::util::WidgetTab::Interactive> seird_widget_interactive;
	
    gtk_builder_connect_signals(builder, NULL);
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
	// gtk_container_add(GTK_CONTAINER(window), notebook);


	gtk_widget_show(window);
	gtk_main();
	std::cout<<"Programm ended\n";
	return 0;
}
