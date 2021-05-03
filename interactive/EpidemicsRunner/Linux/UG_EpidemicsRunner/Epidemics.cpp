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

#include "utility.h"




double parameter_values[5] = {0};
bool check_values[5] = {0};
double initial_values[8] = {0};
double upper_bound_values[5] = {0};
double lower_bound_values[5] = {0};

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
double& _stepsize = initial_values[7];

int _max_iter = 3;
int _no_groups = 2;
int _no_particles = 8;

std::vector<std::string> param_names = {"alpha","kappa","theta","qq","pp"};
std::vector<std::string> initial_names = {"Initial Susceptibles","Initial Exposed","Initial Infected","Initial Recovered","Initial Deaths","Simulation Starttime","Simulation Endtime","RK4 Stepsize h"};             
std::vector<GtkWidget*> parameter_input_widget = std::vector<GtkWidget*>(5);
std::vector<GtkWidget*> initial_input_widget = std::vector<GtkWidget*>(8);
std::vector<GtkWidget*> check_input_widget = std::vector<GtkWidget*>(8);



std::vector<double> timepoints;
std::vector<double> datapoints;

//look at https://developer.gnome.org/gtk3/stable/ch01s05.html
//https://stackoverflow.com/questions/56610208/the-pointer-in-signal-connect-function-is-not-working-correct




/* MAYBE REIMPLEMENT LATER FOR BETTER STRUCTURE!?

typedef struct
{
    GtkSpinButton *w_spin_initial_susceptibles;
    GtkSpinButton *w_spin_initial_exposed;
    GtkSpinButton *w_spin_initial_infected;
    GtkSpinButton *w_spin_initial_recovered;
    GtkSpinButton *w_spin_initial_deaths;
    GtkSpinButton *w_spin_t_start;
    GtkSpinButton *w_spin_t_end;
    GtkSpinButton *w_spin_rk4_stepsize;

} initial_input_widgets;


typedef struct
{
    GtkSpinButton *w_spin_alpha;
    GtkSpinButton *w_spin_kappa;
    GtkSpinButton *w_spin_theta;
    GtkSpinButton *w_spin_qq;
    GtkSpinButton *w_spin_pp;
} parameter_input_widgets;


typedef struct
{
    GtkToggleButton *w_check_alpha;
    GtkToggleButton *w_check_kappa;
    GtkToggleButton *w_check_theta;
    GtkToggleButton *w_check_qq;
    GtkToggleButton *w_check_pp;
} check_input_widgets;


typedef struct
{
    GtkSpinButton *w_spin_lower_bound_alpha;
    GtkSpinButton *w_spin_upper_bound_alpha;
    GtkSpinButton *w_spin_lower_bound_kappa;
    GtkSpinButton *w_spin_upper_bound_kappa;
    GtkSpinButton *w_spin_lower_bound_theta;
    GtkSpinButton *w_spin_upper_bound_theta;
    GtkSpinButton *w_spin_lower_bound_qq;
    GtkSpinButton *w_spin_upper_bound_qq;
    GtkSpinButton *w_spin_lower_Wbound_pp;
    GtkSpinButton *w_spin_upper_bound_pp;
    
} bound_input_widgets;

*/


