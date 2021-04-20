#include <gtk/gtk.h>
#include <iostream>
// #include "widget1.h"

#include <string>
#include <vector>
#include <iostream>

#include <gtk/gtk.h>
#include <cairo.h>

#include "../../../../models/seird.h"
#include "../../../../models/writer.h"
#include "../../ConstrainedOptimization/core/parameter_estimation.h"
#include "../../ConstrainedOptimization/core/parameters.h"

#include "utility.h"




double parameter_values[5]={0};
double initial_values[8]={0};

double& _alpha=parameter_values[0];
double& _kappa=parameter_values[1];
double& _theta=parameter_values[2];
double& _qq=parameter_values[3];
double& _pp=parameter_values[4];

double& _initial_susceptibles=initial_values[0];
double& _initial_exposed=initial_values[1];
double& _initial_infected=initial_values[2];
double& _initial_recovered=initial_values[3];
double& _initial_deaths=initial_values[4];          
double& _simulation_starttime=initial_values[5];    
double& _simulation_endtime=initial_values[6];  
double& _stepsize=initial_values[7];                            
            
std::vector<std::string> param_names={"alpha","kappa","theta","qq","pp"};   
std::vector<std::string> initial_names={"Initial Susceptibles","Initial Exposed","Initial Infected","Initial Recovered","Initial Deaths","Simulation Starttime","Simulation Endtime","RK4 Stepsize h"};             
std::vector<GtkWidget*> parameter_input_widget=std::vector<GtkWidget*>(5);
std::vector<GtkWidget*> initial_input_widget=std::vector<GtkWidget*>(8);



std::vector<double> timepoints;
std::vector<double> datapoints;

//look at https://developer.gnome.org/gtk3/stable/ch01s05.html
//https://stackoverflow.com/questions/56610208/the-pointer-in-signal-connect-function-is-not-working-correct




typedef struct{
	GtkBuilder *builder;
	GtkWidget *window_chooser;
	GtkWidget *window_seird;
	GtkWidget *window_optimized;
	GtkWidget *w_spin_alpha;
	GtkWidget *w_drawing_widget;
	GtkSpinButton *w_spin_kappa;
	GtkSpinButton *w_spin_theta;
	GtkSpinButton *w_spin_qq;
	GtkSpinButton *w_spin_pp;
	GtkSpinButton *w_spin_initial_susceptibles;
	GtkSpinButton *w_spin_initial_exposed;
	GtkSpinButton *w_spin_initial_infected;
	GtkSpinButton *w_spin_initial_recovered;
	GtkSpinButton *w_spin_initial_deaths;
	GtkSpinButton *w_spin_t_start;
	GtkSpinButton *w_spin_t_end;
	GtkSpinButton *w_spin_rk4_stepsize;

} app_widgets;

	GtkBuilder *builder;
	GtkWidget *window_seird, *window_chooser, *window_optimized;

	GtkWidget *w_spin_alpha;
	GtkWidget *w_drawing_widget;
	GtkSpinButton *w_spin_kappa;
	GtkSpinButton *w_spin_theta;
	GtkSpinButton *w_spin_qq;
	GtkSpinButton *w_spin_pp;
	GtkSpinButton *w_spin_initial_susceptibles;
	GtkSpinButton *w_spin_initial_exposed;
	GtkSpinButton *w_spin_initial_infected;
	GtkSpinButton *w_spin_initial_recovered;
	GtkSpinButton *w_spin_initial_deaths;
	GtkSpinButton *w_spin_t_start;
	GtkSpinButton *w_spin_t_end;
	GtkSpinButton *w_spin_rk4_stepsize;

	app_widgets	*widgets = g_slice_new(app_widgets);

