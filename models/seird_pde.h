#pragma once
#include <vector>
#include <string>
#include <array>
#include "utility.h"
#include "writer.h"

namespace ug {
	namespace epi {

		namespace seird {

			enum class Geometry {
				Plane
			};

		}

		template<class T, seird::Geometry G>
		class SEIRD_PDE {};

		template<class T>
		class SEIRD_PDE<T,seird::Geometry::Plane> {
			using F = typename T::value_type;
		private:
			F rho = 1;
			F alpha = 1;
			F sigma = 1;
			F kappa = 1;
			F theta = 1;
			F tau = 1;
			F dimX = 1;
			F dimY = 1;
			F D=1;
			const size_t dimModel = 5;
			F hx = 0.25;
			F ht = 0.25;
			std::string filepath="";
			std::string filename="";

		void set_susceptibles(typename T::iterator G_prime, typename T::iterator G, typename T::iterator A, int nCols, int nRows) {
			F hinv = 1 / (hx * hx);
			for (int i = 0; i<(nRows-1); i++) {
				for (int j = 0; j < (nCols-1);j++) {
					double a=0;
					double b=0;
					double c=0;
					double d=0;					
					if ((i-1)>=0){
						a=G[(i - 1) * nCols + j];
					}
					if ((i+1)<nRows){
						b=G[(i + 1) * nCols + j];
					}
					
					if ((j-1)>=0){
						c=G[i * nCols + j - 1];
					}
					
					if ((j+1)<nCols){
						d=G[i * nCols + j + 1];
					}
				
					F diffusion =D* hinv * (a - 4 * G[i * nCols + j] + b + c + d);
					G_prime[i * nCols + j] = diffusion - alpha * A[i * nCols + j] * G[i * nCols + j];
				}
			}
		
		}
		void set_exposed(typename T::iterator A_prime, typename T::iterator A, typename T::iterator G, int nCols, int nRows) {
			F hinv = 1 / (hx * hx);
			F tauinv = 1 / tau;
			
			for (int i = 0; i < nRows; i++) {
				for (int j = 0; j < nCols; j++) {
					double a=0;
					double b=0;
					double c=0;
					double d=0;					
					if ((i-1)>=0){
						a=A[(i - 1) * nCols + j];
					}
					if ((i+1)<nRows){
						b=A[(i + 1) * nCols + j];
					}
					
					if ((j-1)>=0){
						c=A[i * nCols + j - 1];
					}
					
					if ((j+1)<nCols){
						d=A[i * nCols + j + 1];
					}					
				
					F diffusion = D * hinv * (a - 4 * A[i * nCols + j] + b + c + d);
					A_prime[i * nCols + j] = diffusion + alpha * A[i * nCols + j] * G[i * nCols + j]-tauinv*A[i*nCols+j];
				}
			}
		}
		void set_infected(typename T::iterator K_prime, typename T::iterator K, typename T::iterator A, int nCols, int nRows) {
			F sigmainv = 1 / sigma;
			F tauinv = 1 / tau;
			for (int i = 0; i < nRows; i++) {
				for (int j = 0; j < nCols; j++) {
					K_prime[i * nCols + j] =kappa* tauinv * A[i * nCols + j]-sigmainv*K[i*nCols+j];
				}
			}
		}

		void set_recovered(typename T::iterator R_prime, typename T::iterator A, typename T::iterator K, int nCols, int nRows) {
			F hinv = 1 / (hx * hx);
			F sigmainv = 1 / sigma;
			F tauinv = 1 / tau;
			for (int i = 0; i < nRows; i++) {
				for (int j = 0; j < nCols; j++) {
					double a=0;
					double b=0;
					double c=0;
					double d=0;						
					if ((i-1)>=0){
						a=A[(i - 1) * nCols + j];
					}
					if ((i+1)<nRows){
						b=A[(i + 1) * nCols + j];
					}
					
					if ((j-1)>=0){
						c=A[i * nCols + j - 1];
					}
					
					if ((j+1)<nCols){
						d=A[i * nCols + j + 1];
					}				
			
					F diffusion = -D * hinv * (A[(i - 1) * nCols + j] - 4 * A[i * nCols + j] + A[(i + 1) * nCols + j] + A[i * nCols + j - 1] + A[i * nCols + j + 1]);
					R_prime[i * nCols + j] = diffusion + alpha * (1-kappa)*tauinv*A[i * nCols + j] + sigmainv*(1-theta) * K[i * nCols + j];
				}
			}
		}

