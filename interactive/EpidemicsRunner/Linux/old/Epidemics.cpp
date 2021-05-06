#include <gtk/gtk.h>
#include <iostream>
// #include "widget1.h"

#include <string>
#include <vector>

#include <gtk/gtk.h>
#include <cairo.h>

#include "../../../../models/seird.h"
#include "../../../../models/seird_pde.h"
#include "../../../../models/writer.h"
#include "../../../../../ConstrainedOptimization/core/parameter_estimation.h"
#include "../../../../../ConstrainedOptimization/core/parameters.h"
#include "test.cpp"

#include "utility.h"



std::string user_selected_optimization_path = "";
double parameter_values[5] = {0};
bool check_values[5] = {0};
double initial_values[8] = {0};
double upper_bound_values[5] = {0};
double lower_bound_values[5] = {0};
int pso_values[3] = {0};

double& _alpha = parameter_values[0];
double& _kappa = parameter_values[1];
double& _theta = parameter_values[2];
double& _qq = parameter_values[3];
double& _pp = parameter_values[4];

bool& _check_alpha = check_values[0];
bool& _check_kappa = check_values[1];
bool& _check_theta = check_values[2];
bool& _check_qq = check_values[3];
bool& _check_pp = check_values[4];

double& _initial_susceptibles = initial_values[0];
double& _initial_exposed = initial_values[1];
double& _initial_infected = initial_values[2];
double& _initial_recovered = initial_values[3];
double& _initial_deaths = initial_values[4];
double& _simulation_starttime = initial_values[5];
double& _simulation_endtime = initial_values[6];
double& _ode_stepsize = initial_values[7];

int& _max_iter = pso_values[0];
int& _no_groups = pso_values[1];
int& _no_particles = pso_values[2];

int _convergence_threshold = 0;

std::vector<std::string> param_names = {"alpha","kappa","theta","qq","pp"};
std::vector<std::string> initial_names = {"Initial Susceptibles","Initial Exposed","Initial Infected","Initial Recovered","Initial Deaths","Simulation Starttime","Simulation Endtime","RK4 Stepsize h"};             
std::vector<GtkWidget*> parameter_input_widget = std::vector<GtkWidget*>(5);
std::vector<GtkWidget*> initial_input_widget = std::vector<GtkWidget*>(8);
std::vector<GtkWidget*> check_input_widget = std::vector<GtkWidget*>(8);



std::vector<double> timepoints;
std::vector<double> datapoints;
std::vector<double> sq_error;


//look at https://developer.gnome.org/gtk3/stable/ch01s05.html
//https://stackoverflow.com/questions/56610208/the-pointer-in-signal-connect-function-is-not-working-correct


typedef struct{
    GtkWidget *window_chooser;
    GtkWidget *window_optimized;
    GtkWidget *window_bounds;
    GtkSpinButton *w_spin_alpha;
    GtkSpinButton *w_spin_kappa;
    GtkSpinButton *w_spin_theta;
    GtkSpinButton *w_spin_qq;
    GtkSpinButton *w_spin_pp;
    GtkSpinButton *w_spin_alpha_optimized;
    GtkSpinButton *w_spin_kappa_optimized;
    GtkSpinButton *w_spin_theta_optimized;
    GtkSpinButton *w_spin_qq_optimized;
    GtkSpinButton *w_spin_pp_optimized;
    GtkSpinButton *w_spin_initial_susceptibles;
    GtkSpinButton *w_spin_initial_exposed;
    GtkSpinButton *w_spin_initial_infected;
    GtkSpinButton *w_spin_initial_recovered;
    GtkSpinButton *w_spin_initial_deaths;
    GtkSpinButton *w_spin_t_start;
    GtkSpinButton *w_spin_t_end;
    GtkSpinButton *w_spin_ode_stepsize;
    GtkToggleButton *w_check_alpha;
    GtkToggleButton *w_check_kappa;
    GtkToggleButton *w_check_theta;
    GtkToggleButton *w_check_qq;
    GtkToggleButton *w_check_pp;
    GtkSpinButton *w_spin_lower_bound_alpha;
    GtkSpinButton *w_spin_upper_bound_alpha;
    GtkSpinButton *w_spin_lower_bound_kappa;
    GtkSpinButton *w_spin_upper_bound_kappa;
    GtkSpinButton *w_spin_lower_bound_theta;
    GtkSpinButton *w_spin_upper_bound_theta;
    GtkSpinButton *w_spin_lower_bound_qq;
    GtkSpinButton *w_spin_upper_bound_qq;
    GtkSpinButton *w_spin_lower_bound_pp;
    GtkSpinButton *w_spin_upper_bound_pp;

} app_widgets;


    GtkBuilder *builder;

    app_widgets *widgets = g_slice_new(app_widgets);
    // initial_input_widgets *initial_inputs = g_slice_new(initial_input_widgets);
    // parameter_input_widgets *parameter_inputs = g_slice_new(parameter_input_widgets);
    // check_input_widgets *check_inputs = g_slice_new(check_input_widgets);



