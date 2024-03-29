#pragma once 

#include <gtk/gtk.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime> // experimental, may not work on MAC/Win?
#include "../../../models/seird_pde.h"
#include "../../../models/writer.h"
#include "initial_value_editor_widget.h"
#include "../utility.h"
#include "../../../../ConstrainedOptimization/core/parameter_estimation.h"
#include "../../../../ConstrainedOptimization/core/parameters.h"


namespace ug{
	namespace epi{
		
class SEIRDPDE_EDITORWidget;

	extern "C" G_MODULE_EXPORT void on_drawing_squared_error_pde_editor_draw(GtkWidget *_widget,cairo_t* cr, SEIRDPDE_EDITORWidget* seird_pde_object);
		
		
		class SEIRDPDE_EDITORWidget{
		
			private:
			GtkBuilder *builder;
			
			//These variables store all the data values and parameter settings
			double parameter_values[6]={0};
			double initial_values[14]={0};
			double upper_bound_values[5] = {0};
			double lower_bound_values[5] = {0};
			
			double& _alpha=parameter_values[0];
			double& _kappa=parameter_values[1];
			double& _theta=parameter_values[2];
			double& _qq=parameter_values[3];
			double& _pp=parameter_values[4];
			double& _diffusion=parameter_values[5];


			std::vector<double> u0; //vector with the initial conditions. will be set through the editor 			
			double& _simulation_starttime=initial_values[10];
			double& _simulation_endtime=initial_values[11];
			double& _stepsize_time=initial_values[12];
			double& _stepsize_spatial=initial_values[13];
			
			std::vector<std::string> param_names={"alpha","kappa","theta","qq","pp","diffusion"};
			std::vector<std::string> initial_names={"Simulation Endtime","Solver Stepsize h"};				
			
			std::vector<double> timepoints; //time values of simulation
			std::vector<double> datapoints; //data values of simulation
			
			int pso_values[3];
			int& _pso_max_iter = pso_values[0];
			int& _pso_no_particles = pso_values[1];
			int& _pso_no_groups = pso_values[2];
			double newton_convergence_threshold;
			
			std::vector<double> sq_error; //vector of squared errors

			//app_widgets glade_widgets=g_slice_new(app_widgets); //represents the widgets in the seird.glade file

		
			void initialize_widget(){
				//gtk_init(&argc, &argv);

				builder = gtk_builder_new_from_file("glades/seird_pde_editor.glade");

				main_widget = GTK_WIDGET(gtk_builder_get_object(builder,"grid_main_pde_editor"));
				//main_widget=gtk_grid_new();
				app_widgets* ptr=&glade_widgets;
				ptr->seird_pde_object=this;
				gtk_builder_connect_signals(builder, ptr);
			}
			
			void initialize_values(){
				glade_widgets.w_spin_alpha = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_alpha_pde_editor"));
				glade_widgets.w_spin_kappa = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_kappa_pde_editor"));
				glade_widgets.w_spin_theta = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_theta_pde_editor"));
				glade_widgets.w_spin_qq = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_qq_pde_editor"));
				glade_widgets.w_spin_pp = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pp_pde_editor"));
				glade_widgets.w_spin_diffusion = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_diffusion_pde_editor"));

				glade_widgets.w_check_alpha = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_alpha_pde_editor"));
				glade_widgets.w_check_kappa = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_kappa_pde_editor"));
				glade_widgets.w_check_theta = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_theta_pde_editor"));
				glade_widgets.w_check_qq = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_qq_pde_editor"));
				glade_widgets.w_check_pp = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_pp_pde_editor"));
				glade_widgets.w_check_diffusion = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"check_diffusion_pde_editor"));
		
				// new	
				glade_widgets.w_spin_stepsize_time = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_stepsize_time_pde_editor"));
				glade_widgets.w_spin_stepsize_spatial = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_stepsize_spatial_pde_editor"));
				glade_widgets.w_spin_t_start = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_t_start_pde_editor"));
				glade_widgets.w_spin_t_end = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_t_end_pde_editor"));
				glade_widgets.w_spin_time= GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_time_pde_editor"));

				glade_widgets.w_label_max= GTK_LABEL(gtk_builder_get_object(builder,"label_seird_pde_editor_max"));
				glade_widgets.w_label_min= GTK_LABEL(gtk_builder_get_object(builder,"label_seird_pde_editor_min"));

				glade_widgets.w_spin_pde_editor_lower_bound_alpha = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pde_editor_lower_bound_alpha"));
				glade_widgets.w_spin_pde_editor_upper_bound_alpha = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pde_editor_upper_bound_alpha"));
				glade_widgets.w_spin_pde_editor_lower_bound_kappa = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pde_editor_lower_bound_kappa"));
				glade_widgets.w_spin_pde_editor_upper_bound_kappa = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pde_editor_upper_bound_kappa"));
				glade_widgets.w_spin_pde_editor_lower_bound_theta = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pde_editor_lower_bound_theta"));
				glade_widgets.w_spin_pde_editor_upper_bound_theta = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pde_editor_upper_bound_theta"));
				glade_widgets.w_spin_pde_editor_lower_bound_qq = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pde_editor_lower_bound_qq"));
				glade_widgets.w_spin_pde_editor_upper_bound_qq = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pde_editor_upper_bound_qq"));
				glade_widgets.w_spin_pde_editor_lower_bound_pp = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pde_editor_lower_bound_pp"));
				glade_widgets.w_spin_pde_editor_upper_bound_pp = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_pde_editor_upper_bound_pp"));

