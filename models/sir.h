#pragma once
#include <vector>
#include <array>
#include <tuple>
#include <string>

namespace ug{
	namespace epi{
	
		template<class T>
		class SIR{
			using F=typename T::value_type;
			
			private:
			F tau;
			F alpha;
			F theta;
			F h=0.01;

			std::array<F,4> sir_ode(F t, std::array<F,4>& u){
				std::array<F,4> res;
				
				F S=u[0];
				F I=u[1];
				
				res[0]=-alpha*S*I; // ds/dt=-alphaSI
				res[1]=alpha*S*I-(tau+theta)*I; //dI/dt = alphaSI -(tau+theta)I
				res[2]=tau*I; // dr/dt = tauI
			 	res[3]=theta*I; //dV/dt = thetaI 
				return res;
			}


			void calc_values(F t, std::array<F,4>& u, std::vector<F>& res){
				std::array<F,4> k1=sir_ode(t,u);
				std::array<F,4> v;
				v[0]=u[0]+h*0.5*k1[0];
				v[1]=u[1]+h*0.5*k1[1];
				v[2]=u[2]+h*0.5*k1[2];
				v[3]=u[3]+h*0.5*k1[3];
				std::array<F,4> k2=sir_ode(t+0.5*h,v);

				v[0]=u[0]+h*0.5*k2[0];
				v[1]=u[1]+h*0.5*k2[1];
				v[2]=u[2]+h*0.5*k2[2];
				v[3]=u[3]+h*0.5*k2[3];
				std::array<F,4> k3=sir_ode(t+0.5*h,v);

				v[0]=u[0]+h*k3[0];
				v[1]=u[1]+h*k3[1];
				v[2]=u[2]+h*k3[2];
				v[3]=u[3]+h*k3[3];
				std::array<F,4> k4=sir_ode(t+h,v);				

				u[0]=u[0]+(1.0/6.0)*h*(k1[0]+2*k2[0]+2*k3[0]+k4[0]);
				u[1]=u[1]+(1.0/6.0)*h*(k1[1]+2*k2[1]+2*k3[1]+k4[1]);
				u[2]=u[2]+(1.0/6.0)*h*(k1[2]+2*k2[2]+2*k3[2]+k4[2]);
				u[3]=u[3]+(1.0/6.0)*h*(k1[3]+2*k2[3]+2*k3[3]+k4[3]);
				res.push_back(u[0]);
				res.push_back(u[1]);	
				res.push_back(u[2]);
				res.push_back(u[3]);
			}	
			
			
			public:
			const std::array<std::string,4> names={"Susceptibles","Infected", "Recovered","Deaths"};
			SIR(F _alpha, F _tau, F _theta):tau(_tau),alpha(_alpha),theta(_theta){
			
			}
			void change_step_size(F _h){
				h=_h;
			}
			std::tuple<std::vector<F>,std::vector<F>> run(F t0, const T u0, F tend){
				std::vector<F> res;
				std::vector<F> ts;
				
				res.push_back(u0[0]);
				res.push_back(u0[1]);
				res.push_back(u0[2]);
				res.push_back(u0[3]);
				ts.push_back(t0);
				std::array<F,4> u={u0[0],u0[1],u0[2],u0[3]};
				
				F t=t0+h;
				while(t<=tend){
					calc_values(t,u,res);
					ts.push_back(t);
					t+=h;
				}
				if (t!=tend){
					t = tend;
					calc_values(t,u,res);
					ts.push_back(tend);
				}
				return std::make_tuple(ts,res);			
			}		
		
		};

	
	
	}
}

