#include "seird.h"
#include "writer.h"
#include<vector>
#include <iostream>


int main(){

	double alpha=4.95954479066937e-07;
	double kappa=0.356035567977659;
	double theta=4.14932000304998e-07;
	double qq=8;
	double pp=5;
	
	

	ug::epi::SEIRD<std::vector<double>> seird_model(alpha,kappa,theta,qq,pp);
	
	std::vector<double> u0={753056,2714,0,0,72};
	double t_start=0;
	double t_end=42;

	auto [timepoints, data] =seird_model.run(t_start,u0,t_end);

	ug::epi::write_data("/home/devanshr/gcsc/ug4/plugins/Epidemics/models/", "test.txt", timepoints, data,seird_model.names);
}
