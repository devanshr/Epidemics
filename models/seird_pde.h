/** \file seird_pde.h
 * This file defines necessary classes and enums in order to be able to run the
 * partial differential equations version of the SEIRD model. 
 * The model is discretized using finite differences on a structured planar grid.
 */

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
		/*! Dummy class of the SEIRD PDE model for an unspecified geometry.  More information about the theoretical foundation can be found in the other documents in the documents folder of this plugin.*/	

		template<class T, seird::Geometry G>
		class SEIRD_PDE {};

		/*! Class of the SEIRD PDE model on a a planar grid. The SEIRD model includes a new class (Exposed) amongst other additions. More information about the theoretical foundation can be found in the other documents in the documents folder of this plugin.*/	
		template<class T>
		class SEIRD_PDE<T,seird::Geometry::Plane> {
			using F = typename T::value_type;
		private:
			F rho = 1;
			F alpha = 1; /**< Infection coefficient that controls how many people go from Susceptible to Exposed*/
			F sigma = 1; /**< Coefficient that controls how many people leave the Infected class*/
			F kappa = 1;/**< Coefficient that controls how many people become infected (from those that left the Exposed class)*/
			F theta = 1; /**< Death coefficient that controls how many people go from the Infected to Deceased class*/
			F tau = 1; /**< Coefficient that controls how many people leave the Exposed class*/
			F dimX = 1;
			F dimY = 1;
			F D=1; /**< Diffusion coefficient for the Susceptible and Exposed class*/
			const size_t dimModel = 5;
			F hx = 0.25; /**< Step size of the ODE solver in the spatial domain. Does not have to equal ht*/
			F ht = 0.25; /**< Step size of the ODE solver in the time domain. Does not have to equal hx*/
			std::string filepath=""; /**< Filepath where simulation results are stored*/
			std::string filename=""; /**< Name of the created file that contains simulation results*/

		/*! Sets values for the Susceptible class. On the rectangular boundary, either double forward or double backwards finite differences are used. See other documents in the documents folder of this plugin for a mathematical derivation.
			@param[in] G_prime Derivative of Susceptible grid element with respect to time
			@param[in] G Susceptible grid element with respect to time				
			@param[in] A Exposed grid element with respect to time	
			@param[in] nCols Number of columns in the rectangular discretization
			@param[in] nRows Number of rows in the rectangular discretization									
		*/	
		void set_susceptibles(typename T::iterator G_prime, typename T::iterator G, typename T::iterator A, int nCols, int nRows) {
			F hinv = 1 / (hx * hx);
			for (int i = 0; i<(nRows); i++) {
				for (int j = 0; j < (nCols);j++) {
					F diffusion=0;
							
					if (((i-1)>=0)&&((i+1)<nRows)&&((j-1)>=0)&&((j+1)<nCols)){
						F a=G[(i - 1) * nCols + j];
						F b=G[(i + 1) * nCols + j];
						F c=G[i * nCols + j - 1];
						F d=G[i * nCols + j + 1];
						diffusion=(a - 4 * G[i * nCols + j] + b + c + d);
					}
					else{
						//Upper boundary. Forward difference for y dimension
						if ((i-1)<0){
							diffusion+=2*G[(i)*nCols+j]-5*G[(i+1)*nCols+j]+4*G[(i+2)*nCols+j]-G[(i+3)*nCols+j];
						//	std::cout<<"C1:"<<G[(i)*nCols+j]<<"   "<<G[(i+1)*nCols+j]<<"   "<<G[(i+2)*nCols+j]<<"   "<<G[(i+3)*nCols+j]<<"\n";
						}
						//Lower boundary. Backwards difference for y dimension
						else if ((i+1)>=nRows){
							diffusion+=2*G[i*nCols+j]-5*G[(i-1)*nCols+j]+4*G[(i-2)*nCols+j]-G[(i-3)*nCols+j];
					//		std::cout<<"C2:"<<G[i*nCols+j]<<"   "<<G[(i-1)*nCols+j]<<"  "<<G[(i-2)*nCols+j]<<"   "<<G[(i-3)*nCols+j]<<"\n";
						}
						else{
							diffusion+=G[(i - 1) * nCols + j]-2* G[i * nCols + j]+G[(i + 1) * nCols + j];
						}
						
						//Left boundary. Forward difference for x dimension
						if ((j-1)<0){
							diffusion+=2*G[i*nCols+j]-5*G[i*nCols+(j+1)]+4*G[i*nCols+(j+2)]-G[i*nCols+(j+3)];
							//std::cout<<"c4"<<G[i*nCols+j]<<"   "<<G[i*nCols+j+1]<<"   "<<G[i*nCols+j+2]<<"  "<<G[i*nCols+j+3]<<"\n";
						}	
						//Right boundary. Backwards boundary for x dimension
						else if ((j+1)>=nCols){
							diffusion+=2*G[i*nCols+j]-5*G[i*nCols+(j-1)]+4*G[i*nCols+(j-2)]-G[i*nCols+(j-3)];
						//	std::cout<<"C4:"<<G[i*nCols+j]<<"  "<<G[i*nCols+(j-1)]<<"   "<<G[i*nCols+(j-2)]<<"   "<<G[i*nCols+(j-3)]<<"\n";
						}	
						else{
							diffusion+=G[i * nCols + j - 1]-2*G[i * nCols + j]+G[i * nCols + j +1];
						}
					}
				
					diffusion*=D*hinv;
					//std::cout<<"diffusion:"<<diffusion<<"\n";
				//	std::cin.get();
					G_prime[i * nCols + j] = diffusion - alpha * A[i * nCols + j] * G[i * nCols + j];
				}
			}
		
		}
		
		/*! Sets values for the Exposed class. On the rectangular boundary, either double forward or double backwards finite differences are used. See other documents in the documents folder of this plugin for a mathematical derivation.
			@param[in] A_prime Derivative of Exposed grid element with respect to time
			@param[in] E Exposed grid element with respect to time				
			@param[in] G Susceptible grid element with respect to time	
			@param[in] nCols Number of columns in the rectangular discretization
			@param[in] nRows Number of rows in the rectangular discretization									
		*/			
		void set_exposed(typename T::iterator A_prime, typename T::iterator A, typename T::iterator G, int nCols, int nRows) {
			F hinv = 1 / (hx * hx);
			F tauinv = 1 / tau;
			
			for (int i = 0; i < nRows; i++) {
				for (int j = 0; j < nCols; j++) {
					F diffusion=0;
					if (((i-1)>=0)&&((i+1)<nRows)&&((j-1)>=0)&&((j+1)<nCols)){
						F a=A[(i - 1) * nCols + j];
						F b=A[(i + 1) * nCols + j];
						F c=A[i * nCols + j - 1];
						F d=A[i * nCols + j + 1];
						diffusion=(a - 4 * A[i * nCols + j] + b + c + d);
					}
					else{
						//Upper boundary. Forward difference for y dimension
						if ((i-1)<0){
							diffusion+=2*A[(i)*nCols+j]-5*A[(i+1)*nCols+j]+4*A[(i+2)*nCols+j]-A[(i+3)*nCols+j];
							//std::cout<<"C1:"<<A[(i)*nCols+j]<<"   "<<A[(i+1)*nCols+j]<<"   "<<A[(i+2)*nCols+j]<<"   "<<A[(i+3)*nCols+j]<<"\n";
						}
						//Lower boundary. Backwards difference for y dimension
						else if ((i+1)>=nRows){
							diffusion+=2*A[i*nCols+j]-5*A[(i-1)*nCols+j]+4*A[(i-2)*nCols+j]-A[(i-3)*nCols+j];
							//std::cout<<"C2:"<<A[i*nCols+j]<<"   "<<A[(i-1)*nCols+j]<<"  "<<A[(i-2)*nCols+j]<<"   "<<A[(i-3)*nCols+j]<<"\n";
						}
						else{
							diffusion+=A[(i - 1) * nCols + j]-2* A[i * nCols + j]+A[(i + 1) * nCols + j];
						}
						
						//Left boundary. Forward difference for x dimension
						if ((j-1)<0){
							diffusion+=2*A[i*nCols+j]-5*A[i*nCols+(j+1)]+4*A[i*nCols+(j+2)]-A[i*nCols+(j+3)];
							//std::cout<<"c4"<<A[i*nCols+j]<<"   "<<A[i*nCols+j+1]<<"   "<<A[i*nCols+j+2]<<"  "<<A[i*nCols+j+3]<<"\n";
						}	
						//Right boundary. Backwards boundary for x dimension
						else if ((j+1)>=nCols){
							diffusion+=2*A[i*nCols+j]-5*A[i*nCols+(j-1)]+4*A[i*nCols+(j-2)]-A[i*nCols+(j-3)];
							//std::cout<<"C4:"<<A[i*nCols+j]<<"  "<<A[i*nCols+(j-1)]<<"   "<<A[i*nCols+(j-2)]<<"   "<<A[i*nCols+(j-3)]<<"\n";
						}	
						else{
							diffusion+=A[i * nCols + j - 1]-2*A[i * nCols + j]+A[i * nCols + j +1];
						}

					}
				
					diffusion*=D*hinv;
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
					F diffusion=0;
					
					if (((i-1)>=0)&&((i+1)<nRows)&&((j-1)>=0)&&((j+1)<nCols)){
						a=A[(i - 1) * nCols + j];
						b=A[(i + 1) * nCols + j];
						c=A[i * nCols + j - 1];
						d=A[i * nCols + j + 1];
						diffusion=(a - 4 * A[i * nCols + j] + b + c + d);
					}
					else{
						//Upper boundary. Forward difference for y dimension
						if ((i-1)<0){
							diffusion+=2*A[(i)*nCols+j]-5*A[(i+1)*nCols+j]+4*A[(i+2)*nCols+j]-A[(i+3)*nCols+j];
						}	
						//Lower boundary. Backwards difference for y dimension
						else if ((i+1)>=nRows){
							diffusion+=2*A[i*nCols+j]-5*A[(i-1)*nCols+j]+4*A[(i-2)*nCols+j]-A[(i-3)*nCols+j];
						}
						else{
							diffusion+=A[(i - 1) * nCols + j]-2* A[i * nCols + j]+A[(i + 1) * nCols + j];
						}
						
						//Left boundary. Forward difference for x dimension
						if ((j-1)<0){
							diffusion+=2*A[i*nCols+j]-5*A[i*nCols+(j+1)]+4*A[i*nCols+(j+2)]-A[i*nCols+(j+3)];
						}
						
						//Right boundary. Backwards boundary for x dimension
						else if ((j+1)>=nCols){
							diffusion+=2*A[i*nCols+j]-5*A[i*nCols+(j-1)]+4*A[i*nCols+(j-2)]-A[i*nCols+(j-3)];
						}
						else{
							diffusion+=A[i * nCols + j - 1]-2*A[i * nCols + j]+A[i * nCols + j +1];
						}
						
					}
				
					diffusion=diffusion*-D*hinv;
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
		/*! Sets values of the Jacobian matrix for the Susceptible class. On the rectangular boundary, either double forward or double backwards finite differences are used. See other documents in the documents folder of this plugin for a mathematical derivation.
			@param[in] J_S Susceptible subset of the Jacobi matrix where results will be stored
			@param[in] S Susceptible subset of the finite difference system matrix				
			@param[in] E Exposed subset of the finite difference system matrix	
			@param[in] nCols Number of columns in the rectangular discretization
			@param[in] nRows Number of rows in the rectangular discretization
			@param[in] nRows Number of rows in the Jacobian matrix of the rectangular discretization													
		*/			
		void set_susceptibles_jacobian(typename T::iterator J_S,typename T::iterator S, typename T::iterator E, int nCols, int nRows, int nRowsJacobian) {
			auto J=J_S; //Start of Jacobian matrix
			auto J_e=J_S+nRows*nCols;
			F hinv = 1 / (hx * hx);
			for (int i = 0; i<(nRows); i++) {
				for (int j = 0; j < (nCols);j++) {
							
					if (((i-1)>=0)&&((i+1)<nRows)&&((j-1)>=0)&&((j+1)<nCols)){
						J_S[i*nCols+j]=-4*D*hinv;
						J_S[(i - 1) * nCols + j]=1*D*hinv;
						J_S[(i + 1) * nCols + j]=1*D*hinv;
						J_S[i * nCols + j - 1]=1*D*hinv;
						J_S[i * nCols + j + 1]=1*D*hinv;
					}
					else{
						//Upper boundary. Forward difference for y dimension
						if ((i-1)<0){
							J_S[(i)*nCols+j]+=2*D*hinv;
							J_S[(i+1)*nCols+j]+=-5*D*hinv;
							J_S[(i+2)*nCols+j]+=4*D*hinv;
							J_S[(i+3)*nCols+j]+=-1*D*hinv;
						//	std::cout<<"C1:"<<G[(i)*nCols+j]<<"   "<<G[(i+1)*nCols+j]<<"   "<<G[(i+2)*nCols+j]<<"   "<<G[(i+3)*nCols+j]<<"\n";
						}
						//Lower boundary. Backwards difference for y dimension
						else if ((i+1)>=nRows){
							J_S[i*nCols+j]+=2*D*hinv;
							J_S[(i-1)*nCols+j]+=-5*D*hinv;
							J_S[(i-2)*nCols+j]+=4*D*hinv;
							J_S[(i-3)*nCols+j]+=-1*D*hinv;
					//		std::cout<<"C2:"<<G[i*nCols+j]<<"   "<<G[(i-1)*nCols+j]<<"  "<<G[(i-2)*nCols+j]<<"   "<<G[(i-3)*nCols+j]<<"\n";
						}
						else{
							J_S[(i - 1) * nCols + j]+=1*D*hinv;
							J_S[i * nCols + j]+=-2*D*hinv;
							J_S[(i + 1) * nCols + j]+=1*D*hinv;						
						}
						
						//Left boundary. Forward difference for x dimension
						if ((j-1)<0){
							J_S[i*nCols+j]+=2*D*hinv;
							J_S[i*nCols+(j+1)]+=-5*D*hinv;
							J_S[i*nCols+(j+2)]+=4*D*hinv;
							J_S[i*nCols+(j+3)]+=-1*D*hinv;	
							//std::cout<<"c4"<<G[i*nCols+j]<<"   "<<G[i*nCols+j+1]<<"   "<<G[i*nCols+j+2]<<"  "<<G[i*nCols+j+3]<<"\n";
						}	
						//Right boundary. Backwards boundary for x dimension
						else if ((j+1)>=nCols){
							J_S[i*nCols+j]+=2*D*hinv;
							J_S[i*nCols+(j-1)]+=-5*D*hinv;
							J_S[i*nCols+(j-2)]+=4*D*hinv;
							J_S[i*nCols+(j-3)]+=-1*D*hinv;					
						//	std::cout<<"C4:"<<G[i*nCols+j]<<"  "<<G[i*nCols+(j-1)]<<"   "<<G[i*nCols+(j-2)]<<"   "<<G[i*nCols+(j-3)]<<"\n";
						}	
						else{
							J_S[i * nCols + j - 1]+=1*D*hinv;
							J_S[i * nCols + j]+=-2*D*hinv;
							J_S[i * nCols + j +1]+=1*D*hinv;						
						}
					}
				
					J_S[i*nCols+j]+=-alpha * E[i * nCols + j];
					J_e[i*nCols+j]+=-alpha*S[i * nCols + j];
					J_S+=nRowsJacobian;
					J_e+=nRowsJacobian;
				}
			}
		
		}



		// copy of example
		void set_exposed_jacobian(typename T::iterator J_E,typename T::iterator S, typename T::iterator E, int nCols, int nRows, int nRowsJacobian) {
			auto J=J_E; //Start of Exposed rows in Jacobian matrix
			auto J_e=J_E+nRows*nCols; //Start of exposed derivative of Exposed rows
			F hinv = 1 / (hx * hx);
			F tinv = 1 / tau;
			for (int i = 0; i<(nRows); i++) {
				for (int j = 0; j < (nCols);j++) {
							
					if (((i-1)>=0)&&((i+1)<nRows)&&((j-1)>=0)&&((j+1)<nCols)){
						J_e[i*nCols+j]=-4*D*hinv;
						J_e[(i - 1) * nCols + j]=1*D*hinv;
						J_e[(i + 1) * nCols + j]=1*D*hinv;
						J_e[i * nCols + j - 1]=1*D*hinv;
						J_e[i * nCols + j + 1]=1*D*hinv;
					}
					else{
						//Upper boundary. Forward difference for y dimension
						if ((i-1)<0){
							J_e[(i)*nCols+j]+=2*D*hinv;
							J_e[(i+1)*nCols+j]+=-5*D*hinv;
							J_e[(i+2)*nCols+j]+=4*D*hinv;
							J_e[(i+3)*nCols+j]+=-1*D*hinv;
						//	std::cout<<"C1:"<<G[(i)*nCols+j]<<"   "<<G[(i+1)*nCols+j]<<"   "<<G[(i+2)*nCols+j]<<"   "<<G[(i+3)*nCols+j]<<"\n";
						}
						//Lower boundary. Backwards difference for y dimension
						else if ((i+1)>=nRows){
							J_e[i*nCols+j]+=2*D*hinv;
							J_e[(i-1)*nCols+j]+=-5*D*hinv;
							J_e[(i-2)*nCols+j]+=4*D*hinv;
							J_e[(i-3)*nCols+j]+=-1*D*hinv;
					//		std::cout<<"C2:"<<G[i*nCols+j]<<"   "<<G[(i-1)*nCols+j]<<"  "<<G[(i-2)*nCols+j]<<"   "<<G[(i-3)*nCols+j]<<"\n";
						}
						else{
							J_e[(i - 1) * nCols + j]+=1*D*hinv;
							J_e[i * nCols + j]+=-2*D*hinv;
							J_e[(i + 1) * nCols + j]+=1*D*hinv;						
						}
						
						//Left boundary. Forward difference for x dimension
						if ((j-1)<0){
							J_e[i*nCols+j]+=2*D*hinv;
							J_e[i*nCols+(j+1)]+=-5*D*hinv;
							J_e[i*nCols+(j+2)]+=4*D*hinv;
							J_e[i*nCols+(j+3)]+=-1*D*hinv;	
							//std::cout<<"c4"<<G[i*nCols+j]<<"   "<<G[i*nCols+j+1]<<"   "<<G[i*nCols+j+2]<<"  "<<G[i*nCols+j+3]<<"\n";
						}	
						//Right boundary. Backwards boundary for x dimension
						else if ((j+1)>=nCols){
							J_e[i*nCols+j]+=2*D*hinv;
							J_e[i*nCols+(j-1)]+=-5*D*hinv;
							J_e[i*nCols+(j-2)]+=4*D*hinv;
							J_e[i*nCols+(j-3)]+=-1*D*hinv;					
						//	std::cout<<"C4:"<<G[i*nCols+j]<<"  "<<G[i*nCols+(j-1)]<<"   "<<G[i*nCols+(j-2)]<<"   "<<G[i*nCols+(j-3)]<<"\n";
						}	
						else{
							J_e[i * nCols + j - 1]+=1*D*hinv;
							J_e[i * nCols + j]+=-2*D*hinv;
							J_e[i * nCols + j +1]+=1*D*hinv;						
						}
					}
				
					J_E[i*nCols+j]+=alpha*E[i * nCols + j];
					J_e[i*nCols+j]+=alpha*S[i * nCols + j] - tinv;
					J_E+=nRowsJacobian;
					J_e+=nRowsJacobian;
				}
			}
		
		}


		// copy of example
		void set_infected_jacobian(typename T::iterator J_I, int nCols, int nRows, int nRowsJacobian) {
			auto J=J_I; //Start of Infected rows in Jacobian matrix
			auto J_e=J_I+nRows*nCols; //Start of exposed derivative of Infected rows
			auto J_i=J_e+nRows*nCols; //Start of infected derivative of Infrected rows
			F tinv = 1 / tau;
			F sinv = 1 / sigma;
			for (int i = 0; i<(nRows); i++) {
				for (int j = 0; j < (nCols);j++) {
							
					J_e[i*nCols+j]=kappa*tinv;
					J_i[i*nCols+j]=-1*sinv;
					J_e+=nRowsJacobian;
					J_i+=nRowsJacobian;
				}
			}
		}



		// copy of example
		void set_recovered_jacobian(typename T::iterator J_R,typename T::iterator E, int nCols, int nRows, int nRowsJacobian) {
			auto J=J_R; //Start of Recovered rows in Jacobian matrix
			auto J_e=J_R+nRows*nCols; //Start of exposed derivative of Recovered rows
			auto J_i=J_e+nRows*nCols; //Start of infected derivative of Recovered rows
			F hinv = 1 / (hx * hx);
			F tinv = 1 / tau;
			F sinv = 1 / sigma;
			for (int i = 0; i<(nRows); i++) {
				for (int j = 0; j < (nCols);j++) {
							
					if (((i-1)>=0)&&((i+1)<nRows)&&((j-1)>=0)&&((j+1)<nCols)){
						J_e[i*nCols+j]=4*D*hinv;
						J_e[(i - 1) * nCols + j]=-1*D*hinv;
						J_e[(i + 1) * nCols + j]=-1*D*hinv;
						J_e[i * nCols + j - 1]=-1*D*hinv;
						J_e[i * nCols + j + 1]=-1*D*hinv;
					}
					else{
						//Upper boundary. Forward difference for y dimension
						if ((i-1)<0){
							J_e[(i)*nCols+j]+=-2*D*hinv;
							J_e[(i+1)*nCols+j]+=5*D*hinv;
							J_e[(i+2)*nCols+j]+=-4*D*hinv;
							J_e[(i+3)*nCols+j]+=1*D*hinv;
						//	std::cout<<"C1:"<<G[(i)*nCols+j]<<"   "<<G[(i+1)*nCols+j]<<"   "<<G[(i+2)*nCols+j]<<"   "<<G[(i+3)*nCols+j]<<"\n";
						}
						//Lower boundary. Backwards difference for y dimension
						else if ((i+1)>=nRows){
							J_e[i*nCols+j]+=-2*D*hinv;
							J_e[(i-1)*nCols+j]+=5*D*hinv;
							J_e[(i-2)*nCols+j]+=-4*D*hinv;
							J_e[(i-3)*nCols+j]+=1*D*hinv;
					//		std::cout<<"C2:"<<G[i*nCols+j]<<"   "<<G[(i-1)*nCols+j]<<"  "<<G[(i-2)*nCols+j]<<"   "<<G[(i-3)*nCols+j]<<"\n";
						}
						else{
							J_e[(i - 1) * nCols + j]+=-1*D*hinv;
							J_e[i * nCols + j]+=2*D*hinv;
							J_e[(i + 1) * nCols + j]+=-1*D*hinv;						
						}
						
						//Left boundary. Forward difference for x dimension
						if ((j-1)<0){
							J_e[i*nCols+j]+=-2*D*hinv;
							J_e[i*nCols+(j+1)]+=5*D*hinv;
							J_e[i*nCols+(j+2)]+=-4*D*hinv;
							J_e[i*nCols+(j+3)]+=1*D*hinv;	
							//std::cout<<"c4"<<G[i*nCols+j]<<"   "<<G[i*nCols+j+1]<<"   "<<G[i*nCols+j+2]<<"  "<<G[i*nCols+j+3]<<"\n";
						}	
						//Right boundary. Backwards boundary for x dimension
						else if ((j+1)>=nCols){
							J_e[i*nCols+j]+=-2*D*hinv;
							J_e[i*nCols+(j-1)]+=5*D*hinv;
							J_e[i*nCols+(j-2)]+=-4*D*hinv;
							J_e[i*nCols+(j-3)]+=1*D*hinv;					
						//	std::cout<<"C4:"<<G[i*nCols+j]<<"  "<<G[i*nCols+(j-1)]<<"   "<<G[i*nCols+(j-2)]<<"   "<<G[i*nCols+(j-3)]<<"\n";
						}	
						else{
							J_e[i * nCols + j - 1]+=-1*D*hinv;
							J_e[i * nCols + j]+=2*D*hinv;
							J_e[i * nCols + j +1]+=-1*D*hinv;						
						}
					}
				
					J_e[i*nCols+j]+=alpha*(1-kappa)*tinv;
					J_i[i*nCols+j]+=sinv*(1-theta);
					J_e+=nRowsJacobian;
					J_i+=nRowsJacobian;
				}
			}
		
		}



		// copy of example
		void set_deceased_jacobian(typename T::iterator J_D, int nCols, int nRows, int nRowsJacobian) {
			auto J=J_D; //Start of Deceased rows in Jacobian matrix
			auto J_i=J_D+(nRows*nCols*2); //Start of infected derivative of Deceased rows
			F sinv = 1 / sigma;
			for (int i = 0; i<(nRows); i++) {
				for (int j = 0; j < (nCols);j++) {
							
					J_i[i*nCols+j]=sinv*kappa;
					J_i+=nRowsJacobian;
				}
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
				ow.write_to_file(filepath, filename+std::to_string(iter)+".txt",t,u);
			}

			
		}
		
			bool StoreToFile=true; // if true, results are stored to file only
	
		public:
			/*! Determines if simulation results will be stored to on the hard drive. It is recommended to turn this on, because high discretizations might require more memory than RAM is available.
				@param[in] _store_to_file Determines, if results will be stored to file
				@param[in] _filepath Path where simulation results will be saved				
				@param[in] _filename Name of the file that contains simulation results													
			*/			
			void set_store_to_file(bool _store_to_file, std::string _filepath, std::string _filename){
				StoreToFile=_store_to_file;
				filepath=_filepath;
				filename=_filename;
			}			
			
			/*! Constructor of the class that the model parameters.
			@param[in] _alpha Infection coefficient that controls how many people go from Susceptible to Exposed
			@param[in] _kappa Coefficient that controls how many people leave the Exposed class
			@param[in] _theta Death coefficient that controls how many people go from the Infected to Deceased class
			@param[in] _sigma Coefficient that controls how many people leave the Infected class
			@param[in]  _tau Coefficient that controls how many people leave the Exposed class
			@param[in] _diffusion Diffusion coefficient for the Susceptible and Exposed class		
			*/	
			SEIRD_PDE( F _alpha, F _kappa, F _theta, F _sigma, F _tau  , F _diffusion):tau(_tau), alpha(_alpha), sigma(_sigma), kappa(_kappa), theta(_theta)  , D(_diffusion){
				
			}		
			
			
			const std::vector<std::string> names = { "Susceptibles","Exposed", "Infected", "Recovered", "Deaths" };  /**< Names of the various SEIRD classes */

			/*! Sets the time step size for the ordinary differential equation solvers.
			@param[in] _ht Time step size for the ODE solvers		
			*/
			void change_step_size_time(F _ht) {
				ht = _ht;
			}
			/*! Sets the spatial step size for the ordinary differential equation solvers.
			@param[in] _hx Spatial step size for the ODE solvers		
			*/				void change_step_size_spatial(F _hx) {
				hx= _hx;
			}
			
			/*! Returns the system matrix of the finite difference forumlation of the PDE SEIRD model evaluated at time t and values u.
			@param[in] u S-E-I-R-D class values at time t at the various spatial locations
			@param[in] t Coefficient that controls how many people leave the Exposed class	
			@param[out] T System matrix of the finite difference forumlation of the PDE SEIRD model evaluated at time t and values u				
			*/				
			T system(T& u, F t=0) {
				size_t vars_per_dim = static_cast<int>(std::ceil(dimX / hx) + 1)* static_cast<int>(std::ceil(dimY / hx) + 1);
				size_t vars_per_row = (std::ceil(dimX / hx) + 1);
				size_t vars_per_column = (std::ceil(dimY / hx) + 1);
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

			/*! Returns the Jacobi matrix of the finite difference forumlation of the PDE SEIRD model evaluated at time t and values u.
			@param[in] u S-E-I-R-D class values at time t at the various spatial locations
			@param[in] t Coefficient that controls how many people leave the Exposed class	
			@param[out] T Jacobi matrix of the finite difference forumlation of the PDE SEIRD model evaluated at time t and values u				
			*/		
			T jacobian(T& u, F t=0) {
				size_t vars_per_dim = static_cast<int>(std::ceil(dimX / hx) + 1)* static_cast<int>(std::ceil(dimY / hx) + 1);
				size_t vars_per_row_jacobian=dimModel*vars_per_dim;
				size_t vars_per_row = (std::ceil(dimX / hx) + 1); //Row means with respect to a single class
				size_t vars_per_column = (std::ceil(dimY / hx) + 1);
				T res(vars_per_row_jacobian*vars_per_row_jacobian,F(0.0)); //jacobian matrix
				auto curr = res.begin();
				auto S = u.begin(); // Gesunde (Susceptibles)
				auto E = S+ vars_per_dim; // Angesteckte (Exposed)
				auto I = E+ vars_per_dim; // Kranke (Infected)
				auto R = I+ vars_per_dim; // Erholte (Recovered)
				auto D = R+ vars_per_dim; // Verstorbene (Deaths)
				

				set_susceptibles_jacobian(curr, S, E, vars_per_row, vars_per_column, vars_per_row_jacobian);

				curr += vars_per_dim*vars_per_row_jacobian; // move to exposed
				set_exposed_jacobian(curr, S, E, vars_per_row,vars_per_column,vars_per_row_jacobian);

				curr += vars_per_dim*vars_per_row_jacobian; // move to infected
				set_infected_jacobian(curr, vars_per_row,vars_per_column,vars_per_row_jacobian);
				curr += vars_per_dim*vars_per_row_jacobian; // move to recovered
				set_recovered_jacobian(curr, E, vars_per_row,vars_per_column,vars_per_row_jacobian);

				curr += vars_per_dim*vars_per_row_jacobian; // move to deceased
				set_deceased_jacobian(curr, vars_per_row,vars_per_column,vars_per_row_jacobian);
				std::cout<<"Jacobian min, max:\n";
				std::cout<<*std::min_element(res.begin(), res.end())<<"\n";
				std::cout<<*std::max_element(res.begin(), res.end())<<"\n";
				//std::cin.get();
				return res;
			}	
			
			//Returns Jacobian value at position i,j. Will be useful to reduce computation time. Function is not finished yet.
			T Jacobian_get(size_t i, size_t j){
				size_t vars_per_dim = static_cast<int>(std::ceil(dimX / hx) + 1)* static_cast<int>(std::ceil(dimY / hx) + 1);
				size_t vars_per_row_jacobian=dimModel*vars_per_dim;
				size_t vars_per_row = (std::ceil(dimX / hx) + 1); //Row means with respect to a single class
				size_t vars_per_column = (std::ceil(dimY / hx) + 1);
				//if (j<vars_per_row_jacobian*va
			}


			/*! Solves the PDE SEIRD model with an explicit solver of fourth order. Results are stored in a vector of vectors. Results are written to file. 
			 * If the diffusion coefficient is zero (D=0), then this solver is relatively reliable. Otherwise it is often unstable. If any negative numbers are encountered in the results,
			 * the step size either has to be made smaller of the linear implicit solver should be tried out.
			@param[in] t0 Simulation start time		
			@param[in] u0 Initial conditions for the five S-E-I-R-D classes on the rectangular grid
			@param[in] tend end time
			@param[out] std::tuple<std::vector<F>,std::vector<F>> Dummy vector with simulation output that shall not be used			
			*/			
			std::tuple<std::vector<F>,std::vector<F>> run(F t0,  T& u0, F tend) {
				size_t vars_per_dim = static_cast<int>(std::ceil(dimX / hx) + 1)* static_cast<int>(std::ceil(dimY / hx) + 1);
				
				OutputPDEWriter<std::vector<double>,double> writer(5,dimX,dimY,names,hx,ht);
				
				std::vector<F> u = u0;
				std::vector<F> res;
				std::vector<F> ts;
				if (StoreToFile==false){
					res=u;
					ts.push_back(t0);
				}
				else{
					writer.write_to_file(filepath, filename+std::to_string(0)+".txt",t0,u);
					writer.write_gridmapping(filepath, filename+".txt",t0,u);
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
			
				if (t!= tend){
					t=tend;
					calc_values(t,u, res,temp,iter,writer);
					if (StoreToFile==false){
						ts.push_back(t);					
					}					
				}
				return std::make_tuple(ts, res);

			}
			
			/*! Solves the PDE SEIRD model with a linear implicit solver of second order. Results are stored in a vector of vectors. Results are written to file. 
			 * For high discretizations, this solver might be very slow (even hours for a time step). The explicit solver can then be tried out instead.
			@param[in] t0 Simulation start time		
			@param[in] u0 Initial conditions for the five S-E-I-R-D classes on the rectangular grid
			@param[in] tend end time
			@param[out] std::tuple<std::vector<F>,std::vector<F>> Dummy vector with simulation output that shall not be used			
			*/				
			std::tuple<std::vector<F>,std::vector<F>> run_linear_implicit(F t0,  T& u0, F tend) {
				std::printf("hx = %f\n", hx);
				size_t nVars = static_cast<int>(std::ceil(dimX / hx) + 1)* static_cast<int>(std::ceil(dimY / hx) + 1);
				size_t dim=nVars*5;
				utility::LinearImplicitSolver23<std::vector<F>,std::vector<F>,SEIRD_PDE,F> solver(this,dim);
				
			
				solver.change_step_size(hx);
				
				std::cout<<"Staring linear implicit solver\n";
				OutputPDEWriter<std::vector<double>,double> writer(5,dimX,dimY,names,hx,hx);
				solver.set_store_to_file(true, filepath, filename,&writer);

				writer.write_gridmapping(filepath, filename+".txt",t0,u0);
				
				solver.change_step_size(ht);
				auto result=solver.run(t0, u0, tend);
				std::cout<<"Ended linear implicit solver\n";
				std::cout<<result.second.size();

				return std::make_tuple(result.first,result.second);
			}			
		
		};


	}
}
