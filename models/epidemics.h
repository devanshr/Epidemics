/*! \mainpage Epidemics Plugin for UG4
 *
 * \section intro_sec Overview
 *
 *The Epidemics plugin consists of various algorithms used in epidemics modeling.
 *This manual was created in March 2021 for version number 0.1


 */

/** \file epidemics.h
 * This file is used if the optimization functions are indirectly called.
 * Indirectly means that the user only passes secondary information like path, options and
 * shell commands instead of directly calling the model functions.
 */

#pragma once
#include "sir.h"
#include "seird.h"
#include "writer.h"

namespace ug{
	namespace epi{
		
			constexpr int version_number=0.2;//change if you update your Epidemics version
			
			void RunSIR(ug::epi::SIR<std::vector<double>>& sir_model,std::string path, std::string name, double v1, double v2, double v3,  double v4, double t_start, double t_end, double stepsize){		
				std::vector<double> u0={v1,v2,v3,v4};

				sir_model.change_step_size(stepsize);
				auto result =sir_model.run(t_start,u0,t_end);
				auto timepoints=std::get<0>(result);
				auto data=std::get<1>(result);
				ug::epi::write_data(path, name, timepoints, data,sir_model.names,"#"); //write to file
				
			}

			void RunSEIRD(ug::epi::SEIRD<std::vector<double>>& seird_model,std::string path, std::string name, double v1, double v2, double v3, double v4, double v5, double t_start, double t_end, double stepsize){		
				std::vector<double> u0={v1,v2,v3,v4,v5};

				seird_model.change_step_size(stepsize);
				auto result =seird_model.run(t_start,u0,t_end);
				auto timepoints=std::get<0>(result);
				auto data=std::get<1>(result);
				ug::epi::write_data(path, name, timepoints, data,seird_model.names,"#"); //write to file
				
			}
		}
	
	
}