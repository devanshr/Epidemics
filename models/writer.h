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
			virtual void write_to_file(std::string path, std::string name, F t, const T& u, int points_x, int points_y)=0;
			
		};
		template<class T, class F>
		class OutputPDEWriter: public OutputWriter<T,F>{
			
			private:
			int dim=-1;
			
			std::vector<std::string> names;
			
			public:
			OutputPDEWriter(){
			}
			OutputPDEWriter(int _dim, std::vector<std::string> _names): names(_names), dim(_dim){
			}
			
			virtual void write_to_file(std::string path, std::string name, F t, const T& u, int points_x, int points_y) override{
				std::ofstream output;	
				output.open(path+name);	
				int points_per_dim=u.size()/dim;
				output<<"#Seen are the grid output values for t="<<std::to_string(t)<<". If you want to see which gridpoints corrosponds to which coordinate entry, see the gridmapping.txt file\n";
				output<<"#The following dimensions are plotted:\n";
				for (int i=0;i<names.size();i++){
					output<<"#"<<names[i]<<"\n";						
				}
				output<<"#The values are plotted in the above order. Each dimension has "<<std::to_string(points_y)<<" rows \n";
				auto pos=u.begin();
				
				for (int k=0;k<dim;k++){
					

					
					
					for (int i=0;i<points_y;i++){
						for (int j=0;j<points_x;j++){
							output<<pos[i*points_x+j]<<"\t";
						}
						output<<"\n";
					}	
					pos+=points_per_dim;				
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
			
			for (int i=0;i<dim;i++){
				general_output<<datanames[i]<<"\t";
			}
			
			general_output<<"\n";
			for (int i=0;i<(m.size()/dim);i++){
				general_output<<times[i]<<"\t";
				for (int j=0;j<dim;j++){
					general_output<<m[i*dim+j]<<"\t";
				}
				general_output<<"\n";
			}

			general_output.close();
		}
	}
}