extern "C" G_MODULE_EXPORT void update_simulation()
{

    printf("Update Simulation ");
    double alpha=_alpha;
    double kappa=_kappa;
    double theta=_theta;
    double qq=_qq;
    double pp=_pp;  

    ug::epi::SEIRD<std::vector<double>> seird_model(alpha,kappa,theta,qq,pp);

    seird_model.change_step_size(_ode_stepsize);

    std::vector<double> u0 = {_initial_susceptibles, _initial_exposed, _initial_infected,_initial_recovered,_initial_deaths};
    double t_start = _simulation_starttime;
    double t_end = _simulation_endtime;

    auto res = seird_model.run(t_start, u0, t_end);
    timepoints=std::get<0>(res);
    datapoints=std::get<1>(res);

    ug::epi::write_data("/output/dd", "_test.txt", timepoints, datapoints,seird_model.names);

}


extern "C" G_MODULE_EXPORT void initialize_values()
{
    // gtk_widget_set_size_request (GTK_WIDGET(gtk_builder_get_object<(builder,"drawing")), 600, 600);
 
    // widgets -> w_spin_alpha = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_alpha"));
    // widgets -> w_spin_kappa = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_kappa"));
    // widgets -> w_spin_theta = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_theta"));
    // widgets -> w_spin_qq = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_qq"));
    // widgets -> w_spin_pp = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pp"));


    widgets -> w_spin_alpha = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_alpha_optimized"));
    widgets -> w_spin_kappa = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_kappa_optimized"));
    widgets -> w_spin_theta = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_theta_optimized"));
    widgets -> w_spin_qq = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_qq_optimized"));
    widgets -> w_spin_pp = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pp_optimized"));

    widgets -> w_check_alpha = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_alpha_optimized"));
    widgets -> w_check_kappa = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_kappa_optimized"));
    widgets -> w_check_theta = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_theta_optimized"));
    widgets -> w_check_qq = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_qq_optimized"));
    widgets -> w_check_pp = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_pp_optimized"));

    widgets -> w_spin_initial_susceptibles = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_susceptibles_optimized"));
    widgets -> w_spin_initial_exposed = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_exposed_optimized"));
    widgets -> w_spin_initial_infected = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_infected_optimized"));
    widgets -> w_spin_initial_recovered = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_recovered_optimized"));
    widgets -> w_spin_initial_deaths = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_deaths_optimized"));
    widgets -> w_spin_ode_stepsize = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_ode_stepsize_optimized"));
    widgets -> w_spin_t_start = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_t_start_optimized"));
    widgets -> w_spin_t_end = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_t_end_optimized"));

    widgets -> w_spin_lower_bound_alpha = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_lower_bound_alpha"));
    widgets -> w_spin_upper_bound_alpha = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_upper_bound_alpha"));
    widgets -> w_spin_lower_bound_kappa = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_lower_bound_kappa"));
    widgets -> w_spin_upper_bound_kappa = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_upper_bound_kappa"));
    widgets -> w_spin_lower_bound_theta = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_lower_bound_theta"));
    widgets -> w_spin_upper_bound_theta = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_upper_bound_theta"));
    widgets -> w_spin_lower_bound_qq = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_lower_bound_qq"));
    widgets -> w_spin_upper_bound_qq = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_upper_bound_qq"));
    widgets -> w_spin_lower_bound_pp = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_lower_bound_pp"));
    widgets -> w_spin_upper_bound_pp = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_upper_bound_pp"));

    parameter_values[0]=gtk_spin_button_get_value(widgets -> w_spin_alpha);
    parameter_values[1]=gtk_spin_button_get_value(widgets -> w_spin_kappa);
    parameter_values[2]=gtk_spin_button_get_value(widgets -> w_spin_theta);
    parameter_values[3]=gtk_spin_button_get_value(widgets -> w_spin_qq);
    parameter_values[4]=gtk_spin_button_get_value(widgets -> w_spin_pp);


    check_values[0]= gtk_toggle_button_get_active(widgets -> w_check_alpha);
    check_values[1]= gtk_toggle_button_get_active(widgets -> w_check_kappa);
    check_values[2]= gtk_toggle_button_get_active(widgets -> w_check_theta);
    check_values[3]= gtk_toggle_button_get_active(widgets -> w_check_qq);
    check_values[4]= gtk_toggle_button_get_active(widgets -> w_check_pp);

    initial_values[0]=gtk_spin_button_get_value(widgets -> w_spin_initial_susceptibles);
    initial_values[1]=gtk_spin_button_get_value(widgets -> w_spin_initial_exposed);
    initial_values[2]=gtk_spin_button_get_value(widgets -> w_spin_initial_infected);
    initial_values[3]=gtk_spin_button_get_value(widgets -> w_spin_initial_recovered);
    initial_values[4]=gtk_spin_button_get_value(widgets -> w_spin_initial_deaths);
    initial_values[5]=gtk_spin_button_get_value(widgets -> w_spin_t_start);
    initial_values[6]=gtk_spin_button_get_value(widgets -> w_spin_t_end);
    initial_values[7]=gtk_spin_button_get_value(widgets -> w_spin_ode_stepsize);

    update_simulation();

    // for (int i=0;i<8;i++)
    // {
    //     initial_values[i]=gtk_spin_button_get_value(initial_inputs[i]);
    // }               
    
}