typedef struct{
    GtkWidget *window_chooser;
    GtkWidget *window_seird;
    GtkWidget *window_optimized;
    GtkWidget *window_bounds;
    GtkWidget *w_drawing_widget;
    GtkWidget *w_drawing_widget2;
    GtkWidget *w_drawing_widget3;
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
    GtkSpinButton *w_spin_rk4_stepsize;
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

    seird_model.change_step_size(_stepsize);

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
 
    widgets -> w_spin_alpha = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_alpha"));
    widgets -> w_spin_kappa = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_kappa"));
    widgets -> w_spin_theta = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_theta"));
    widgets -> w_spin_qq = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_qq"));
    widgets -> w_spin_pp = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pp"));


    widgets -> w_spin_alpha_optimized = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_alpha_optimized"));
    widgets -> w_spin_kappa_optimized = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_kappa_optimized"));
    widgets -> w_spin_theta_optimized = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_theta_optimized"));
    widgets -> w_spin_qq_optimized = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_qq_optimized"));
    widgets -> w_spin_pp_optimized = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pp_optimized"));

    widgets -> w_check_alpha = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_alpha_optimized"));
    widgets -> w_check_kappa = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_kappa_optimized"));
    widgets -> w_check_theta = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_theta_optimized"));
    widgets -> w_check_qq = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_qq_optimized"));
    widgets -> w_check_pp = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_pp_optimized"));

    widgets -> w_spin_initial_susceptibles = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_susceptibles"));
    widgets -> w_spin_initial_exposed = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_exposed"));
    widgets -> w_spin_initial_infected = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_infected"));
    widgets -> w_spin_initial_recovered = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_recovered"));
    widgets -> w_spin_initial_deaths = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_deaths"));
    widgets -> w_spin_rk4_stepsize = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_rk4_stepsize"));
    widgets -> w_spin_t_start = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_t_start"));
    widgets -> w_spin_t_end = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_t_end"));

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
    initial_values[7]=gtk_spin_button_get_value(widgets -> w_spin_rk4_stepsize);

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
//     gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing")));  

//     update_simulation();
// }   


extern "C" G_MODULE_EXPORT void upper_bound_value_changed(GtkSpinButton *spin_button, int n)
{
    // GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(spin_button);
    double val = gtk_spin_button_get_value(spin_button);
    upper_bound_values[n]=val;
}   


extern "C" G_MODULE_EXPORT void lower_bound_value_changed(GtkSpinButton *spin_button, int n)
{
    // GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(spin_button);
    double val = gtk_spin_button_get_value(spin_button);
    lower_bound_values[n]=val;
}   


extern "C" G_MODULE_EXPORT void parameter_value_changed(GtkSpinButton *spin_button, gpointer user_data, int n)
{
    // GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(spin_button);
    double val = gtk_spin_button_get_value(spin_button);
    parameter_values[n]=val;
    gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing")));  
    update_simulation();
}   

extern "C" G_MODULE_EXPORT void initial_value_changed(GtkSpinButton *spin_button, gpointer user_data, int n)
{
    // GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(spin_button);
    double val = gtk_spin_button_get_value(spin_button);
    initial_values[n]=val;
    gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing")));
    update_simulation();
}   



extern "C" G_MODULE_EXPORT double numeric_input(GtkSpinButton *button, gpointer user_data)
{
  return gtk_spin_button_get_value(button);
}


extern "C" G_MODULE_EXPORT void on_spin_alpha_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    parameter_value_changed(button,data,0);
    printf("alpha\n");;
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







// extern "C" G_MODULE_EXPORT void on_check_alpha_toggled(GtkToggleButton* button, gpointer* data)
// {
//     checkbox_toggled(button,data,0);
//     printf("alpha\n");;
//     }

// extern "C" G_MODULE_EXPORT void on_check_kappa_toggled(GtkToggleButton* button, gpointer* data)
// {
//     GtkToggleButton *_this = reinterpret_cast<GtkToggleButton*>(button);
//     checkbox_toggled(button,data,1);
//     printf("kappa\n");

// }           
// extern "C" G_MODULE_EXPORT void on_check_theta_toggled(GtkToggleButton* button, gpointer* data)
// {
//     GtkToggleButton *_this = reinterpret_cast<GtkToggleButton*>(button);
//     checkbox_toggled(button,data,2);
//     printf("theta\n");
// }   

// extern "C" G_MODULE_EXPORT void on_check_qq_toggled(GtkToggleButton* button, gpointer* data)
// {
//     GtkToggleButton *_this = reinterpret_cast<GtkToggleButton*>(button);
//     checkbox_toggled(button,data,3);
//     printf("qq\n");
// }                       

// extern "C" G_MODULE_EXPORT void on_check_pp_toggled(GtkToggleButton* button, gpointer* data)
// {
//     GtkToggleButton *_this = reinterpret_cast<GtkToggleButton*>(button);
//     checkbox_toggled(button,data,4);
//     printf("pp\n");

// }   








// extern "C" G_MODULE_EXPORT void on_check_alpha_pde_toggled(GtkToggleButton* button, gpointer* data)
// {
//     GtkToggleButton *_this = reinterpret_cast<GtkToggleButton*>(button);
//     checkbox_toggled(button,data,0);
//     printf("alpha\n");;
//     }

// extern "C" G_MODULE_EXPORT void on_check_kappa_pde_toggled(GtkToggleButton* button, gpointer* data)
// {
//     GtkToggleButton *_this = reinterpret_cast<GtkToggleButton*>(button);
//     checkbox_toggled(button,data,1);
//     printf("kappa\n");

// }           
// extern "C" G_MODULE_EXPORT void on_check_theta_pde_toggled(GtkToggleButton* button, gpointer* data)
// {
//     GtkToggleButton *_this = reinterpret_cast<GtkToggleButton*>(button);
//     checkbox_toggled(button,data,2);
//     printf("theta\n");
// }   

// extern "C" G_MODULE_EXPORT void on_check_qq_pde_toggled(GtkToggleButton* button, gpointer* data)
// {
//     GtkToggleButton *_this = reinterpret_cast<GtkToggleButton*>(button);
//     checkbox_toggled(button,data,3);
//     printf("qq\n");
// }                       

// extern "C" G_MODULE_EXPORT void on_check_pp_pde_toggled(GtkToggleButton* button, gpointer* data)
// {
//     GtkToggleButton *_this = reinterpret_cast<GtkToggleButton*>(button);
//     checkbox_toggled(button,data,4);
//     printf("pp\n");

// }





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
    printf( "Lower: %4.2f\n", lower);

}




