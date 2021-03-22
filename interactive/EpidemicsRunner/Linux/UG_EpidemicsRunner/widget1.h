#include <string>
#include <vector>
#include <iostream>

#include <gtk/gtk.h>
#include <cairo.h>

#include "../../../../models/seird.h"
#include "../../../../models/writer.h"
#include "../../../../../ConstrainedOptimization/core/parameter_estimation.h"
#include "../../../../../ConstrainedOptimization/core/parameters.h"

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
				//widget=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
				
				//widget=gtk.Table(2,2,false);
				widget=gtk_grid_new();
				
				int v_offset1=20;
				int h_offset1=20;
				//Create alpha input
				GtkWidget* label0=gtk_label_new(param_names[0].c_str());				
				GtkAdjustment *adjustment0;
				adjustment0 = gtk_adjustment_new (2.500, 0.0, 1.0, 0.00001, 0.1, 0.0);								
				parameter_input_widget[0]=gtk_spin_button_new (adjustment0, 0.000001, 9);
				gtk_grid_attach(GTK_GRID(widget),label0,0,0,1,1);					
				gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[0],1,0,1,1);	
				g_signal_connect (GTK_SPIN_BUTTON(parameter_input_widget[0]), "value-changed",  G_CALLBACK (alpha_value_changed_callback), this);	

				
				//Create Kappa input
				GtkWidget* label1=gtk_label_new(param_names[1].c_str());				
				GtkAdjustment *adjustment1;
				adjustment1 = gtk_adjustment_new (2.500, 0.0, 1.0, 0.00001, 0.1, 0.0);								
				parameter_input_widget[1]=gtk_spin_button_new (adjustment1, 0.000001, 9);
				gtk_grid_attach(GTK_GRID(widget),label1,0,1,1,1);				
				gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[1],1,1,1,1);	
				g_signal_connect (GTK_SPIN_BUTTON(parameter_input_widget[1]), "value-changed",  G_CALLBACK (kappa_value_changed_callback), this);		
	
				
				//Create theta input
				GtkWidget* label2=gtk_label_new(param_names[2].c_str());				
				GtkAdjustment *adjustment2;
				adjustment2 = gtk_adjustment_new (2.500, 0.0, 1.0, 0.00001, 0.1, 0.0);								
				parameter_input_widget[2]=gtk_spin_button_new (adjustment2, 0.000001, 9);
				gtk_grid_attach(GTK_GRID(widget),label2,0,2,1,1);				
				gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[2],1,2,1,1);
				g_signal_connect (GTK_SPIN_BUTTON(parameter_input_widget[2]), "value-changed",  G_CALLBACK (theta_value_changed_callback), this);		
					
				//Create qq input
				GtkWidget* label3=gtk_label_new(param_names[3].c_str());				
				GtkAdjustment *adjustment3;
				adjustment3 = gtk_adjustment_new (2.500, 0.0, 1.0, 0.00001, 0.1, 0.0);								
				parameter_input_widget[3]=gtk_spin_button_new (adjustment3, 0.000001, 9);
				gtk_grid_attach(GTK_GRID(widget),label3,0,3,1,1);				
				gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[3],1,3,1,1);
				g_signal_connect (GTK_SPIN_BUTTON(parameter_input_widget[3]), "value-changed",  G_CALLBACK (qq_value_changed_callback), this);		
					
												
				//Create pp input
				GtkWidget* label4=gtk_label_new(param_names[4].c_str());				
				GtkAdjustment *adjustment4;
				adjustment4 = gtk_adjustment_new (2.500, 0.0, 1.0, 0.00001, 0.1, 0.0);								
				parameter_input_widget[4]=gtk_spin_button_new (adjustment4, 0.000001, 9);
				gtk_grid_attach(GTK_GRID(widget),label4,0,4,1,1);				
				gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[4],1,4,1,1);								
				g_signal_connect (GTK_SPIN_BUTTON(parameter_input_widget[4]), "value-changed",  G_CALLBACK (pp_value_changed_callback), this);		
					
				//Create initial values
				
				//Initial Susceptibles
				GtkWidget* label5=gtk_label_new(initial_names[0].c_str());				
				GtkAdjustment *adjustment5;
				adjustment5 = gtk_adjustment_new (100, 0.0, 1000000, 100, 0.1,0);								
				initial_input_widget[0]=gtk_spin_button_new (adjustment5, 1000, 0);
				gtk_grid_attach(GTK_GRID(widget),label5,2,0,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[0],3,0,1,1);								
				g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[0]), "value-changed",  G_CALLBACK (susceptibles_value_changed_callback), this);							


				//Initial Exposed
				GtkWidget* label6=gtk_label_new(initial_names[1].c_str());				
				GtkAdjustment *adjustment6;
				adjustment6 = gtk_adjustment_new (100, 0.0, 1000000, 100, 0.1,0);							
				initial_input_widget[1]=gtk_spin_button_new (adjustment6, 1000, 0);
				gtk_grid_attach(GTK_GRID(widget),label6,2,1,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[1],3,1,1,1);								
				g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[1]), "value-changed",  G_CALLBACK (exposed_value_changed_callback), this);		


				//Initial Infected
				GtkWidget* label7=gtk_label_new(initial_names[2].c_str());				
				GtkAdjustment *adjustment7;
				adjustment7 = gtk_adjustment_new (100, 0.0, 1000000, 100, 0.1,0);							
				initial_input_widget[2]=gtk_spin_button_new (adjustment7, 1000, 0);
				gtk_grid_attach(GTK_GRID(widget),label7,2,2,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[2],3,2,1,1);								
				g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[2]), "value-changed",  G_CALLBACK (infected_value_changed_callback), this);		

	
				//Initial Recovered
				GtkWidget* label8=gtk_label_new(initial_names[3].c_str());				
				GtkAdjustment *adjustment8;
				adjustment8 = gtk_adjustment_new (100, 0.0, 1000000, 100, 0.1,0);								
				initial_input_widget[3]=gtk_spin_button_new (adjustment8, 1000, 0);
				gtk_grid_attach(GTK_GRID(widget),label8,2,3,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[3],3,3,1,1);								
				g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[3]), "value-changed",  G_CALLBACK (recovered_value_changed_callback), this);		

	
				//Initial Deaths
				GtkWidget* label9=gtk_label_new(initial_names[4].c_str());				
				GtkAdjustment *adjustment9;
				adjustment9 = gtk_adjustment_new (100, 0.0, 1000000, 100, 0.1,0);							
				initial_input_widget[4]=gtk_spin_button_new (adjustment9, 1000, 0);
				gtk_grid_attach(GTK_GRID(widget),label9,2,4,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[4],3,4,1,1);								
				g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[4]), "value-changed",  G_CALLBACK (deaths_value_changed_callback), this);		


				//t0
				GtkWidget* label10=gtk_label_new(initial_names[5].c_str());				
				GtkAdjustment *adjustment10;
				adjustment10 = gtk_adjustment_new (0, -100000, 1000000, 1, 0.1,0);						
				initial_input_widget[5]=gtk_spin_button_new (adjustment10, 0.1, 2);
				gtk_grid_attach(GTK_GRID(widget),label10,4,0,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[5],5,0,1,1);								
				g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[5]), "value-changed",  G_CALLBACK (simstarttime_value_changed_callback), this);		

				//tend
				GtkWidget* label11=gtk_label_new(initial_names[6].c_str());				
				GtkAdjustment *adjustment11;
				adjustment11 = gtk_adjustment_new (42, -10000, 1000000, 1, 0.1, 0.0);								
				initial_input_widget[6]=gtk_spin_button_new (adjustment11, 0.1, 2);
				gtk_grid_attach(GTK_GRID(widget),label11,4,1,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[6],5,1,1,1);	
				g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[6]), "value-changed",  G_CALLBACK (simendtime_value_changed_callback), this);		
		
											
				//stepsize h
				GtkWidget* label12=gtk_label_new(initial_names[7].c_str());				
				GtkAdjustment *adjustment12;
				adjustment12 = gtk_adjustment_new (2.500, 0.0, 1.0, 0.00001, 0.1, 0.0);								
				initial_input_widget[7]=gtk_spin_button_new (adjustment12, 0.000001, 9);
				gtk_grid_attach(GTK_GRID(widget),label12,4,2,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[7],5,2,1,1);	
				g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[7]), "value-changed",  G_CALLBACK (h_value_changed_callback), this);		
	
				
													
				//Create graph
				
				drawing_widget = gtk_drawing_area_new ();
				gtk_widget_set_size_request (drawing_widget, 600, 600);				
				gtk_grid_attach(GTK_GRID(widget),drawing_widget,0,5,6,6);	
				g_signal_connect (G_OBJECT (drawing_widget), "draw",  G_CALLBACK (draw_callback), this);

				//Initialize simulation
				update_simulation();
		
				
			}
