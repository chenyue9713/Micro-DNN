/*
 * cifar10Dataset.cpp
 *
 *  Created on: Aug 11, 2019
 *      Author: yue
 */

#include"cifar10Dataset.h"

cifar10Dataset::cifar10Dataset(vector<ifstream*>& imageFiles){

	for(uint8_t i = 0 ; i < imageFiles.size(); ++i){

		ifstream* imageFile = imageFiles[i];


		while(!imageFile->eof()){

			double label = double(readUint8(imageFile));

			if(label < 0.0 || label > 9.0)
				cout << "label error." << endl;

			if(imageFile->eof())
				break;

			vector<uint8_t> image;

			readUint8Array(imageFile, image, 3072);

			vector<double> image_double(image.begin(), image.end());

			this->m_Dataset.push_back(image_double);
			this->m_Labels.push_back(label);

		}
	}
	this->m_NumImages = this->m_Labels.size();

}

cifar10Dataset::~cifar10Dataset(){


}


void cifar10Dataset::preprocess(uint32_t NumTrainSet, uint32_t NumTestSet, uint32_t NumValSet){

	vector<image>::const_iterator first_train = this->m_Dataset.begin();
	vector<image>::const_iterator last_train = first_train + NumTrainSet;
	vector<double>::const_iterator first_train_l = this->m_Labels.begin();
	vector<double>::const_iterator last_train_l = first_train_l + NumTrainSet;
	vector<image> trainset_data;
	vector<double> trainset_labels;
	copy(first_train, last_train, back_inserter(trainset_data));
	copy(first_train_l, last_train_l, back_inserter(trainset_labels));
	this->m_trainset.setData(trainset_data);
	this->m_trainLabels.setData(trainset_labels);

	vector<image>::const_iterator first_val = this->m_Dataset.begin() + NumTrainSet;
	vector<image>::const_iterator last_val = first_val + NumValSet;
	vector<double>::const_iterator first_val_l = this->m_Labels.begin() + NumTrainSet;
	vector<double>::const_iterator last_val_l = first_val_l + NumValSet;
	vector<image> valset_data;
	vector<double> valset_labels;
	copy(first_val, last_val, back_inserter(valset_data));
	copy(first_val_l, last_val_l, back_inserter(valset_labels));
	this->m_valset.setData(valset_data);
	this->m_valLabels.setData(valset_labels);

	vector<image>::const_iterator first_test = this->m_Dataset.begin();
	vector<image>::const_iterator last_test = first_test + NumTestSet;
	vector<double>::const_iterator first_test_l = this->m_Labels.begin();
	vector<double>::const_iterator last_test_l = first_test_l + NumTestSet;
	vector<image> testset_data;
	vector<double> testset_labels;
	copy(first_test, last_test, back_inserter(testset_data));
	copy(first_test_l, last_test_l, back_inserter(testset_labels));
	this->m_testset.setData(testset_data);
	this->m_testLabels.setData(testset_labels);

	// Normalize the data: substract the mean image
	Vector mean_image = this->m_trainset.RowWiseMean();
	this->m_trainset = this->m_trainset.substractRowWise(mean_image);
	this->m_valset = this->m_valset.substractRowWise(mean_image);
	this->m_testset = this->m_testset.substractRowWise(mean_image);

}


uint8_t cifar10Dataset::readUint8(ifstream* imageFile){

	char buf;

	imageFile->read(&buf, 1);

	return buf;

}

void cifar10Dataset::readUint8Array(ifstream* imageFile, vector<uint8_t>& image, uint32_t NumBytes){

	for(uint32_t i = 0; i < NumBytes; ++i){
		char buf;
		imageFile->read(&buf, 1);
		image.push_back(buf);
	}


}




