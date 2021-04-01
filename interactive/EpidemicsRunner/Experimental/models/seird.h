#include <cstring>
#include <vector>

namespace epi{

	template<class F>
	class SEIRD{

		private:
		F alpha;
		F kappa;
		F theta;
		F qq;
		F pp;
		F h=0.01;

		void change_step_size(F _h) {
			h = _h;
		}

		void system(const F* u, F* res) {

			F S = u[0]; // Gesunde (Susceptibles)
			F E = u[1]; // Angesteckte (Exposed)
			F I = u[2]; // Kranke (Infected)
			F R = u[3]; // Erholte (Recovered)
			F D = u[4]; // Verstorbene (Deaths)


			res[0] = -alpha * S * E; 				// dS/dt=-alpha*S*E
			res[1] = alpha * S * E - (1 / qq) * E; 			// dE/dt = alpha*S*E - (E/q)
			res[2] = (kappa / qq) * E - (1 / pp) * I; 		// dI/dt = (kappa*E)/qq - (I/pp) 
			res[3] = ((1 - kappa) / qq) * E + ((1 - theta) / pp) * I;   // dR/dt= (1-kappa)/q *E +(1 -theta)/pp *I
			res[4] = (theta / pp) * I; 				// dD/dt = theta/pp * I
		}

		void jacobian(const F* u, F* res) {
			for (size_t i = 0; i < 25; i++) {
				res[i] = 0;
			}

			F S = u[0]; // Gesunde (Susceptibles)
			F E = u[1]; // Angesteckte (Exposed)
			F I = u[2]; // Kranke (Infected)
			F R = u[3]; // Erholte (Recovered)
			F D = u[4]; // Verstorbene (Deaths)
			
			res[0] = -alpha*E;
			res[1] = -alpha * S;
			res[5] = alpha * E;
			res[6] = alpha * S - 1 + qq;
			res[11] = kappa / qq;
			res[12] = -(1 / pp);
			res[16] = (1 - kappa) / qq;
			res[17] = (1 - theta) / pp;
			res[22] = theta / pp;

		}
		
		void set_M(F* M, F* J, F ah){
			std::memset(M,F(0.0),25*sizeof(F));
			M[0]=F(1.0)-ah*J[0];
			M[1]=-ah*J[1];
			M[5]=-ah*J[5];
			M[6]=F(1.0)-ah*J[6];
			M[11]=ah*J[11];
			M[12]=F(1.0)-ah*J[12];
			M[16]=ah*J[16];
			M[17]=ah*J[17];
			M[18]=F(1.0);
			M[22]=ah*J[22];
			M[24]=F(1.0);
		}
		void solve_system(const F* A, const F* y, F* x){
			F a=A[0];
			F b=A[1];
			F c=A[5];
			F d=A[6];
			F e=A[11];
			F f=A[12];
			F g=A[16];
			F h=A[17];
			F i=A[18];
			F j=A[22];
			F k=A[24];

			x[0]=(y[0]+y[1]/d)/(a-(b/d));
			x[1]=(y[1]-c*x[0])/(d);
			x[2]=(y[2]-e*x[1])/f;
			x[3]=(y[3]-g*x[1]-h*x[2])/i;
			x[4]=(y[4]-j*y[2])/k;
		
		}
		void setup_right_side_k2(F* fy, const F* J, const F* k1, F ah){
			F a=J[0];
			F b=J[1];
			F c=J[5];
			F d=J[6];
			F e=J[11];
			F f=J[12];
			F g=J[16];
			F h=J[17];
			F i=J[18];
			F j=J[22];
			F k=J[24];
			
			fy[0]-=ah*(J[0]*k1[0]+J[1]*k1[1]);
			fy[1]-=ah*(J[5]*k1[0]+J[6]*k1[1]);
			fy[2]-=ah*(J[11]*k1[1]+J[12]*k1[2]);
			fy[3]-=ah*(J[16]*k1[1]+J[17]*k1[2]+J[18]*k1[3]);
			fy[4]-=ah*(J[22]*k1[2]+J[24]*k1[4]);
		}		
		
		public:

		SEIRD(F _alpha, F _kappa, F _theta, F _qq, F _pp):alpha(_alpha),kappa(_kappa),theta(_theta),qq(_qq),pp(_pp){
		
		}	
		
		
		
		void start_linear_implicit23(F t0, const F* u0, F tend, std::vector<F>& t_result, std::vector<F>& u_result){
				//std::vector<F> timepoints = {t0};
				F u[5];
				std::memcpy(u,u0,sizeof(u));
				
				F a = 1 / (2 + 1.41);
				F d31 = -(4 + 1.41) / (2 + 1.41);
				F d32 = (6+1.41)/ (2+1.41);
				F I[25]={0};
				F J[25];				
				F M[25]; //M=(I-ahJ)
				F k1[5];
				F k2[5];
				F k3[5];
				F fy[5]={0};
				F t=t0+h;
				F temp[5];
				F ah=a*h;
					
			while (t<=tend){
				system(u, fy);
				jacobian(u,J);
				set_M(M,J,ah);
				solve_system(M,fy,k1);
				
				for (int i = 0; i < 5; i++) {
					temp[i] = u[i] + 0.5 * h * k1[i];
				}
				system(temp, fy);
				setup_right_side_k2(fy,J,k1,ah);
				
				for (int i = 0; i < dim; i++) {
					u[i] += h*k2[i];
					u_result.push_back(u[i]);
				}
				t_result.push_back(t);				
				t+=h;
			}		
		}

		
		const int dim=5;
		void run_linear_implicit(F t0, const F* u0, F tend, std::vector<F>& t_result, std::vector<F>& u_result){
			start_linear_implicit23(t0,u0,tend,t_result,u_result);		
		}

	};

}
