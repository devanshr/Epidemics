#include <gtk/gtk.h>
#include <iostream>
#include <vector>
#include "../../../../../models/seird.h"
#include "../../../../../models/writer.h"
//#include "../../../../../ConstrainedOptimization/core/parameter_estimation.h"
//#include "../../../../../ConstrainedOptimization/core/parameters.h"

#include "../utility.h"



namespace ug{
	namespace epi{
		
		class SEIRDWidget{
		
			private:
			GtkBuilder *builder;
			
			//These variables store all the data values and parameter settings
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
			
			std::vector<double> timepoints; //time values of simulation
			std::vector<double> datapoints; //data values of simulation
			
			//app_widgets glade_widgets=g_slice_new(app_widgets); //represents the widgets in the seird.glade file

		
			void initialize_widget(){
				//gtk_init(&argc, &argv);

				builder = gtk_builder_new_from_file("glades/seird.glade");

				main_widget = GTK_WIDGET(gtk_builder_get_object(builder,"grid_main_seird"));
				//main_widget=gtk_grid_new();
				app_widgets* ptr=&glade_widgets;
				ptr->seird_object=this;
				gtk_builder_connect_signals(builder, ptr);
			}
			
			void initialize_values(){
				glade_widgets.w_spin_alpha = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_alpha"));
				glade_widgets.w_spin_kappa = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_kappa"));
				glade_widgets.w_spin_theta = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_theta"));
				glade_widgets.w_spin_qq = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_qq"));
				glade_widgets.w_spin_pp = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pp"));

				glade_widgets.w_check_alpha = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_alpha"));
				glade_widgets.w_check_kappa = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_kappa"));
				glade_widgets.w_check_theta = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_theta"));
				glade_widgets.w_check_qq = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_qq"));
				glade_widgets.w_check_pp = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_pp"));

				glade_widgets.w_spin_initial_susceptibles = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_susceptibles"));
				glade_widgets.w_spin_initial_exposed = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_exposed"));
				glade_widgets.w_spin_initial_infected = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_infected"));
				glade_widgets.w_spin_initial_recovered = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_recovered"));
				glade_widgets.w_spin_initial_deaths = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_initial_deaths"));
				glade_widgets.w_spin_ode_stepsize = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_stepsize"));
				glade_widgets.w_spin_t_start = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_t_start"));
				glade_widgets.w_spin_t_end = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_t_end"));

				glade_widgets.w_spin_lower_bound_alpha = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_lower_bound_alpha"));
				glade_widgets.w_spin_upper_bound_alpha = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_upper_bound_alpha"));
				glade_widgets.w_spin_lower_bound_kappa = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_lower_bound_kappa"));
				glade_widgets.w_spin_upper_bound_kappa = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_upper_bound_kappa"));
				glade_widgets.w_spin_lower_bound_theta = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_lower_bound_theta"));
				glade_widgets.w_spin_upper_bound_theta = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_upper_bound_theta"));
				glade_widgets.w_spin_lower_bound_qq = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_lower_bound_qq"));
				glade_widgets.w_spin_upper_bound_qq = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_upper_bound_qq"));
				glade_widgets.w_spin_lower_bound_pp = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_lower_bound_pp"));
				glade_widgets.w_spin_upper_bound_pp = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_upper_bound_pp"));

				parameter_values[0]=gtk_spin_button_get_value(glade_widgets.w_spin_alpha);
				parameter_values[1]=gtk_spin_button_get_value(glade_widgets.w_spin_kappa);
				parameter_values[2]=gtk_spin_button_get_value(glade_widgets.w_spin_theta);
				parameter_values[3]=gtk_spin_button_get_value(glade_widgets.w_spin_qq);
				parameter_values[4]=gtk_spin_button_get_value(glade_widgets.w_spin_pp);
				
				initial_values[0]=gtk_spin_button_get_value(glade_widgets.w_spin_initial_susceptibles);
				initial_values[1]=gtk_spin_button_get_value(glade_widgets.w_spin_initial_exposed);
				initial_values[2]=gtk_spin_button_get_value(glade_widgets.w_spin_initial_infected);
				initial_values[3]=gtk_spin_button_get_value(glade_widgets.w_spin_initial_recovered);
				initial_values[4]=gtk_spin_button_get_value(glade_widgets.w_spin_initial_deaths);
				initial_values[5]=gtk_spin_button_get_value(glade_widgets.w_spin_t_start);
				initial_values[6]=gtk_spin_button_get_value(glade_widgets.w_spin_t_end);
				initial_values[7]=gtk_spin_button_get_value(glade_widgets.w_spin_ode_stepsize);

				update_simulation();			
				
			}
			
