#pragma once
#include <string>
#include <fstream>
#include <iostream>

namespace ug{
	namespace epi{
		template<class TA,class TB,class TC>
		void write_data(std::string path, std::string name, const TA& times, const TB& m, const TC& datanames,std::string delimiter="--",std::string reason=""){
			int dim=datanames.size();
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
