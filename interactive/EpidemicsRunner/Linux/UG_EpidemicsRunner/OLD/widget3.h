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

namespace ug{
    namespace epi{
        
        namespace util{
            enum class WidgetTab{
                Interactive,
                Optimization
            };
        }
        
    
        template<util::WidgetTab T>
        class SEIRDWidget{
        };
        
        template<>
        class SEIRDWidget<util::WidgetTab::Interactive>{

        public:     

            typedef struct{
                GtkWidget *w_spin_alpha;
                GtkWidget *w_spin_kappa;
                GtkWidget *w_spin_theta;
                GtkWidget *w_spin_qq;
                GtkWidget *w_spin_pp;
                GtkWidget *w_spin_initial_susceptibles;
                GtkWidget *w_spin_initial_exposed;
                GtkWidget *w_spin_initial_infected;
                GtkWidget *w_spin_initial_recovered;
                GtkWidget *w_spin_initial_deaths;
                GtkWidget *w_spin_rk4_stepsize;
                GtkWidget *w_drawing;

            } app_widgets;
            
            void createWidget(){
            
                GtkBuilder *builder;
                GtkWidget *window;
                app_widgets *widgets = g_slice_new(app_widgets);
                
                builder = gtk_builder_new_from_file("Glades/SEIRD.glade");
                
                window = GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
                
                widgets -> w_spin_alpha = GTK_WIDGET(gtk_builder_get_object(builder,"spin_alpha"));
                widgets -> w_spin_kappa = GTK_WIDGET(gtk_builder_get_object(builder,"spin_kappa"));
                widgets -> w_spin_theta = GTK_WIDGET(gtk_builder_get_object(builder,"spin_theta"));
                widgets -> w_spin_qq = GTK_WIDGET(gtk_builder_get_object(builder,"spin_qq"));
                widgets -> w_spin_pp = GTK_WIDGET(gtk_builder_get_object(builder,"spin_pp"));
                widgets -> w_spin_initial_susceptibles = GTK_WIDGET(gtk_builder_get_object(builder,"spin_initial_susceptibles"));
                widgets -> w_spin_initial_exposed = GTK_WIDGET(gtk_builder_get_object(builder,"spin_initial_exposed"));
                widgets -> w_spin_initial_infected = GTK_WIDGET(gtk_builder_get_object(builder,"spin_initial_infected"));
                widgets -> w_spin_initial_recovered = GTK_WIDGET(gtk_builder_get_object(builder,"spin_initial_recovered"));
                widgets -> w_spin_initial_deaths = GTK_WIDGET(gtk_builder_get_object(builder,"spin_initial_deaths"));
                widgets -> w_spin_rk4_stepsize = GTK_WIDGET(gtk_builder_get_object(builder,"spin_rk4_stepsize"));
                widgets -> w_drawing = GTK_WIDGET(gtk_builder_get_object(builder,"drawing"));

                gtk_builder_connect_signals(builder, widgets);
                g_slice_free(app_widgets, widgets);

                gtk_widget_show(window);                
                // gtk_main();

                    
                                                        
                    //Create graph
                    
                    drawing_widget = gtk_drawing_area_new ();
                    gtk_widget_set_size_request (drawing_widget, 600, 600);             
                    // gtk_grid_attach(GTK_GRID(widget),drawing_widget,0,5,6,6);    

                    //Initialize values
                    initialize_values();
                    
                    //Initialize simulation
                    update_simulation();
            
                    
            }
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
            GtkWidget* drawing_widget;

            void initialize_values(){
                for (int i=0;i<5;i++){
                    parameter_values[i]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(parameter_input_widget[i]));
                }
                
                for (int i=0;i<8;i++){
                    initial_values[i]=gtk_spin_button_get_value(GTK_SPIN_BUTTON(initial_input_widget[i]));
                }               
                
            }

            void parameter_value_changed(GtkSpinButton *spin_button,gpointer user_data, int n) {
                double val=gtk_spin_button_get_value(spin_button);
                parameter_values[n]=val;
                gtk_widget_queue_draw(drawing_widget);  
                update_simulation();            
            }   

             void initial_value_changed(GtkSpinButton *spin_button,gpointer user_data, int n) {
                double val=gtk_spin_button_get_value(spin_button);
                initial_values[n]=val;
                update_simulation();
            }   


            std::vector<double> timepoints;
            std::vector<double> datapoints;

            //look at https://developer.gnome.org/gtk3/stable/ch01s05.html
            //https://stackoverflow.com/questions/56610208/the-pointer-in-signal-connect-function-is-not-working-correct
            
            
            void update_simulation(){
                //std::cout<<"alpha:"<<_alpha<<"\n";
                double alpha=_alpha;
                double kappa=_kappa;
                double theta=_theta;
                double qq=_qq;
                double pp=_pp;  
            
                SEIRD<std::vector<double>> seird_model(alpha,kappa,theta,qq,pp);
           
                seird_model.change_step_size(_stepsize);

                std::vector<double> u0 = {_initial_susceptibles, _initial_exposed, _initial_infected,_initial_recovered,_initial_deaths};
                double t_start = _simulation_starttime;
                double t_end = _simulation_endtime;

                auto res = seird_model.run(t_start, u0, t_end);
                timepoints=std::get<0>(res);
                datapoints=std::get<1>(res);
                
                
                
            }
            
            
                        
            double numeric_input(GtkSpinButton *button,
                            gpointer       user_data)
            {
              return gtk_spin_button_get_value(button);
            }
            
        
            
            public:
            SEIRDWidget(){
                createWidget();
            }
            const std::string tab_name="Interactive";
            GtkWidget* widget;
            GtkWidget* name_widget=gtk_label_new("Interactive");
            
        };      
    
    }   
}
