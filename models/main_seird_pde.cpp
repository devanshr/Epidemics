#include "seird_pde.h"
#include "writer.h"
#include<vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>

template<class T>
void set_radial_values(T& u0, typename T::value_type x_points, typename T::value_type y_points, typename T::value_type dimX, typename T::value_type dimY,typename T::value_type hx, typename T::value_type radius, typename T::value_type val,int current_dimension) {
	using F = typename T::value_type;
	for (int i = 0; i < y_points; i++) {
		for (int j = 0; j < x_points; j++) {
			F worldX =dimY- ((i) / (y_points-1.0)) * dimY;
			F worldY = ((j) / (x_points-1.0)) * dimX;
			int offset = current_dimension*x_points*y_points;
			F a = (worldX - 0.5 * dimX);
			F b = (worldY - 0.5 * dimY);
			F r = 0.2;
			if ((a * a + b * b) <= r*r) {
				u0[i * x_points + j+offset] = val;
			}
			else {
				u0[i * x_points + j+offset] = 0;
			}
		}

	}
}


template<class T>
void set_gaussian_values(T& u0, typename T::value_type x_points, typename T::value_type y_points, typename T::value_type dimX, typename T::value_type dimY,typename T::value_type hx, typename T::value_type radius, typename T::value_type val,int current_dimension) {
	using F = typename T::value_type;
	for (int i = 0; i < y_points; i++) {
		for (int j = 0; j < x_points; j++) {
			F worldX =dimY- ((i) / (y_points-1.0)) * dimY;
			F worldY = ((j) / (x_points-1.0)) * dimX;
			int offset = current_dimension*x_points*y_points;
			
			
			F a = (worldX - 0.5 * dimX);
			F b = (worldY - 0.5 * dimY);
			F sigma=1;
			F x=(a * a + b * b);
			u0[i * x_points + j+offset] = val*std::exp(-sigma*x);
			
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
	set_gaussian_values(u0, x_points, y_points, dimX, dimY, hx, r1, v1,0);

	//Sets initial values for second dimension
	F r2 = 100;
	F v2 = 20;
	set_gaussian_values(u0, x_points, y_points, dimX, dimY, hx, r2,v2, 1);


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


void image_to_grid(int index_image_i, int index_image_j, int image_width, int image_height, int grid_width, int grid_height, int& i_g, int& j_g){
	float ratio_i=index_image_i/(image_width-1.0);
	float ratio_j=index_image_j/(image_height-1.0);	

	i_g=ratio_i*(grid_width-1);
	j_g=ratio_j*(grid_height-1);
}

void determine_color(double val, double min_val, double max_val, int& r, int& g, int& b){
	float ratio=(val-min_val)/(max_val-min_val);
	//std::cout<<"val:"<<val-min_val<<"\n";
	int start_r=0;
	int start_g=0;
	int start_b=0;

	r=start_r+(255-start_r)*ratio;
	g=start_g+(255-start_g)*ratio;	
	b=start_b+(255-start_b)*ratio;
}

int main() {

	double alpha = 4.95954479066937e-07;
	double kappa = 0.356035567977659;
	double theta = 4.14932000304998e-07;
	double sigma = 0.1;
	double rho = 0.1;
	double diffusion=0; //if turned to one, finite difference approximation gives errors. probably boundary conditions needed 
	ug::epi::SEIRD<std::vector<double>,ug::epi::seird::Geometry::Plane> seird_model(alpha, kappa, theta, sigma,rho,diffusion);

	double t_start = 0;
	double t_end = 42;
	double h=0.01;
	std::vector<double> u0 =  initial_values<std::vector<double>>(1, 1, h);
	std::cout << "Initial values on the grid:" << "\n";
	for (int i = 0; i < 5; i++) {
		std::cout << "Initial values dimension: " << i << "\n";
		print_initialvalues(u0, 1, 1, h, i);
		std::cout << "\n";
	}

	seird_model.change_step_size_spatial(h);
	seird_model.change_step_size_time(h);

	std::vector<double> heatvals;
	double min_val=*std::min_element(u0.begin(),u0.end());
	double max_val=*std::max_element(u0.begin(),u0.end());

	for (int i=0;i<u0.size();i++){
		int r;
		int g;
		int b;
		determine_color(u0[i],min_val,max_val,r,g,b);
		heatvals.push_back(r);
	}

	std::cout<<"Heatmap vals\n";

	for (int i = 0; i < 5; i++) {
		std::cout << "Initial values dimension: " << i << "\n";
		print_initialvalues(heatvals, 1, 1, h, i);
		std::cout << "\n";
	}



	std::string filepath="C:/Users/Annett/Desktop/Epidemics Git/Output/";

	std::string filename="output";
			
	seird_model.set_store_to_file(true,filepath,filename);


	auto [timepoints, data] = seird_model.run(t_start, u0, t_end);

}
