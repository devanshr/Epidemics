/*! \mainpage Epidemics Plugin for UG4
 *
 * \section intro_sec Overview
 *
 *The Epidemics plugin consists of various algorithms used in epidemics modeling.
 *This manual was created in April 2021 for version number 0.3


 */

/** \file epidemics.h
 * This file is used if the optimization functions are indirectly called.
 * Indirectly means that the user only passes secondary information like path, options and
 * shell commands instead of directly calling the model functions.
 */

#pragma once
#include "sir.h"
#include "seird.h"
#include "seird_pde.h"
#include "writer.h"

namespace ug{
	namespace epi{
		
			constexpr int version_number=0.3;//change if you update your Epidemics version
			
template<seird::Geometry T, class F>
			class InitialValueManager{
			};
			
			template<class F>
			class InitialValueManager<seird::Geometry::Plane,F>{
				
				F r1=10;
				F r2=10;
				F r3=10;
				F r4=10;
				F r5=10;
				
				F v1=10;
				F v2=10;
				F v3=10;
				F v4=10;
				F v5=10;
				
				F hx=0.1;
				F ht=0.1;
				F t_start=0;
				F t_end=5;
				
				F dimX=1.0;
				F dimY=1.0;

				std::vector<F> u0 = {};
				
				public:
				InitialValueManager<ug::epi::seird::Geometry::Plane,F>(){
					
				}
				
				F get_r1() const{
					return r1;
				}
								
				void set_r1(F _val){
					r1=_val;
				}
				F get_r2() const{
					return r2;
				}
								
				void set_r2(F _val){
					r2=_val;
				}
				
				F get_r3() const{
					return r3;
				}
								
				void set_r3(F _val){
					r3=_val;
				}
				F get_r4() const{
					return r4;
				}
								
				void set_r4(F _val){
					r4=_val;
				}
				F get_r5() const{
					return r5;
				}
								
				void set_r5(F _val){
					r5=_val;
				}
				F get_v1() const{
					return v1;
				}
								
				void set_v1(F _val){
					v1=_val;
				}
				F get_v2() const{
					return v2;
				}
								
				void set_v2(F _val){
					v2=_val;
				}
				F get_v3() const{
					return v3;
				}							
				void set_v3(F _val){
					v3=_val;
				}
				F get_v4() const{
					return v4;
				}							
				void set_v4(F _val){
					v4=_val;
				}		
				F get_v5() const{
					return v5;
				}						
				void set_v5(F _val){
					v5=_val;
				}	
				F get_hx() const{
					return hx;
				}						
				F get_ht() const{
					return ht;
				}						
				void set_hx(F _val){
					hx=_val;
				}	
				void set_ht(F _val){
					ht=_val;
				}	
				F get_t_start() const{
					return t_start;
				}						
				void set_t_start(F _val){
					t_start=_val;
				}		
				F get_t_end() const{
					return t_end;
				}						
				void set_t_end(F _val){
					t_end=_val;
				}		

				F get_dimX() const{
					return dimX;
				}
				
				F get_dimY() const{
					return dimY;
					
				}

				std::vector<F> get_u0() const{
					return u0;
				}
				
				void set_u0(std::vector<F> _u0){
					u0 = _u0;
				}


			};

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
						F sigma=radius;
						F x=(a * a + b * b);
						u0[i * x_points + j+offset] = val*std::exp(-sigma*x);

					}

				}
			}

			template<class T>
			T initial_values(InitialValueManager<seird::Geometry::Plane,typename T::value_type>& initial_manager) {
				using F = typename T::value_type;
				
				F dimX=initial_manager.get_dimX();
				F dimY=initial_manager.get_dimY();
				
				F hx=initial_manager.get_hx();

				size_t x_points = static_cast<int>(std::ceil(dimX / hx) + 1);
				size_t y_points = static_cast<int>(std::ceil(dimY / hx) + 1);

				size_t nVars = static_cast<int>(std::ceil(dimX / hx) + 1)* static_cast<int>(std::ceil(dimY / hx) + 1);
				std::vector<F> u0(nVars*5,F(0)); //number of vertices in discretization

				//Sets initial values for first dimension
				F r1 = initial_manager.get_r1();
				F v1 = initial_manager.get_v1();
				set_gaussian_values(u0, x_points, y_points, dimX, dimY, hx, r1, v1,0);

				//Sets initial values for second dimension
				F r2 = initial_manager.get_r2();
				F v2 = initial_manager.get_v2();
				set_gaussian_values(u0, x_points, y_points, dimX, dimY, hx, r2,v2, 1);

				F r3 = initial_manager.get_r3();
				F v3 = initial_manager.get_v3();
				set_gaussian_values(u0, x_points, y_points, dimX, dimY, hx, r3,v3, 2);

				F r4 = initial_manager.get_r4();
				F v4 = initial_manager.get_v4();
				set_gaussian_values(u0, x_points, y_points, dimX, dimY, hx, r4,v4, 3);

				F r5 = initial_manager.get_r5();
				F v5 = initial_manager.get_v5();
				set_gaussian_values(u0, x_points, y_points, dimX, dimY, hx, r5,v5, 4);



				// continue with r3,r4,v3,v4, etc.
				return u0;
			}
			
	
			void RunSIR(ug::epi::SIR<std::vector<double>>& sir_model,std::string path, std::string name, double v1, double v2, double v3,  double v4, double t_start, double t_end, double stepsize){		
				std::vector<double> u0={v1,v2,v3,v4};

				sir_model.change_step_size(stepsize);
				auto result =sir_model.run(t_start,u0,t_end);
				auto timepoints=std::get<0>(result);
				auto data=std::get<1>(result);
				ug::epi::write_data(path, name, timepoints, data,sir_model.names,"#"); //write to file
				
			}

			void RunSEIRD(ug::epi::SEIRD<std::vector<double>>& seird_model,std::string path, std::string name, double v1, double v2, double v3, double v4, double v5, double t_start, double t_end, double stepsize_time){		
				std::vector<double> u0={v1,v2,v3,v4,v5};

				seird_model.change_step_size_time(stepsize_time);
				auto result =seird_model.run_linear_implicit(t_start,u0,t_end);
				auto timepoints=std::get<0>(result);
				auto data=std::get<1>(result);
				ug::epi::write_data(path, name, timepoints, data,seird_model.names,"#"); //write to file
				
			}
			
			void RunSEIRDPDE(ug::epi::SEIRD_PDE<std::vector<double>,ug::epi::seird::Geometry::Plane>& seird_model,InitialValueManager<seird::Geometry::Plane,double>& initial_manager, std::string path, std::string name){		
	
				double t_start=initial_manager.get_t_start();
				double t_end=initial_manager.get_t_end();
				double hx=initial_manager.get_hx();
				double ht=initial_manager.get_ht();
				std::cout << "RunSEIRDPDE, hx = " << hx << std::endl; 
				std::cout << "RunSEIRDPDE, ht = " << ht << std::endl; 

				std::vector<double> u0 = initial_manager.get_u0();

				if(u0.size() == 0){
					u0 =  initial_values<std::vector<double>>(initial_manager);
				}
				seird_model.change_step_size_spatial(hx);
				seird_model.change_step_size_time(ht);	

				std::string filename=name;

				seird_model.set_store_to_file(true,path,filename);

				seird_model.run_linear_implicit(t_start, u0, t_end);
	
			}
		}
	
	
}