// extern "C" G_MODULE_EXPORT void checkbox_toggled(GtkToggleButton *check_button, gpointer user_data, int n)
// {
//     if (val == true)
//     {
//         printf("True\n");
//         widgets -> window_bounds = GTK_WIDGET(gtk_builder_get_object(builder,"window_bounds"));
//         gtk_widget_show(window_bounds);
//     }
//     // GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(check_button);
//     bool val = (check_button);
//     // else
//     // {
//         // parameter_values[n]= None;
//         // printf("False\n");
//     // }
    // gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing_seird")));  

//     update_simulation();
// }   


extern "C" G_MODULE_EXPORT void upper_bound_value_changed(GtkSpinButton *spin_button, int n)
{
    double val = gtk_spin_button_get_value(spin_button);
    upper_bound_values[n]=val;
}   


extern "C" G_MODULE_EXPORT void lower_bound_value_changed(GtkSpinButton *spin_button, int n)
{
    double val = gtk_spin_button_get_value(spin_button);
    lower_bound_values[n]=val;
}   




extern "C" G_MODULE_EXPORT void initial_value_changed(GtkSpinButton *spin_button, gpointer user_data, int n)
{
    double val = gtk_spin_button_get_value(spin_button);
    initial_values[n]=val;
    gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing_seird_optimized")));
    update_simulation();
}   


extern "C" G_MODULE_EXPORT void pso_value_changed(GtkSpinButton *spin_button, gpointer user_data, int n)
{
    double val = gtk_spin_button_get_value(spin_button);
    pso_values[n]=val;
   // gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing_seird_optimized")));  
    update_simulation();
}   




extern "C" G_MODULE_EXPORT double numeric_input(GtkSpinButton *button, gpointer user_data)
{
  return gtk_spin_button_get_value(button);
}



extern "C" G_MODULE_EXPORT void on_spin_kappa_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    parameter_value_changed(button,data,1);
    printf("kappa\n");

}           
extern "C" G_MODULE_EXPORT void on_spin_theta_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    parameter_value_changed(button,data,2);
    printf("theta\n");
}   

extern "C" G_MODULE_EXPORT void on_spin_qq_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    parameter_value_changed(button,data,3);
    printf("qq\n");
}

extern "C" G_MODULE_EXPORT void on_spin_pp_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    parameter_value_changed(button,data,4);
    printf("pp\n");

}   



