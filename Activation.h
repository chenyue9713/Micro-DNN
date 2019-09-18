/*
 * activation.h
 *
 *  Created on: Aug 7, 2019
 *      Author: yue
 */

#ifndef ACTIVATION_H_
#define ACTIVATION_H_

#include"Config.h"
#include "Matrix.h"

using namespace std;

class Activation{

public:
	Activation(){};
	~Activation(){};

	void Relu_forward(Matrix & z, Matrix & out){
		double* out_data_pt = out.Data();
		double* z_data_pt = z.Data();
		for(uint32_t i = 0; i < z.getRowNum() * z.getColNum(); ++i, ++out_data_pt, ++z_data_pt){
			*out_data_pt = max(0.0, *z_data_pt);
		}
	}
	void Relu_backward(Matrix & z, Matrix & da){
		uint32_t row = z.getRowNum();
		uint32_t col = z.getColNum();

		double* a_data_pt = z.Data();
		double* da_data_pt = da.Data();
		for (uint32_t i = 0; i < row * col; ++i){
			if(*a_data_pt < 0.0){
				*da_data_pt = 0;
			}
		}


	}


};









#endif /* ACTIVATION_H_ */
