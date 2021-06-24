#pragma once
#include <algorithm>
#include <gtk/gtk.h>
#include <cairo.h>
#include <sstream>
#include<stdlib.h>

namespace ug{	
	namespace epi{

		void create_evaluate_lua(std::string path, std::string textbody, std::vector<std::string>& names_of_constants,std::vector<double>& values_of_constants, std::vector<std::string>& names_of_variables, std::vector<std::string>& names_of_inits, std::vector<double>& values_of_inits, double stepsize) 
		{

			std::ofstream lua_output;
			std::ofstream general_output;
			lua_output.open(path + "/evaluate.lua");

			lua_output << R"(PrintBuildConfiguration()

-----------------------------------------------------------------
-- define Home-Directories
----------------------------------------------------------------
ug4_home        = ug_get_root_path().."/"

--common_scripts  = app_home.."scripts/"
--geom_home       = app_home.."geometry/"

-----------------------------------------------------------------


--Load Parameters
local pars = "parameters.lua"

local parmfileloaded= false
if(pfile ~= "") then
	local file = assert(loadfile(pars))
	file()
	parmfileloaded = true
end
if parmfileloaded == false then
	print("Parameter file could not be loaded")
end

--Start of parameter, constants and initial values definitions

)";
			lua_output << "h=" << stepsize << "\n";			
			for (size_t i = 0; i < names_of_inits.size(); i++) {
				lua_output << names_of_inits[i] << "=" << values_of_inits[i] << "\n";
			}
			
			for (size_t i= 0; i < names_of_constants.size(); i++) {
				lua_output << names_of_constants[i] << "=" << values_of_constants[i] << "\n";
			}

			for (size_t i = 0; i < names_of_variables.size(); i++) {
				lua_output << names_of_variables[i] << "=parameters."<<names_of_variables[i]<<":get_value_as_double()\n";
			}
			
			lua_output << textbody;

			lua_output.close();

		}

				namespace util{			
			void plot_values(GtkWidget* _drawing_widget,cairo_t* cr,const std::vector<double>& timepoints, const std::vector<double>& datapoints, int selected_dim){
				int dim_data=datapoints.size()/timepoints.size();
				guint width, height;
				width = gtk_widget_get_allocated_width (_drawing_widget);
				height = gtk_widget_get_allocated_height (_drawing_widget);
				
				double xrange_min=*std::min_element(timepoints.begin(), timepoints.end());
				double xrange_max=*std::max_element(timepoints.begin(), timepoints.end());	
				
				double yrange_min=*std::min_element(datapoints.begin(), datapoints.end());
				double yrange_max=*std::max_element(datapoints.begin(), datapoints.end());	
				
				double rgbR=0;
				double rgbG=0;
				double rgbB=0;	
				
				if (selected_dim==0){
					rgbR=0.8;
				}
				else if (selected_dim==1){
					rgbB=0.8;
					rgbG=0.3;
				}
				else {
					rgbR=(double)selected_dim/timepoints.size();
				}
										
				cairo_set_source_rgb(cr,rgbR,rgbG,rgbB);
				double xrange_inv=1/(xrange_max-xrange_min);
				double yrange_inv=1/(yrange_max-yrange_min);
				auto get_canvas_coordinates=[&](double x, double y,double* xg, double* yg){
					*xg=(x-xrange_min)*xrange_inv*width;
					*yg=height-(y-yrange_min)*yrange_inv*height;					
				};

				double xg;
				double yg;
				
				cairo_set_line_width(cr, 2);				
			//	std::cout<<"drin\n";
				
				for (size_t i = 0; i < timepoints.size() ; i++ ) {
					get_canvas_coordinates(timepoints[i],datapoints[i*dim_data+selected_dim],&xg,&yg);  
					//std::cout<<xg<<"  "<<yg<<"\n";
					cairo_line_to(cr, xg, yg);
				}   
				
				cairo_stroke(cr);
									
			}
			