extern "C" G_MODULE_EXPORT void on_spin_iterations_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    pso_value_changed(button,data,0);
    printf("Iterations\n");

}   


extern "C" G_MODULE_EXPORT void on_spin_particles_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    pso_value_changed(button,data,1);
    printf("Particles\n");

}   

extern "C" G_MODULE_EXPORT void on_spin_groups_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    pso_value_changed(button,data,2);
    printf("Groups\n");

}   



extern "C" G_MODULE_EXPORT void on_spin_convergence_threshold_value_changed(GtkSpinButton* button, gpointer* data)
{

    double val = gtk_spin_button_get_value(button);
    _convergence_threshold = val;
    gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing_seird_optimized")));  
    update_simulation();
    printf("Convergence Threshold\n");

}   


extern "C" G_MODULE_EXPORT void on_spin_lower_bound_alpha_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    lower_bound_value_changed(button,0);
    printf( "Lower: %4.2f\n", lower);

}




extern "C" G_MODULE_EXPORT void on_spin_lower_bound_kappa_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    lower_bound_value_changed(button, 1);
    printf( "Lower: %4.2f\n", lower);

}



extern "C" G_MODULE_EXPORT void on_spin_lower_bound_theta_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    lower_bound_value_changed(button, 2);
    printf( "Lower: %4.2f\n", lower);

}



extern "C" G_MODULE_EXPORT void on_spin_lower_bound_qq_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    lower_bound_value_changed(button, 3);
    printf( "Lower: %4.2f\n", lower);

}


extern "C" G_MODULE_EXPORT void on_spin_lower_bound_pp_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    lower_bound_value_changed(button, 4);
    printf( "Lower: %4.2f\n", lower);

}








extern "C" G_MODULE_EXPORT void on_spin_upper_bound_alpha_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    upper_bound_value_changed(button, 0);
    printf( "Upper: %4.2f\n", lower);

}




extern "C" G_MODULE_EXPORT void on_spin_upper_bound_kappa_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    upper_bound_value_changed(button, 1);
    printf( "Upper: %4.2f\n", lower);

}



extern "C" G_MODULE_EXPORT void on_spin_upper_bound_theta_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    upper_bound_value_changed(button, 2);
    printf( "Upper: %4.2f\n", lower);

}



extern "C" G_MODULE_EXPORT void on_spin_upper_bound_qq_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    upper_bound_value_changed(button, 3);
    printf( "Upper: %4.2f\n", lower);

}

extern "C" G_MODULE_EXPORT void on_spin_upper_bound_pp_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    upper_bound_value_changed(button, 4);
    printf( "Upper: %4.2f\n", lower);

}






extern "C" G_MODULE_EXPORT void on_spin_initial_susceptibles_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    initial_value_changed(button,data,0);
    printf("Susceptibles\n");
}

extern "C" G_MODULE_EXPORT void on_spin_initial_exposed_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    initial_value_changed(button,data,1);
    printf("Exposed\n");
}

extern "C" G_MODULE_EXPORT void on_spin_initial_infected_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    initial_value_changed(button,data,2);
    printf("Infected\n");
}           
extern "C" G_MODULE_EXPORT void on_spin_initial_recovered_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    initial_value_changed(button,data,3);
    printf("Recovered\n");
}

extern "C" G_MODULE_EXPORT void on_spin_initial_deaths_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    initial_value_changed(button,data,4);
    printf("Deaths\n");
}           

extern "C" G_MODULE_EXPORT void on_spin_t_start_value_changed(GtkSpinButton* button, gpointer* data)
{
    double* _this = reinterpret_cast<double*>(data);
    initial_value_changed(button,data,5);
    printf("t_start\n");
}       
extern "C" G_MODULE_EXPORT void on_spin_t_end_value_changed(GtkSpinButton* button, gpointer* data)
{
    double* _this = reinterpret_cast<double*>(data);
    initial_value_changed(button,data,6);
    printf("t_end\n");
}

extern "C" G_MODULE_EXPORT void on_spin_ode_stepsize_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    initial_value_changed(button,data,7);
    printf("RK4\n");
}


