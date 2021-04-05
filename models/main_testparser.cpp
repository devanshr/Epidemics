#include "../../ConstrainedOptimization/core/parameter_estimation.h"
#include<vector>
#include <iostream>
#include <string>


int main(){

	std::string dir="C:/Users/Annett/Desktop/Epidemics Git/testoptimization_pde/";
	co::EpidemicsPDEEvaluation<co::EFloat64,co::ConfigComputation::Local, co::ConfigOutput::File> evaluator(dir,"subset_target.lua", "subset_sim.lua");
	
	
	std::vector<double> times;
	std::vector<double> positions;
	std::vector<double> data;
	std::vector<int> selected_columns;
	co::utility::parse_csv_table_times_pde(dir, "subset_target.lua", data, positions,times,selected_columns);
	
	std::cout<<"selected columns\n";
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
	co::utility::parse_csv("C:/Users/Annett/Desktop/Epidemics Git/Output/gridmapping_output.txt", grid_world_coordinates,"\t");
	
	for (auto& x: grid_world_coordinates){
		std::cout<<x<<"\t";
	}
	
	//Parsing of simulated_data
	double current_time=0;
	double successor_time=0;
	int i=0;
	int index=0;
	std::vector<double> parsed_sim_times;
	while (true){
			std::string path="C:/Users/Annett/Desktop/Epidemics Git/Output/output"+std::to_string(i)+".txt";
			std::string path_successor="C:/Users/Annett/Desktop/Epidemics Git/Output/output"+std::to_string(i+1)+".txt";
			std::ifstream file(path_successor);
			
			//If file does not exist, exist loop
			if (file.fail()){
				break;
			}
			co::utility::parse_pde_time(path, current_time, "\t");
			co::utility::parse_pde_time(path_successor, successor_time, "\t");
			i++;
			std::cout<<"\n\nCurrent time of simulated data: "<<current_time<< "The successor time is:"<<successor_time<<"\n";	
			
			if ((current_time <=times[index]) && (successor_time > times[index])){
				parsed_sim_times.push_back(current_time);
				
				//Todo: Now parse the sim data with the right columns (think about offset)
				
				
				index++;
			}
	}
	
	std::cout<<"\n\nParsed sim times:\n";
	for (auto& x: parsed_sim_times){
		std::cout<<x<<"\t";
	}

}