			void plot_values(GtkWidget* _drawing_widget,cairo_t* cr,const std::vector<double>& timepoints, const std::vector<double>& datapoints, bool* selected_dims,std::vector<double>& colors, bool set_background){
				int dim_data=datapoints.size()/timepoints.size();
				guint width, height;
				width = gtk_widget_get_allocated_width (_drawing_widget);
				height = gtk_widget_get_allocated_height (_drawing_widget);
	
				double yrange_min=std::numeric_limits<double>::max();
				double yrange_max=-std::numeric_limits<double>::max();
				for (int j=0;j<dim_data;j++){
					if (selected_dims[j]==true){
						for (int i=0;i<timepoints.size();i++){
						double val=datapoints[i*dim_data+j];
							
							if (val>yrange_max){
								yrange_max=val;
							}
							if (val<yrange_min){
								yrange_min=val;
							}								
							
						}			
					}		
				}

				double xrange_min=*std::min_element(timepoints.begin(), timepoints.end());
				double xrange_max=*std::max_element(timepoints.begin(), timepoints.end());	
				
				colors=std::vector<double>();

				double xrange_inv=1/(xrange_max-xrange_min);
				double yrange_inv=1/(yrange_max-yrange_min);
				auto get_canvas_coordinates=[&](double x, double y,double* xg, double* yg){
					*xg=(x-xrange_min)*xrange_inv*width;
					*yg=height-(y-yrange_min)*yrange_inv*height;					
				};
				if (set_background){
					cairo_set_source_rgb (cr, 1,1,1);
					cairo_rectangle (cr, 0, 0, width,height);
					cairo_fill (cr);	
				}	
				srand(173);

				double xg;
				double yg;
                double rgbR;
                double rgbG;
                double rgbB;

				cairo_set_line_width(cr, 2);				
			//	std::cout<<"drin\n";
				for (int j=0;j<dim_data;j++){
					if (selected_dims[j]==true){
                        if (j == 0)
                        {
                            rgbR=255;
                            rgbG=0;
                            rgbB=0;
                        }

                        else if (j == 1)
                        {
                            rgbR=0;
                            rgbG=128;
                            rgbB=0;

                        }

                        else if (j == 2)
                        {
                            rgbR=0;
                            rgbG=0;
                            rgbB=255;

                        }

                        else if (j == 3)
                        {
                            rgbR=255;
                            rgbG=255;
                            rgbB=0;

                        }

                        else if (j == 4)
                        {
                            rgbR=75;
                            rgbG=0;
                            rgbB=130;

                        }
                        else if (j == 5)
                        {
                            rgbR=238;
                            rgbG=130;
                            rgbB=238;

                        }
                        else
                        {
                            srand(rand());
                            rgbR=(rand()%255)/255.0;
                            rgbG=(rand()%255)/255.0;
                            rgbB=(rand()%125)/255.0;
                        }
						colors.push_back(rgbR);
						colors.push_back(rgbG);
						colors.push_back(rgbB);
						cairo_set_source_rgb(cr,rgbR,rgbG,rgbB);
						get_canvas_coordinates(timepoints[0],datapoints[j],&xg,&yg);  
						cairo_move_to(cr,xg,yg);
						for (size_t i = 0; i < timepoints.size() ; i++ ) {
							get_canvas_coordinates(timepoints[i],datapoints[i*dim_data+j],&xg,&yg);  
							cairo_line_to(cr, xg, yg);
						}   	
						cairo_stroke(cr);								
					}		
				}						
			}
			
