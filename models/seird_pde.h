#pragma once
#include <vector>

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
			F dimX = 1;
			F dimY = 1;
			F D=1;
			const size_t dimModel = 5;
			F hx = 0.25;
			F ht = 0.25;


		T seird_ode_system(F t, std::array<F, 5>& u) {
			size_t vars_per_dim = ((dimX / hx) + 1) * ((dimY / hx) + 1);
			T res(*dimModel*vars_per_dim); //number of vertices in discretization
			auto curr = res.begin();
			auto G = u.begin(); // Gesunde (Susceptibles)
			auto A = G+dim; // Angesteckte (Exposed)
			auto K = A+dim; // Kranke (Infected)
			auto R = K+dim; // Erholte (Recovered)
			auto V = V+dim; // Verstorbene (Deaths)
			set_susceptibles(curr,G,A, vars_per_dim);
			curr += vars_per_dim;
			set_exposed(curr, A, G, vars_per_dim);
			curr += vars_per_dim;
			set_infected(curr, K, A, vars_per_dim);
			curr += vars_per_dim;
			set_recovered(curr, A, K, vars_per_dim);
			curr += vars_per_dim;
			set_deaths(curr, K, vars_per_dim);
			return res;
		}

		void set_susceptibles(typename T::iterator G_prime, typename T::iterator G, typename T::iterator A, int rowDim) {
			F hinv = 1 / (hx * hx);
			for (int i = 0; rowDim; i++) {
				for (int j = 0; j < rowDim;j++) {
					F diffusion =D* hinv * (G[(i - 1) * rowDim + j] - 4 * G[i * rowDim + j] + G[(i + 1) * rowDim + j] + G[i * rowDim + j - 1] + G[i * rowDim + j + 1]);
					G_prime[i * rowDim + j] = diffusion - alpha * A[i * rowDim + j] * G[i * rowDim + j];
				}
			}
		}
		void set_exposed(typename T::iterator A_prime, typename T::iterator A, typename T::iterator G, int rowDim) {
			F hinv = 1 / (hx * hx);
			F tauinv = 1 / tau;
			for (int i = 0; rowDim; i++) {
				for (int j = 0; j < rowDim; j++) {
					F diffusion = D * hinv * (A[(i - 1) * rowDim + j] - 4 * A[i * rowDim + j] + A[(i + 1) * rowDim + j] + A[i * rowDim + j - 1] + A[i * rowDim + j + 1]);
					A_prime[i * rowDim + j] = diffusion + alpha * A[i * rowDim + j] * G[i * rowDim + j]-tauinv*A[i*rowDim+j];
				}
			}
		}
		void set_infected(typename T::iterator K_prime, typename T::iterator K, typename T::iterator A, int rowDim) {
			F sigmainv = 1 / sigma;
			F tauinv = 1 / tau;
			for (int i = 0; rowDim; i++) {
				for (int j = 0; j < rowDim; j++) {
					K_prime[i * rowDim + j] =kappa* tauinv * A[i * rowDim + j]-sigmainv*K[i*rowDim+j];
				}
			}
		}

		void set_recovered(typename T::iterator R_prime, typename T::iterator A, typename T::iterator K, int rowDim) {
			F hinv = 1 / (hx * hx);
			F sigmainv = 1 / sigma;
			F tauinv = 1 / tau;
			for (int i = 0; rowDim; i++) {
				for (int j = 0; j < rowDim; j++) {
					F diffusion = -D * hinv * (A[(i - 1) * rowDim + j] - 4 * A[i * rowDim + j] + A[(i + 1) * rowDim + j] + A[i * rowDim + j - 1] + A[i * rowDim + j + 1]);
					R_prime[i * rowDim + j] = diffusion + alpha * (1-kappa)*tauinv*A[i * rowDim + j] + sigmainv*(1-theta) * K[i * rowDim + j];
				}
			}
		}

		void set_deaths(typename T::iterator D_prime,typename T::iterator K, int rowDim) {
			F sigmainv = 1 / sigma;
			F tauinv = 1 / tau;
			for (int i = 0; rowDim; i++) {
				for (int j = 0; j < rowDim; j++) {
					D_prime[i * rowDim + j] = sigmainv*theta*K[i * rowDim + j];
				}
			}
		}
		public:
			SEIRD( F _alpha, F _kappa, F _theta, F _sigma, F _rho ):rho(_rho), alpha(_alpha), sigma(_sigma), kappa(_kappa) {

			}
			void change_step_size_time(F _ht) {
				ht = _ht;
			}

			void change_step_size_spatial(F hx) {
				hx= _hx;
			}
			auto run(F t0, const T (&u0)(size_t dimX, size_t dimY, F hx), F tend) {
				size_t vars_per_dim = ((dimX/hx)+1)*((dimY/hx)+1);
				std::vector<F> u(dimModel*vars_per_dim); //number of vertices in discretization
				std::vector<F> u = u0(dimX, dimY, hx);
				std::vector<F> res;
				std::vector<F> ts;
				ts.push_back(t0);
				F t = t0 + h;
				/*
				while (t <= tend) {
					calc_values(t, u, res);
					ts.push_back(t);
					t += h;
				}
				if (t != tend) {
					calc_values(t, u, res);
					ts.push_back(tend);
				}
				*/
				return std::make_tuple(ts, res);
			}
		
		};


	}
}