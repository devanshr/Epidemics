/** \file seird.h
 * This file contains the SEIRD class. The SEIRD ODE model includes a new class (Exposed) amongst other additions. More information can be found in the other documents in the documents folder of this plugin.
 */
#pragma once
#include <vector>
#include <array>
#include <tuple>
#include <string>
#include "utility.h"

namespace ug{
	namespace epi{
		
		/*! Class of the SEIRD ODE model. The SEIRD model includes a new class (Exposed) amongst other additions. More information can be found in the other documents in the documents folder of this plugin.*/	
		template<class T>
		class SEIRD{
			using F=typename T::value_type;
			
			private:
			F alpha; /**< Infection coefficient that controls how many people go from Susceptible to Exposed*/
			F kappa; /**< Coefficient that controls how many people leave the Exposed class*/
			F theta; /**< Death coefficient that controls how many people go from the Infected to Deceased class*/
			F qq; /**< Incubation coefficient that controls how many people leave the Exposed class*/
			F pp; /**< Coefficient that controls how many people leave the Infected class*/
			F ht=0.01; /**< Step size for the ordinary differential equation solvers */

			void calc_values(F t, std::array<F,5>& u, std::vector<F>& res){
				std::array<F,5> k1=system(u);
				std::array<F,5> v;
				v[0]=u[0]+ht*0.5*k1[0];
				v[1]=u[1]+ht*0.5*k1[1];
				v[2]=u[2]+ht*0.5*k1[2];
				v[3]=u[3]+ht*0.5*k1[3];
				v[4]=u[4]+ht*0.5*k1[4];
				std::array<F,5> k2= system(v);

				v[0]=u[0]+ht*0.5*k2[0];
				v[1]=u[1]+ht*0.5*k2[1];
				v[2]=u[2]+ht*0.5*k2[2];
				v[3]=u[3]+ht*0.5*k2[3];
				v[4]=u[4]+ht*0.5*k2[4];
				std::array<F,5> k3= system(v);

				v[0]=u[0]+ht*k3[0];
				v[1]=u[1]+ht*k3[1];
				v[2]=u[2]+ht*k3[2];
				v[3]=u[3]+ht*k3[3];
				v[4]=u[4]+ht*k3[4];
				std::array<F,5> k4= system(v);

				u[0]=u[0]+(1.0/6.0)*ht*(k1[0]+2*k2[0]+2*k3[0]+k4[0]);
				u[1]=u[1]+(1.0/6.0)*ht*(k1[1]+2*k2[1]+2*k3[1]+k4[1]);
				u[2]=u[2]+(1.0/6.0)*ht*(k1[2]+2*k2[2]+2*k3[2]+k4[2]);
				u[3]=u[3]+(1.0/6.0)*ht*(k1[3]+2*k2[3]+2*k3[3]+k4[3]);
				u[4]=u[4]+(1.0/6.0)*ht*(k1[4]+2*k2[4]+2*k3[4]+k4[4]);
				res.push_back(u[0]);
				res.push_back(u[1]);	
				res.push_back(u[2]);
				res.push_back(u[3]);
				res.push_back(u[4]);
			}	
			
			
			public:
			const std::array<std::string,5> names={"Susceptibles","Exposed", "Infected", "Recovered", "Deaths"}; /**< Names of the various SEIRD classes */
			SEIRD(F _alpha, F _kappa, F _theta, F _qq, F _pp):alpha(_alpha),kappa(_kappa),theta(_theta),qq(_qq),pp(_pp){
			
			}	
			
			/*! Sets the step size for the ordinary differential equation solvers.
			@param[in] _ht Step size for the ODE solvers		
			*/	
			void change_step_size_time(F _ht) {
				ht = _ht;
			}
			