		void update_simulation()
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

			auto res = seird_model.run_linear_implicit(t_start, u0, t_end);
			timepoints=std::get<0>(res);
			datapoints=std::get<1>(res);

			//ug::epi::write_data("/home/devanshr/Desktop/", "_test.txt", timepoints, datapoints,seird_model.names);

		}
			
			public:
			
			SEIRDWidget(){
				initialize_widget();
				initialize_values();
				std::cout<<"Initialization done\n";
				std::cout<<"Datapoints size konst:"<<this<<"\n";
			}
			
			~SEIRDWidget(){
				 //g_slice_free(app_widgets, glade_widgets);
			}
			
			GtkWidget* get_widget() const{
				return main_widget;
				
			}
			GtkWidget* get_name() const{
				return name_widget;
			}
			GtkWidget* main_widget; //main widget
			GtkWidget* name_widget=gtk_label_new("SEIRD");
			
		/* This struct is given to a glade builder to automatically connect signals.
		 The members need to have the same name as the "name" property in the glade files*/
			struct app_widgets{
				GtkWidget *window_bounds;
				GtkSpinButton *w_spin_alpha;
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
				SEIRDWidget* seird_object;
			};	
			
			//These are helper functions for the event handlers
			void parameter_value_changed(double val, int n) {
				parameter_values[n]=val;
				update_simulation();
				gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing_seird")));				
			}	

			void initial_value_changed(double val, int n) {
				initial_values[n]=val;
				update_simulation();
				gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing_seird")));	
			}				
						
			
			app_widgets glade_widgets;		
			//Evenhandler functions

			static gboolean on_drawing_seird_draw (GtkWidget *_widget,cairo_t* cr, SEIRDWidget* _this)
			{
				std::cout<<"Redrawing SEIRD graph\n";
				if (_this->datapoints.size()!=0){
					int dim_data=(_this->datapoints.size())/(_this->timepoints.size());			
					for (int i=0;i<dim_data;i++){
						util::plot_values(_widget,cr,_this->timepoints,_this->datapoints,i);
					}
					
					util::plot_axis(_widget,cr,_this->timepoints,_this->datapoints);	
				}			
				return 1;			
			}			
									
		};
		
		
		
		/*Here we create C bindings to our class callback functions		
		These are the bindings that will be called by Glade.
		*/
		
		//Draw the seird canvas
		extern "C" G_MODULE_EXPORT void on_drawing_seird_draw(GtkWidget *_widget,cairo_t* cr, gpointer* data){
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
		
			glade_widgets->seird_object->on_drawing_seird_draw(_widget,cr,glade_widgets->seird_object);
		}		
		
		extern "C" G_MODULE_EXPORT void on_spin_alpha_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_object->parameter_value_changed(val,0);		
			//printf("alpha changed \n");

		}    
		extern "C" G_MODULE_EXPORT void on_spin_kappa_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_object->parameter_value_changed(val,1);		
			//printf("kappa changed \n");

		}    
		
		extern "C" G_MODULE_EXPORT void on_spin_theta_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_object->parameter_value_changed(val,3);		
			//printf("theta changed \n");

		}    
		
		extern "C" G_MODULE_EXPORT void on_spin_qq_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_object->parameter_value_changed(val,4);		
			//printf("qq changed \n");

		}  
  
		
		extern "C" G_MODULE_EXPORT void on_spin_pp_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_object->parameter_value_changed(val,4);		
			//printf("pp changed \n");

		}  
		
		extern "C" G_MODULE_EXPORT void on_spin_initial_susceptibles_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_object->initial_value_changed(val,0);		
	

		}     
		extern "C" G_MODULE_EXPORT void on_spin_initial_exposed_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_object->initial_value_changed(val,1);		

		}   
		
		extern "C" G_MODULE_EXPORT void on_spin_initial_infected_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_object->initial_value_changed(val,2);		

		}   
		extern "C" G_MODULE_EXPORT void on_spin_initial_recovered_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_object->initial_value_changed(val,3);		

		}   
		
		extern "C" G_MODULE_EXPORT void on_spin_initial_deaths_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_object->initial_value_changed(val,4);		

		}   
		
		extern "C" G_MODULE_EXPORT void on_spin_t_start_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_object->initial_value_changed(val,5);		

		}   
		
		extern "C" G_MODULE_EXPORT void on_spin_t_end_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_object->initial_value_changed(val,6);		

		}   
		
		extern "C" G_MODULE_EXPORT void on_spin_stepsize_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_object->initial_value_changed(val,7);		

		}   
		
		
	}
}
