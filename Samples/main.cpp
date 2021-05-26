#include "../models/sir.h"
#include "../models/writer.h"
#include<vector>
#include <iostream>

/*
This function evaluates the SIR model and writes the output to file.
*/

int main(int argc, char *argv[]){

	double tau=0.356035567977659;
	double theta=4.14932000304998e-07;
	double alpha=4.95954479066937e-07;

	ug::epi::SIR<std::vector<double>> sir_model(alpha,tau,theta);
	
	std::vector<double> u0={753056,2714,0,72};
	double t_start=0;
	double t_end=42;

	auto result =sir_model.run(t_start,u0,t_end);
	auto timepoints=std::get<0>(result);
	auto data=std::get<1>(result);
	ug::epi::write_data(argv[0], "_test.txt", timepoints, data,sir_model.names);
}