extern "C" G_MODULE_EXPORT void on_spin_upper_bound_kappa_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    upper_bound_value_changed(button, 1);
    printf( "Lower: %4.2f\n", lower);

}



extern "C" G_MODULE_EXPORT void on_spin_upper_bound_theta_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    upper_bound_value_changed(button, 2);
    printf( "Lower: %4.2f\n", lower);

}



extern "C" G_MODULE_EXPORT void on_spin_upper_bound_qq_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    upper_bound_value_changed(button, 3);
    printf( "Lower: %4.2f\n", lower);

}

extern "C" G_MODULE_EXPORT void on_spin_upper_bound_pp_value_changed(GtkSpinButton* button, gpointer* data)
{
    // GtkWidget *_this = reinterpret_cast<GtkWidget*>(gtk_widget_get_parent_window(reinterpret_cast<GtkWidget*>(button)));
    // GtkSpinButton *_that = reinterpret_cast<GtkSpinButton*>(data);
    double lower  = gtk_spin_button_get_value(button);
    upper_bound_value_changed(button, 4);
    printf( "Lower: %4.2f\n", lower);

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

extern "C" G_MODULE_EXPORT void on_spin_rk4_stepsize_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    initial_value_changed(button,data,7);
    printf("RK4\n");
}



extern "C" G_MODULE_EXPORT void on_show_menu(GtkButton* button, gpointer* data)
{
    GtkWidget* _this = reinterpret_cast<GtkWidget*>(data);
    gtk_widget_show(_this);
        //Initialize value<s
    // initialize_values();

    //Initialize simulation
    // update_simulation();

}




extern "C" G_MODULE_EXPORT void on_cancel(GtkButton* button, gpointer* data)
{
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
    // GtkWidget* _this = reinterpret_cast<GtkWidget*>(data);

    
    if (datapoints.size()!=0)
    {
        int dim_data=(datapoints.size())/(timepoints.size());
        int selected_dim=0;             
        for (int i=0;i<dim_data;i++)
        {
            ug::epi::util::plot_values(_widget,cr,timepoints,datapoints,i);
            printf("Plot Values Iteration %d\n", i );
        }
        
        ug::epi::util::plot_axis(_widget,cr,timepoints, datapoints);    
    }           
    return 1;
    
}





