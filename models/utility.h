#pragma once
#include "../../ConstrainedOptimization/core/parameters.h"
#include "../../ConstrainedOptimization/core/transformation.h"
#include "writer.h"
#include <utility>
#include <vector>

namespace ug {
	namespace epi {
		namespace utility {

			
			
			
			template<class T1,class T2, class C,class F>
			class LinearImplicitSolver23 {

				C* model;
				int dim;
				F h = 0.25;
				bool StoreToFile=false; //if true, results are stored to file
				OutputWriter<T1,F>* ow;
				std::string filepath="";
				std::string filename="output";				

				std::vector<F> create_identity_matrix() {
					std::vector<F>  result(dim*dim,F(0.0));
					for (int i = 0; i < dim; i++) {
						result[i + i * dim] = F(1.0);
					}
					return result;
				}

				std::vector<F> sumAB(F alpha, std::vector<F>& A, F beta, std::vector<F>& B) {
					std::vector<F>  result(dim * dim, F(0.0));

					for (int i = 0; i < dim;i++) {
						for (int j = 0; j < dim; j++) {
							result[i * dim + j] = alpha*A[i * dim + j] + beta*B[i * dim + j];
						}
					}
					return result;
				}

			public:
				void set_store_to_file(bool _store_to_file, std::string _filepath, std::string _filename, OutputWriter<T1,F>* _ow){
					StoreToFile=_store_to_file;
					filepath=_filepath;
					filename=_filename;
					ow=_ow;
				}

				LinearImplicitSolver23(C* _model, int _dim) : model(_model), dim(_dim) {

				}

				void change_step_size(F _h) {
					h = _h;
				}

				std::pair<std::vector<F>,std::vector<F>> run(F t0,  T1 u,  F tend) {
					if (u.size() != dim) {
						std::cerr << "Error: Input dimension of u0 in LinearImplicitSolver23 is different than the dimension previously given in the constructor\n";
						std::cerr << "u.size() = " << u.size() << std::endl;
						std::cerr << "dim = " << dim << std::endl;
					}
					if (StoreToFile){
						(*ow).write_to_file(filepath, filename+std::to_string(0)+".txt",t0,u);
					}
					std::vector<F> datapoints;

					for (int i = 0; i < dim; i++) {
						datapoints.push_back(u[i]);
					}
					std::vector<F> timepoints = {t0};
					std::vector<F> I;
					std::vector<F> J(dim * dim,F(0.0));
					std::vector<F> Qt(dim * dim);
					std::vector<F> R(dim * dim);
					std::vector<F> M(dim*dim); //M=(I-ahJ)
					std::vector<F> q1(dim);
					std::vector<F> k1(dim);
					std::vector<F> k2(dim);
					std::vector<F> k3(dim);


					F t = t0+h;
					//std::copy(u0.begin(), u0.end(), u.begin());
					F a = 1 / (2 + 1.41);
					F d31 = -(4 + 1.41) / (2 + 1.41);
					F d32 = (6+1.41)/ (2+1.41);
					std::vector<F> u_copy(dim);
					int iter = 1;
				
					while ((double)t < (double)(tend+h)) {
						std::copy(u.begin(), u.end(), u_copy.begin());						
						//k1
						T1 temp = model->system(u,t); //it only has dim entries but otherwise type errors in this old version of dgemm
						std::vector<F> fy(dim);
						std::copy(temp.begin(),temp.end(), fy.begin());
						
						I = create_identity_matrix();
						T2 temp2=model->jacobian(u,t);
						std::copy(temp2.begin(), temp2.end(), J.begin());
						M=sumAB(F(1), I, F(-a * h), J);
						co::dc::qr<typename std::vector<F>::iterator,F> (M.begin(), dim, dim, Qt.begin(), R.begin());
						//co::dc::qr<typename std::vector<F>::iterator> (M.begin(), dim, dim, Qt.begin(), R.begin());
						co::mul::dgemm_nn(dim, 1, dim, F(1.0), Qt.begin(), 1, dim, fy.begin(), 1, 1, F(0.0), q1.begin(), 1, 1);
						co::dc::backwards_substitution<F>(R.begin(), k1.begin(), 1, q1.begin(), dim);
						
						//k2
						for (int i = 0; i < dim; i++) {
							u[i] = u_copy[i] + F(0.5) * h * k1[i];
							//std::cout<<I[i]<<"\t";
						}
				
					
						temp = model->system(u,t+F(0.5)*h); //it only has dim entries but otherwise type errors in this old version of dgemm
						temp2=model->jacobian(u,t+F(0.5)*h);
						std::copy(temp.begin(), temp.end(), fy.begin());
						co::mul::dgemm_nn(dim, 1, dim, -a*h, J.begin(), 1, dim, k1.begin(), 1, 1, F(1.0), fy.begin(), 1, 1);
						co::mul::dgemm_nn(dim, 1, dim, F(1.0), Qt.begin(), 1, dim, fy.begin(), 1, 1, F(0.0), q1.begin(), 1, 1);
						co::dc::backwards_substitution<F>(R.begin(), k2.begin(), 1, q1.begin(), dim);

						//k3 (useful for adaptive stepsizes)
						/*
						for (int i = 0; i < dim; i++) {
							u[i] = u_copy[i] +h * k2[i];
						}
						temp = model->system(u,t+h); //it only has dim entries but otherwise type errors in this old version of dgemm
						std::copy(temp.begin(), temp.end(), fy.begin());
						co::mul::dgemm_nn(dim, 1, dim, -d31* h, J.begin(), 1, dim, k1.begin(), 1, 1, F(1.0), fy.begin(), 1, 1); //f(yi+h*k2)=f(yi+h*k2)-d31*h*J*k1
						co::mul::dgemm_nn(dim, 1, dim, -d32  *h, J.begin(), 1, dim, k2.begin(), 1, 1, F(1.0), fy.begin(), 1, 1);
						co::mul::dgemm_nn(dim, 1, dim, F(1.0), Qt.begin(), 1, dim, fy.begin(), 1, 1, F(0.0), q1.begin(), 1, 1);
						co::dc::backwards_substitution<F>(R.begin(), k3.begin(), 1, q1.begin(), dim);
						*/
						//calculating yi+1
						if (StoreToFile==false){
							for (int i = 0; i < dim; i++) {
								//u[i] = u[i] + (h / 6) * (k1[i] + 4 * k2[i] + k3[i]);
								u[i] = u_copy[i] + h*k2[i];
								datapoints.push_back(u[i]);
							}
							timepoints.push_back(t);
						}
						else{
							for (int i = 0; i < dim; i++) {
								//u[i] = u[i] + (h / 6) * (k1[i] + 4 * k2[i] + k3[i]);
								u[i] = u_copy[i] + h*k2[i];
							}							
							
							(*ow).write_to_file(filepath, filename+std::to_string(iter)+".txt",t,u);
						}
						iter++;
						t+=h;
					}
				
					return std::make_pair(timepoints, datapoints);
				}
			};


		}
	}

}


