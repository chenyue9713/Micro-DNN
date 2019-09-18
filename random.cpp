/*
 * random.cpp
 *
 *  Created on: Aug 14, 2019
 *      Author: yue
 */

#include"Config.h"
#include "Matrix.h"
#include "Vector.h"


inline void shuffle_batch(uint16_t batch_size, uint32_t numSample, Matrix& batch_mask){

	// size of batch_x_mask is numBatch X (batch_size + 1)
	//batch_mask data format: [[0(real batch number),1~batch_size(mask)],
	//							 [.......................................],
	//							 ..........................................]

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,numSample-1);

	const int numBatch = (numSample - 1) / batch_size + 1;
	const int last_batch_size = numSample - (numBatch - 1) * batch_size;

	batch_mask.resize(numBatch, batch_size+1);
	double* batch_mask_pt = batch_mask.Data();

	for(int i = 0 ; i < numBatch; ++i){
		const int bsize = (i == numBatch - 1) ? last_batch_size : batch_size;
		*(batch_mask_pt + i * batch_size) = bsize;
		//batch_mask.Data()[i][0] = bsize;
		for(int j = 1; j < bsize + 1; ++j)
			*(batch_mask_pt + i * batch_size + j) = distribution(generator);
	}

}