			void plot_values(GtkWidget* _drawing_widget,cairo_t* cr,const std::vector<double>& timepoints, const std::vector<double>& datapoints, bool* selected_dims,std::vector<double>& colors, bool set_background, double xrange_min, double xrange_max, double yrange_min, double yrange_max){
				int dim_data=datapoints.size()/timepoints.size();
				guint width, height;
				width = gtk_widget_get_allocated_width (_drawing_widget);
				height = gtk_widget_get_allocated_height (_drawing_widget);
	
				colors=std::vector<double>();

				double xrange_inv=1/(xrange_max-xrange_min);
				double yrange_inv=1/(yrange_max-yrange_min);
				auto get_canvas_coordinates=[&](double x, double y,double* xg, double* yg){
					*xg=(x-xrange_min)*xrange_inv*width;
					*yg=height-(y-yrange_min)*yrange_inv*height;					
				};
				if (set_background){
					cairo_set_source_rgb (cr, 1,1,1);
					cairo_rectangle (cr, 0, 0, width,height);
					cairo_fill (cr);	
				}	
				srand(173);

				double xg;
				double yg;

				cairo_set_line_width(cr, 2);				
			//	std::cout<<"drin\n";
				for (int j=0;j<dim_data;j++){
					if (selected_dims[j]==true){
						double rgbR=(rand()%255)/255.0;
						double rgbG=(rand()%255)/255.0;
						double rgbB=(rand()%125)/255.0;
						colors.push_back(rgbR);
						colors.push_back(rgbG);
						colors.push_back(rgbB);
						cairo_set_source_rgb(cr,rgbR,rgbG,rgbB);
						get_canvas_coordinates(timepoints[0],datapoints[j],&xg,&yg);  
						cairo_move_to(cr,xg,yg);
						for (size_t i = 0; i < timepoints.size() ; i++ ) {
							get_canvas_coordinates(timepoints[i],datapoints[i*dim_data+j],&xg,&yg);  
							cairo_line_to(cr, xg, yg);
						}   	
						cairo_stroke(cr);								
					}		
				}						
			}
		
			
			void plot_values_square(GtkWidget* _drawing_widget,cairo_t* cr,const std::vector<double>& timepoints, const std::vector<double>& datapoints, bool* selected_dims,std::vector<double>& colors, bool set_background){
				int dim_data=datapoints.size()/timepoints.size();
				guint width, height;
				width = gtk_widget_get_allocated_width (_drawing_widget);
				height = gtk_widget_get_allocated_height (_drawing_widget);
	
				double yrange_min=std::numeric_limits<double>::max();
				double yrange_max=-std::numeric_limits<double>::max();
				for (int j=0;j<dim_data;j++){
					if (selected_dims[j]==true){
						for (int i=0;i<timepoints.size();i++){
						double val=datapoints[i*dim_data+j];
							
							if (val>yrange_max){
								yrange_max=val;
							}
							if (val<yrange_min){
								yrange_min=val;
							}								
							
						}			
					}		
				}

				double xrange_min=*std::min_element(timepoints.begin(), timepoints.end());
				double xrange_max=*std::max_element(timepoints.begin(), timepoints.end());	
				
				colors=std::vector<double>();

				double xrange_inv=1/(xrange_max-xrange_min);
				double yrange_inv=1/(yrange_max-yrange_min);
				auto get_canvas_coordinates=[&](double x, double y,double* xg, double* yg){
					*xg=(x-xrange_min)*xrange_inv*width;
					*yg=height-(y-yrange_min)*yrange_inv*height;					
				};
				if (set_background){
					cairo_set_source_rgb (cr, 1,1,1);
					cairo_rectangle (cr, 0, 0, width,height);
					cairo_fill (cr);	
				}	
				srand(173);

				double xg;
				double yg;

				cairo_set_line_width(cr, 2);				
			//	std::cout<<"drin\n";
				for (int j=0;j<dim_data;j++){
					if (selected_dims[j]==true){
						double rgbR=(rand()%255)/255.0;
						double rgbG=(rand()%255)/255.0;
						double rgbB=(rand()%125)/255.0;
						colors.push_back(rgbR);
						colors.push_back(rgbG);
						colors.push_back(rgbB);
						cairo_set_source_rgb(cr,rgbR,rgbG,rgbB);
						get_canvas_coordinates(timepoints[0],datapoints[j],&xg,&yg);  

						for (size_t i = 0; i < timepoints.size() ; i++ ) {
							get_canvas_coordinates(timepoints[i],datapoints[i*dim_data+j],&xg,&yg);  
							cairo_move_to(cr,xg,yg);
							cairo_rectangle (cr, xg, yg, 10,10);
							cairo_fill (cr);	
							cairo_move_to(cr,xg,yg);
						}   	
						cairo_stroke(cr);								
					}		
				}						
			}