int main(int argc, char *argv[])
{

	// notebook = gtk_notebook_new();
	// gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_BOTTOM);

 //    gtk_builder_connect_signals(builder, NULL);
	// gtk_notebook_append_page(GTK_NOTEBOOK(notebook), seird_widget_interactive.widget, seird_widget_interactive.name_widget); //represents GUI tab of the interactive SEIRD model
	// //gtk_notebook_append_page(GTK_NOTEBOOK(notebook), seird_widget_interactive2.widget, seird_widget_interactive2.name_widget);
	// std::cout<<"Address:"<<&seird_widget_interactive<<"\n";


	gtk_init(&argc, &argv);
	
	builder = gtk_builder_new_from_file("Glades/Epidemics.glade");
	 
	widgets -> window_chooser = GTK_WIDGET(gtk_builder_get_object(builder,"window_chooser"));
	
	// widgets -> w_spin_alpha = GTK_WIDGET(gtk_builder_get_object(builder,"spin_alpha"));
	// widgets -> w_spin_kappa = GTK_WIDGET(gtk_builder_get_object(builder,"spin_kappa"));
	// widgets -> w_spin_theta = GTK_WIDGET(gtk_builder_get_object(builder,"spin_theta"));
	// widgets -> w_spin_qq = GTK_WIDGET(gtk_builder_get_object(builder,"spin_qq"));
	// widgets -> w_spin_pp = GTK_WIDGET(gtk_builder_get_object(builder,"spin_pp"));
	// widgets -> w_spin_initial_susceptibles = GTK_WIDGET(gtk_builder_get_object(builder,"spin_initial_susceptibles"));
	// widgets -> w_spin_initial_exposed = GTK_WIDGET(gtk_builder_get_object(builder,"spin_initial_exposed"));
	// widgets -> w_spin_initial_infected = GTK_WIDGET(gtk_builder_get_object(builder,"spin_initial_infected"));
	// widgets -> w_spin_initial_recovered = GTK_WIDGET(gtk_builder_get_object(builder,"spin_initial_recovered"));
	// widgets -> w_spin_initial_deaths = GTK_WIDGET(gtk_builder_get_object(builder,"spin_initial_deaths"));
	// widgets -> w_spin_rk4_stepsize = GTK_WIDGET(gtk_builder_get_object(builder,"spin_rk4_stepsize"));

    gtk_builder_connect_signals(builder, widgets);
	g_slice_free(app_widgets, widgets);

    gtk_widget_show(window_chooser);
    gtk_main();
// 

    return 0;
}



extern "C" G_MODULE_EXPORT void update_simulation(){
    //std::cout<<"alpha:"<<_alpha<<"\n";
    printf("Update Simulation");
    double alpha=_alpha;
    double kappa=_kappa;
    double theta=_theta;
    double qq=_qq;
    double pp=_pp;  

    ug::epi::SEIRD<std::vector<double>> seird_model(alpha,kappa,theta,qq,pp);

    seird_model.change_step_size(_stepsize);

    std::vector<double> u0 = {_initial_susceptibles, _initial_exposed, _initial_infected,_initial_recovered,_initial_deaths};
    double t_start = _simulation_starttime;
    double t_end = _simulation_endtime;

    auto res = seird_model.run(t_start, u0, t_end);
    timepoints=std::get<0>(res);
    datapoints=std::get<1>(res);
    
    
    
}


extern "C" G_MODULE_EXPORT void initialize_values(){
    for (int i=0;i<5;i++){
        parameter_values[i]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(parameter_input_widget[i]));
    }

	// widgets -> w_spin_alpha = GTK_WIDGET(gtk_builder_get_object(builder,"spin_alpha"));
	// widgets -> w_spin_kappa = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_kappa"));
	// widgets -> w_spin_theta = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_theta"));
	// widgets -> w_spin_qq = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_qq"));
	// widgets -> w_spin_pp = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pp"));
	// widgets -> w_spin_initial_susceptibles = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_susceptibles"));
	// widgets -> w_spin_initial_exposed = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_exposed"));
	// widgets -> w_spin_initial_infected = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_infected"));
	// widgets -> w_spin_initial_recovered = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_recovered"));
	// widgets -> w_spin_initial_deaths = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_deaths"));
	// widgets -> w_spin_rk4_stepsize = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_rk4_stepsize"));
	// widgets -> w_spin_t_start = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_t_start"));
	// widgets -> w_spin_t_end = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_t_end"));
	// GtkSpinButton *a = GTK_SPIN_BUTTON(w_spin_alpha);
 //    parameter_values[0]=gtk_spin_button_get_value(a);
    // parameter_values[1]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_spin_kappa));
    // parameter_values[2]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_spin_theta));
    // parameter_values[3]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_spin_qq));
    // parameter_values[4]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_spin_pp));
    // initial_values[0]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_spin_initial_susceptibles));
    // initial_values[1]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_spin_initial_exposed));
    // initial_values[2]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_spin_initial_infected));
    // initial_values[3]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_spin_initial_recovered));
    // initial_values[4]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_spin_initial_deaths));
    // initial_values[5]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_spin_t_start));
    // initial_values[6]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_spin_t_end));
    // initial_values[7]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(w_spin_rk4_stepsize));
    
    for (int i=0;i<8;i++){
        initial_values[i]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(initial_input_widget[i]));
    }               
    
}
extern "C" G_MODULE_EXPORT void parameter_value_changed(GtkSpinButton *spin_button, gpointer user_data, int n) {
    double val=gtk_spin_button_get_value(spin_button);
    parameter_values[n]=val;
    gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing")));  
    // update_simulation();            
}   

extern "C" G_MODULE_EXPORT void initial_value_changed(GtkSpinButton *spin_button, gpointer user_data, int n) {
    double val=gtk_spin_button_get_value(spin_button);
    initial_values[n]=val;
    // update_simulation();
}   