				glade_widgets.w_spin_pso_iterations = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_iterations_pde_editor"));
				glade_widgets.w_spin_pso_no_particles = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_particles_pde_editor"));
				glade_widgets.w_spin_pso_no_groups = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,"spin_groups_pde_editor"));

				parameter_values[0]=gtk_spin_button_get_value(glade_widgets.w_spin_alpha);
				parameter_values[1]=gtk_spin_button_get_value(glade_widgets.w_spin_kappa);
				parameter_values[2]=gtk_spin_button_get_value(glade_widgets.w_spin_theta);
				parameter_values[3]=gtk_spin_button_get_value(glade_widgets.w_spin_qq);
				parameter_values[4]=gtk_spin_button_get_value(glade_widgets.w_spin_pp);
				parameter_values[5]=gtk_spin_button_get_value(glade_widgets.w_spin_diffusion);
				
				initial_values[10]=gtk_spin_button_get_value(glade_widgets.w_spin_t_start);
				initial_values[11]=gtk_spin_button_get_value(glade_widgets.w_spin_t_end);
				initial_values[12]=gtk_spin_button_get_value(glade_widgets.w_spin_stepsize_time);
				initial_values[13]=gtk_spin_button_get_value(glade_widgets.w_spin_stepsize_spatial);
				
				pso_values[0]=gtk_spin_button_get_value(glade_widgets.w_spin_pso_iterations); 
				pso_values[1]=gtk_spin_button_get_value(glade_widgets.w_spin_pso_no_particles);
				pso_values[2]=gtk_spin_button_get_value(glade_widgets.w_spin_pso_no_groups);
				
				
				glade_widgets.frame_min_max = GTK_FRAME(gtk_builder_get_object(builder,"frame_min_max_pde_editor"));

                glade_widgets.frame_exposed = GTK_FRAME(gtk_builder_get_object(builder,"frame_susceptibles_pde_editor"));
                glade_widgets.frame_susceptibles_drawing_area_pde = GTK_DRAWING_AREA(gtk_builder_get_object(builder,"frame_susceptibles_drawing_area_pde_editor"));


                glade_widgets.frame_exposed = GTK_FRAME(gtk_builder_get_object(builder,"frame_exposed_pde_editor"));
                glade_widgets.frame_exposed_drawing_area_pde = GTK_DRAWING_AREA(gtk_builder_get_object(builder,"frame_exposed_drawing_area_pde_editor"));
                
                glade_widgets.frame_infected = GTK_FRAME(gtk_builder_get_object(builder,"frame_infected_pde_editor"));
                glade_widgets.frame_infected_drawing_area_pde = GTK_DRAWING_AREA(gtk_builder_get_object(builder,"frame_infected_drawing_area_pde_editor"));
                
                glade_widgets.frame_recovered = GTK_FRAME(gtk_builder_get_object(builder,"frame_recovered_pde_editor"));
                glade_widgets.frame_recovered_drawing_area_pde = GTK_DRAWING_AREA(gtk_builder_get_object(builder,"frame_recovered_drawing_area_pde_editor"));
                
                glade_widgets.frame_deceased = GTK_FRAME(gtk_builder_get_object(builder,"frame_deceased_pde_editor"));
                glade_widgets.frame_deceased_drawing_area_pde = GTK_DRAWING_AREA(gtk_builder_get_object(builder,"frame_deceased_drawing_area_pde_editor"));
                glade_widgets.drawing_heatmap_big = GTK_DRAWING_AREA(gtk_builder_get_object(builder,"drawing_heatmap_big_pde_editor"));
                
    			//glade_widgets.legend_pde = GTK_DRAWING_AREA(gtk_builder_get_object(builder,"legend_pde"));
				
				//update_simulation();			
				
			}

	
			public:
			
			std::string user_selected_optimization_path; //path used in optimizations
			int zoomed;

			
			SEIRDPDE_EDITORWidget(){
				initialize_widget();
				initialize_values();
				//std::cout<<"Initialization done\n";
			//std::cout<<"PtrB:"<<this<<"\n";
			}
			
			~SEIRDPDE_EDITORWidget(){
				 //g_slice_free(app_widgets, glade_widgets);
			}
			
			GtkWidget* get_widget() const{
				return main_widget;
			}
			GtkWidget* get_name() const{
				return name_widget;
			}
			GtkWidget* main_widget; //main widget
			GtkWidget* name_widget=gtk_label_new("SEIRD PDE Editor");
			
			cairo_surface_t *image_legend; //can be removed
			cairo_surface_t* heatmap_images[5]; //handles to the heatmap images displayed in the gui
			cairo_surface_t *legend_images[1];
		/* This struct is given to a glade builder to automatically connect signals.
		 The members need to have the same name as the "name" property in the glade files*/
			struct app_widgets{
                GtkWidget *window_bounds;
                GtkSpinButton *w_spin_alpha;
                GtkSpinButton *w_spin_kappa;
                GtkSpinButton *w_spin_theta;
                GtkSpinButton *w_spin_qq;
                GtkSpinButton *w_spin_pp;
                GtkSpinButton *w_spin_diffusion;
                GtkSpinButton *w_spin_t_start;
                GtkSpinButton *w_spin_t_end;
                GtkSpinButton *w_spin_stepsize_time;
                GtkSpinButton *w_spin_stepsize_spatial;
                GtkToggleButton *w_check_alpha;
                GtkToggleButton *w_check_kappa;
                GtkToggleButton *w_check_theta;
                GtkToggleButton *w_check_qq;
                GtkToggleButton *w_check_pp;
                GtkToggleButton *w_check_diffusion;
                GtkSpinButton *w_spin_pde_editor_lower_bound_alpha;
                GtkSpinButton *w_spin_pde_editor_upper_bound_alpha;
                GtkSpinButton *w_spin_pde_editor_lower_bound_kappa;
                GtkSpinButton *w_spin_pde_editor_upper_bound_kappa;
                GtkSpinButton *w_spin_pde_editor_lower_bound_theta;
                GtkSpinButton *w_spin_pde_editor_upper_bound_theta;
                GtkSpinButton *w_spin_pde_editor_lower_bound_qq;
                GtkSpinButton *w_spin_pde_editor_upper_bound_qq;
                GtkSpinButton *w_spin_pde_editor_lower_bound_pp;
                GtkSpinButton *w_spin_pde_editor_upper_bound_pp;
                GtkSpinButton *w_spin_pso_iterations;
                GtkSpinButton *w_spin_pso_no_particles;
                GtkSpinButton *w_spin_pso_no_groups;
                GtkSpinButton *w_spin_time;
                GtkLabel *w_label_max;
                GtkLabel *w_label_min;
                GtkFrame *frame_susceptibles;
                GtkDrawingArea *frame_susceptibles_drawing_area_pde;
                GtkFrame *frame_infected;
                GtkDrawingArea *frame_infected_drawing_area_pde;
                GtkFrame *frame_deceased;
                GtkDrawingArea *frame_deceased_drawing_area_pde;
                GtkFrame *frame_recovered;
                GtkDrawingArea *frame_recovered_drawing_area_pde;
                GtkFrame *frame_exposed;
                GtkDrawingArea *frame_exposed_drawing_area_pde;
                GtkFrame *frame_min_max;
                GtkDrawingArea *legend_pde; 
                GtkDrawingArea *drawing_heatmap_big;
                
                
				SEIRDPDE_EDITORWidget* seird_pde_object;
			};	
			
			//These are helper functions for the event handlers
			void parameter_value_changed(double val, int n) {
				parameter_values[n]=val;
				//update_simulation();
				//gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing_seird")));				
			}	

			void initial_value_changed(double val, int n) {
				initial_values[n]=val;
				//update_simulation();
				//gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing_seird")));	
			}				
				
			void upper_bound_value_changed(double val, int n)
			{
				upper_bound_values[n]=val;
			} 
			
			void lower_bound_value_changed(double val, int n)
			{
				lower_bound_values[n]=val;
			}     		
			
			static void update_simulation(SEIRDPDE_EDITORWidget* widget)
			{

				printf("Update Simulation ");
				double alpha=widget->_alpha;
				double kappa=widget->_kappa;
				double theta=widget->_theta;
				double qq=widget->_qq;
				double pp=widget->_pp;  
				double diffusion = widget->_diffusion;
				
				double t_start =widget-> _simulation_starttime;
				double t_end = widget->_simulation_endtime;

				ug::epi::SEIRD_PDE<std::vector<double>,ug::epi::seird::Geometry::Plane> seird_model(alpha, kappa, theta, pp,qq,diffusion);

				seird_model.change_step_size_time(widget->_stepsize_time);	
				seird_model.change_step_size_spatial(widget->_stepsize_spatial);
				
			
				std::string filename = "output";

				if (widget->user_selected_optimization_path.size()==0) {
					std::cout<<"No data dir";	
					//return false;
				}
				else {
					if(widget->user_selected_u0_path.empty()==false){
						widget->get_u0_from_image(widget);
						seird_model.set_store_to_file(true,widget->user_selected_optimization_path, filename);

						//seird_model.run_linear_implicit(t_start, widget->u0, t_end);
						seird_model.run(t_start, widget->u0, t_end);
						widget->set_u0(std::vector<double>());
					}
					else{
						std::cout<<"No initial data u0\n";
					}

				}
			

			}
			
			
			static void image_to_grid(int index_image_i, int index_image_j, int image_width, int image_height, int grid_width, int grid_height, int& i_g, int& j_g) {
				float ratio_i = index_image_i / (image_width - 1.0);
				float ratio_j = index_image_j / (image_height - 1.0);

				i_g = ratio_i * (grid_width - 1);
				j_g = ratio_j * (grid_height - 1);
			}

			static void determine_color(double val, double min_val, double max_val, int& r, int& g, int& b) {
				float ratio = (val - min_val) / (max_val - min_val);
				//std::cout<<"val:"<<val-min_val<<"\n";
				int start_r = 0;
				int start_g = 0;
				int start_b = 0;

				r = start_r + (255 - start_r) * ratio;
				g = start_g + (255 - start_g) * ratio;
				b = start_b + (255 - start_b) * ratio;
			}


			
			static void plot_heatmaps(SEIRDPDE_EDITORWidget* widget,std::string filenum) {
				double t_start =widget-> _simulation_starttime;
				double t_end = widget->_simulation_endtime;
				double stepsize_spatial = widget->_stepsize_spatial;
				
				//std::cout<< "\nInPlot Heatmaps\n";
				int img_x = 200;
				int img_y = 200;
				double dimX = 1.0;
				double dimY = 1.0;
				size_t grid_x = std::ceil(dimX / stepsize_spatial) + 1;
				size_t grid_y = std::ceil(dimY / stepsize_spatial) + 1;

				std::string delimiter = "\t";
				int gridx = (int)grid_x;

				widget->datapoints = std::vector<double>();
				
				if (widget->user_selected_optimization_path.size() == 0) {
					//MessageBox::Show(L"Please specify the directory for Output generation");
					std::cout<<"No dir\n";
				}
				else {
					co::ErrorCode err;					
					std::string path = widget->user_selected_optimization_path + filenum;
					err = co::utility::parse_csv(path, widget->datapoints, delimiter, &gridx);
				
					if (err == co::ErrorCode::ParseError)
					{std::cout<<" Parse Error - Could not locate file";
					}

					int offset = (widget->datapoints).size() / 5;

					double min_val = *std::min_element(widget->datapoints.begin(), widget->datapoints.end());
					double max_val = *std::max_element(widget->datapoints.begin(), widget->datapoints.end());

				
					int stride=cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32,200);
					guint8* imgdata=new guint8[img_y*stride];
					
					//Set everything full
					  for (int i=0;i<img_y*stride;i++){
						  
							imgdata[i]=126;
					 }
					 //std::cout<<"Filled Image\n";
				widget->image_legend=cairo_image_surface_create_for_data(imgdata,CAIRO_FORMAT_ARGB32,img_x,img_y,stride);
				gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(widget->builder,"frame_exposed_drawing_area_pde")));
				//gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(widget->builder,"legend_pde")));
				
				}
			}
			
		static bool load_datapoints(SEIRDPDE_EDITORWidget::app_widgets* glade_widgets, SEIRDPDE_EDITORWidget* seird_pde_object,std::string filenum){
			seird_pde_object->datapoints=std::vector<double>();
			double dimX = 1.0;
			double dimY = 1.0;
			int gridx = std::ceil(dimX / seird_pde_object->_stepsize_spatial) + 1;		
			std::string path = seird_pde_object->user_selected_optimization_path + "/output"+filenum+".txt";
			auto err = co::utility::parse_csv(path, seird_pde_object->datapoints, "/t", &gridx);
			if (err==co::ErrorCode::NoError){
				double min_val = *std::min_element(seird_pde_object->datapoints.begin(), seird_pde_object->datapoints.end());
				double max_val = *std::max_element(seird_pde_object->datapoints.begin(), seird_pde_object->datapoints.end());
				gtk_label_set_text(glade_widgets->w_label_min, std::to_string(min_val).c_str());	
				gtk_label_set_text(glade_widgets->w_label_max, std::to_string(max_val).c_str());	
				
				return true;
			}
			else
			{
				return false;
			}
		}
		
		static void update_time_spin(SEIRDPDE_EDITORWidget::app_widgets* glade_widgets){
			
				int maxrange=(glade_widgets->seird_pde_object->_simulation_endtime-glade_widgets->seird_pde_object->_simulation_starttime)/glade_widgets->seird_pde_object->_stepsize_time;
				gtk_spin_button_set_range(glade_widgets->w_spin_time,0,maxrange);
		}
		
			
        static void generate_heatmap(SEIRDPDE_EDITORWidget* widget,int mapindex, bool big=false) {
                double t_start =widget-> _simulation_starttime;
                double t_end = widget->_simulation_endtime;
                double stepsize_spatial = widget->_stepsize_spatial;
                int img_x;
                int img_y;
                if (big ==  true)
                {
                    img_x = 500;
                    img_y = 500;
                }
                else
                {
                    img_x = 200;
                    img_y = 200;
                }

                double dimX = 1.0;
                double dimY = 1.0;
                size_t grid_x = std::ceil(dimX / stepsize_spatial) + 1;
                size_t grid_y = std::ceil(dimY / stepsize_spatial) + 1;

                int gridx = (int)grid_x;

                int stride=cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32,img_x);
                guint8* imgdata=new guint8[img_y*stride];
                    
                double min_val = *std::min_element(widget->datapoints.begin(), widget->datapoints.end());
                double max_val = *std::max_element(widget->datapoints.begin(), widget->datapoints.end());
                int offset = (widget->datapoints).size() / 5;

                        for (int i = 0; i < img_y; i++) {
                            for (int j = 0; j < img_x; j++) {
                                int i_g;
                                int j_g;
                                widget->image_to_grid(j, i, img_x, img_y, grid_x, grid_y, j_g, i_g);
                                int r;
                                int g;
                                int b;
                                widget->determine_color((widget->datapoints)[i_g * grid_x + j_g + static_cast<unsigned long long>(mapindex) * offset], min_val, max_val, r, g, b);
                            //std::cout<<(widget->datapoints)[i_g * grid_x + j_g + static_cast<unsigned long long>(mapindex) * offset]<<"/n";
                                r=153+(r/255.0)*102;
                                g=153-(g/255.0)*120;
                                b=255 - b;
                                    
                                int index=i*stride+j*4;
                                imgdata[index]=b;
                                imgdata[index+1]=g;
                                imgdata[index+2]=r;
                                imgdata[index+3]=255;
                            }
                        }

                    
        
                if (big == true)
                {
                widget->heatmap_images[5]=cairo_image_surface_create_for_data(imgdata,CAIRO_FORMAT_ARGB32,img_x,img_y,stride);
                }
                else
                {
                widget->heatmap_images[mapindex]=cairo_image_surface_create_for_data(imgdata,CAIRO_FORMAT_ARGB32, img_x,img_y,stride);          
                }

            }           
            		
			
					
		static void generate_legend(SEIRDPDE_EDITORWidget* widget,int width,int height,int mapindex) {


				int stride=cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32,width);
				guint8* imgdata=new guint8[height*stride];
					
				double min_val = *std::min_element(widget->datapoints.begin(), widget->datapoints.end());
				double max_val = *std::max_element(widget->datapoints.begin(), widget->datapoints.end());

						for (int i = 0; i < height; i++) {
							for (int j = 0; j < width; j++) {

								int r=255*(1-(static_cast<double>(i)/height));
								int g=255*(1-(static_cast<double>(i)/height));
								int b=255*(1-(static_cast<double>(i)/height));
							//std::cout<<(widget->datapoints)[i_g * grid_x + j_g + static_cast<unsigned long long>(mapindex) * offset]<<"/n";
								r=153+(r/255.0)*102;
								g=153-(g/255.0)*120;
								b=255 - b;
									
								int index=i*stride+j*4;
								imgdata[index]=b;
								imgdata[index+1]=g;
								imgdata[index+2]=r;
								imgdata[index+3]=255;
							}
						}

					
		
				widget->legend_images[mapindex]=cairo_image_surface_create_for_data(imgdata,CAIRO_FORMAT_ARGB32,width,height,stride);			

			}			
			
			static bool save_heatmaps(SEIRDPDE_EDITORWidget* _this, std::string path, int tstep){
			
				const int tlen = 80;	
				char tstamp[tlen];
				time_t time = std::time(0);
				std::strftime(tstamp, tlen, "%Y.%m.%d_%H:%M:%S", localtime(&time));

				std::string ctstep;
				ctstep = std::to_string(tstep);

				cairo_surface_write_to_png(_this->heatmap_images[0], (path+"/"+ tstamp + "_TimeStep" + ctstep + "_Susceptibles.png").c_str());
				cairo_surface_write_to_png(_this->heatmap_images[1], (path+"/"+ tstamp + "_TimeStep"  + ctstep + "_Exposed.png").c_str());
				cairo_surface_write_to_png(_this->heatmap_images[2], (path+"/"+ tstamp + "_TimeStep" + ctstep  + "_Infected.png").c_str());
				cairo_surface_write_to_png(_this->heatmap_images[3], (path+"/"+ tstamp + "_TimeStep" + ctstep  + "_Recovered.png").c_str());
				cairo_surface_write_to_png(_this->heatmap_images[4], (path+"/"+ tstamp + "_TimeStep" + ctstep  + "_Deaths.png").c_str());
				cairo_surface_write_to_png(_this->legend_images[0], (path+"/"+ tstamp + "_TimeStep" + ctstep  + "_legend.png").c_str());

				return true;
			}
			app_widgets glade_widgets;		
			//Evenhandler functions
			
			static gboolean on_drawing_squared_error_draw (GtkWidget *_widget,cairo_t* cr, SEIRDPDE_EDITORWidget* _this)
			{
				std::cout<<"Redrawing squared error graph\n";
				//std::cout<<_this->sq_error[0]<<"\n";
				std::vector<double> iterations; 
				for (int i = 0; i < _this->sq_error.size(); ++i)
				{
					iterations.push_back(i);
				}


				if (_this->sq_error.size()!=0)
				{
					
					ug::epi::util::plot_values(_widget,cr,iterations,_this->sq_error,0);
					ug::epi::util::plot_axis(_widget,cr,iterations, _this->sq_error);    
				}           
				return 1;	
			}	
	
			
			
			static gboolean do_drawing_legend(SEIRDPDE_EDITORWidget::app_widgets* widget,cairo_t *cr,SEIRDPDE_EDITORWidget* _this,int width, int height, int index)
			{
				//std::cout<<"In do_drawing_legend\n";
					
				if(_this->datapoints.size()!=0){
					_this->generate_legend(_this,width,height,index);
					cairo_set_source_surface(cr,_this->legend_images[index], 0, 0);
					cairo_paint(cr);   
				}
				return 1;		 
			}
			
			static gboolean do_drawing_heatmap(SEIRDPDE_EDITORWidget::app_widgets* widget,cairo_t *cr,SEIRDPDE_EDITORWidget* _this,int mapindex,bool big=false)
			            {
			                //std::cout<<"Drawing heatmap"<<std::to_string(mapindex)<<"\n";
			                if(_this->datapoints.size()!=0){
			                    _this->generate_heatmap(_this,mapindex,big);
			                    if (big == true)
			                    {
			                        cairo_set_source_surface(cr,_this->heatmap_images[5], 0, 0);
			                    }
			                    else
			                    {
			                        cairo_set_source_surface(cr,_this->heatmap_images[mapindex], 0, 0);
			                    }
			                    cairo_paint(cr);   
			                }
			                return 1;        
			            }           
			            
			
			static void set_convergence_threshold(double val,SEIRDPDE_EDITORWidget* _this)
			{
			_this->newton_convergence_threshold=val;	
			}
			static void set_pso_iterations(int val, SEIRDPDE_EDITORWidget* _this)
			{
				//std::cout<<"set iter"<<"\n";
				//std::cout<<val<<"\n";
				_this->_pso_max_iter=val;
			}	
			
			static void set_pso_particles(int val, SEIRDPDE_EDITORWidget* _this)
			{
				_this->_pso_no_particles=val;
			}	
			
			static void set_pso_groups(int val, SEIRDPDE_EDITORWidget* _this)
			{
				_this->_pso_no_groups=val;
			}	
			
			//Returns vector with simulation initial conditions at time t0
			std::vector<double> get_u0() const
			{
				return u0;
			}	
			
			void set_u0(std::vector<double> v) 
			{
				u0=v;
			}				
			
			
			void run_pso(SEIRDPDE_EDITORWidget::app_widgets* glade_widgets, SEIRDPDE_EDITORWidget* seird_pde_object)
			{
				double alpha = seird_pde_object->_alpha;
				double kappa = seird_pde_object->_kappa;
				double theta = seird_pde_object->_theta;
				double qq = seird_pde_object->_qq;
				double pp = seird_pde_object->_pp;
				double diffusion=seird_pde_object->_diffusion;
				printf("Run PSO\n");
				size_t count = 0;
				seird_pde_object->get_u0_from_image(seird_pde_object);
				std::vector<std::string > names_of_constants;
				std::vector<double> values_of_constants;
				std::vector<std::string> names_of_variables;

				std::vector<std::string>name_of_inits = { "ht", "hx","t_end","t_start" };

				std::vector<double> values_of_inits;

				std::vector<co::EFloat64> bounds;

				if (gtk_toggle_button_get_active(glade_widgets->w_check_alpha)) 
				{
				  //std::cout << gtk_toggle_button_get_active(glade_widgets->w_check_alpha) << "\n";
				   names_of_variables.push_back("alpha");
				   bounds.push_back(co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_lower_bound_alpha))); 
				   bounds.push_back( co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_upper_bound_alpha)));
					count++;
				}

				else
				{
				   names_of_constants.push_back("alpha");
				   values_of_constants.push_back(alpha);
				}

				if (gtk_toggle_button_get_active(glade_widgets->w_check_kappa)) 
				{
				  //std::cout << gtk_toggle_button_get_active(glade_widgets->w_check_kappa) << "\n";
				   names_of_variables.push_back("kappa");
				   bounds.push_back(co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_lower_bound_kappa)));
				   bounds.push_back(co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_upper_bound_kappa)));
					count++;
				}
				else 
				{
				   names_of_constants.push_back("kappa");
				   values_of_constants.push_back(kappa);
				}

				if (gtk_toggle_button_get_active(glade_widgets->w_check_theta)) {
				  //std::cout << gtk_toggle_button_get_active(glade_widgets->w_check_theta) << "\n";
				   names_of_variables.push_back("theta");
				   bounds.push_back(co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_lower_bound_theta)));
				   bounds.push_back(co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_upper_bound_theta)));
					count++;
			   }
			   else 
			   {
				   names_of_constants.push_back("theta");
				   values_of_constants.push_back(theta);
			   }

			   if (gtk_toggle_button_get_active(glade_widgets->w_check_qq)) {
				   //std::cout << gtk_toggle_button_get_active(glade_widgets->w_check_qq) << "\n";
				   names_of_variables.push_back("qq");
				   bounds.push_back(co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_lower_bound_qq)));
				   bounds.push_back(co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_upper_bound_qq)));
					count++;
			   }
			   else
			   {
				   names_of_constants.push_back("qq");
				   values_of_constants.push_back(qq);
			   }

			   if (gtk_toggle_button_get_active(glade_widgets->w_check_pp)) {
				  //std::cout << gtk_toggle_button_get_active(glade_widgets->w_check_pp) << "\n";
				   names_of_variables.push_back("pp");
				   bounds.push_back(co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_lower_bound_pp)));
				   bounds.push_back(co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_upper_bound_pp)));
					count++;
			   }
			   else
			   {
				   names_of_constants.push_back("pp");
				   values_of_constants.push_back(pp);
			   }
			   
			   if (gtk_toggle_button_get_active(glade_widgets->w_check_diffusion)) {
				  //std::cout << gtk_toggle_button_get_active(glade_widgets->w_check_diffusion) << "\n";
				   names_of_variables.push_back("diffusion");
				   //bounds.push_back(co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_lower_bound_diffusion)));
				   //bounds.push_back(co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_upper_bound_diffusion)));
					count++;
					//TODO add Diffusion bounds in set constraints window.
			   }
			   else
			   {
				   names_of_constants.push_back("diffusion");
				   values_of_constants.push_back(diffusion);
			   }
			   
				if (count <= 0) {
					GtkWidget *dialog;
					GtkDialogFlags flags = GTK_DIALOG_MODAL;
					dialog = gtk_dialog_new_with_buttons ("Error",
														  nullptr,
														 flags,
														  "_No Parameters Checked!!",
														  GTK_RESPONSE_ACCEPT,
														  NULL);			  
					gtk_dialog_run(GTK_DIALOG(dialog));
														  
					gtk_widget_destroy(dialog);
					std::cout<<"No parameters Checked\n";
					return;
				}
			   values_of_inits = {seird_pde_object->_stepsize_time, seird_pde_object->_stepsize_spatial, seird_pde_object->_simulation_endtime,seird_pde_object->_simulation_starttime};

			   std::string textbody = R"(
