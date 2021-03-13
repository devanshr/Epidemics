#include "seird_pde.h"
#include "writer.h"
#include<vector>
#include <iostream>


template<class T>
T initial_values(typename T::value_type dimX, typename T::value_type dimY, typename T::value_type hx) {
	using F = typename T::value_type;

	size_t x_points = (dimX / hx) + 1;
	size_t y_points = (dimY / hx) + 1;

	size_t nVars = ((dimX / hx) + 1) * ((dimY / hx) + 1);
	std::vector<F> u0(nVars*5,F(0)); //number of vertices in discretization
/*
	F radius = 0.5;
	for (int i = 0; i < x_points; i++) {
		for (int j = 0; j < y_points; j++) {
			F worldX = ((i + 1) / x_points)*dimX;
			F worldY = ((j + 1) / y_points) * dimY;

			F a = (worldX - 0.5 * dimX);
			F b = (worldY - 0.5 * dimY);
			F r = 0.5;
			if ((a*b+b*b) <= r) {
				//u0[i*x_points]
			}
		}
		
	}
*/
	return u0;

}


int main() {

	double alpha = 4.95954479066937e-07;
	double kappa = 0.356035567977659;
	double theta = 4.14932000304998e-07;
	double sigma = 0.1;
	double rho = 0.1;



	ug::epi::SEIRD<std::vector<double>,ug::epi::seird::Geometry::Plane> seird_model(alpha, kappa, theta, sigma,rho);

//	std::vector<double> u0 = { 753056,2714,0,0,72 };
//	std::vector<double> u0 = { 753056,2714,0,0,72 };
	double t_start = 0;
	double t_end = 42;

	//auto [timepoints, data] = seird_model.run(t_start, u0, t_end);
}
