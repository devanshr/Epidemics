#include "../../ConstrainedOptimization/core/parameter_estimation.h"
#include<vector>
#include <iostream>


int main(){

	std::string dir="C:/Users/Annett/Desktop/Epidemics Git/testoptimization_pde/";
	co::EpidemicsPDEEvaluation<co::EFloat64,co::ConfigComputation::Local, co::ConfigOutput::File> evaluator(dir,"subset_target.lua", "subset_sim.lua");
	
	
	std::vector<double> times;
	std::vector<double> positions;
	std::vector<double> data;
	
	co::utility::parse_csv_table_times_pde(dir, "subset_target.lua", data, positions,times);
	
	std::cout<<"times\n";
	for (auto &x:times){
		std::cout<<x<<"\t";
	}
	
	std::cout<<"\n\npositions\n";
	for (auto &x:positions){
		std::cout<<x<<"\t";
	}


	std::cout<<"\n\ndata\n";
	for (auto &x:data){
		std::cout<<x<<"\t";
	}	
	
	std::cout<<"\n\ngrid_world_coordinates\n";
	std::vector<double> grid_world_coordinates;
	
	co::utility::parse_csv("C:/Users/Annett/Desktop/Epidemics Git/Output/gridmapping_output.txt", grid_world_coordinates,"\t");
	
	for (auto& x: grid_world_coordinates){
		std::cout<<x<<"\t";
	}
}