initial_vars=InitialValueManager()

initial_vars:set_hx(hx)
initial_vars:set_ht(ht)
initial_vars:set_t_end(t_end)
initial_vars:set_t_start(t_start)
initial_vars:set_u0(grid)
seird_model=SEIRD_PDE(alpha,kappa,theta,qq,pp,diffusion)
RunSEIRDPDE(seird_model,initial_vars,"./","output")
							)";

				if (seird_pde_object->user_selected_optimization_path.size() == 0) 
				{
				   GtkWidget *dialog;
					GtkDialogFlags flags = GTK_DIALOG_MODAL;
					dialog = gtk_dialog_new_with_buttons ("Error",
														  nullptr,
														 flags,
														  "_Please specify the directory for the experimental data",
														  GTK_RESPONSE_ACCEPT,
														  NULL);			  
					gtk_dialog_run(GTK_DIALOG(dialog));
														  
					gtk_widget_destroy(dialog);
					printf("Nope, kein Pfad.\n");
				}
				else 
				{
					std::printf("calling create_evaluate_lua, with seird_pde_object->u0 size: %d\n", (int)seird_pde_object->u0.size());
					ug::epi::create_evaluate_lua(seird_pde_object->user_selected_optimization_path, textbody, names_of_constants, values_of_constants, names_of_variables, name_of_inits, values_of_inits, seird_pde_object->u0);

					co::PSOOptions options;
					options.set_max_iterations(seird_pde_object->_pso_max_iter);
					options.set_n_groups(seird_pde_object->_pso_no_groups);
					options.set_n_particles(seird_pde_object->_pso_no_particles);
					co::EpidemicsPDEEvaluation<co::EFloat64, co::ConfigComputation::Local, co::ConfigOutput::File> evaluator(seird_pde_object->user_selected_optimization_path, "subset_target.lua", "subset_sim.lua");
					co::ParticleSwarmOptimizer<co::EpidemicsPDEEvaluation<co::EFloat64, co::ConfigComputation::Local, co::ConfigOutput::File>> pso(options, evaluator);
					co::EVarManager<co::EFloat64> estimated_parameters;

				    auto result = pso.run(estimated_parameters, names_of_variables, bounds);

					// Handle errors
				   if (result == co::ErrorCode::OptimizationError) {
						GtkWidget *dialog;
						GtkDialogFlags flags = GTK_DIALOG_MODAL;
						dialog = gtk_dialog_new_with_buttons ("Error",
															  nullptr,
															 flags,
															  "_Optimization Error",
															  GTK_RESPONSE_ACCEPT,
															  NULL);			  
						gtk_dialog_run(GTK_DIALOG(dialog));
															  
						gtk_widget_destroy(dialog);
						std::cout<<"Optimization Error\n"; 
					}
					else if (result == co::ErrorCode::PathError) {
						GtkWidget *dialog;
						GtkDialogFlags flags = GTK_DIALOG_MODAL;
						dialog = gtk_dialog_new_with_buttons ("Error",
															  nullptr,
															 flags,
															  "_Path Error",
															  GTK_RESPONSE_ACCEPT,
															  NULL);			  
						gtk_dialog_run(GTK_DIALOG(dialog));
															  
						gtk_widget_destroy(dialog);
						std::cout<<"Path Error\n"; 
					}
					else if (result == co::ErrorCode::ComputationError) {
						GtkWidget *dialog;
						GtkDialogFlags flags = GTK_DIALOG_MODAL;
						dialog = gtk_dialog_new_with_buttons ("Error",
															  nullptr,
															 flags,
															  "_Computation Error",
															  GTK_RESPONSE_ACCEPT,
															  NULL);			  
						gtk_dialog_run(GTK_DIALOG(dialog));
															  
						gtk_widget_destroy(dialog);
						std::cout<<"Computation Error\n";
					}
					else if (result == co::ErrorCode::ParseError) { 
						GtkWidget *dialog;
						GtkDialogFlags flags = GTK_DIALOG_MODAL;
						dialog = gtk_dialog_new_with_buttons ("Error",
															  nullptr,
															 flags,
															  "_Parse Error",
															  GTK_RESPONSE_ACCEPT,
															  NULL);			  
						gtk_dialog_run(GTK_DIALOG(dialog));
															  
						gtk_widget_destroy(dialog);
						std::cout<<"Parse Error!\n"; 
					}
					else {
						for (int i = 0; i < estimated_parameters.len(); i++) 
						{
							if (estimated_parameters.get_name(i) == "alpha") {
								parameter_values[0] = estimated_parameters.get_param(i).get_value_as_double();
								gtk_spin_button_set_value(glade_widgets->w_spin_alpha, parameter_values[0]);
							}
							if (estimated_parameters.get_name(i) == "kappa") {
								parameter_values[1] =estimated_parameters.get_param(i).get_value_as_double();
								gtk_spin_button_set_value(glade_widgets->w_spin_kappa, parameter_values[1]);
							}
							if (estimated_parameters.get_name(i) == "theta") {
								parameter_values[2] = estimated_parameters.get_param(i).get_value_as_double();
								gtk_spin_button_set_value(glade_widgets->w_spin_theta, parameter_values[2]);
							}
							if (estimated_parameters.get_name(i) == "qq") {
								parameter_values[3] = estimated_parameters.get_param(i).get_value_as_double();
								gtk_spin_button_set_value(glade_widgets->w_spin_qq, parameter_values[3]);
							}
							if (estimated_parameters.get_name(i) == "pp") {
								parameter_values[4] = estimated_parameters.get_param(i).get_value_as_double();
								gtk_spin_button_set_value(glade_widgets->w_spin_pp, parameter_values[4]);
							}
						}
						
						seird_pde_object->sq_error = pso.get_saved_losses_in_past_iteration_as_double();
				
						//Redraw image by loading current data
						seird_pde_object->update_simulation(seird_pde_object);	
						seird_pde_object->load_datapoints(glade_widgets,seird_pde_object,"0");	
						gtk_spin_button_set_value(glade_widgets->w_spin_time,0);
					
					}
				}
							
			}
			
			
			
			void run_newton(SEIRDPDE_EDITORWidget::app_widgets* glade_widgets, SEIRDPDE_EDITORWidget* widget) 
			{    
				double alpha = widget->_alpha;
				double kappa = widget->_kappa;
				double theta = widget->_theta;
				double qq = widget->_qq;
				double pp = widget->_pp;
				double diffusion=widget->_diffusion;
				widget->get_u0_from_image(widget);
				
				size_t count = 0;

				printf("Run Newton\n");
				std::vector<std::string > names_of_constants;
				std::vector<double> values_of_constants;
				std::vector<std::string> names_of_variables;

				std::vector<std::string>name_of_inits = { "ht", "hx","t_end","t_start" };
				std::vector<double> values_of_inits;

				co::EVar64Manager initial_vars;

				   if (gtk_toggle_button_get_active(glade_widgets->w_check_alpha)) 
				   {
					   names_of_variables.push_back("alpha");
					   co::EVar64 v_alpha=co::EVar64(co::EFloat64(alpha), co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_lower_bound_alpha)), co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_upper_bound_alpha)));
					   std::cout << "Evar65 = " << v_alpha << std::endl;
					   initial_vars.add("alpha", v_alpha);
					   count++;
				   }
				   else 
				   {
					   names_of_constants.push_back("alpha");
					   values_of_constants.push_back(alpha);
				   }

				   if (gtk_toggle_button_get_active(glade_widgets->w_check_kappa))
				   {
					   names_of_variables.push_back("kappa");
					   //EFloats for bounds aswelll!!
					   co::EVar64 v_kappa= co::EVar64(co::EFloat64(kappa), co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_lower_bound_kappa)), co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_upper_bound_kappa)));
					   initial_vars.add("kappa", v_kappa);
					   count++;
				   }
				   else 
				   {
					   names_of_constants.push_back("kappa");
					   values_of_constants.push_back(kappa);
				   }

				   if (gtk_toggle_button_get_active(glade_widgets->w_check_theta)) 
				   {
					   names_of_variables.push_back("theta");
					   co::EVar64 v_theta = co::EVar64(co::EFloat64(theta), co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_lower_bound_theta)), co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_upper_bound_theta)));
					   initial_vars.add("theta", v_theta);
					   count++;
				   }
				   else 
				   {
					   names_of_constants.push_back("theta");
					   values_of_constants.push_back(theta);
				   }

				   if (gtk_toggle_button_get_active(glade_widgets->w_check_qq)) 
				   {
					   names_of_variables.push_back("qq");
					   co::EVar64 v_qq = co::EVar64(co::EFloat64(qq), co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_lower_bound_qq)), co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_upper_bound_qq)));
					   initial_vars.add("qq", v_qq);
					   count++;
				   }
				   else 
				   {
					   names_of_constants.push_back("qq");
					   values_of_constants.push_back(qq);
				   }

				   if (gtk_toggle_button_get_active(glade_widgets->w_check_pp)) 
				   {
					   names_of_variables.push_back("pp");
					   co::EVar64 v_pp = co::EVar64(co::EFloat64(pp), co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_lower_bound_pp)), co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_upper_bound_pp)));
					   initial_vars.add("pp", v_pp);
					   count++;
				   }
				   else 
				   {
					   names_of_constants.push_back("pp");
					   values_of_constants.push_back(pp);
				   }
					if (gtk_toggle_button_get_active(glade_widgets->w_check_diffusion)) {
					   names_of_variables.push_back("diffusion");
					   //change values for diffusion
					   co::EVar64 v_diffusion = co::EVar64(co::EFloat64(pp), co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_lower_bound_pp)), co::EFloat64(gtk_spin_button_get_value(glade_widgets->w_spin_pde_editor_upper_bound_pp)));
					   initial_vars.add("diffusion", v_diffusion);
					   
						//TODO add Diffusion bounds in set constraints window.
						count++;
				   }
				   else
				   {
					   names_of_constants.push_back("diffusion");
					   values_of_constants.push_back(diffusion);
				   }
				   
				   if (count <= 0) {
						GtkWidget *dialog;
						GtkDialogFlags flags = GTK_DIALOG_MODAL;
						dialog = gtk_dialog_new_with_buttons ("Error",
															  nullptr,
															 flags,
															  "_No Parameters Checked!!",
															  GTK_RESPONSE_ACCEPT,
															  NULL);			  
						gtk_dialog_run(GTK_DIALOG(dialog));
															  
						gtk_widget_destroy(dialog);
						std::cout<<"No parameters Checked\n";
						return;
					}

				   values_of_inits = {widget->_stepsize_time, widget->_stepsize_spatial,widget->_simulation_endtime,widget->_simulation_starttime};

				   std::string textbody = R"(
