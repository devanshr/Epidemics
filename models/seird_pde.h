#pragma once
#include <vector>
#include <string>
#include <array>

namespace ug {
	namespace epi {

		namespace seird {

			enum class Geometry {
				Plane
			};

		}

		template<class T, seird::Geometry G>
		class SEIRD {};

		template<class T>
		class SEIRD<T,seird::Geometry::Plane> {
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


		T seird_pde_to_ode(T& u) {
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
			curr += vars_per_dim;
			set_infected(curr, K, A, vars_per_row, vars_per_column);
			curr += vars_per_dim;
			set_recovered(curr, A, K, vars_per_row, vars_per_column);
			curr += vars_per_dim;
			set_deaths(curr, K, vars_per_row, vars_per_column);
			return res;
		}

		void set_susceptibles(typename T::iterator G_prime, typename T::iterator G, typename T::iterator A, int nCols, int nRows) {
			F hinv = 1 / (hx * hx);
			for (int i = 0; i<nRows; i++) {
				for (int j = 0; j < nCols;j++) {
					F diffusion =D* hinv * (G[(i - 1) * nCols + j] - 4 * G[i * nCols + j] + G[(i + 1) * nCols + j] + G[i * nCols + j - 1] + G[i * nCols + j + 1]);
					G_prime[i * nCols + j] = diffusion - alpha * A[i * nCols + j] * G[i * nCols + j];
				}
			}
		}
		void set_exposed(typename T::iterator A_prime, typename T::iterator A, typename T::iterator G, int nCols, int nRows) {
			F hinv = 1 / (hx * hx);
			F tauinv = 1 / tau;
			for (int i = 0; i < nRows; i++) {
				for (int j = 0; j < nCols; j++) {
					F diffusion = D * hinv * (A[(i - 1) * nCols + j] - 4 * A[i * nCols + j] + A[(i + 1) * nCols + j] + A[i * nCols + j - 1] + A[i * nCols + j + 1]);
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
		void calc_values(T& u, T& res,T& v) {
		
			T ks = seird_pde_to_ode(u);
			
			get_new_point(v, u, ks, hx, 0.5);
			add_k_to_vector(u, ks, hx, (1.0 / 6.0));
			ks = seird_pde_to_ode(v);
			get_new_point(v, u, ks, hx, 0.5);
			add_k_to_vector(u, ks, hx, (2.0 / 6.0));
			ks = seird_pde_to_ode(v);
			get_new_point(v, u, ks, hx, 1);
			add_k_to_vector(u, ks, hx, (2.0 / 6.0));
			ks = seird_pde_to_ode(v);
	
			for (int i = 0; i < u.size(); i++) {
				res.push_back(u[i]);
			}
			
		}

		public:
			SEIRD( F _alpha, F _kappa, F _theta, F _sigma, F _tau ):tau(_tau), alpha(_alpha), sigma(_sigma), kappa(_kappa) {

			}
			const std::array<std::string, 5> names = { "Susceptibles","Exposed", "Infected", "Recovered", "Deaths" };

			void change_step_size_time(F _ht) {
				ht = _ht;
			}

			void change_step_size_spatial(F _hx) {
				hx= _hx;
			}
			auto run(F t0,  T (&u0)(F dimX,F dimY, F hx), F tend) {
				size_t vars_per_dim = ((dimX/hx)+1)*((dimY/hx)+1);
				
				std::vector<F> u = u0(dimX, dimY, hx);
				std::vector<F> res;
				std::vector<F> ts;
				ts.push_back(t0);
				F t = t0 + ht;
				std::vector<F> temp(u.size());
				
				while (t <= tend) {
					calc_values(u, res,temp);
					ts.push_back(t);
					t += ht;
				}
				if (t != tend) {
					calc_values(u, res, temp);
					ts.push_back(tend);
				}
				
				return std::make_pair(ts, res);
			}
		
		};


	}
}