		void set_deaths(typename T::iterator D_prime,typename T::iterator K, int nCols, int nRows) {
			F sigmainv = 1 / sigma;
			F tauinv = 1 / tau;
			for (int i = 0; i < nRows; i++) {
				for (int j = 0; j < nCols; j++) {
					D_prime[i * nCols + j] = sigmainv*theta*K[i * nCols + j];
				}
			}
		}

		void get_new_point(T& dest, const T& source1,const T& source2,F h, F factor) {
			int n = source1.size();
			for (int i = 0; i < n;i++) {
				dest[i]=source1[i] + h*factor*source2[i];
			}
		}

		void add_k_to_vector(T& dest, const T& source, F h, F factor) {
			int n = source.size();
			for (int i = 0; i < n; i++) {
				dest[i] += h * factor * source[i];
			}
		}


		//As ODE system does not depend on time, the ODE is autonomous
		
		void calc_values(F t, T& u, T& res,T& v, int iter, OutputPDEWriter<std::vector<F>,F>& ow ) {
		
			T ks = system(u);
			
			get_new_point(v, u, ks, hx, 0.5);
			add_k_to_vector(u, ks, hx, (1.0 / 6.0));
		
			ks = system(v);
			get_new_point(v, u, ks, hx, 0.5);
			add_k_to_vector(u, ks, hx, (2.0 / 6.0));
			ks = system(v);
			get_new_point(v, u, ks, hx, 1);
			add_k_to_vector(u, ks, hx, (2.0 / 6.0));
			ks = system(v);
			
			if (StoreToFile==false){
				for (int i = 0; i < u.size(); i++) {
					res.push_back(u[i]);
				}				
			}
			else{
				std::cout<<"Writing to file\n";
				//std::cin.get();
				ow.write_to_file(filepath, filename+std::to_string(iter)+".txt",t,u,((dimX/hx)+1),((dimY/hx)+1));
			}

			
		}
		
			bool StoreToFile=true; // if true, results are stored to file only
	
		public:
		
			void set_store_to_file(bool _store_to_file, std::string _filepath, std::string _filename){
				StoreToFile=_store_to_file;
				filepath=_filepath;
				filename=_filename;
			}			
			SEIRD_PDE( F _alpha, F _kappa, F _theta, F _sigma, F _tau , F _rho , F _diffusion):tau(_tau), alpha(_alpha), sigma(_sigma), kappa(_kappa), theta(_theta) ,rho(_rho) , D(_diffusion){
				
			}		
			
			
			const std::vector<std::string> names = { "Susceptibles","Exposed", "Infected", "Recovered", "Deaths" };

			void change_step_size_time(F _ht) {
				ht = _ht;
			}

			void change_step_size_spatial(F _hx) {
				hx= _hx;
			}
			
