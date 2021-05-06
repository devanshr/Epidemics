#pragma once
#include <algorithm>
#include <gtk/gtk.h>
#include <cairo.h>

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
			
			for (int i = 0; i < names_of_inits.size(); i++) {
				lua_output << names_of_inits[i] << "=" << values_of_inits[i] << "\n";
			}
			
			for (int i = 0; i < names_of_constants.size(); i++) {
				lua_output << names_of_constants[i] << "=" << values_of_constants[i] << "\n";
			}

			for (int i = 0; i < names_of_variables.size(); i++) {
				lua_output << names_of_variables[i] << "=parameters."<<names_of_variables[i]<<":get_value_as_double()\n";
			}
			
			lua_output << textbody;

			lua_output.close();

		}

		// /*Loads csv data and displays it on a chart*/
		// template<class E>
		// void load_csv_data_on_click(E obj, int number_of_prior_plotted_lines)
		// {
		// 	System::Windows::Forms::OpenFileDialog fileDialog;
		// 	System::IO::Stream^ win_stream;
		// 	fileDialog.Title = L"Open Experimental Data";
		// 	fileDialog.Filter = "TXT files|*.txt";

		// 	//Remove old plots of experimental data
		// 	if (obj->user_datapoints != nullptr && obj->user_names != nullptr && obj->user_cols != nullptr) {

		// 		for (int i = 0; i < obj->user_names->size() - 1; i++) {
		// 			obj->chart1->Series->RemoveAt(number_of_prior_plotted_lines);
		// 		}
		// 	}

		// 	if (obj->user_datapoints != nullptr) {
		// 		delete obj->user_datapoints;
		// 	}
		// 	if (obj->user_names != nullptr) {
		// 		delete obj->user_names;
		// 	}
		// 	if (obj->user_cols != nullptr) {
		// 		delete obj->user_cols;
		// 	}
		// 	obj->user_datapoints = new std::vector<double>;
		// 	obj->user_names = new std::vector<std::string>;
		// 	obj->user_cols = new int(0);
		// 	co::ErrorCode err;
		// 	if (fileDialog.ShowDialog() == System::Windows::Forms::DialogResult::OK) 
		// 	{
		// 		try {
		// 			win_stream = fileDialog.OpenFile();
		// 			if (win_stream != nullptr) {
		// 				auto str = win_stream->ToString();
		// 				str = fileDialog.FileName->ToString();
		// 				std::string file_location = msclr::interop::marshal_as<std::string>(str);
		// 				err = co::utility::parse_csv_names<double, std::vector<double>*, std::vector<std::string>*>(file_location, obj->user_datapoints, obj->user_names, "", obj->user_cols);
		// 			}

		// 		}
		// 		catch (System::Exception^ e) {
		// 			MessageBox::Show(L"Error: Could not read file." + e);
		// 		}

		// 		if (err != co::ErrorCode::NoError) {

		// 			MessageBox::Show(L"The input file has the wrong data layout. It must be comma or tab separated. In addition, the first line must start with a # and indicate the column names.");
		// 		}
		// 		else
		// 		{
		// 			if (obj->user_datapoints != nullptr && obj->user_names != nullptr && obj->user_cols != nullptr)
		// 			{
		// 				for (int i = 1; i < obj->user_names->size(); i++)
		// 				{
		// 					System::Windows::Forms::DataVisualization::Charting::Series^ seriesExp = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		// 					obj->chart1->Series->Add(seriesExp);
		// 					seriesExp->ChartArea = L"ChartArea1";
		// 					seriesExp->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
		// 					seriesExp->Legend = L"Legend1";
		// 					//	seriesExp->ShadowColor = System::Drawing::Color::Pink;
		// 					auto var = gcnew String((*(obj->user_names))[i].c_str());
		// 					seriesExp->Name = var;
		// 				}
		// 			}
		// 		}

		// 	}
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
				int len_t=timepoints.size();
				int tick_stride=len_t/n_ticks;
				
				//x ticks
				for (int i=0;i<n_ticks;i++){
					get_canvas_coordinates(timepoints[i*tick_stride],yrange_min,&xg,&yg); 		
					cairo_move_to(cr,xg,yg);
					cairo_show_text(cr,std::to_string(timepoints[i*tick_stride]).c_str());
				}	
				//y ticks
				int max_column=0; //datacolumn that contains highest value
				tick_stride=(yrange_max-yrange_min)/n_ticks;;
				for (int i=0;i<n_ticks;i++){
					//std::cout<<datapoints[i*tick_stride*dim_data+max_column]<<"\n";
					get_canvas_coordinates(0,yrange_min+tick_stride*i,&xg,&yg); 		
					cairo_move_to(cr,xg,yg);
					cairo_show_text(cr,std::to_string(yrange_min+tick_stride*i).c_str());
				}							
				cairo_stroke(cr);
									
			}				
						
		}
			
		
	}
}