			void plot_values_square(GtkWidget* _drawing_widget,cairo_t* cr,const std::vector<double>& timepoints, const std::vector<double>& datapoints, bool* selected_dims,std::vector<double>& colors, bool set_background,double xrange_min, double xrange_max, double yrange_min, double yrange_max){
				int dim_data=datapoints.size()/timepoints.size();
				guint width, height;
				width = gtk_widget_get_allocated_width (_drawing_widget);
				height = gtk_widget_get_allocated_height (_drawing_widget);
	
				colors=std::vector<double>();

				double xrange_inv=1/(xrange_max-xrange_min);
				double yrange_inv=1/(yrange_max-yrange_min);
				auto get_canvas_coordinates=[&](double x, double y,double* xg, double* yg){
					*xg=(x-xrange_min)*xrange_inv*width;
					*yg=height-(y-yrange_min)*yrange_inv*height;					
				};
				if (set_background){
					cairo_set_source_rgb (cr, 1,1,1);
					cairo_rectangle (cr, 0, 0, width,height);
					cairo_fill (cr);	
				}	
				srand(173);

				double xg;
				double yg;

				cairo_set_line_width(cr, 2);				
			//	std::cout<<"drin\n";
				for (int j=0;j<dim_data;j++){
					if (selected_dims[j]==true){
						double rgbR=(rand()%255)/255.0;
						double rgbG=(rand()%255)/255.0;
						double rgbB=(rand()%125)/255.0;
						colors.push_back(rgbR);
						colors.push_back(rgbG);
						colors.push_back(rgbB);
						cairo_set_source_rgb(cr,rgbR,rgbG,rgbB);
						get_canvas_coordinates(timepoints[0],datapoints[j],&xg,&yg);  

						for (size_t i = 0; i < timepoints.size() ; i++ ) {
							get_canvas_coordinates(timepoints[i],datapoints[i*dim_data+j],&xg,&yg);  
							cairo_move_to(cr,xg,yg);
							cairo_rectangle (cr, xg, yg, 10,10);
							cairo_fill (cr);	
							cairo_move_to(cr,xg,yg);
						}   	
						cairo_stroke(cr);								
					}		
				}						
			}
				
				
					
