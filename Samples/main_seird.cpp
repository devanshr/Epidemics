#include "../models/seird.h"
#include "../models/writer.h"
#include<vector>
#include <iostream>

/*
This function evaluates the SEIRD model and writes the output to file.
*/

int main(int argc, char *argv[]){

	double alpha=4.95954479066937e-07;
	double kappa=0.356035567977659;
	double theta=4.14932000304998e-07;
	double qq=8;
	double pp=5;
	
	ug::epi::SEIRD<std::vector<double>> seird_model(alpha,kappa,theta,qq,pp);
	
	std::vector<double> u0={753056,2714,0,0,72}; // Inital Values: Susceptibles, Exposed, Infected, Recoverd, Deceased
	double t_start=0;
	double t_end=42;

	auto [timepoints, data]=seird_model.run_linear_implicit(t_start,u0,t_end);
	std::cout<<"Optimization done\n";
	ug::epi::write_data(argv[0], "_test.txt", timepoints, data,seird_model.names);
}
