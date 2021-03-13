#include "seird_pde.h"
#include "writer.h"
#include<vector>
#include <iostream>

template<class T>
void set_radial_values(T& u0, typename T::value_type x_points, typename T::value_type y_points, typename T::value_type dimX, typename T::value_type dimY,typename T::value_type hx, typename T::value_type radius, typename T::value_type val,int current_dimension) {
	using F = typename T::value_type;
	for (int i = 0; i < x_points; i++) {
		for (int j = 0; j < y_points; j++) {
			F worldX = ((i + 1.0) / x_points) * dimX;
			F worldY = ((j + 1.0) / y_points) * dimY;
			int offset = current_dimension*x_points*y_points;
			F a = (worldX - 0.5 * dimX);
			F b = (worldY - 0.5 * dimY);
			F r = 0.1;
			if ((a * a + b * b) <= r) {
				u0[i * x_points + j+offset] = val;
			}
			else {
				u0[i * x_points + j+offset] = 0;
			}
		}

	}
}

template<class T>
T initial_values(typename T::value_type dimX, typename T::value_type dimY, typename T::value_type hx) {
	using F = typename T::value_type;

	size_t x_points = (dimX / hx) + 1;
	size_t y_points = (dimY / hx) + 1;

	size_t nVars = ((dimX / hx) + 1) * ((dimY / hx) + 1);
	std::vector<F> u0(nVars*5,F(0)); //number of vertices in discretization
	
	//Sets initial values for first dimension
	F r1 = 0.1;
	F v1 = 100;
	set_radial_values(u0, x_points, y_points, dimX, dimY, hx, r1, v1,0);

	//Sets initial values for second dimension
	F r2 = 100;
	F v2 = 20;
	set_radial_values(u0, x_points, y_points, dimX, dimY, hx, r2,v2, 1);


	return u0;
}

template<class T>
void print_initialvalues(const T& u,  typename T::value_type dimX, typename T::value_type dimY, typename T::value_type hx, int current_dimension) {	
	size_t x_points = (dimX / hx) + 1;
	size_t y_points = (dimY / hx) + 1;
	int offset = current_dimension * x_points * y_points;
	for (int i = 0; i < x_points; i++) {
		
		for (int j = 0; j < y_points; j++) {
			std::cout << u[i * x_points + j+offset]<< "\t";			
		}
		std::cout << "\n";	
	}	
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
	std::vector<double> u0 =  initial_values<std::vector<double>>(1, 1, 0.1);
	std::cout << "Initial values on the grid:" << "\n";
	for (int i = 0; i < 5; i++) {
		std::cout << "Initial values dimension: " << i << "\n";
		print_initialvalues(u0, 1, 1, 0.1, i);
		std::cout << "\n";
	}

	seird_model.change_step_size_spatial(0.1);
	seird_model.change_step_size_time(0.1);

	auto [timepoints, data] = seird_model.run(t_start, initial_values<std::vector<double>>, t_end);
}