			void plot_axis(GtkWidget* _drawing_widget,cairo_t* cr,const std::vector<double>& timepoints, const std::vector<double>& datapoints){
				cairo_set_source_rgb(cr,0.0, 0.0, 0.0);
				

				guint width, height;
				width = gtk_widget_get_allocated_width (_drawing_widget);
				height = gtk_widget_get_allocated_height (_drawing_widget);
				
				double xrange_min=*std::min_element(timepoints.begin(), timepoints.end());
				double xrange_max=*std::max_element(timepoints.begin(), timepoints.end());	
				
				double yrange_min=*std::min_element(datapoints.begin(), datapoints.end());
				double yrange_max=*std::max_element(datapoints.begin(), datapoints.end());	
				
				double xrange_inv=1/(xrange_max-xrange_min);
				double yrange_inv=1/(yrange_max-yrange_min);
				auto get_canvas_coordinates=[&](double x, double y,double* xg, double* yg){
					*xg=(x-xrange_min)*xrange_inv*width;
					*yg=height-(y-yrange_min)*yrange_inv*height;					
				};
								
				double xg;
				double yg;
				
				//x axis
				cairo_set_line_width(cr, 2);				

				if (yrange_max>=0){
					get_canvas_coordinates(timepoints[0],0.0,&xg,&yg); 		
					cairo_line_to(cr, xg, yg);
					cairo_show_text(cr,std::to_string(xrange_min).c_str());					
					get_canvas_coordinates(timepoints[timepoints.size()-1],0.0,&xg,&yg); 		
					cairo_line_to(cr, xg, yg);						
					cairo_show_text(cr,std::to_string(xrange_max).c_str());					
				}
				//y axis
				if (xrange_min <= 0){
					get_canvas_coordinates(0,yrange_min,&xg,&yg); 		
					cairo_move_to(cr,xg,yg);
					cairo_show_text(cr,std::to_string(yrange_min).c_str());
					cairo_line_to(cr, xg, yg);					
					get_canvas_coordinates(0,yrange_max,&xg,&yg); 		
					cairo_line_to(cr, xg, yg);
					cairo_move_to(cr,xg,yg);
					cairo_show_text(cr,std::to_string(yrange_max).c_str());
					
				}
				int n_ticks=5;
				if (timepoints.size()<n_ticks){
					n_ticks=timepoints.size();
				}
				int len_t=timepoints.size();
				int tick_stride=len_t/n_ticks;
				
				//x ticks
				for (int i=0;i<n_ticks;i++){
					get_canvas_coordinates(timepoints[i*tick_stride],yrange_min,&xg,&yg); 		
					cairo_move_to(cr,xg,yg);
					cairo_show_text(cr,std::to_string(timepoints[i*tick_stride]).c_str());
				}	
				//y ticks
				tick_stride=(yrange_max-yrange_min)/n_ticks;;
				for (int i=0;i<n_ticks;i++){
					//std::cout<<datapoints[i*tick_stride*dim_data+max_column]<<"\n";
					get_canvas_coordinates(0,yrange_min+tick_stride*i,&xg,&yg); 		
					cairo_move_to(cr,xg,yg);
					cairo_show_text(cr,std::to_string(yrange_min+tick_stride*i).c_str());
				}							
				cairo_stroke(cr);
									
			}			