initial_vars=InitialValueManager()

initial_vars:set_hx(hx)
initial_vars:set_ht(ht)
initial_vars:set_t_end(t_end)
initial_vars:set_t_start(t_start)
initial_vars:set_u0(grid)
seird_model=SEIRD_PDE(alpha,kappa,theta,qq,pp,diffusion)
RunSEIRDPDE(seird_model,initial_vars,"./","output")
							)";
				   
				if (widget->user_selected_optimization_path.size() == 0) 
				{
					GtkWidget *dialog;
					GtkDialogFlags flags = GTK_DIALOG_MODAL;
					dialog = gtk_dialog_new_with_buttons ("Error",
														  nullptr,
														 flags,
														  "_No Path Selected!",
														  GTK_RESPONSE_ACCEPT,
														  NULL);			  
					gtk_dialog_run(GTK_DIALOG(dialog));
														  
					gtk_widget_destroy(dialog);
					printf("Nope, kein Pfad.\n");
				}
				else
				{
					   ug::epi::create_evaluate_lua(widget->user_selected_optimization_path, textbody, names_of_constants, values_of_constants, names_of_variables, name_of_inits, values_of_inits, widget->u0);
	
					   co::NewtonOptions options;
					   options.set_stepsize_alpha(1);
					  
					   co::EpidemicsPDEEvaluation<co::EFloat64, co::ConfigComputation::Local, co::ConfigOutput::File> evaluator(widget->user_selected_optimization_path, "subset_target.lua", "subset_sim.lua");
					   co::EVarManager<co::EFloat64> estimated_parameters;
					   co::NewtonOptimizer<decltype(evaluator)> solver(options, evaluator);

					   solver.set_convergence_threshold(widget->newton_convergence_threshold);

					   auto result = solver.run(initial_vars, estimated_parameters);
						
						// Handle errors
					   if (result == co::ErrorCode::OptimizationError) {
							GtkWidget *dialog;
							GtkDialogFlags flags = GTK_DIALOG_MODAL;
							dialog = gtk_dialog_new_with_buttons ("Error",
																  nullptr,
																 flags,
																  "_Optimization Error",
																  GTK_RESPONSE_ACCEPT,
																  NULL);			  
							gtk_dialog_run(GTK_DIALOG(dialog));
																  
							gtk_widget_destroy(dialog);
							std::cout<<"Optimization Error\n"; 
						}
					    else if (result == co::ErrorCode::PathError) {
							GtkWidget *dialog;
							GtkDialogFlags flags = GTK_DIALOG_MODAL;
							dialog = gtk_dialog_new_with_buttons ("Error",
																  nullptr,
																 flags,
																  "_Path Error",
																  GTK_RESPONSE_ACCEPT,
																  NULL);			  
							gtk_dialog_run(GTK_DIALOG(dialog));
																  
							gtk_widget_destroy(dialog);
							std::cout<<"Path Error\n"; 
						}
					    else if (result == co::ErrorCode::ComputationError) {
							GtkWidget *dialog;
							GtkDialogFlags flags = GTK_DIALOG_MODAL;
							dialog = gtk_dialog_new_with_buttons ("Error",
																  nullptr,
																 flags,
																  "_Computation Error",
																  GTK_RESPONSE_ACCEPT,
																  NULL);			  
							gtk_dialog_run(GTK_DIALOG(dialog));
																  
							gtk_widget_destroy(dialog);
							std::cout<<"Computation Error\n";
						}
					    else if (result == co::ErrorCode::ParseError) { 
							GtkWidget *dialog;
							GtkDialogFlags flags = GTK_DIALOG_MODAL;
							dialog = gtk_dialog_new_with_buttons ("Error",
																  nullptr,
																 flags,
																  "_Parse Error",
																  GTK_RESPONSE_ACCEPT,
																  NULL);			  
							gtk_dialog_run(GTK_DIALOG(dialog));
																  
							gtk_widget_destroy(dialog);
							std::cout<<"Parse Error!\n"; 
						}
					    else{

							for (int i = 0; i < estimated_parameters.len(); i++) 
							{
								if (estimated_parameters.get_name(i) == "alpha") 
								{
									parameter_values[0] = estimated_parameters.get_param(i).get_value_as_double();
									gtk_spin_button_set_value(glade_widgets->w_spin_alpha, parameter_values[0]);
								}
								if (estimated_parameters.get_name(i) == "kappa") 
								{
									parameter_values[1] =estimated_parameters.get_param(i).get_value_as_double();
									gtk_spin_button_set_value(glade_widgets->w_spin_kappa, parameter_values[1]);
								}
								if (estimated_parameters.get_name(i) == "theta") 
								{
									parameter_values[2] = estimated_parameters.get_param(i).get_value_as_double();
									gtk_spin_button_set_value(glade_widgets->w_spin_theta, parameter_values[2]);
								}
								if (estimated_parameters.get_name(i) == "qq") 
								{
									parameter_values[3] = estimated_parameters.get_param(i).get_value_as_double();
									gtk_spin_button_set_value(glade_widgets->w_spin_qq, parameter_values[3]);
								}
								if (estimated_parameters.get_name(i) == "pp") 
								{
									parameter_values[4] = estimated_parameters.get_param(i).get_value_as_double();
									gtk_spin_button_set_value(glade_widgets->w_spin_pp, parameter_values[4]);
								}
							}
    
						   sq_error = solver.get_saved_losses_in_past_iteration_as_double();
						  
							//Redraw image by loading current data
							widget->update_simulation(widget);	
							widget->load_datapoints(glade_widgets,widget,"0");
							gtk_spin_button_set_value(glade_widgets->w_spin_time,0);							

						}
				}
			}	
			
			
			//Sets path used in the Newton and PSO optimizations
			void set_optimization_path(std::string path)
			{
				user_selected_optimization_path = path + "/";

			}			
			
			
			void set_u0_path(std::string path)
			{
				user_selected_u0_path = path+"/";

			}	
			
			
			std::string get_u0_path() const
			{
				return user_selected_u0_path;

			}				
			static void optimization_details(SEIRDPDE_EDITORWidget* _this){
				GtkWidget *dialog;
				GtkDialogFlags flags = GTK_DIALOG_MODAL;
				dialog = gtk_dialog_new_with_buttons ("Optimization Details",
													  nullptr,
													 flags,
													  "_OK",
													  GTK_RESPONSE_ACCEPT,
													  NULL);	
													  		  
				GtkWidget* content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
				if (_this->sq_error.size()!=0){
					
						GtkWidget* grid_widget=gtk_grid_new();
					
						gtk_container_add (GTK_CONTAINER (content_area), grid_widget);
					
						GtkWidget* drawing_widget = gtk_drawing_area_new ();
						gtk_widget_set_size_request (drawing_widget, 600, 600);				
						gtk_grid_attach(GTK_GRID(grid_widget),drawing_widget,0,5,6,6);	
						g_signal_connect (G_OBJECT (drawing_widget), "draw",  G_CALLBACK (on_drawing_squared_error_pde_editor_draw), _this);
					
				}
				else
				{GtkWidget* label = gtk_label_new ("No optimization has been conducted yet!");
				// Ensure that the dialog box is destroyed when the user responds

				 g_signal_connect_swapped (dialog,
										   "response",
										   G_CALLBACK (gtk_widget_destroy),
										   dialog);

				 // Add the label, and show everything we’ve added

				 gtk_container_add (GTK_CONTAINER (content_area), label);
				}			
				gtk_widget_show_all (dialog);
				gtk_dialog_run(GTK_DIALOG(dialog));		
				gtk_widget_destroy(dialog);
							  
			}
			
			//Loads initial values from png image. Converts greyscale into gridvalues
			static void get_u0_from_image(SEIRDPDE_EDITORWidget* _this){
				
				int dimX=1;
				int dimY=1;

				double hx=_this->_stepsize_spatial;
				
				size_t x_points = std::ceil(dimX / hx) + 1;
				size_t y_points = std::ceil(dimY /hx) + 1;

				size_t nVars = static_cast<int>(x_points)* static_cast<int>(y_points);

				_this->u0=std::vector<double>(5*nVars,0.0);
				
				std::vector<std::string> names={"Initial_Susceptibles.png","Initial_Exposed.png","Initial_Infected.png","Initial_Recovered.png","Initial_Deaths.png"}; 
				
				for (int k=0;k<5;k++){
					std::string temp=_this->user_selected_u0_path+names[k];
					const char* u0_path=temp.c_str();				
	
						
					if (FILE* file=fopen(u0_path,"r")){	
						fclose(file);			
						GError** error;
						GdkPixbuf* pixbuf =gdk_pixbuf_new_from_file(u0_path,error);						
						int n_channels=gdk_pixbuf_get_n_channels(pixbuf);
						int width=gdk_pixbuf_get_width(pixbuf);
						int height=gdk_pixbuf_get_height(pixbuf);
						int row_stride=gdk_pixbuf_get_rowstride(pixbuf);
						guchar* pixels=gdk_pixbuf_get_pixels(pixbuf);
						for (int i=0;i<y_points;i++){
							for (int j=0;j<x_points;j++){
								double worldY = ((i) / (y_points - 1.0)) * dimY;
								double worldX = (j / (x_points - 1.0)) * dimX;
								int img_gridX=worldX*(width-1);
								int img_gridY=worldY*(height-1);
								int stride=img_gridY*row_stride+img_gridX*n_channels;					
								_this->u0[k*(nVars)+i*x_points+j]=(((float)pixels[stride])/255.0)*_this->maxDensity;		
							}
						}
					}
					else{
						std::cout<<temp<<" not found. Default values assumed as initial conditions.\n";
					}
				}
				std::printf("set_u0 finished current size of u0 = %d\n", (int)_this->u0.size());
			}
			
			std::string user_selected_u0_path;
			double maxDensity=1.0;
									
		};
		
		
		
		/*Here we create C bindings to our class callback functions		
		These are the bindings that will be called by Glade.
		*/
		
		

		// Spin Buttons for the parameters
		extern "C" G_MODULE_EXPORT void on_spin_alpha_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->parameter_value_changed(val,0);		
			printf("alpha pde changed \n");

		}    
		extern "C" G_MODULE_EXPORT void on_spin_kappa_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->parameter_value_changed(val,1);		
			printf("kappa pde changed \n");

		}    
		
		extern "C" G_MODULE_EXPORT void on_spin_theta_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->parameter_value_changed(val,2);		
			printf("theta pde changed \n");

		}    
		
		extern "C" G_MODULE_EXPORT void on_spin_qq_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->parameter_value_changed(val,3);		
			printf("qq pde changed \n");

		}  
  
		
		extern "C" G_MODULE_EXPORT void on_spin_pp_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->parameter_value_changed(val,4);		
			printf("pp pde changed \n");

		} 
		
		extern "C" G_MODULE_EXPORT void on_spin_diffusion_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->parameter_value_changed(val,5);		
			printf("diffusion pde changed \n");

		} 
		
		// Spin Buttons for the Lower and Upper bounds from "window_bounds"
		extern "C" G_MODULE_EXPORT void on_spin_upper_bound_pde_editor_alpha_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->upper_bound_value_changed(val, 0);
			printf( "Upper pde: %4.2f\n", val);

		}
		
		extern "C" G_MODULE_EXPORT void on_spin_upper_bound_pde_editor_kappa_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->upper_bound_value_changed(val, 1);
			printf( "Upper pde: %4.2f\n", val);

		}
		
		extern "C" G_MODULE_EXPORT void on_spin_upper_bound_pde_editor_theta_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->upper_bound_value_changed(val, 2);
			printf( "Upper pde: %4.2f\n", val);

		}
		
		extern "C" G_MODULE_EXPORT void on_spin_upper_bound_pde_editor_qq_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->upper_bound_value_changed(val, 3);
			printf( "Upper pde: %4.2f\n", val);

		}
		
		extern "C" G_MODULE_EXPORT void on_spin_upper_bound_pde_editor_pp_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->upper_bound_value_changed(val, 4);
			printf( "Upper pde: %4.2f\n", val);

		}
		
		extern "C" G_MODULE_EXPORT void on_spin_lower_bound_pde_editor_alpha_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->lower_bound_value_changed(val, 0);
			printf( "Lower pde: %4.2f\n", val);

		}
		
		extern "C" G_MODULE_EXPORT void on_spin_lower_bound_pde_editor_kappa_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->lower_bound_value_changed(val, 1);
			printf( "Lower pde: %4.2f\n", val);

		}
		
		extern "C" G_MODULE_EXPORT void on_spin_lower_bound_pde_editor_theta_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->lower_bound_value_changed(val, 2);
			printf( "Lower pde: %4.2f\n", val);

		}
		
		extern "C" G_MODULE_EXPORT void on_spin_lower_bound_pde_editor_qq_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->lower_bound_value_changed(val, 3);
			printf( "Lower pde: %4.2f\n", val);

		}
		
		extern "C" G_MODULE_EXPORT void on_spin_lower_bound_pde_editor_pp_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->lower_bound_value_changed(val, 4);
			printf( "Lower pde: %4.2f\n", val);

		}
		
		
		extern "C" G_MODULE_EXPORT void on_spin_t_start_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->initial_value_changed(val,10);
			printf( "t_start pde pde: %4.2f\n", val);		

		}   
		
		extern "C" G_MODULE_EXPORT void on_spin_t_end_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->initial_value_changed(val,11);	
			printf( "t_end pde: %4.2f\n", val);	

		}   
		
		extern "C" G_MODULE_EXPORT void on_spin_stepsize_time_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->initial_value_changed(val,12);
			printf( "Stepsize_time pde: %4.2f\n", val);

		}   

		extern "C" G_MODULE_EXPORT void on_spin_stepsize_spatial_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			double val=gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->initial_value_changed(val,13);
			printf( "Stepsize_spatial pde: %4.2f\n", val);

		}   
		
		extern "C" G_MODULE_EXPORT void run_pso_pde_editor(GtkButton* button, gpointer* data) {
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			glade_widgets->seird_pde_object->run_pso(glade_widgets,glade_widgets->seird_pde_object);
			glade_widgets->seird_pde_object->update_simulation(glade_widgets->seird_pde_object);
			gtk_spin_button_set_value(glade_widgets->w_spin_time,0);		
			glade_widgets->seird_pde_object->update_time_spin(glade_widgets);	
	
		}
		
		extern "C" G_MODULE_EXPORT void on_spin_iterations_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			double val=gtk_spin_button_get_value(button);
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			glade_widgets->seird_pde_object->set_pso_iterations(val,glade_widgets->seird_pde_object);	

		}   


		extern "C" G_MODULE_EXPORT void on_spin_particles_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			double val=gtk_spin_button_get_value(button);
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			glade_widgets->seird_pde_object->set_pso_particles(val,glade_widgets->seird_pde_object);	

		}   

		extern "C" G_MODULE_EXPORT void on_spin_groups_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			double val=gtk_spin_button_get_value(button);
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			glade_widgets->seird_pde_object->set_pso_groups(val,glade_widgets->seird_pde_object);	

		}  		
		
		extern "C" G_MODULE_EXPORT void run_newton_pde_editor(GtkButton* button, gpointer* data) {
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			glade_widgets->seird_pde_object->run_newton(glade_widgets,glade_widgets->seird_pde_object);
			glade_widgets->seird_pde_object->update_simulation(glade_widgets->seird_pde_object);
			gtk_spin_button_set_value(glade_widgets->w_spin_time,0);		
			glade_widgets->seird_pde_object->update_time_spin(glade_widgets);	
	
		}
		
		extern "C" G_MODULE_EXPORT void on_spin_convergence_threshold_pde_editor_value_changed(GtkSpinButton* button, gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);

			double val = gtk_spin_button_get_value(button);
			glade_widgets->seird_pde_object->set_convergence_threshold(val,glade_widgets->seird_pde_object);	

		}   
		
		//Menu callbacks
		//TODO: Might leak memory because the dialog is only hidden and not destroyed
		extern "C" G_MODULE_EXPORT void select_optimization_path_pde_editor(int resp_id, GtkFileChooserDialog* dialog,gpointer* data)
		{
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);				
			GtkWidget* dia= reinterpret_cast<GtkWidget*>(dialog);
			auto temp=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			//std::cout << "Set path to " << temp << "\n";
			//std::cout<<"Ptr1:"<<glade_widgets->seird_pde_object<<"\n";
			glade_widgets->seird_pde_object->set_optimization_path(temp);
			gtk_widget_hide(dia);
		}	
			
		extern "C" G_MODULE_EXPORT void on_show_popup_menu_pde_editor(GtkMenuItem *button, gpointer* data)
		{
			//GtkWidget* _this = reinterpret_cast<GtkWidget*>(data);
			//gtk_widget_show(_this);
			printf("Show Menu\n");
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			
			GtkFileChooserNative *native;
			GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
			gint res;
			
			native = gtk_file_chooser_native_new("Select folder",
												0,
												action,
												"_Select"
												,"_Cancel");

			res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));
			if (res == GTK_RESPONSE_ACCEPT)
			{
				auto temp=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(native));
						
						glade_widgets->seird_pde_object->set_optimization_path(temp);
			}
		}
		

		extern "C" G_MODULE_EXPORT void on_cancel_pde_editor(GtkButton* button, gpointer* data)
		{
			GtkWidget* _this = reinterpret_cast<GtkWidget*>(data);
			gtk_widget_hide(_this);
			printf("Cancel\n");
		}
		extern "C" G_MODULE_EXPORT void on_show_menu_pde_editor(GtkButton *button, gpointer* data)
		{
			GtkWidget* _this = reinterpret_cast<GtkWidget*>(data);
			gtk_widget_show(_this);
				//Initialize value<s
			// initialize_values();
			printf("Show Menu\n");
			//Initialize simulation
			// update_simulation();
		}

        extern "C" G_MODULE_EXPORT void on_show_map_pde_editor(GtkWidget *widget, GdkEvent *event, gpointer data)
        {
            std::cout<<"In callback Show Menu PDE\n";

            GtkWidget* _this = reinterpret_cast<GtkWidget*>(data);
            GtkWindow* _that = reinterpret_cast<GtkWindow*>(data);
            std::cout<<"In callback Show Menu PDE\n";
            gtk_widget_show(_this);
            gtk_window_present(_that);
                //Initialize values
            // initialize_values();
            printf("Show Menu\n");
            //Initialize simulation
            // update_simulation();
        }
		extern "C" G_MODULE_EXPORT void on_run_sim_pde_editor_button(GtkSpinButton* button, gpointer* data)
		{
	
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			
			if(glade_widgets->seird_pde_object->user_selected_optimization_path.empty()==true){
				GtkWidget *dialog;
				GtkDialogFlags flags = GTK_DIALOG_MODAL;
				dialog = gtk_dialog_new_with_buttons ("Error",
													  nullptr,
													 flags,
													  "_No Path Selected!",
													  GTK_RESPONSE_ACCEPT,
													  NULL);			  
				gtk_dialog_run(GTK_DIALOG(dialog));
													  
				gtk_widget_destroy(dialog);
			}
			else if (glade_widgets->seird_pde_object->user_selected_u0_path.empty()==true){
				GtkWidget *dialog;
				GtkDialogFlags flags = GTK_DIALOG_MODAL;
				dialog = gtk_dialog_new_with_buttons ("Error",
													  nullptr,
													 flags,
													  "_No initial data u0 set in editor",
													  GTK_RESPONSE_ACCEPT,
													  NULL);			  
				gtk_dialog_run(GTK_DIALOG(dialog));
													  
				gtk_widget_destroy(dialog);				
				
			}
			else{		
				glade_widgets->seird_pde_object->update_simulation(glade_widgets->seird_pde_object);	
				glade_widgets->seird_pde_object->load_datapoints(glade_widgets,glade_widgets->seird_pde_object,"0");
				gtk_spin_button_set_value(glade_widgets->w_spin_time,0);		
				glade_widgets->seird_pde_object->update_time_spin(glade_widgets);	
			}
			
			//glade_widgets->seird_pde_object->plot_heatmapa(glade_widgets->seird_pde_object,"/output0.txt");
		}
		
		extern "C" G_MODULE_EXPORT void on_drawing_squared_error_pde_editor_draw(GtkWidget *_widget,cairo_t* cr, SEIRDPDE_EDITORWidget* seird_pde_object){
		
			seird_pde_object->on_drawing_squared_error_draw(_widget,cr,seird_pde_object);
		}	
		
		extern "C" G_MODULE_EXPORT void on_drawing_legend_pde_editor(GtkWidget *widget, cairo_t *cr,gpointer* data)
		{      
		  //std::cout<<"In callback Legend draw\n";
		  SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
		glade_widgets->seird_pde_object->do_drawing_legend(glade_widgets,cr,glade_widgets->seird_pde_object,12,200,0);

			//Draw the legend
		
		}
		
		        extern "C" G_MODULE_EXPORT void draw_big_map_pde_editor(GtkWidget *widget, GdkEvent  *event, gpointer* data)
        {
            std::cout<<"In callback draw_big_map\n";
            SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
            GtkDrawingArea* heatmap= reinterpret_cast<GtkDrawingArea*>(widget);

            // g_signal_emit (data, "draw", GQuark *detail, orign_map)
            if (heatmap == glade_widgets -> frame_susceptibles_drawing_area_pde)
            {
                std::cout<<"0\n";
                glade_widgets -> seird_pde_object -> zoomed = 0;
                
            }
            else if (heatmap == glade_widgets -> frame_exposed_drawing_area_pde)
            {
                std::cout<<"1\n";
                            glade_widgets -> seird_pde_object -> zoomed = 1;

            }
            else if (heatmap == glade_widgets -> frame_infected_drawing_area_pde)
            {
                std::cout<<"2\n";
                glade_widgets -> seird_pde_object -> zoomed = 2;

            }
            else if (heatmap == glade_widgets -> frame_recovered_drawing_area_pde)
            {
                std::cout<<"3\n";
                glade_widgets -> seird_pde_object -> zoomed = 3;

            }
            else if (heatmap == glade_widgets -> frame_deceased_drawing_area_pde)
            {
                std::cout<<"4\n";
                glade_widgets -> seird_pde_object -> zoomed = 4;
            }
        }

        extern "C" G_MODULE_EXPORT void on_drawing_heatmap_big_draw_pde_editor(GtkWidget *widget, cairo_t *cr,gpointer* data)
        {
            std::cout<<"In callback Heatmap Big draw\n";

            // SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
            // GtkDrawingArea* heatmap = reinterpret_cast<GtkDrawingArea*>(data);

            SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);

            glade_widgets->seird_pde_object->do_drawing_heatmap(glade_widgets, cr,glade_widgets->seird_pde_object, glade_widgets -> seird_pde_object -> zoomed, true);
            std::cout<<"In callback Heatmap Big draw\n";

        }

				
		extern "C" G_MODULE_EXPORT void on_drawing_susceptibles_pde_editor(GtkWidget *widget, cairo_t *cr,gpointer* data)
		{      
		  //std::cout<<"In callback Susceptibles draw\n";
		  SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
		  glade_widgets->seird_pde_object->do_drawing_heatmap(glade_widgets,cr,glade_widgets->seird_pde_object,0);

		  
		}
		

		extern "C" G_MODULE_EXPORT void on_drawing_exposed_pde_editor(GtkWidget *widget, cairo_t *cr,gpointer* data)
		{      
		  //std::cout<<"In callback Exposed draw\n";
		  SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
		  glade_widgets->seird_pde_object->do_drawing_heatmap(glade_widgets,cr,glade_widgets->seird_pde_object,1);

		  
		}
		
				
		extern "C" G_MODULE_EXPORT void on_drawing_infected_pde_editor(GtkWidget *widget, cairo_t *cr,gpointer* data)
		{      
		  //std::cout<<"In callback Infected draw\n";
		  SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
		  glade_widgets->seird_pde_object->do_drawing_heatmap(glade_widgets,cr,glade_widgets->seird_pde_object,2);

		  
		}
		
				
		extern "C" G_MODULE_EXPORT void on_drawing_recovered_pde_editor(GtkWidget *widget, cairo_t *cr,gpointer* data)
		{      
		  //std::cout<<"In callback recovered draw\n";
		  SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
		  glade_widgets->seird_pde_object->do_drawing_heatmap(glade_widgets,cr,glade_widgets->seird_pde_object,3);

		  
		}
	
						
		extern "C" G_MODULE_EXPORT void on_drawing_deceased_pde_editor(GtkWidget *widget, cairo_t *cr,gpointer* data)
		{      
		  //std::cout<<"In callback Deceased draw\n";
		  SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
		  glade_widgets->seird_pde_object->do_drawing_heatmap(glade_widgets,cr,glade_widgets->seird_pde_object,4);

		  
		}
		
		extern "C" G_MODULE_EXPORT void seird_pde_editor_time_spin(GtkWidget *widget, gpointer* data)
		{      
		  //std::cout<<"In callback seird_pde_time_spin\n";
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			std::string time_index=std::to_string((int)gtk_spin_button_get_value(glade_widgets->w_spin_time));
			glade_widgets->seird_pde_object->load_datapoints(glade_widgets,glade_widgets->seird_pde_object,time_index);	
		}
		
		
		
		extern "C" G_MODULE_EXPORT void seird_pde_editor_save_heatmaps(GtkWidget *widget, gpointer* data, int time_step)
		{      
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			auto seird_pde_object=glade_widgets->seird_pde_object;
		 	int tstep = gtk_spin_button_get_value(glade_widgets->w_spin_time);

			GtkFileChooserNative *native;
			GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
			gint res;
	
			native = gtk_file_chooser_native_new("Select folder",
												0,
												action,
												"_Select"
												,"_Cancel");


			res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));
			if (res == GTK_RESPONSE_ACCEPT)
			{
				auto path=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(native));
		
				seird_pde_object->save_heatmaps(seird_pde_object,path, tstep);
			
			}
		}
		
		extern "C" G_MODULE_EXPORT void seird_pde_editor_optimization_details(GtkWidget *widget, gpointer* data)
		{      
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			SEIRDPDE_EDITORWidget* seird_pde_object=glade_widgets->seird_pde_object;
			seird_pde_object->optimization_details(seird_pde_object);
		}
		
		extern "C" G_MODULE_EXPORT void on_run_pde_editor_button(GtkWidget *widget, gpointer* data)
		{      
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			SEIRDPDE_EDITORWidget* seird_pde_object=glade_widgets->seird_pde_object;

			//seird_pde_object->optimization_details(seird_pde_object);
			
			GtkWidget *dialog;
					GtkDialogFlags flags = GTK_DIALOG_MODAL;
					dialog = gtk_dialog_new_with_buttons ("Error",
														  nullptr,
														 flags,
														  "_Editor not implemented yet!",
														  GTK_RESPONSE_ACCEPT,
														  NULL);			  
					gtk_dialog_run(GTK_DIALOG(dialog));
														  
					gtk_widget_destroy(dialog);
			
		
		}	
		
		extern "C" G_MODULE_EXPORT void on_show_popup_menu_load_initial_data_pde_editor(GtkWidget *widget, gpointer* data)
		{      
			SEIRDPDE_EDITORWidget::app_widgets* glade_widgets= reinterpret_cast<SEIRDPDE_EDITORWidget::app_widgets*>(data);
			SEIRDPDE_EDITORWidget* seird_pde_object=glade_widgets->seird_pde_object;
			
			GtkFileChooserNative *native;
			GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
			gint res;
			
			//auto parent_window=gtk_builder_get_object(glade_widgets->seird_object->builder,"grid_seird");

			native = gtk_file_chooser_native_new("Select folder",
												0,
												action,
												"_Open"
												,"_Cancel");

			res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));
			if (res == GTK_RESPONSE_ACCEPT)
			{
				auto temp=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(native));
				seird_pde_object->set_u0_path(temp);
				//std::cout<<temp<<"\n";
			}
			
		
		}			

		
	}
}
