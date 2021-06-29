#pragma once
#include <vector>
#include <array>
#include <tuple>
#include <string>
#include "utility.h"

namespace ug{
	namespace epi{
	
		template<class T>
		class SEIRD_VARA{
			using F=typename T::value_type;
			
			private:
			std::vector<F> alpha;
			std::vector<F> alpha_limits;
			F kappa;
			F theta;
			F qq;
			F pp;
			F ht=0.01;

			void calc_values(F t, std::array<F,5>& u, std::vector<F>& res){
				std::array<F,5> k1=system(u,t);
				std::array<F,5> v;
				v[0]=u[0]+ht*0.5*k1[0];
				v[1]=u[1]+ht*0.5*k1[1];
				v[2]=u[2]+ht*0.5*k1[2];
				v[3]=u[3]+ht*0.5*k1[3];
				v[4]=u[4]+ht*0.5*k1[4];
				std::array<F,5> k2= system(v,t+ht*0.5);

				v[0]=u[0]+ht*0.5*k2[0];
				v[1]=u[1]+ht*0.5*k2[1];
				v[2]=u[2]+ht*0.5*k2[2];
				v[3]=u[3]+ht*0.5*k2[3];
				v[4]=u[4]+ht*0.5*k2[4];
				std::array<F,5> k3= system(v,t+ht*0.5);

				v[0]=u[0]+ht*k3[0];
				v[1]=u[1]+ht*k3[1];
				v[2]=u[2]+ht*k3[2];
				v[3]=u[3]+ht*k3[3];
				v[4]=u[4]+ht*k3[4];
				std::array<F,5> k4= system(v,t+ht);

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
			
			F eval_alpha(F t){
				bool interpolation=false;
				int alphaindex=0;
				int limitindex=-1;
				F eps=0.5;
				
				for (int i=0;i<alpha_limits.size();i++){
					if (t>(alpha_limits[i]-eps)){
						alphaindex=i+1;
						limitindex=i;
						if (t>=alpha_limits[i]){
							interpolation=false;
						}
						else{
							interpolation=true;
						}
					}
					
				}
				
				if (interpolation==false){
					return alpha[alphaindex];
				}else{
					
					F x0= alpha_limits[limitindex]-eps;
					F x1=alpha_limits[limitindex];
					F y0=alpha[alphaindex-1];
					F y1=alpha[alphaindex];
					F R;
					F C;
					F c;
					F d=std::sqrt((y0-y1)*(y0-y1));
					if (y1>y0){
						R=x1;
						C=x0;
						c=y0;
					}
					else{
						R=x0;
						C=x1;
						c=y1;
					}
					return d*std::exp(-((t-R)*(t-R))/((t-C)*(t-C)));
				}
				
			}
			
			public:
			const std::array<std::string,5> names={"Susceptibles","Exposed", "Infected", "Recovered", "Deaths"};
			SEIRD_VARA(std::vector<F> _alpha,std::vector<F> _alpha_limits , F _kappa, F _theta, F _qq, F _pp):alpha(_alpha),alpha_limits(_alpha_limits),kappa(_kappa),theta(_theta),qq(_qq),pp(_pp){
			
			}	

			void change_step_size_time(F _ht) {
				ht = _ht;
			}
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

			std::array<F, 5> system(std::array<F, 5>& u, F t) {
				std::array<F, 5> res;

				F G = u[0]; // Gesunde (Susceptibles)
				F A = u[1]; // Angesteckte (Exposed)
				F K = u[2]; // Kranke (Infected)
				//F R = u[3]; // Erholte (Recovered)
				//F V = u[4]; // Verstorbene (Deaths)

				F _alpha=eval_alpha(t);
				res[0] = -_alpha * G * A; 				// dG/dt=-alpha*G*A
				res[1] = _alpha * G * A - (1 / qq) * A; 			// dA/dt = alpha*G*A - (A/q)
				res[2] = (kappa / qq) * A - (1 / pp) * K; 		// dK/dt = (kappa*A)/qq - (K/pp) 
				res[3] = ((1 - kappa) / qq) * A + ((1 - theta) / pp) * K;   // dR/dt= (1-kappa)/q *A +(1 -theta)/pp *K
				res[4] = (theta / pp) * K; 				// dV/dt = theta/pp * K
				return res;
			}

			std::array<F,25> jacobian(const std::array<F, 5>& u, F t) {
				std::array<F, 5*5> res;

				for (int i = 0; i < res.size(); i++) {
					res[i] = 0;
				}
				F _alpha=eval_alpha(t);
				F S = u[0]; // Gesunde (Susceptibles)
				F E = u[1]; // Angesteckte (Exposed)
				res[0] = -_alpha*E;
				res[1] = -_alpha * S;
				res[5] = _alpha * E;
				res[6] = _alpha * S - (1/qq);
				res[11] = kappa / qq;
				res[12] = -(1 / pp);
				res[16] = (1 - kappa) / qq;
				res[17] = (1 - theta) / pp;
				res[22] = theta / pp;

				return res;
			}
			std::tuple<std::vector<F>,std::vector<F>> run_linear_implicit(F t0, const T& u0, F tend) {
				std::array<F, 5> u = { u0[0],u0[1],u0[2],u0[3],u0[4] };
				utility::LinearImplicitSolver23<std::array<F,5>,std::array<F,25>,SEIRD_VARA,F> solver(this,5);
				solver.change_step_size(ht);
				auto result=solver.run(t0, u, tend);
				return std::make_tuple(result.first,result.second);
			}
		
		};

	
	
	}
}

