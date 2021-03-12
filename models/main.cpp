#include "sir.h"
#include "writer.h"
#include<vector>
#include <iostream>


int main(){

	double tau=0.356035567977659;
	double theta=4.14932000304998e-07;
	double alpha=4.95954479066937e-07;

	ug::epi::SIR<std::vector<double>> sir_model(alpha,tau,theta);
	
	std::vector<double> u0={753056,2714,0,72};
	double t_start=0;
	double t_end=42;

	auto [timepoints, data] =sir_model.run(t_start,u0,t_end);

	ug::epi::write_data("C:/Users/Annett/Desktop/Epidemics/models/", "test.txt", timepoints, data,sir_model.names);
}
