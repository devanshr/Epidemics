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
            private:
            
            void createWidget(){

                GtkBuilder      *builder; 
                builder = gtk_builder_new();
                gtk_builder_add_from_file (builder, "Glades/SEIRD_OPTIMIZED.glade", NULL);

                widget = GTK_WIDGET(gtk_builder_get_object(builder, "grid_main"));



                // Create graph
                
                drawing_widget = GTK_WIDGET(gtk_builder_get_object(builder, "drawing"));

                gtk_widget_set_size_request (drawing_widget, 600, 600);             
                // gtk_grid_attach(GTK_GRID(widget),drawing_widget,0,5,6,6);   
                g_signal_connect (G_OBJECT (drawing_widget), "draw",  G_CALLBACK (draw_callback), this);

                //Initialize values
                initialize_values();
                
                //Initialize simulation
                update_simulation();
        
                
            }
public:     
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
 
			extern "C" G_MODULE_EXPORT void alpha_value_changed_callback(GtkSpinButton* button, gpointer* data) {
							 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
							 _this->parameter_value_changed(button,data,0);
			}
            static void kappa_value_changed_callback(GtkSpinButton* button, gpointer* data) {
                     SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
                     _this->parameter_value_changed(button, data,1);
            }           
            static void theta_value_changed_callback(GtkSpinButton* button, gpointer* data) {
                     SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
                     _this->parameter_value_changed(button, data,2);
            }   
            
            static void qq_value_changed_callback(GtkSpinButton* button, gpointer* data) {
                     SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
                     _this->parameter_value_changed(button, data,3);
            }                       
            
            static void pp_value_changed_callback(GtkSpinButton* button, gpointer* data) {
                     SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
                     _this->parameter_value_changed(button, data,4);
            }   
            
            static void susceptibles_value_changed_callback(GtkSpinButton* button, gpointer* data) {
                     SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
                     _this->initial_value_changed(button, data,0);
            }       
            static void exposed_value_changed_callback(GtkSpinButton* button, gpointer* data) {
                     SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
                     _this->initial_value_changed(button, data,1);
            }
            
            static void infected_value_changed_callback(GtkSpinButton* button, gpointer* data) {
                     SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
                     _this->initial_value_changed(button, data,2);
            }
            
            static void recovered_value_changed_callback(GtkSpinButton* button, gpointer* data) {
                     SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
                     _this->initial_value_changed(button, data,3);
            }
            
            static void deaths_value_changed_callback(GtkSpinButton* button, gpointer* data) {
                     SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
                     _this->initial_value_changed(button, data,4);
            }           
            static void simstarttime_value_changed_callback(GtkSpinButton* button, gpointer* data) {
                     SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
                     _this->initial_value_changed(button, data,5);
            }
            
            static void simendtime_value_changed_callback(GtkSpinButton* button, gpointer* data) {
                     SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
                     _this->initial_value_changed(button, data,6);
            }           

        
            static void h_value_changed_callback(GtkSpinButton* button, gpointer* data) {
                     SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
                     _this->initial_value_changed(button, data,7);
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
            
            static gboolean draw_callback (GtkWidget *_widget,cairo_t* cr, gpointer* data)
            {
    
                
                SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);  
                
                if (_this->datapoints.size()!=0){
                    int dim_data=(_this->datapoints.size())/(_this->timepoints.size());
                    int selected_dim=0;             
                    for (int i=0;i<dim_data;i++){
                        util::plot_values(_widget,cr,_this->timepoints,_this->datapoints,i);
                    }
                    
                    util::plot_axis(_widget,cr,_this->timepoints,_this->datapoints);    
                }           
                return 1;
                
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