extern "C" G_MODULE_EXPORT void on_folder_chooser_response(int bla, GtkFileChooserDialog* dialog)
{
    GtkWidget* _this = reinterpret_cast<GtkWidget*>(dialog);
    user_selected_optimization_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    std::cout << "Set path to " << user_selected_optimization_path << "\n";
    gtk_widget_hide(_this);

}



extern "C" G_MODULE_EXPORT void on_show_menu(GtkButton *button, gpointer* data)
{
    GtkWidget* _this = reinterpret_cast<GtkWidget*>(data);
    gtk_widget_show(_this);
        //Initialize value<s
    // initialize_values();
    printf("Show Menu\n");
    //Initialize simulation
    // update_simulation();
}


extern "C" G_MODULE_EXPORT void on_show_popup_menu(GtkMenuItem *button, gpointer* data)
{
    GtkWidget* _this = reinterpret_cast<GtkWidget*>(data);
    gtk_widget_show(_this);
        //Initialize value<s
    // initialize_values();
    printf("Show Menu\n");
    //Initialize simulation
    // update_simulation();
}

extern "C" G_MODULE_EXPORT void on_cancel(GtkButton* button, gpointer* data)
{
    GtkWidget* _this = reinterpret_cast<GtkWidget*>(data);
    gtk_widget_hide(_this);
    printf("Cancel\n");


}


// called when window is closed
extern "C" G_MODULE_EXPORT void on_window_main_destroy(GtkButton* caller, gpointer data)
{
    gtk_main_quit();
}

extern "C" G_MODULE_EXPORT gboolean on_drawing_squared_error_draw (GtkWidget *_widget,cairo_t* cr, gpointer* data)
{
    // GtkWidget* _this = reinterpret_cast<GtkWidget*>(data);

    std::vector<double> iterations; 


    for (int i = 0; i < sq_error.size(); ++i)
    {
        iterations.push_back(i);
    }


    if (sq_error.size()!=0)
    {
        ug::epi::util::plot_values(_widget,cr,iterations,sq_error,0);
        printf("Plot Squared Error\n");
        ug::epi::util::plot_axis(_widget,cr,iterations, sq_error);    
    }           

    return 1;
    
}


extern "C" G_MODULE_EXPORT gboolean on_drawing_seird_draw (GtkWidget *_widget,cairo_t* cr, gpointer* data)
{
    // GtkWidget* _this = reinterpret_cast<GtkWidget*>(data);


    if (datapoints.size()!=0)
    {
        int dim_data=(datapoints.size())/(timepoints.size());
        for (int i=0;i<dim_data;i++)
        {
            ug::epi::util::plot_values(_widget,cr,timepoints,datapoints,i);
            printf("Plot Values Iteration %d\n", i );
        }
        
        ug::epi::util::plot_axis(_widget,cr,timepoints, datapoints);    
    }           
    return 1;
    
}


extern "C" G_MODULE_EXPORT void run_pso() 
{
    double alpha = _alpha;
    double kappa = _kappa;
    double theta = _theta;
    double qq = _qq;
    double pp = _pp;
    printf("Run PSO\n");

    std::vector<std::string > names_of_constants;
    std::vector<double> values_of_constants;
    std::vector<std::string> names_of_variables;

    std::vector<std::string> names_of_inits = { "t_start","t_end","init_susceptibles","init_exposed","init_infected","init_recovered","init_deaths" };
    std::vector<double> values_of_inits;

    std::vector<co::EFloat64> bounds;

    if (gtk_toggle_button_get_active(widgets -> w_check_alpha)) 
    {
      std::cout << gtk_toggle_button_get_active(widgets -> w_check_alpha) << "\n";
       names_of_variables.push_back("alpha");
       bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_alpha))); 
       bounds.push_back( co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_alpha)));
    }

    else
    {
       names_of_constants.push_back("alpha");
       values_of_constants.push_back(alpha);
    }

    if (gtk_toggle_button_get_active(widgets -> w_check_kappa)) 
    {
      std::cout << gtk_toggle_button_get_active(widgets -> w_check_kappa) << "\n";
       names_of_variables.push_back("kappa");
       bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_kappa)));
       bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_kappa)));

    }
    else 
    {
       names_of_constants.push_back("kappa");
       values_of_constants.push_back(kappa);
    }

    if (gtk_toggle_button_get_active(widgets -> w_check_theta)) {
      std::cout << gtk_toggle_button_get_active(widgets -> w_check_theta) << "\n";
       names_of_variables.push_back("theta");
       bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_theta)));
       bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_theta)));

   }
   else 
   {
       names_of_constants.push_back("theta");
       values_of_constants.push_back(theta);
   }

   if (gtk_toggle_button_get_active(widgets -> w_check_qq)) {
       std::cout << gtk_toggle_button_get_active(widgets -> w_check_qq) << "\n";
       names_of_variables.push_back("qq");
       bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_qq)));
       bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_qq)));

   }
   else
   {
       names_of_constants.push_back("qq");
       values_of_constants.push_back(qq);
   }

   if (gtk_toggle_button_get_active(widgets -> w_check_pp)) {
      std::cout << gtk_toggle_button_get_active(widgets -> w_check_pp) << "\n";
       names_of_variables.push_back("pp");
       bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_pp)));
       bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_pp)));

   }
   else
   {
       names_of_constants.push_back("pp");
       values_of_constants.push_back(pp);
   }


   values_of_inits = { _simulation_starttime, _simulation_endtime, _initial_susceptibles, _initial_exposed, _initial_infected, _initial_recovered, _initial_deaths };

   std::string textbody = R"(
