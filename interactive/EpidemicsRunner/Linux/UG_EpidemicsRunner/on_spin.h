
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