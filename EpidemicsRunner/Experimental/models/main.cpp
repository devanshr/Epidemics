#include "seird.h"
#include<vector>

int main(){
	double alpha=4.95954479066937e-07;
	double kappa=0.356035567977659;
	double theta=4.14932000304998e-07;
	double qq=8;
	double pp=5;

	
	epi::SEIRD<double> seird_model(alpha,kappa,theta,qq,pp);
	
	double u0[5]={753056,2714,0,0,72};
	double t0=0;
	double tend=42;
	
	std::vector<double> u;
	std::vector<double> t;
	
	seird_model.run_linear_implicit(t0, u0, tend, t, u);
	
	
}