seird_model=SEIRD(alpha,kappa,theta,qq,pp)
RunSEIRD(seird_model,"./","output.txt",init_susceptibles,init_exposed,init_infected,init_recovered,init_deaths,t_start,t_end,h)
                    )";

    if (user_selected_optimization_path == "") 
    {
       // MessageBox::Show(L"Please specify the directory for the experimental data");
        printf("Nope, kein Pfad.\n");
    }
    else 
    {
        ug::epi::create_evaluate_lua(user_selected_optimization_path, textbody, names_of_constants, values_of_constants, names_of_variables, names_of_inits, values_of_inits, _ode_stepsize);

        co::PSOOptions options;
        options.set_max_iterations(_max_iter);
        options.set_n_groups(_no_groups);
        options.set_n_particles(_no_particles);
        co::BiogasEvaluation<co::EFloat64, co::ConfigComputation::Local, co::ConfigOutput::File> evaluator(user_selected_optimization_path, "subset_target.lua", "subset_sim.lua");
        co::ParticleSwarmOptimizer<co::BiogasEvaluation<co::EFloat64, co::ConfigComputation::Local, co::ConfigOutput::File>> pso(options, evaluator);
        co::EVarManager<co::EFloat64> estimated_parameters;

        printf("%d \n",_max_iter);
        printf("%d \n",_no_groups);
        printf("%d \n",_no_particles);

        std::cout << names_of_variables.size() << "\n";
        std::cout << bounds.size() << "\n";
       for (int i = 0; i < names_of_variables.size(); ++i)
       {
       std::cout  << "names_of_variables:" << names_of_variables[i] << "\n" ;
       std::cout << "bounds:" << bounds[2*i] << "\n";
       std::cout << "bounds:" << bounds[2*i+1] << "\n";
       }
       auto result = pso.run(estimated_parameters, names_of_variables, bounds);



        for (int i = 0; i < estimated_parameters.len(); i++) 
        {
                if (estimated_parameters.get_name(i) == "alpha") {
                    parameter_values[0] = estimated_parameters.get_param(i).get_value_as_double();
                    gtk_spin_button_set_value(widgets -> w_spin_alpha, parameter_values[0]);
                }
                if (estimated_parameters.get_name(i) == "kappa") {
                    parameter_values[1] =estimated_parameters.get_param(i).get_value_as_double();
                    gtk_spin_button_set_value(widgets -> w_spin_kappa, parameter_values[1]);
                }
                if (estimated_parameters.get_name(i) == "theta") {
                    parameter_values[2] = estimated_parameters.get_param(i).get_value_as_double();
                    gtk_spin_button_set_value(widgets -> w_spin_theta, parameter_values[2]);
                }
                if (estimated_parameters.get_name(i) == "qq") {
                    parameter_values[3] = estimated_parameters.get_param(i).get_value_as_double();
                    gtk_spin_button_set_value(widgets -> w_spin_qq, parameter_values[3]);
                }
                if (estimated_parameters.get_name(i) == "pp") {
                    parameter_values[4] = estimated_parameters.get_param(i).get_value_as_double();
                    gtk_spin_button_set_value(widgets -> w_spin_pp, parameter_values[4]);
                }
        }


        // if (result == co::ErrorCode::OptimizationError) { MessageBox::Show(L"Optimization Error"); }
        // else if (result == co::ErrorCode::PathError) { MessageBox::Show(L"Path Error"); }
        // else if (result == co::ErrorCode::ComputationError) { MessageBox::Show(L"ComputationError"); }
        // else if (result == co::ErrorCode::ParseError) { MessageBox::Show(L"Parse Error!"); }
        // else if (result == co::ErrorCode::NoError) {  MessageBox::Show(L"Optimization Complete!"); 

        sq_error = pso.get_saved_losses_in_past_iteration_as_double();
        // auto converted_name = gcnew String(L"Series1");
        // this->chart2->Series[converted_name]->Points->Clear();
        // this->chart2->Refresh();

       // gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing_seird_optimized")));  

       update_simulation();
       // for (int i = 0; i < sq_error.size(); i++) {

          //  System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint1 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(i,
             //   sq_error[i]));

          //  this->chart2->Series[converted_name]->Points->Add(dataPoint1);
       // }
       // }
       // else { MessageBox::Show(L"Please check the settings"); }

    }
}