extern "C" G_MODULE_EXPORT double numeric_input(GtkSpinButton *button,
                gpointer       user_data)
{
  return gtk_spin_button_get_value(button);
}


extern "C" G_MODULE_EXPORT void on_spin_alpha_value_changed(GtkSpinButton* button, gpointer* data) {
	double* _this = reinterpret_cast<double*>(data);
	parameter_value_changed(button,data,0);
	printf("alpha\n");;
	}

extern "C" G_MODULE_EXPORT void on_spin_kappa_value_changed(GtkSpinButton* button, gpointer* data) {
	double* _this = reinterpret_cast<double*>(data);
	parameter_value_changed(button,data,1);
	printf("kappa\n");

}           
extern "C" G_MODULE_EXPORT void on_spin_theta_value_changed(GtkSpinButton* button, gpointer* data) {
	double* _this = reinterpret_cast<double*>(data);
	parameter_value_changed(button,data,2);
	printf("theta\n");
}   

extern "C" G_MODULE_EXPORT void on_spin_qq_value_changed(GtkSpinButton* button, gpointer* data) {
	double* _this = reinterpret_cast<double*>(data);
	parameter_value_changed(button,data,3);
	printf("qq\n");
}                       

extern "C" G_MODULE_EXPORT void on_spin_pp_value_changed(GtkSpinButton* button, gpointer* data) {
	double* _this = reinterpret_cast<double*>(data);
	parameter_value_changed(button,data,4);
	printf("pp\n");

}   

extern "C" G_MODULE_EXPORT void on_spin_t_start_value_changed(GtkSpinButton* button, gpointer* data) {
	double* _this = reinterpret_cast<double*>(data);
	initial_value_changed(button,data,0);
	printf("t_start\n");
}       
extern "C" G_MODULE_EXPORT void on_spin_t_end_value_changed(GtkSpinButton* button, gpointer* data) {
	double* _this = reinterpret_cast<double*>(data);
	initial_value_changed(button,data,1);
	printf("t_end\n");
}

extern "C" G_MODULE_EXPORT void on_spin_initial_susceptibles_value_changed(GtkSpinButton* button, gpointer* data) {
	double* _this = reinterpret_cast<double*>(data);
	initial_value_changed(button,data,2);
	printf("Susceptibles\n");
}

extern "C" G_MODULE_EXPORT void on_spin_initial_exposed_value_changed(GtkSpinButton* button, gpointer* data) {
	double* _this = reinterpret_cast<double*>(data);
	initial_value_changed(button,data,3);
	printf("Exposed\n");
}

extern "C" G_MODULE_EXPORT void on_spin_initial_infected_value_changed(GtkSpinButton* button, gpointer* data) {
	double* _this = reinterpret_cast<double*>(data);
	initial_value_changed(button,data,4);
	printf("Infected\n");
}           
extern "C" G_MODULE_EXPORT void on_spin_initial_recovered_value_changed(GtkSpinButton* button, gpointer* data) {
	double* _this = reinterpret_cast<double*>(data);
	initial_value_changed(button,data,5);
	printf("Recovered\n");
}

extern "C" G_MODULE_EXPORT void on_spin_initial_death_value_changed(GtkSpinButton* button, gpointer* data) {
	double* _this = reinterpret_cast<double*>(data);
	initial_value_changed(button,data,6);
	printf("Deaths\n");
}           

extern "C" G_MODULE_EXPORT void on_spin_rk4_stepsize_value_changed(GtkSpinButton* button, gpointer* data) {
	double* _this = reinterpret_cast<double*>(data);
	initial_value_changed(button,data,7);
	printf("RK4\n");
}

extern "C" G_MODULE_EXPORT void on_show_menu(GtkButton* button, gpointer* data) {
	GtkWidget* _this = reinterpret_cast<GtkWidget*>(data);
	gtk_widget_show(_this);
		//Initialize values
	// initialize_values();

	//Initialize simulation
	// update_simulation();

}

extern "C" G_MODULE_EXPORT void on_cancel(GtkButton* button, gpointer* data) {
	GtkWidget* _this = reinterpret_cast<GtkWidget*>(data);
	gtk_widget_hide(_this);


}

// called when window is closed
extern "C" G_MODULE_EXPORT void on_window_main_destroy(GtkButton* caller, gpointer data)
{
    gtk_main_quit();
}

extern "C" G_MODULE_EXPORT gboolean on_drawing_draw (GtkWidget *_widget,cairo_t* cr, gpointer* data)
{

	
	if (datapoints.size()!=0){
		int dim_data=(datapoints.size())/(timepoints.size());
		int selected_dim=0;				
		for (int i=0;i<dim_data;i++){
			ug::epi::util::plot_values(_widget,cr,timepoints,datapoints,i);
		}
		
		ug::epi::util::plot_axis(_widget,cr,timepoints,datapoints);	
	}			
	return 1;
	
}
