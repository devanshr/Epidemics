extern "C" G_MODULE_EXPORT void parameter_value_changed(GtkSpinButton *spin_button, gpointer user_data, int n)
{
    double val = gtk_spin_button_get_value(spin_button);
    //parameter_values[n]=val;
    //gtk_widget_queue_draw(GTK_WIDGET(gtk_builder_get_object(builder,"drawing_seird_optimized")));  
    //update_simulation();
}   


extern "C" G_MODULE_EXPORT void on_spin_alpha_value_changed(GtkSpinButton* button, gpointer* data)
{
    GtkSpinButton *_this = reinterpret_cast<GtkSpinButton*>(button);
    parameter_value_changed(button,data,0);
    printf("alpha\n");;
    }
