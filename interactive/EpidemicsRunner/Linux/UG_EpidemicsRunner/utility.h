#pragma once
#include <algorithm>
#include <gtk/gtk.h>
#include <cairo.h>

namespace ug{	
	namespace epi{
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
								
							
				double height_world=5;
				double length_world=5;
				  

				double xg;
				double yg;
				
				cairo_set_line_width(cr, 2);				
			//	std::cout<<"drin\n";
				
				for (int i = 0; i < timepoints.size() ; i++ ) {
					get_canvas_coordinates(timepoints[i],datapoints[i*dim_data+selected_dim],&xg,&yg);  
					//std::cout<<xg<<"  "<<yg<<"\n";
					cairo_line_to(cr, xg, yg);
				}   
				
				cairo_stroke(cr);
									
			}
			void plot_axis(GtkWidget* _drawing_widget,cairo_t* cr,const std::vector<double>& timepoints, const std::vector<double>& datapoints){
				cairo_set_source_rgb(cr,0.0, 0.0, 0.0);
				
				int dim_data=datapoints.size()/timepoints.size();
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
								
							
				double height_world=5;
				double length_world=5;
				  
				double xg;
				double yg;
				
				//x axis
				cairo_set_line_width(cr, 2);				

				if (yrange_max>=0){
					get_canvas_coordinates(timepoints[0],0.0,&xg,&yg); 		
					cairo_line_to(cr, xg, yg);					
					get_canvas_coordinates(timepoints[timepoints.size()-1],0.0,&xg,&yg); 		
					cairo_line_to(cr, xg, yg);						
				}
				//y axis
				if (xrange_min <= 0){
					get_canvas_coordinates(0,yrange_min,&xg,&yg); 		
					cairo_move_to(cr,xg,yg);
					cairo_line_to(cr, xg, yg);					
					get_canvas_coordinates(0,yrange_max,&xg,&yg); 		
					cairo_line_to(cr, xg, yg);

				}
	
				
				cairo_stroke(cr);
									
			}				
						
		}
			
		
	}
}