public:		
			double parameter_values[5]={0};
			double initial_values[8]={0};
			
			double& alpha=parameter_values[0];
			double& kappa=parameter_values[1];
			double& theta=parameter_values[2];
			double& qq=parameter_values[3];
			double& pp=parameter_values[4];
						
						
			std::vector<std::string> param_names={"alpha","kappa","theta","qq","pp"};	
			std::vector<std::string> initial_names={"Initial Susceptibles","Initial Exposed","Initial Infected","Initial Recovered","Initial Deaths","Simulation Starttime","Simulation Endtime","RK4 Stepsize h"};				
			std::vector<GtkWidget*> parameter_input_widget=std::vector<GtkWidget*>(5);
			std::vector<GtkWidget*> initial_input_widget=std::vector<GtkWidget*>(8);
			GtkWidget* drawing_widget;
			void printstuff(SEIRDWidget* obj){
				std::cout<<obj->a<<"\n";
			}
			int a=25;
			void parameter_value_changed(GtkSpinButton *spin_button,GtkScrollType  scroll, gpointer user_data, int n) {
				//std::cout<<n<<"\n";
				//std::cout<<n<<"\n";
				double val=gtk_spin_button_get_value(spin_button);
				//parameter_values[n]=val;
				//  g_print("clicked\n");
				//  std::cout<<"hey\n";
			}	


			void initial_value_changed(GtkSpinButton *spin_button,GtkScrollType  scroll, gpointer user_data, int n) {
				double val=gtk_spin_button_get_value(spin_button);
				//initial_values[n]=val;
				std::cout<<n<<"\n";
				//  g_print("clicked\n");
				//  std::cout<<"hey\n";
			}	
			static void alpha_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
			//	alpha=gtk_spin_button_get_value(button);
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					std::cout<<_this->a<<"\n"<<"danach\n";
					// _this->parameter_values[0]=9;
					 _this->parameter_value_changed(button, scroll,data,0);
			
			   // reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>>(data)->on_button_clicked(button);
			}			
			static void kappa_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					 _this->parameter_value_changed(button, scroll,data,1);
			}			
			static void theta_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					 _this->parameter_value_changed(button, scroll,data,2);
			}	
			
			static void qq_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					 _this->parameter_value_changed(button, scroll,data,3);
			}						
			
			static void pp_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					 _this->parameter_value_changed(button, scroll,data,4);
			}	
			
			static void susceptibles_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					 _this->initial_value_changed(button, scroll,data,0);
			}		
			static void exposed_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					 _this->initial_value_changed(button, scroll,data,1);
			}
			
			static void infected_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					 _this->initial_value_changed(button, scroll,data,2);
			}
			
			static void recovered_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					 _this->initial_value_changed(button, scroll,data,3);
			}
			
			static void deaths_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					 _this->initial_value_changed(button, scroll,data,4);
			}			
			static void simstarttime_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					 _this->initial_value_changed(button, scroll,data,5);
			}
			
			static void simendtime_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					 _this->initial_value_changed(button, scroll,data,6);
			}			

		
			static void h_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					 _this->initial_value_changed(button, scroll,data,7);
			}
			
			std::vector<double> timepoints;
			std::vector<double> datapoints;
			/*
			void update_plot(){
				std::cout<<parameter_input_widget.size()<<"\n";
				std::vector<double> times={0,1,2,3};
				std::vector<double> datapoints={3,1,-3,9};	
				int selected_dim=0;				
				
				util::plot_values(_widget,cr,times,datapoints,selected_dim);
			}
			*/
			//look at https://developer.gnome.org/gtk3/stable/ch01s05.html
			//https://stackoverflow.com/questions/56610208/the-pointer-in-signal-connect-function-is-not-working-correct
			
			
			void update_simulation(){
				double alpha=0.000003;
				double kappa=0.1;
				double theta=0.01;
				double qq=1;
				double pp=1;	
				

				SEIRD<std::vector<double>> seird_model(alpha, kappa, theta,qq,pp);
		   
			//	seird_model.change_step_size(h);

				std::vector<double> u0 = {750000,100,0,0,0 };
				double t_start = 0;
				double t_end = 42;

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
