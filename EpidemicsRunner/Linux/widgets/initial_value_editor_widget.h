#pragma once
#include "../../../models/seird_pde.h"

namespace ug{
	namespace epi{
		
		template<ug::epi::seird::Geometry G>
		class Editor{
			
		};
		
		template<>
		class Editor<ug::epi::seird::Geometry::Plane>{
			private:
			
			GtkBuilder *builder;
			GtkWidget* main_widget; //main widget
			GtkWidget* name_widget=gtk_label_new("Initial Value Editor");		
				
			void initialize_widget(){

				builder = gtk_builder_new_from_file("glades/initial_value_editor.glade");

				main_widget = GTK_WIDGET(gtk_builder_get_object(builder,"grid_main_initial_value_editor"));

				glade_widgets->editor_object=this;
				gtk_builder_connect_signals(builder, glade_widgets);
			}
			
			
			
			void initialize_values(){
		
				
			}
			
			
			public:
			Editor()
			{
			}
			
			void save_map() const;
			
			void load_map();
			/* This struct is given to a glade builder to automatically connect signals.
			The members need to have the same name as the "name" property in the glade files*/
			struct app_widgets{
               
                
				Editor<ug::epi::seird::Geometry::Plane>* editor_object;
			};
			
			app_widgets* glade_widgets;	
			
			GtkWidget* get_widget() const{
				return main_widget;
			}
			GtkWidget* get_name() const{
				return name_widget;
			}
			
			
		};
		
		extern "C" G_MODULE_EXPORT void on_drawing_initial_value_editor_map_window(GtkWidget *widget, gpointer* data)
		{      
		//	Editor::app_widgets* glade_widgets= reinterpret_cast<Editor::app_widgets*>(data);
		//	Editor* editor_object=glade_widgets->editor_object;
			//seird_pde_object->optimization_details(seird_pde_object);
			
		}	
	}
}