extern "C" G_MODULE_EXPORT void run_newton() 
{    

        double alpha = _alpha;
        double kappa = _kappa;
        double theta = _theta;
        double qq = _qq;
        double pp = _pp;
        printf("Run Newton\n");

       std::vector<std::string > names_of_constants;
       std::vector<double> values_of_constants;
       std::vector<std::string> names_of_variables;

       std::vector<std::string > names_of_inits = { "t_start","t_end","init_susceptibles","init_exposed","init_infected","init_recovered","init_deaths" };
       std::vector<double> values_of_inits;

       co::EVar64Manager initial_vars;

       if (gtk_toggle_button_get_active(widgets -> w_check_alpha)) 
       {
           names_of_variables.push_back("alpha");
           co::EVar64 v_alpha=co::EVar64(co::EFloat64(alpha), co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_alpha)), co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_alpha)));
           initial_vars.add("alpha", v_alpha);
       }
       else 
       {
           names_of_constants.push_back("alpha");
           values_of_constants.push_back(alpha);
       }

       if (gtk_toggle_button_get_active(widgets -> w_check_kappa))
       {
           names_of_variables.push_back("kappa");
           //EFloats for bounds aswelll!!
           co::EVar64 v_kappa= co::EVar64(co::EFloat64(kappa), co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_kappa)), co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_kappa)));
           initial_vars.add("kappa", v_kappa);
       }
       else 
       {
           names_of_constants.push_back("kappa");
           values_of_constants.push_back(kappa);
       }

       if (gtk_toggle_button_get_active(widgets -> w_check_theta)) 
       {
           names_of_variables.push_back("theta");
           co::EVar64 v_theta = co::EVar64(co::EFloat64(theta), co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_theta)), co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_theta)));
           initial_vars.add("theta", v_theta);
       }
       else 
       {
           names_of_constants.push_back("theta");
           values_of_constants.push_back(theta);
       }

       if (gtk_toggle_button_get_active(widgets -> w_check_qq)) 
       {
           names_of_variables.push_back("qq");
           co::EVar64 v_qq = co::EVar64(co::EFloat64(qq), co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_qq)), co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_qq)));
           initial_vars.add("qq", v_qq);
       }
       else 
       {
           names_of_constants.push_back("qq");
           values_of_constants.push_back(qq);
       }

       if (gtk_toggle_button_get_active(widgets -> w_check_pp)) 
       {
           names_of_variables.push_back("pp");
           co::EVar64 v_pp = co::EVar64(co::EFloat64(pp), co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_pp)), co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_pp)));
           initial_vars.add("pp", v_pp);
       }
       else 
       {
           names_of_constants.push_back("pp");
           values_of_constants.push_back(pp);
       }




       values_of_inits = { _simulation_starttime, _simulation_endtime, _initial_susceptibles, _initial_exposed, _initial_infected, _initial_recovered, _initial_deaths };

       std::string textbody = R"(