			void plot_axis(GtkWidget* _drawing_widget,cairo_t* cr,const std::vector<double>& timepoints, const std::vector<double>& datapoints,bool* selected_dims){
				cairo_set_source_rgb(cr,0.0, 0.0, 0.0);
				

				guint width, height;
				width = gtk_widget_get_allocated_width (_drawing_widget);
				height = gtk_widget_get_allocated_height (_drawing_widget);
				
				double xrange_min=*std::min_element(timepoints.begin(), timepoints.end());
				double xrange_max=*std::max_element(timepoints.begin(), timepoints.end());	
				
				int dim_data=datapoints.size()/timepoints.size();	
				double yrange_min=std::numeric_limits<double>::max();
				double yrange_max=-std::numeric_limits<double>::max();
				for (int j=0;j<dim_data;j++){
					if (selected_dims[j]==true){
						for (int i=0;i<timepoints.size();i++){
						double val=datapoints[i*dim_data+j];
							
							if (val>yrange_max){
								yrange_max=val;
							}
							if (val<yrange_min){
								yrange_min=val;
							}								
							
						}			
					}		
				}	
				double xrange_inv=1/(xrange_max-xrange_min);
				double yrange_inv=1/(yrange_max-yrange_min);
				auto get_canvas_coordinates=[&](double x, double y,double* xg, double* yg){
					*xg=(x-xrange_min)*xrange_inv*width;
					*yg=height-(y-yrange_min)*yrange_inv*height;					
				};
								
				double xg;
				double yg;
				
				//x axis
				cairo_set_line_width(cr, 2);				

				if (yrange_max>=0){
					get_canvas_coordinates(timepoints[0],0.0,&xg,&yg); 		
					cairo_line_to(cr, xg, yg);
					std::stringstream ss;
					ss << std::fixed << std::setprecision(2) << xrange_min;
					std::string numstring = ss.str();
					cairo_show_text(cr,numstring.c_str());			
					get_canvas_coordinates(timepoints[timepoints.size()-1],0.0,&xg,&yg); 		
					cairo_line_to(cr, xg, yg);						
					cairo_show_text(cr,std::to_string(xrange_max).c_str());					
				}
				//y axis
				if (xrange_min <= 0){
					get_canvas_coordinates(0,yrange_min,&xg,&yg); 		
					cairo_move_to(cr,xg,yg);
					std::stringstream ss;
					ss << std::fixed << std::setprecision(2) << yrange_min;
					std::string numstring = ss.str();
					cairo_show_text(cr,numstring.c_str());
					cairo_line_to(cr, xg, yg);					
					get_canvas_coordinates(0,yrange_max,&xg,&yg); 		
					cairo_line_to(cr, xg, yg);
					cairo_move_to(cr,xg,yg);
					cairo_show_text(cr,std::to_string(yrange_max).c_str());
					
				}
				int n_ticks=5;
				if (timepoints.size()<n_ticks){
					n_ticks=timepoints.size();
				}
				int len_t=timepoints.size();
				int tick_stride=len_t/n_ticks;
				
				//x ticks
				for (int i=0;i<n_ticks;i++){
					get_canvas_coordinates(timepoints[i*tick_stride],yrange_min,&xg,&yg); 		
					cairo_move_to(cr,xg,yg);
					std::stringstream ss;
					ss << std::fixed << std::setprecision(2) << timepoints[i*tick_stride];
					std::string numstring = ss.str();
					cairo_show_text(cr,numstring.c_str());
				}	
				//y ticks
				tick_stride=(yrange_max-yrange_min)/n_ticks;;
				for (int i=0;i<n_ticks;i++){
					//std::cout<<datapoints[i*tick_stride*dim_data+max_column]<<"\n";
					get_canvas_coordinates(0,yrange_min+tick_stride*i,&xg,&yg); 		
					cairo_move_to(cr,xg,yg);
					std::stringstream ss;
					ss << std::fixed << std::setprecision(2) << yrange_min+tick_stride*i;
					std::string numstring = ss.str();
					cairo_show_text(cr,numstring.c_str());
				}							
				cairo_stroke(cr);
									
			}	
			
