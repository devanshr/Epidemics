/*
 * Copyright (c) 2011-2021:  G-CSC, Goethe University Frankfurt
 */

#include "bridge/util.h"

// if possible, replace this with util_domain_dependent.h or
// util_algebra_dependent.h to speed up compilation time
#include "bridge/util_domain_algebra_dependent.h"

#include "models/epidemics.h"
#include<string>


using namespace std;
using namespace ug::bridge;

namespace ug{
namespace Epidemics{

struct Functionality
{

/**
 * Function called for the registration of Domain and Algebra independent parts.
 * All Functions and Classes not depending on Domain and Algebra
 * are to be placed here when registering.
 *
 * @param reg				registrySSSS
 * @param parentGroup		group for sorting of functionality
 */
static void Common(Registry& reg, string grp)
{
			 
//	The code below shows how a simple function can be registered


	 reg.add_function("RunSIR", ug::epi::RunSIR,"call Function",
	 				 "model#dir#name#init_susceptible#init_infected#init_recovered#init_deaths#tstart#tend#stepsize", "Runs the SIR ode model. See manual for details.");
	 				 
	 reg.add_function("RunSEIRD", ug::epi::RunSEIRD,"call Function",
	 				 "model#dir#name#init_susceptible#init_infected#init_3#init_4#init_5#tstart#tend#stepsize", "Runs the SEIRD ode model. See manual for details.");
 
	reg.add_function("RunSEIRDPDE", ug::epi::RunSEIRDPDE,"call Function",
	 				 "model#initial_manager#dir#name", "Runs the SEIRD PDE model. See manual for details.");
 
 
 
	reg.add_class_<ug::epi::SIR<std::vector<double>>>("SIR", grp)
				.add_constructor<void(*)(double, double,double)>();	 
 
	reg.add_class_<ug::epi::SEIRD<std::vector<double>>>("SEIRD", grp)
				.add_constructor<void(*)(double, double,double, double,double)>();	
				
	reg.add_class_<ug::epi::SEIRD_PDE<std::vector<double>,ug::epi::seird::Geometry::Plane>>("SEIRD_PDE", grp)
				.add_constructor<void(*)(double, double,double, double,double,double)>();	
				
	reg.add_class_<ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>>("InitialValueManager", grp)
				.add_constructor<void(*)()>()
				.add_method("set_r1",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_r1,"index")
				.add_method("set_r2",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_r2,"index")
				.add_method("set_r3",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_r3,"index")
				.add_method("set_r4",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_r4,"index")				
				.add_method("set_r5",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_r5,"index")
				.add_method("set_v1",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_v1,"index")
				.add_method("set_v2",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_v2,"index")
				.add_method("set_v3",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_v3,"index")
				.add_method("set_v4",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_v4,"index")
				.add_method("set_v5",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_v5,"index")
				.add_method("set_hx",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_hx,"index")
				.add_method("set_ht",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_ht,"index")
				.add_method("set_u0",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_u0,"index")
				.add_method("set_t_start",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_t_start,"index")
				.add_method("set_t_end",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::set_t_end,"index")
				.add_method("get_t_start",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::get_t_start,"index")
				.add_method("get_t_end",&ug::epi::InitialValueManager<ug::epi::seird::Geometry::Plane,double>::get_t_end,"index");	
				
				
}


};

} 


/**
 * This function is called when the plugin is loaded.
 */
extern "C" void
InitUGPlugin_Epidemics(Registry* reg, string grp)
{
	grp.append("Epidemics");
	typedef Epidemics::Functionality Functionality;

	try{
		RegisterCommon<Functionality>(*reg,grp);
	}
	UG_REGISTRY_CATCH_THROW(grp);
}

}// namespace ug
