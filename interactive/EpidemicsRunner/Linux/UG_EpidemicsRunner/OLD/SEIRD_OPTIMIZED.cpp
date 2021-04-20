#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
    GtkWidget       *spin_alpha;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "Glades/SEIRD_OPTIMIZED.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    // window_settings_gauss = GTK_WIDGET(gtk_builder_get_object(builder, "window_settings_gauss"));
    // spin_alpha = GTK_WIDGET(gtk_builder_get_object(builder, "spin_alpha"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    gtk_widget_show(window);                
    

    // gtk_widget_hide(spin_alpha);                
// -
//     float digits = ;
//     float value = ;
//     float min_value = ;
//     float max_value = ;
//     float step_increment = ;
//     float page_increment = ;
//     float page_size = ;

    int v_offset1=20;
    int h_offset1=20;

    //Create alpha input
    GtkWidget* label0 = GTK_WIDGET(gtk_builder_get_object(builder, "label_alpha"));
    GtkAdjustment *adjustment0;
    adjustment0 = gtk_adjustment_new (0.000003, 0.0, 1, 0.0000001, 0.1, 0.0);
    parameter_input_widget[0] = GTK_WIDGET(gtk_builder_get_object(builder, "spin_alpha"));
    gtk_grid_attach(GTK_GRID(widget),label0,0,0,1,1);                   
    gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[0],1,0,1,1);    
    g_signal_connect (GTK_SPIN_BUTTON(parameter_input_widget[0]), "value-changed",  G_CALLBACK (&alpha_value_changed_callback), this);  

    
    //Create Kappa input
    GtkWidget* label1= GTK_WIDGET(gtk_builder_get_object(builder, "label_kappa"));                
    GtkAdjustment *adjustment1;
    adjustment1 = gtk_adjustment_new (.1, 0.0, 1.0, 0.00001, 0.1, 0.0);                             
    parameter_input_widget[1]=GTK_WIDGET(gtk_builder_get_object(builder, "spin_kappa"));
    gtk_grid_attach(GTK_GRID(widget),label1,0,1,1,1);               
    gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[1],1,1,1,1);    
    g_signal_connect (GTK_SPIN_BUTTON(parameter_input_widget[1]), "value-changed",  G_CALLBACK (kappa_value_changed_callback), this);       

    
    //Create theta input
    GtkWidget* label2= GTK_WIDGET(gtk_builder_get_object(builder, "label_theta"));                
    GtkAdjustment *adjustment2;
    adjustment2 = gtk_adjustment_new (.01, 0.0, 1.0, 0.00001, 0.1, 0.0);                                
    parameter_input_widget[2]=GTK_WIDGET(gtk_builder_get_object(builder, "spin_theta"));
    gtk_grid_attach(GTK_GRID(widget),label2,0,2,1,1);               
    gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[2],1,2,1,1);
    g_signal_connect (GTK_SPIN_BUTTON(parameter_input_widget[2]), "value-changed",  G_CALLBACK (theta_value_changed_callback), this);       

    //Create qq input
    GtkWidget* label3= GTK_WIDGET(gtk_builder_get_object(builder, "label_qq"));                
    GtkAdjustment *adjustment3;
    adjustment3 = gtk_adjustment_new (1, 0.0, 100, 1, 0.1, 0.0);                                
    parameter_input_widget[3]=GTK_WIDGET(gtk_builder_get_object(builder, "spin_qq"));
    gtk_grid_attach(GTK_GRID(widget),label3,0,3,1,1);               
    gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[3],1,3,1,1);
    g_signal_connect (GTK_SPIN_BUTTON(parameter_input_widget[3]), "value-changed",  G_CALLBACK (qq_value_changed_callback), this);      
        
                                    
    //Create pp input
    GtkWidget* label4= GTK_WIDGET(gtk_builder_get_object(builder, "label_pp"));                
    GtkAdjustment *adjustment4;
    adjustment4 = gtk_adjustment_new (1, 0.0, 100.0, 1, 0.1, 0.0);                              
    parameter_input_widget[4]=GTK_WIDGET(gtk_builder_get_object(builder, "spin_pp"));
    gtk_grid_attach(GTK_GRID(widget),label4,0,4,1,1);               
    gtk_grid_attach(GTK_GRID(widget),parameter_input_widget[4],1,4,1,1);                                
    g_signal_connect (GTK_SPIN_BUTTON(parameter_input_widget[4]), "value-changed",  G_CALLBACK (pp_value_changed_callback), this);      
        
    //Create initial values
    
    //Initial Susceptibles
    GtkWidget* label5= GTK_WIDGET(gtk_builder_get_object(builder, "label_initial_susceptibles"));              
    GtkAdjustment *adjustment5;
    adjustment5 = gtk_adjustment_new (750000, 0.0, 1000000, 100, 0.1,0);                                
    initial_input_widget[0]=GTK_WIDGET(gtk_builder_get_object(builder, "spin_initial_susceptibles"));
    gtk_grid_attach(GTK_GRID(widget),label5,2,0,1,1);               
    gtk_grid_attach(GTK_GRID(widget),initial_input_widget[0],3,0,1,1);                              
    g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[0]), "value-changed",  G_CALLBACK (susceptibles_value_changed_callback), this);                          


    //Initial Exposed
    GtkWidget* label6= GTK_WIDGET(gtk_builder_get_object(builder, "label_initial_exposed"));              
    GtkAdjustment *adjustment6;
    adjustment6 = gtk_adjustment_new (70, 0.0, 1000000, 100, 0.1,0);                            
    initial_input_widget[1]=GTK_WIDGET(gtk_builder_get_object(builder, "spin_initial_exposed"));
    gtk_grid_attach(GTK_GRID(widget),label6,2,1,1,1);               
    gtk_grid_attach(GTK_GRID(widget),initial_input_widget[1],3,1,1,1);                              
    g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[1]), "value-changed",  G_CALLBACK (exposed_value_changed_callback), this);       


    //Initial Infected
    GtkWidget* label7= GTK_WIDGET(gtk_builder_get_object(builder, "label_initial_infected"));              
    GtkAdjustment *adjustment7;
    adjustment7 = gtk_adjustment_new (0, 0.0, 1000000, 100, 0.1,0);                         
    initial_input_widget[2]=GTK_WIDGET(gtk_builder_get_object(builder, "spin_initial_infected"));
    gtk_grid_attach(GTK_GRID(widget),label7,2,2,1,1);               
    gtk_grid_attach(GTK_GRID(widget),initial_input_widget[2],3,2,1,1);                              
    g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[2]), "value-changed",  G_CALLBACK (infected_value_changed_callback), this);      


    //Initial Recovered
    GtkWidget* label8= GTK_WIDGET(gtk_builder_get_object(builder, "label_initial_recovered"));              
    GtkAdjustment *adjustment8;
    adjustment8 = gtk_adjustment_new (0, 0.0, 1000000, 100, 0.1,0);                             
    initial_input_widget[3]=GTK_WIDGET(gtk_builder_get_object(builder, "spin_initial_recovered"));
    gtk_grid_attach(GTK_GRID(widget),label8,2,3,1,1);               
    gtk_grid_attach(GTK_GRID(widget),initial_input_widget[3],3,3,1,1);                              
    g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[3]), "value-changed",  G_CALLBACK (recovered_value_changed_callback), this);     


    //Initial Deaths
    GtkWidget* label9= GTK_WIDGET(gtk_builder_get_object(builder, "label_initial_deaths"));              
    GtkAdjustment *adjustment9;
    adjustment9 = gtk_adjustment_new (0, 0.0, 1000000, 100, 0.1,0);                         
    initial_input_widget[4]=GTK_WIDGET(gtk_builder_get_object(builder, "spin_initial_deaths"));
    gtk_grid_attach(GTK_GRID(widget),label9,2,4,1,1);               
    gtk_grid_attach(GTK_GRID(widget),initial_input_widget[4],3,4,1,1);                              
    g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[4]), "value-changed",  G_CALLBACK (deaths_value_changed_callback), this);        


    //t0
    GtkWidget* label10= GTK_WIDGET(gtk_builder_get_object(builder, "label_t_start"));             
    GtkAdjustment *adjustment10;
    adjustment10 = gtk_adjustment_new (0, -100000, 1000000, 1, 0.1,0);                      
    initial_input_widget[5]=GTK_WIDGET(gtk_builder_get_object(builder, "spin_t_start"));
    gtk_grid_attach(GTK_GRID(widget),label10,4,0,1,1);              
    gtk_grid_attach(GTK_GRID(widget),initial_input_widget[5],5,0,1,1);                              
    g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[5]), "value-changed",  G_CALLBACK (simstarttime_value_changed_callback), this);      

    //tend
    GtkWidget* label11= GTK_WIDGET(gtk_builder_get_object(builder, "label_t_end"));             
    GtkAdjustment *adjustment11;
    adjustment11 = gtk_adjustment_new (42, -10000, 1000000, 1, 0.1, 0.0);                               
    initial_input_widget[6]=GTK_WIDGET(gtk_builder_get_object(builder, "spin_t_end"));
    gtk_grid_attach(GTK_GRID(widget),label11,4,1,1,1);              
    gtk_grid_attach(GTK_GRID(widget),initial_input_widget[6],5,1,1,1);  
    g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[6]), "value-changed",  G_CALLBACK (simendtime_value_changed_callback), this);        

                                
    //stepsize h
    GtkWidget* label12= GTK_WIDGET(gtk_builder_get_object(builder, "label_rk4_stepsize"));             
    GtkAdjustment *adjustment12;
    adjustment12 = gtk_adjustment_new (0.1, 0.0, 1.0, 0.00001, 0.1, 0.0);                               
    initial_input_widget[7]=GTK_WIDGET(gtk_builder_get_object(builder, "spin_rk4_stepsize"));
    gtk_grid_attach(GTK_GRID(widget),label12,4,2,1,1);              
    gtk_grid_attach(GTK_GRID(widget),initial_input_widget[7],5,2,1,1);  
    g_signal_connect (GTK_SPIN_BUTTON(initial_input_widget[7]), "value-changed",  G_CALLBACK (h_value_changed_callback), this);     

    
                                        
    //Create graph
    
    drawing_widget = gtk_drawing_area_new ();
    gtk_widget_set_size_request (drawing_widget, 600, 600);             
    gtk_grid_attach(GTK_GRID(widget),drawing_widget,0,5,6,6);   
    g_signal_connect (G_OBJECT (drawing_widget), "draw",  G_CALLBACK (draw_callback), this);

    // //Initialize values
    // initialize_values();
    
    // //Initialize simulation
    // update_simulation();





    gtk_main();

    return 0;
}

// // called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();

}