		void plot_axis(GtkWidget* _drawing_widget,cairo_t* cr,const std::vector<double>& timepoints, const std::vector<double>& datapoints,bool* selected_dims,double xrange_min, double xrange_max, double yrange_min, double yrange_max){
				cairo_set_source_rgb(cr,0.0, 0.0, 0.0);
				

				guint width, height;
				width = gtk_widget_get_allocated_width (_drawing_widget);
				height = gtk_widget_get_allocated_height (_drawing_widget);
							
				int dim_data=datapoints.size()/timepoints.size();	

				double xrange_inv=1/(xrange_max-xrange_min);
				double yrange_inv=1/(yrange_max-yrange_min);
				auto get_canvas_coordinates=[&](double x, double y,double* xg, double* yg){
					*xg=(x-xrange_min)*xrange_inv*width;
					*yg=height-(y-yrange_min)*yrange_inv*height;					
				};
								
				double xg;
				double yg;
				
				//x axis
				cairo_set_line_width(cr, 2);				

				if (yrange_max>=0){
					get_canvas_coordinates(timepoints[0],0.0,&xg,&yg); 		
					cairo_line_to(cr, xg, yg);
					std::stringstream ss;
					ss << std::fixed << std::setprecision(2) << xrange_min;
					std::string numstring = ss.str();
					cairo_show_text(cr,numstring.c_str());			
					get_canvas_coordinates(timepoints[timepoints.size()-1],0.0,&xg,&yg); 		
					cairo_line_to(cr, xg, yg);						
					cairo_show_text(cr,std::to_string(xrange_max).c_str());					
				}
				//y axis
				if (xrange_min <= 0){
					get_canvas_coordinates(0,yrange_min,&xg,&yg); 		
					cairo_move_to(cr,xg,yg);
					std::stringstream ss;
					ss << std::fixed << std::setprecision(2) << yrange_min;
					std::string numstring = ss.str();
					cairo_show_text(cr,numstring.c_str());
					cairo_line_to(cr, xg, yg);					
					get_canvas_coordinates(0,yrange_max,&xg,&yg); 		
					cairo_line_to(cr, xg, yg);
					cairo_move_to(cr,xg,yg);
					cairo_show_text(cr,std::to_string(yrange_max).c_str());
					
				}
				int n_ticks=5;
				if (timepoints.size()<n_ticks){
					n_ticks=timepoints.size();
				}
				int len_t=timepoints.size();
				int tick_stride=len_t/n_ticks;
				
				//x ticks
				for (int i=0;i<n_ticks;i++){
					get_canvas_coordinates(timepoints[i*tick_stride],yrange_min,&xg,&yg); 		
					cairo_move_to(cr,xg,yg);
					std::stringstream ss;
					ss << std::fixed << std::setprecision(2) << timepoints[i*tick_stride];
					std::string numstring = ss.str();
					cairo_show_text(cr,numstring.c_str());
				}	
				//y ticks
				tick_stride=(yrange_max-yrange_min)/n_ticks;;
				for (int i=0;i<n_ticks;i++){
					//std::cout<<datapoints[i*tick_stride*dim_data+max_column]<<"\n";
					get_canvas_coordinates(0,yrange_min+tick_stride*i,&xg,&yg); 		
					cairo_move_to(cr,xg,yg);
					std::stringstream ss;
					ss << std::fixed << std::setprecision(2) << yrange_min+tick_stride*i;
					std::string numstring = ss.str();
					cairo_show_text(cr,numstring.c_str());
				}							
				cairo_stroke(cr);
									
			}		
			
			void get_plotting_dimensions(const std::vector<double>& timepoints, const std::vector<double>& datapoints,bool* selected_dims,double& xrange_min, double& xrange_max, double& yrange_min, double& yrange_max, std::vector<double>* exp_timepoints, std::vector<double>* exp_datapoints){
				xrange_min=*std::min_element(timepoints.begin(), timepoints.end());
				xrange_max=*std::max_element(timepoints.begin(), timepoints.end());	
				
				int dim_data=datapoints.size()/timepoints.size();	
				yrange_min=std::numeric_limits<double>::max();
				yrange_max=-std::numeric_limits<double>::max();
				for (int j=0;j<dim_data;j++){
					if (selected_dims[j]==true){
						for (int i=0;i<timepoints.size();i++){
						double val=datapoints[i*dim_data+j];
							
							if (val>yrange_max){
								yrange_max=val;
							}
							if (val<yrange_min){
								yrange_min=val;
							}								
							
						}			
					}		
				}			
				if (exp_timepoints!=nullptr){
					double temp_min=*std::min_element((*exp_timepoints).begin(), (*exp_timepoints).end());
					double temp_max=*std::max_element((*exp_timepoints).begin(), (*exp_timepoints).end());
					
					if(temp_min<xrange_min){
						xrange_min=temp_min;
					}	
					if (temp_max>xrange_max){
						xrange_max=temp_max;
					}
					
					temp_min=*std::min_element((*exp_datapoints).begin(), (*exp_datapoints).end());
					temp_max=*std::max_element((*exp_datapoints).begin(), (*exp_datapoints).end());
					
					if(temp_min<yrange_min){
						yrange_min=temp_min;
					}	
					if (temp_max>yrange_max){
						yrange_max=temp_max;
					}
					
				
					
					
				}		
			}	
						
		}
			
		
	}
}