			/*! Solves the SEIRD model with an explicit solver of fourth order. Because the solver is explicit, instabilities in the solution
			 * profile can occur. It is recommended to use the linear implicit solver. Results are stored in a vector of vectors. Results are not written to file as of yet.
			@param[in] t0 Simulation start time		
			@param[in] u0 Initial conditions for the five S-E-I-R-D classes
			@param[in] tend end time
			@param[out] std::tuple<std::vector<F>,std::vector<F>> Vector of vectors containing the simulation output			
			*/				
			std::tuple<std::vector<F>,std::vector<F>> run(F t0, const T u0, F tend){
				std::vector<F> res;
				std::vector<F> ts;
				
				res.push_back(u0[0]);
				res.push_back(u0[1]);
				res.push_back(u0[2]);
				res.push_back(u0[3]);
				res.push_back(u0[4]);
				ts.push_back(t0);
				std::array<F,5> u={u0[0],u0[1],u0[2],u0[3],u0[4]};
				
				F t=t0+ht;
				while(t<=tend){
					calc_values(t,u,res);
					ts.push_back(t);
					t+=ht;
				}
				if (t!=tend){
					calc_values(tend,u,res);
					ts.push_back(tend);
				}
				return std::make_tuple(ts,res);			
			}
			
			//!< Returns the system matrix of the ordinary differential equations system determined by the SEIRD model evaluated at time t.
			std::array<F, 5> system(std::array<F, 5>& u, F t=0) {
				std::array<F, 5> res;

				F G = u[0]; // Gesunde (Susceptibles)
				F A = u[1]; // Angesteckte (Exposed)
				F K = u[2]; // Kranke (Infected)

				res[0] = -alpha * G * A; 				// dG/dt=-alpha*G*A
				res[1] = alpha * G * A - (1 / qq) * A; 			// dA/dt = alpha*G*A - (A/q)
				res[2] = (kappa / qq) * A - (1 / pp) * K; 		// dK/dt = (kappa*A)/qq - (K/pp) 
				res[3] = ((1 - kappa) / qq) * A + ((1 - theta) / pp) * K;   // dR/dt= (1-kappa)/q *A +(1 -theta)/pp *K
				res[4] = (theta / pp) * K; 				// dV/dt = theta/pp * K
				return res;
			}

			//!< Returns the Jacobi matrix of the ordinary differential equations system determined by the SEIRD model evaluated at time t.
			std::array<F,25> jacobian(const std::array<F, 5>& u,F t=0) {
				std::array<F, 5*5> res;

				for (int i = 0; i < res.size(); i++) {
					res[i] = 0;
				}

				F S = u[0]; // Gesunde (Susceptibles)
				F E = u[1]; // Angesteckte (Exposed)
				//F I = u[2]; // Kranke (Infected)
				//F R = u[3]; // Erholte (Recovered)
				//F D = u[4]; // Verstorbene (Deaths)
				res[0] = -alpha*E;
				res[1] = -alpha * S;
				res[5] = alpha * E;
				res[6] = alpha * S - (1/qq);
				res[11] = kappa / qq;
				res[12] = -(1 / pp);
				res[16] = (1 - kappa) / qq;
				res[17] = (1 - theta) / pp;
				res[22] = theta / pp;

				return res;
			}
			
			/*! Solves the SEIRD model with a linear implicit solver of second order. Results are stored in a vector of vectors. Results are not written to file as of yet.
			@param[in] t0 Simulation start time		
			@param[in] u0 Initial conditions for the five S-E-I-R-D classes
			@param[in] tend end time
			@param[out] std::tuple<std::vector<F>,std::vector<F>> vector of vectors containing the simulation output			
			*/	
			std::tuple<std::vector<F>,std::vector<F>> run_linear_implicit(F t0, const T& u0, F tend) {
				std::array<F, 5> u = { u0[0],u0[1],u0[2],u0[3],u0[4] };
				utility::LinearImplicitSolver23<std::array<F,5>,std::array<F,25>,SEIRD,F> solver(this,5);
				solver.change_step_size(ht);
				auto result=solver.run(t0, u, tend);
				return std::make_tuple(result.first,result.second);
			}
		
		};

	
	
	}
}

