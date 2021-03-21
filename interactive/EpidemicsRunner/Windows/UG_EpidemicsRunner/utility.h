#pragma once
#include <vector>
#include <string>
#include <fstream>

namespace ug {
	namespace epi {


		void create_evaluate_lua(std::string path, std::string textbody, std::vector<std::string>& names_of_constants,std::vector<double>& values_of_constants, std::vector<std::string>& names_of_variables, std::vector<std::string>& names_of_inits, std::vector<double>& values_of_inits) {

			std::ofstream lua_output;
			std::ofstream general_output;
			lua_output.open(path + "evaluate.lua");

			lua_output << R"(PrintBuildConfiguration()
ug_load_script("ug_util.lua")

-----------------------------------------------------------------
-- define Home-Directories
----------------------------------------------------------------
ug4_home        = ug_get_root_path().."/"
common_scripts  = app_home.."scripts/"
geom_home       = app_home.."geometry/"

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

		/*Loads csv data and displays it on a chart*/
		template<class E>
		void load_csv_data_on_click(E obj, int number_of_prior_plotted_lines){
			System::Windows::Forms::OpenFileDialog fileDialog;
			System::IO::Stream^ win_stream;
			fileDialog.Title = L"Open Experimental Data";
			fileDialog.Filter = "TXT files|*.txt";

			//Remove old plots of experimental data
			if (obj->user_datapoints != nullptr && obj->user_names != nullptr && obj->user_cols != nullptr) {

				for (int i = 0; i < obj->user_names->size() - 1; i++) {
					obj->chart1->Series->RemoveAt(number_of_prior_plotted_lines);
				}
			}

			if (obj->user_datapoints != nullptr) {
				delete obj->user_datapoints;
			}
			if (obj->user_names != nullptr) {
				delete obj->user_names;
			}
			if (obj->user_cols != nullptr) {
				delete obj->user_cols;
			}
			obj->user_datapoints = new std::vector<double>;
			obj->user_names = new std::vector<std::string>;
			obj->user_cols = new int(0);
			co::ErrorCode err;
			if (fileDialog.ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				try {
					win_stream = fileDialog.OpenFile();
					if (win_stream != nullptr) {
						auto str = win_stream->ToString();
						str = fileDialog.FileName->ToString();
						std::string file_location = msclr::interop::marshal_as<std::string>(str);
						err = co::utility::parse_csv_names<double, std::vector<double>*, std::vector<std::string>*>(file_location, obj->user_datapoints, obj->user_names, "", obj->user_cols);
					}

				}
				catch (System::Exception^ e) {
					MessageBox::Show(L"Error: Could not read file." + e);
				}

				if (err != co::ErrorCode::NoError) {

					MessageBox::Show(L"The input file has the wrong data layout. It must be comma or tab separated. In addition, the first line must start with a # and indicate the column names.");
				}
				else {
					if (obj->user_datapoints != nullptr && obj->user_names != nullptr && obj->user_cols != nullptr) {
						for (int i = 1; i < obj->user_names->size(); i++) {
							System::Windows::Forms::DataVisualization::Charting::Series^ seriesExp = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
							obj->chart1->Series->Add(seriesExp);
							seriesExp->ChartArea = L"ChartArea1";
							seriesExp->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
							seriesExp->Legend = L"Legend1";
							//	seriesExp->ShadowColor = System::Drawing::Color::Pink;
							auto var = gcnew String((*(obj->user_names))[i].c_str());
							seriesExp->Name = var;
						}
					}
				}

			}
		}
	}


}