seird_model=SEIRD(alpha,kappa,theta,qq,pp)
RunSEIRD(seird_model,"./","output.txt",init_susceptibles,init_exposed,init_infected,init_recovered,init_deaths,t_start,t_end,h)
                        )";
       
       if (user_selected_optimization_path == "") 
       {
           printf("No Path Set\n");
       }
       else
       {
           ug::epi::create_evaluate_lua(user_selected_optimization_path, textbody, names_of_constants, values_of_constants, names_of_variables, names_of_inits, values_of_inits, _ode_stepsize);

           co::NewtonOptions options;
           options.set_stepsize_alpha(1);
          
           co::BiogasEvaluation<co::EFloat64, co::ConfigComputation::Local, co::ConfigOutput::File> evaluator(user_selected_optimization_path, "subset_target.lua", "subset_sim.lua");
           co::EVarManager<co::EFloat64> estimated_parameters;
           co::NewtonOptimizer<decltype(evaluator)> solver(options, evaluator);
           //   MessageBox::Show(gcnew String(user_selected_optimization_path->c_str())); //display path

           solver.set_convergence_threshold(_convergence_threshold);

           auto result = solver.run(initial_vars, estimated_parameters);

           // if (result == co::ErrorCode::OptimizationError) { MessageBox::Show(L"Optimization Error"); }
           // else if (result == co::ErrorCode::PathError) { MessageBox::Show(L"Path Error"); }
           // else if (result == co::ErrorCode::ComputationError) { MessageBox::Show(L"ComputationError"); }
           // else if (result == co::ErrorCode::ParseError) { MessageBox::Show(L"Parse Error!"); }
           // else

            for (int i = 0; i < estimated_parameters.len(); i++) 
            {
                    if (estimated_parameters.get_name(i) == "alpha") 
                    {
                        parameter_values[0] = estimated_parameters.get_param(i).get_value_as_double();
                        gtk_spin_button_set_value(widgets -> w_spin_alpha, parameter_values[0]);
                    }
                    if (estimated_parameters.get_name(i) == "kappa") 
                    {
                        parameter_values[1] =estimated_parameters.get_param(i).get_value_as_double();
                        gtk_spin_button_set_value(widgets -> w_spin_kappa, parameter_values[1]);
                    }
                    if (estimated_parameters.get_name(i) == "theta") 
                    {
                        parameter_values[2] = estimated_parameters.get_param(i).get_value_as_double();
                        gtk_spin_button_set_value(widgets -> w_spin_theta, parameter_values[2]);
                    }
                    if (estimated_parameters.get_name(i) == "qq") 
                    {
                        parameter_values[3] = estimated_parameters.get_param(i).get_value_as_double();
                        gtk_spin_button_set_value(widgets -> w_spin_qq, parameter_values[3]);
                    }
                    if (estimated_parameters.get_name(i) == "pp") 
                    {
                        parameter_values[4] = estimated_parameters.get_param(i).get_value_as_double();
                        gtk_spin_button_set_value(widgets -> w_spin_pp, parameter_values[4]);
                    }
            }

                   // MessageBox::Show(L"Optimization Complete!");
                   auto sq_error = solver.get_saved_losses_in_past_iteration_as_double();
                   // auto converted_name = gcnew String(L"Series1");
                   // this->chart2->Series[converted_name]->Points->Clear();
                   // this->chart2->Refresh();
                   // for (int i = 0; i < sq_error.size(); i++) {

                   //      System::Windows::Forms::DataVisualization::Charting::DataPoint^ dataPoint1 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(i,
                   //         sq_error[i]));

                   //      this->chart2->Series[converted_name]->Points->Add(dataPoint1);
                   // }
                   
               // }
           // }
           // else { MessageBox::Show(L"Please check the settings"); }
           
       // }
}
}


int main(int argc, char *argv[])
{

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("Glades/Epidemics.glade");

    widgets -> window_chooser = GTK_WIDGET(gtk_builder_get_object(builder,"window_chooser"));

    gtk_builder_connect_signals(builder, widgets);

    g_slice_free(app_widgets, widgets);

    initialize_values();

    // gtk_widget_show(widgets -> window_chooser);

    gtk_main();

    return 0;
}
