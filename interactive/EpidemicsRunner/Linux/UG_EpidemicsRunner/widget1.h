#include <string>
#include <vector>
#include <iostream>
#include <gtk/gtk.h>
#include <cairo.h>


namespace ug{
	namespace epi{
		
		namespace util{
			enum class WidgetTab{
				Interactive,
				Optimization
			};
		}
		
#define WIDTH   640
#define HEIGHT  480

#define ZOOM_X  100.0
#define ZOOM_Y  100.0


gfloat f (gfloat x)
{
    return x*x;
}


	
gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data)
{
	/*
    guint width, height;
    GdkRGBA color;
    GtkStyleContext *context;

    context = gtk_widget_get_style_context (widget);
    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);
    
    gtk_render_background(context, cr, 0, 0, width, height);
    cairo_arc (cr, width/2.0, height/2.0, MIN (width, height) / 2.0, 0, 2 * G_PI);
    gtk_style_context_get_color (context, gtk_style_context_get_state (context), &color);
    gdk_cairo_set_source_rgba (cr, &color);
    gdk_cairo_set_source_rgba (cr, &color);
    cairo_fill (cr);
    */
    guint width, height;
    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);
    /*
    double height_world=5;
    double length_world=5;
      
    int glob_count=4;
    double dx=0.1;
    double x[5]={0,50,100,150};
    double y[5]={height,height-10,height-30,height-15};
    
		cairo_set_line_width(cr, 5);

	  int i, j;
	  for (i = 0; i < glob_count ; i++ ) {
		  for (j = 0; j <glob_count ; j++ ) {
			  cairo_move_to(cr, x[i], y[i]);
			  cairo_line_to(cr, x[j], y[j]);
		  }
	  }    
	  
	    cairo_stroke(cr);  
	    */
		return true;

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
				
