#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

namespace ug{
	namespace epi{
		
		template<class T, class F>
		class OutputWriter{
			public:
			virtual void write_to_file(std::string path, std::string name, F t, const T& u)=0;
			
		};
		template<class T, class F>
		class OutputPDEWriter: public OutputWriter<T,F>{
			
			private:
			int dim=-1;
			
			F dimX=-1; //horizontal dimension of rectangle in world coordinates
			F dimY=-1; //vertical dimension of rectangle in world coordinates
			F hx;
			F hy;
			std::vector<std::string> names;
			
			public:
			OutputPDEWriter(){
			}
			OutputPDEWriter(int _dim, F _dimX, F _dimY, std::vector<std::string> _names, F _hx, F _hy): names(_names), dim(_dim),dimX(_dimX), dimY(_dimY), hx(_hx),hy(_hy){
			}
			
			virtual void write_to_file(std::string path, std::string name, F t, const T& u) override{
				int points_x=(std::ceil(dimX/hx)+1);
				int points_y=(std::ceil(dimY/hx)+1);
				std::ofstream output;	
				output.precision(15);
				//Write outputs
				output.open(path+name);	
				int points_per_dim=u.size()/dim;
				output<<"#[TIME]:"<<std::to_string(t)<<"\n";
				output<<"#Seen are the grid output values for t="<<std::to_string(t)<<". If you want to see which gridpoints correspond to which coordinate entries, look for gridmapping text file (if you generated it)\n";
				output<<"#The following dimensions are plotted:\n";
				for (int i=0;i<names.size();i++){
					output<<"#"<<names[i]<<"\n";						
				}
				output<<"#The values are plotted in the above order. Each dimension has "<<std::to_string(points_y)<<" rows \n";
				auto pos=u.begin();
				
				for (int k=0;k<dim;k++){
					

					
					
					for (int i=0;i<points_y;i++){
						for (int j=0;j<points_x;j++){
							output<<(double)pos[i*points_x+j]<<"\t";
						}
						output<<"\n";
					}	
					pos+=points_per_dim;				
				}
				output.close();	
				

			}
			
			void write_gridmapping(std::string path, std::string name, F t, const T& u){
				int points_x=(std::ceil(dimX/hx)+1);
				int points_y=(std::ceil(dimY/hx)+1);
				std::ofstream output;				
				//Write grid to world coordinates mapping
				output.open(path+"gridmapping_"+name);
				output<<"# Coordinate mapping in the format (posX, posY)\n";
				for (int i=0;i<points_y;i++){
					for (int j=0;j<points_x;j++){
						F wx=(j/(points_x-1.0))*dimX;
						F wy=(F(1.0)-(i/(points_y-1.0)))*dimY;
						output<<"("<<(double)wx<<","<<(double)wy<<")\t";
					}
					output<<"\n";
				}	
				output.close();				
				
			}
		};
				
		
		template<class TA,class TB,class TC>
		void write_data(std::string path, std::string name, const TA& times, const TB& m, const TC& datanames,std::string delimiter="--",std::string reason=""){
			size_t dim=datanames.size();
			std::string output;
			if (reason.length()!=0){
				output.append(delimiter);
				output.append(reason);
				output+="\n";				
			}
			std::ofstream lua_output;
			std::ofstream general_output;

			general_output.precision(7);
			general_output.open(path+name);
			general_output<<output;
			general_output<<delimiter<<"time\t";
			
			for (size_t i=0;i<dim;i++){
				general_output<<datanames[i]<<"\t";
			}
			
			general_output<<"\n";
			for (size_t i=0;i<(m.size()/dim);i++){
				general_output<<times[i]<<"\t";
				for (size_t j=0;j<dim;j++){
					general_output<<m[i*dim+j]<<"\t";
				}
				general_output<<"\n";
			}

			general_output.close();
		}
	}
}
