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


void cifar10Dataset::preprocess(uint32_t NumTrainSet, uint32_t NumTestSet, uint32_t NumValSet, bool stdev){


	this->m_trainset.resize(NumTrainSet,3072);
	this->m_trainLabels.resize(NumTrainSet);
	for(uint32_t i = 0; i < NumTrainSet; ++i){
		this->m_trainset.Data()[i] = this->m_Dataset[i];
		this->m_trainLabels.Data()[i] = this->m_Labels[i];
	}


//	vector<image>::const_iterator first_train = this->m_Dataset.begin();
//	vector<image>::const_iterator last_train = first_train + NumTrainSet;
//	vector<double>::const_iterator first_train_l = this->m_Labels.begin();
//	vector<double>::const_iterator last_train_l = first_train_l + NumTrainSet;
//	vector<image> trainset_data;
//	vector<double> trainset_labels;
//	copy(first_train, last_train, back_inserter(trainset_data));
//	copy(first_train_l, last_train_l, back_inserter(trainset_labels));
//	this->m_trainset.setData(trainset_data);
//	this->m_trainLabels.setData(trainset_labels);
//	trainset_data.resize(0);
//	trainset_data.shrink_to_fit();
//	trainset_labels.resize(0);
//	trainset_labels.shrink_to_fit();
//	vector<image>().swap(trainset_data);
//	vector<double>().swap(trainset_labels);

	this->m_valset.resize(NumValSet, 3072);
	this->m_valLabels.resize(NumValSet);
	for(uint32_t i = 0; i < NumValSet; ++i){
		this->m_valset.Data()[i] = this->m_Dataset[NumTrainSet+i];
		this->m_valLabels.Data()[i] = this->m_Labels[NumTrainSet+i];
	}



//	vector<image>::const_iterator first_val = this->m_Dataset.begin() + NumTrainSet;
//	vector<image>::const_iterator last_val = first_val + NumValSet;
//	vector<double>::const_iterator first_val_l = this->m_Labels.begin() + NumTrainSet;
//	vector<double>::const_iterator last_val_l = first_val_l + NumValSet;
//	vector<image> valset_data;
//	vector<double> valset_labels;
//	copy(first_val, last_val, back_inserter(valset_data));
//	copy(first_val_l, last_val_l, back_inserter(valset_labels));
//	this->m_valset.setData(valset_data);
//	this->m_valLabels.setData(valset_labels);
//	valset_data.resize(0);
//	valset_data.shrink_to_fit();
//	valset_labels.resize(0);
//	valset_labels.shrink_to_fit();

	this->m_testset.resize(NumTestSet, 3072);
	this->m_testLabels.resize(NumTestSet);
	for(uint32_t i = 0; i < NumTestSet; ++i){
		this->m_testset.Data()[i] = this->m_Dataset[i];
		this->m_testLabels.Data()[i] = this->m_Labels[i];
	}

//	vector<image>::const_iterator first_test = this->m_Dataset.begin();
//	vector<image>::const_iterator last_test = first_test + NumTestSet;
//	vector<double>::const_iterator first_test_l = this->m_Labels.begin();
//	vector<double>::const_iterator last_test_l = first_test_l + NumTestSet;
//	vector<image> testset_data;
//	vector<double> testset_labels;
//	copy(first_test, last_test, back_inserter(testset_data));
//	copy(first_test_l, last_test_l, back_inserter(testset_labels));
//	this->m_testset.setData(testset_data);
//	this->m_testLabels.setData(testset_labels);
//	testset_data.resize(0);
//	testset_data.shrink_to_fit();
//	testset_labels.resize(0);
//	testset_labels.shrink_to_fit();
	// free up memory in m_Dataset and m_Labels.
	vector<image>().swap(this->m_Dataset);
	vector<double>().swap(this->m_Labels);


	// Normalize the data: substract the mean image
	Vector mean_image = this->m_trainset.RowWiseMean();
	this->m_trainset = this->m_trainset.substractRowWise(mean_image);
	this->m_valset = this->m_valset.substractRowWise(mean_image);
	this->m_testset = this->m_testset.substractRowWise(mean_image);

	// Normalize the data: divided by standard deviation
	if (stdev){
		Vector stdev_image = this->m_trainset.RowWiseStdev();
		this->m_trainset = this->m_trainset.divideRowWise(stdev_image);
		this->m_valset = this->m_valset.divideRowWise(stdev_image);
		this->m_testset = this->m_testset.divideRowWise(stdev_image);
	}
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

Matrix cifar10Dataset::getTrainset() const{
	return this->m_trainset;
}

Vector cifar10Dataset::getTrainLabels() const{
	return this->m_trainLabels;
}

Matrix cifar10Dataset::getTestset() const{
	return this->m_testset;
}

Vector cifar10Dataset::getTestLabels() const{
	return this->m_testLabels;
}

Matrix cifar10Dataset::getValset() const{
	return this->m_valset;
}

Vector cifar10Dataset::getValLabels() const{
	return this->m_valLabels;
}






