#include "../../ConstrainedOptimization\\core\\parameter_estimation.h"
#include<vector>
#include <iostream>


int main(){

//std::string dir="C:/Users/devan/ug4/apps/testoptimization_pde/";
std::string dir="C:/Users/Annett/Desktop/Epidemics Git/testoptimization_pde/";
co::EpidemicsPDEEvaluation<co::EFloat64,co::ConfigComputation::Local, co::ConfigOutput::File> evaluator(dir,"subset_target.lua", "subset_sim.lua");
	

	std::vector<int> selected_dimensions_sim;
	std::vector<std::string> filenames;
	co::utility::parse_table_dim_pde(dir, "subset_sim.lua", selected_dimensions_sim, filenames);

	std::cout<<"\n\nselected dimensions simulation:\n";
	for (auto& x: selected_dimensions_sim){
		std::cout<<x<<"\t";
	}

	std::vector<double> times;
	std::vector<double> positions;
	std::vector<double> data;
	std::vector<int> selected_columns;
	co::utility::parse_csv_table_times_pde(dir, "subset_target.lua", data, positions,times,selected_columns);
	
	std::cout<<"\n\nselected columns\n"; // Choice from: 0 1 2 (3 4 5 6 7)
	for (auto &x:selected_columns){
		std::cout<<x<<"\t";
	}	
	
	std::cout<<"\n\nexp times\n";
	for (auto &x:times){
		std::cout<<x<<"\t";
	}
	
	std::cout<<"\n\nexp positions\n";
	for (auto &x:positions){
		std::cout<<x<<"\t";
	}


	std::cout<<"\n\nexp data\n";
	for (auto &x:data){
		std::cout<<x<<"\t";
	}	
	
	std::cout<<"\n\ngrid_world_coordinates\n";
	std::vector<double> grid_world_coordinates;
	co::utility::parse_csv(dir+"gridmapping_output.txt", grid_world_coordinates,"\t");
	
	for (auto& x: grid_world_coordinates){
		std::cout<<x<<"\t";
	}
	
	//Parsing of simulated_data
	double current_time=0;
	double successor_time=0;
	int i=0;
	int index=0;

	//collected sim data 
	std::vector<double> sim_data;
	//tmp vector
	std::vector<double> parsed_sim_times;
	while (true){
			std::string path=dir+"Output/output"+std::to_string(i)+".txt";
			std::string path_successor=dir+"Output/output"+std::to_string(i+1)+".txt";
			std::ifstream file(path_successor);
			std::vector<double> tmp;
		
			//If file does not exist, exist loop
			if (file.fail()){
				break;
			}

			co::utility::parse_pde_time(path, current_time, "\t");
			co::utility::parse_pde_time(path_successor, successor_time, "\t");
			i++;
			std::cout<<"\n\nCurrent time of simulated data: "<<current_time<< "  The successor time is:"<<successor_time<<"\n";	
			
			if ((current_time <=times[index]) && (successor_time > times[index])){
				parsed_sim_times.push_back(current_time);
				
				co::utility::parse_csv(path,tmp,"\t");

				int offset=grid_world_coordinates.size() / 2;

				for (int i = 0; i<selected_columns.size()-3;i++){
					for(int j=0;j<offset;j++){
						//std::cout<<j+offset*(selected_dimensions_sim[i])<<"\n";
						sim_data.push_back(tmp[j+offset*(selected_dimensions_sim[i])]);
					}
				}
				
				index++;
			}
	}
	std::cout<<"Simdata: "<<sim_data.size()<<"\n";
	for(auto x:sim_data) std::cout<< x<<"\t";


	std::cout<<"\n\nParsed sim times:\n";
	for (auto& x: parsed_sim_times){
		std::cout<<x<<"\t";
	}

	std::vector<double> filtered_data;
	co::utility::planar_grid_to_world(positions, grid_world_coordinates , sim_data, filtered_data, selected_columns.size()-3,parsed_sim_times.size());

	//std::cout<<counter3<<"\n";

	std::cout<<"Size of Exp data: "<< data.size()<<"\n";
	std::cout<<"Size of Sim data: "<< filtered_data.size()<<"\n";
			

}