			T system(T& u) {
				size_t vars_per_dim = ((dimX / hx) + 1) * ((dimY / hx) + 1);
				size_t vars_per_row = ((dimX / hx) + 1);
				size_t vars_per_column = ((dimY / hx) + 1);
				T res(dimModel*vars_per_dim,F(0.0)); //number of vertices in discretization
				auto curr = res.begin();
				auto G = u.begin(); // Gesunde (Susceptibles)
				auto A = G+ vars_per_dim; // Angesteckte (Exposed)
				auto K = A+ vars_per_dim; // Kranke (Infected)
				auto R = K+ vars_per_dim; // Erholte (Recovered)
				auto V = R+ vars_per_dim; // Verstorbene (Deaths)
	
				set_susceptibles(curr,G,A, vars_per_row,vars_per_column);
	
				
				curr += vars_per_dim;
				set_exposed(curr, A, G, vars_per_row, vars_per_column);
				/*
				for (int i=0;i<vars_per_column;i++){
					for (int j=0;j<vars_per_row;j++){
						std::cout<<res[i*vars_per_row+j]<<"\t";
						
					}
					std::cout<<"\n";
				}
				std::cin.get();
				*/
				curr += vars_per_dim;
				set_infected(curr, K, A, vars_per_row, vars_per_column);
				curr += vars_per_dim;
				set_recovered(curr, A, K, vars_per_row, vars_per_column);
				curr += vars_per_dim;
				set_deaths(curr, K, vars_per_row, vars_per_column);

				return res;
			}	

			T jacobian(T& u) {
				size_t vars_per_dim = ((dimX / hx) + 1) * ((dimY / hx) + 1);
				size_t vars_per_row = ((dimX / hx) + 1);
				size_t vars_per_column = ((dimY / hx) + 1);
				T res(dimModel*vars_per_dim,F(0.0)); //number of vertices in discretization
				auto curr = res.begin();
				auto S = u.begin(); // Gesunde (Susceptibles)
				auto E = S+ vars_per_dim; // Angesteckte (Exposed)
				auto I = E+ vars_per_dim; // Kranke (Infected)
				auto R = I+ vars_per_dim; // Erholte (Recovered)
				auto D = R+ vars_per_dim; // Verstorbene (Deaths)
				
				
				
				/*
	
				set_susceptibles(curr,S,E, vars_per_row,vars_per_column);
				curr += vars_per_dim;
				set_exposed(curr, E, S, vars_per_row, vars_per_column);
				curr += vars_per_dim;
				set_infected(curr, I, E, vars_per_row, vars_per_column);
				curr += vars_per_dim;
				set_recovered(curr, E, I, vars_per_row, vars_per_column);
				curr += vars_per_dim;
				set_deaths(curr, I, vars_per_row, vars_per_column);
				*/
				return res;
			}	


			
			auto run(F t0,  T& u0, F tend) {
				size_t vars_per_dim = ((dimX/hx)+1)*((dimY/hx)+1);
				
				OutputPDEWriter<std::vector<double>,double> writer(5,names);
				
				std::vector<F> u = u0;
				std::vector<F> res;
				std::vector<F> ts;
				if (StoreToFile==false){
					res=u;
					ts.push_back(t0);
				}
				else{
					writer.write_to_file(filepath, filename+std::to_string(0)+".txt",t0,u,((dimX/hx)+1),((dimY/hx)+1));
				}
				F t = t0 + ht;
				std::vector<F> temp(u.size());
				int iter=1;
				while (t <= tend) {
					calc_values(t,u, res,temp,iter,writer);
					if (StoreToFile==false){
						ts.push_back(t);					
					}

					t += ht;
					iter++;
				}
			
				return std::make_tuple(ts, res);

			}
			
			
			auto run_linear_implicit(F t0,  T& u0, F tend) {
				size_t nVars = ((dimX / hx) + 1) * ((dimY / hx) + 1);
				size_t dim=nVars*5;
				utility::LinearImplicitSolver23<std::vector<F>,std::vector<F>,SEIRD_PDE,F> solver(this,dim);
				solver.change_step_size(hx);
				
				std::cout<<nVars;
				OutputPDEWriter<std::vector<double>,double> writer(5,names);
				solver.set_store_to_file(true, filepath, filename,&writer);
				auto result=solver.run(t0, u0, tend);

				return std::make_tuple(result.first,result.second);
			}			
		
		};


	}
}