extern "C" G_MODULE_EXPORT void main_pso() {
       double alpha = _alpha;
       double kappa = _kappa;
       double theta = _theta;
       double qq = _qq;
       double pp = _pp;

       std::vector<std::string > names_of_constants;
       std::vector<double> values_of_constants;
       std::vector<std::string> names_of_variables;

       std::vector<std::string > names_of_inits = { "t_start","t_end","init_susceptibles","init_exposed","init_infected","init_recovered","init_deaths" };
       std::vector<double> values_of_inits;

       std::vector<co::EFloat64> bounds;
       if (gtk_toggle_button_get_active(widgets -> w_check_alpha)) {
          std::cout << gtk_toggle_button_get_active(widgets -> w_check_alpha) << "\n";
           names_of_variables.push_back("alpha");
           bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_alpha))); 
           bounds.push_back( co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_alpha)));

       }
       else {
           names_of_constants.push_back("alpha");
           values_of_constants.push_back(alpha);
       }

       if (gtk_toggle_button_get_active(widgets -> w_check_kappa)) {
          std::cout << gtk_toggle_button_get_active(widgets -> w_check_kappa) << "\n";
           names_of_variables.push_back("kappa");
           bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_kappa)));
           bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_kappa)));

       }
       else {
           names_of_constants.push_back("kappa");
           values_of_constants.push_back(kappa);
       }

       if (gtk_toggle_button_get_active(widgets -> w_check_theta)) {
          std::cout << gtk_toggle_button_get_active(widgets -> w_check_theta) << "\n";
           names_of_variables.push_back("theta");
           bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_theta)));
           bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_theta)));

       }
       else {
           names_of_constants.push_back("theta");
           values_of_constants.push_back(theta);
       }

       if (gtk_toggle_button_get_active(widgets -> w_check_qq)) {
           std::cout << gtk_toggle_button_get_active(widgets -> w_check_qq) << "\n";
           names_of_variables.push_back("qq");
           bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_qq)));
           bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_qq)));

       }
       else {
           names_of_constants.push_back("qq");
           values_of_constants.push_back(qq);
       }

       if (gtk_toggle_button_get_active(widgets -> w_check_pp)) {
          std::cout << gtk_toggle_button_get_active(widgets -> w_check_pp) << "\n";
           names_of_variables.push_back("pp");
           bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_lower_bound_pp)));
           bounds.push_back(co::EFloat64(gtk_spin_button_get_value(widgets -> w_spin_upper_bound_pp)));

       }
       else {
           names_of_constants.push_back("pp");
           values_of_constants.push_back(pp);
       }


       values_of_inits = { _simulation_starttime, _simulation_endtime, _initial_susceptibles, _initial_exposed, _initial_infected, _initial_recovered, _initial_deaths };

       std::string textbody = R"(
seird_model=SEIRD(alpha,kappa,theta,qq,pp)
RunSEIRD(seird_model,"./","output.txt",init_susceptibles,init_exposed,init_infected,init_recovered,init_deaths,t_start,t_end,h)
                        )";

        std::string user_selected_optimization_path = "/home/havelock/Terminus/gcsc/Test";
       if (user_selected_optimization_path == "") {
           // MessageBox::Show(L"Please specify the directory for the experimental data");
            printf("Nope, kein Pfad.\n");
       }
       else {

           ug::epi::create_evaluate_lua(user_selected_optimization_path, textbody, names_of_constants, values_of_constants, names_of_variables, names_of_inits, values_of_inits, _stepsize);

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



            for (int i = 0; i < estimated_parameters.len(); i++) {
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
           
           
           auto sq_error = pso.get_saved_losses_in_past_iteration_as_double();
           // auto converted_name = gcnew String(L"Series1");
           // this->chart2->Series[converted_name]->Points->Clear();
           // this->chart2->Refresh();

           gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing")));  

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