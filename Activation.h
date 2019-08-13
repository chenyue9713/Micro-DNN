/*
 * activation.h
 *
 *  Created on: Aug 7, 2019
 *      Author: yue
 */

#ifndef ACTIVATION_H_
#define ACTIVATION_H_

#include"Matrix.h"
#include"Config.h"

using namespace std;

class Activation{

public:
	Activation(){};
	~Activation(){};

	void Relu_forward(Matrix & z, Matrix & out){
		vector<double>* out_data = out.Data();
		vector<vector<double>> z_data = z.getData();
		for(uint32_t i = 0; i < z_data.size(); ++i){
			for(uint32_t j = 0; j < z_data[0].size(); ++j){
				out_data[i][j] = max(0.0, double(z_data[i][j]));
			}
		}
	}
	void Relu_backward(Matrix & z, Matrix & da){
		uint32_t row = z.getRowNum();
		uint32_t col = z.getColNum();

		vector<vector<double>> a_data = z.getData();
		vector<double>* da_data = da.Data();
		for (uint32_t i = 0; i < row; ++i){
			for (uint32_t j = 0; j < col; ++j){
				if(a_data[i][j] < 0.0){
					da_data[i][j] = 0;
				}
			}
		}


	}


};









#endif /* ACTIVATION_H_ */