				//Create Kappa input
				GtkWidget* label1=gtk_label_new(param_names[1].c_str());				
				GtkAdjustment *adjustment1;
				adjustment1 = gtk_adjustment_new (2.500, 0.0, 1.0, 0.00001, 0.1, 0.0);								
				parameter_input_widget[1]=gtk_spin_button_new (adjustment1, 0.000001, 9);
				gtk_grid_attach(GTK_GRID(widget),label1,0,1,1,1);				
				gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[1],1,1,1,1);	
				
				//Create theta input
				GtkWidget* label2=gtk_label_new(param_names[2].c_str());				
				GtkAdjustment *adjustment2;
				adjustment2 = gtk_adjustment_new (2.500, 0.0, 1.0, 0.00001, 0.1, 0.0);								
				parameter_input_widget[2]=gtk_spin_button_new (adjustment2, 0.000001, 9);
				gtk_grid_attach(GTK_GRID(widget),label2,0,2,1,1);				
				gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[2],1,2,1,1);
				
				//Create qq input
				GtkWidget* label3=gtk_label_new(param_names[3].c_str());				
				GtkAdjustment *adjustment3;
				adjustment3 = gtk_adjustment_new (2.500, 0.0, 1.0, 0.00001, 0.1, 0.0);								
				parameter_input_widget[3]=gtk_spin_button_new (adjustment3, 0.000001, 9);
				gtk_grid_attach(GTK_GRID(widget),label3,0,3,1,1);				
				gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[3],1,3,1,1);
				
												
				//Create pp input
				GtkWidget* label4=gtk_label_new(param_names[4].c_str());				
				GtkAdjustment *adjustment4;
				adjustment4 = gtk_adjustment_new (2.500, 0.0, 1.0, 0.00001, 0.1, 0.0);								
				parameter_input_widget[4]=gtk_spin_button_new (adjustment4, 0.000001, 9);
				gtk_grid_attach(GTK_GRID(widget),label4,0,4,1,1);				
				gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[4],1,4,1,1);								
				
				//Create initial values
				
				//Initial Susceptibles
				GtkWidget* label5=gtk_label_new(initial_names[0].c_str());				
				GtkAdjustment *adjustment5;
				adjustment5 = gtk_adjustment_new (100, 0.0, 1000000, 100, 0.1,0);								
				initial_input_widget[0]=gtk_spin_button_new (adjustment5, 1000, 0);
				gtk_grid_attach(GTK_GRID(widget),label5,2,0,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[0],3,0,1,1);								

				//Initial Exposed
				GtkWidget* label6=gtk_label_new(initial_names[1].c_str());				
				GtkAdjustment *adjustment6;
				adjustment6 = gtk_adjustment_new (100, 0.0, 1000000, 100, 0.1,0);							
				initial_input_widget[1]=gtk_spin_button_new (adjustment6, 1000, 0);
				gtk_grid_attach(GTK_GRID(widget),label6,2,1,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[1],3,1,1,1);								
	
				//Initial Infected
				GtkWidget* label7=gtk_label_new(initial_names[2].c_str());				
				GtkAdjustment *adjustment7;
				adjustment7 = gtk_adjustment_new (100, 0.0, 1000000, 100, 0.1,0);							
				initial_input_widget[2]=gtk_spin_button_new (adjustment7, 1000, 0);
				gtk_grid_attach(GTK_GRID(widget),label7,2,2,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[2],3,2,1,1);								
	
				//Initial Recovered
				GtkWidget* label8=gtk_label_new(initial_names[3].c_str());				
				GtkAdjustment *adjustment8;
				adjustment8 = gtk_adjustment_new (100, 0.0, 1000000, 100, 0.1,0);								
				initial_input_widget[3]=gtk_spin_button_new (adjustment8, 1000, 0);
				gtk_grid_attach(GTK_GRID(widget),label8,2,3,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[3],3,3,1,1);								
	
				//Initial Deaths
				GtkWidget* label9=gtk_label_new(initial_names[4].c_str());				
				GtkAdjustment *adjustment9;
				adjustment9 = gtk_adjustment_new (100, 0.0, 1000000, 100, 0.1,0);							
				initial_input_widget[4]=gtk_spin_button_new (adjustment9, 1000, 0);
				gtk_grid_attach(GTK_GRID(widget),label9,2,4,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[4],3,4,1,1);								

				//t0
				GtkWidget* label10=gtk_label_new(initial_names[5].c_str());				
				GtkAdjustment *adjustment10;
				adjustment10 = gtk_adjustment_new (0, -100000, 1000000, 1, 0.1,0);						
				initial_input_widget[5]=gtk_spin_button_new (adjustment10, 0.1, 2);
				gtk_grid_attach(GTK_GRID(widget),label10,4,0,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[5],5,0,1,1);								
	
				//tend
				GtkWidget* label11=gtk_label_new(initial_names[6].c_str());				
				GtkAdjustment *adjustment11;
				adjustment11 = gtk_adjustment_new (42, -10000, 1000000, 1, 0.1, 0.0);								
				initial_input_widget[6]=gtk_spin_button_new (adjustment11, 0.1, 2);
				gtk_grid_attach(GTK_GRID(widget),label11,4,1,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[6],5,1,1,1);	
				
											
				//stepsize h
				GtkWidget* label12=gtk_label_new(initial_names[7].c_str());				
				GtkAdjustment *adjustment12;
				adjustment12 = gtk_adjustment_new (2.500, 0.0, 1.0, 0.00001, 0.1, 0.0);								
				initial_input_widget[7]=gtk_spin_button_new (adjustment12, 0.000001, 9);
				gtk_grid_attach(GTK_GRID(widget),label12,4,2,1,1);				
				gtk_grid_attach(GTK_GRID(widget),initial_input_widget[7],5,2,1,1);	
				
															


				//Create graph
				
				drawing_widget = gtk_drawing_area_new ();
				gtk_widget_set_size_request (drawing_widget, 600, 600);				
				gtk_grid_attach(GTK_GRID(widget),drawing_widget,0,5,3,3);	
				
				plot_values();
				
			//	draw_callback(da, cairo_t *cr, gpointer data);
			//	g_signal_connect (G_OBJECT (da), "draw",  G_CALLBACK (draw_callback), NULL);										
				
				/*


				//Create graph
				
				GtkWidget* da = gtk_drawing_area_new ();
				gtk_widget_set_size_request (da, 600, 600);				
				gtk_box_pack_end(GTK_BOX(widget),da,10,10,0);
				g_signal_connect (G_OBJECT (da), "draw",  G_CALLBACK (draw_callback), NULL);			
            */
            //gtk_widget_queue_draw (plot);	
				
			}
			
			double parameter_values[5]={0,0,0,0,0};
			double initial_values[5]={0,0,0,0,0};
			
			double& alpha=parameter_values[0];
			double& kappa=parameter_values[1];
			double& theta=parameter_values[2];
			double& qq=parameter_values[3];
			double& pp=parameter_values[4];
			double h=0.01;
			std::vector<std::string> param_names={"alpha","kappa","theta","qq","pp"};	
			std::vector<std::string> initial_names={"Initial Susceptibles","Initial Exposed","Initial Infected","Initial Recovered","Initial Deaths","Simulation Starttime","Simulation Endtime","RK4 Stepsize h"};				
			std::vector<GtkWidget*> parameter_input_widget=std::vector<GtkWidget*>(5);
			std::vector<GtkWidget*> initial_input_widget=std::vector<GtkWidget*>(5);
			GtkWidget* drawing_widget;

			void parameter_value_changed(GtkSpinButton *spin_button,GtkScrollType  scroll, gpointer user_data, int n) {
				
				  g_print("clicked\n");
				  std::cout<<"hey\n";
			}	

			static void alpha_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
			//	alpha=gtk_spin_button_get_value(button);
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
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
			
			static void h_value_changed_callback(GtkSpinButton* button, GtkScrollType  scroll, gpointer* data) {
					 SEIRDWidget<util::WidgetTab::Interactive>* _this = reinterpret_cast<SEIRDWidget<util::WidgetTab::Interactive>*>(data);
					// _this->parameter_value_changed(button, scroll,data,0);
			}				
							
			double numeric_input(GtkSpinButton *button,
							gpointer       user_data)
			{
			  return gtk_spin_button_get_value(button);
			}
			
			void plot_values(){
				cairo_t* cr;	
				
				guint width, height;
				width = gtk_widget_get_allocated_width (drawing_widget);
				height = gtk_widget_get_allocated_height (drawing_widget);
			/*	
				double height_world=5;
				double length_world=5;
				  
				int glob_count=4;
				double dx=0.1;
				double x[5]={0,50,500,550};
				double y[5]={height,height-10,500,500};
				
					cairo_set_line_width(cr, 5);

				  int i, j;
				  for (i = 0; i < glob_count ; i++ ) {
					  for (j = 0; j <glob_count ; j++ ) {
						  cairo_move_to(cr, x[i], y[i]);
						  cairo_line_to(cr, x[j], y[j]);
					  }
				  }    
				  
					cairo_stroke(cr);  
								*/
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
