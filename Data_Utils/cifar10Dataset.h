/*
 * cifar10Dataset.h
 *
 *  Created on: Aug 11, 2019
 *      Author: yue
 */

#ifndef TEST_DATA_CIFAR10_CIFAR10DATASET_H_
#define TEST_DATA_CIFAR10_CIFAR10DATASET_H_

#include"../Config.h"
#include"../Matrix.h"
#include"../Vector.h"

using namespace std;

class cifar10Dataset{

private:

	vector<double> m_Dataset;

	Matrix m_trainset;

	Matrix m_testset;

	Matrix m_valset;

	vector<double> m_Labels;

	Vector m_trainLabels;

	Vector m_testLabels;

	Vector m_valLabels;

	uint32_t m_NumImages;

	uint32_t m_ImageSize;

	uint8_t readUint8(ifstream * imageFile);

	void readUint8Array(ifstream * imageFile, vector<uint8_t>& image, uint32_t NumBytes);

public:

	void preprocess(uint32_t NumTrainSet, uint32_t NumTestSet, uint32_t NumValSet, bool stdev);

	cifar10Dataset(vector<ifstream*>& imageFiles);

	~cifar10Dataset();

	Matrix getTrainset() const;

	Vector getTrainLabels() const;

	Matrix getTestset() const;

	Vector getTestLabels() const;

	Matrix getValset() const;

	Vector getValLabels() const;

//	const vector<image> getDataset() const;


};



#endif /* TEST_DATA_CIFAR10_CIFAR10DATASET_H_ */
