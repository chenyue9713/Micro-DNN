/*
 * main.cpp
 *
 *  Created on: Aug 6, 2019
 *      Author: yue
 */

#include"Config.h"
#include"Micro-DNN.h"
#include<iomanip>
#include<sstream>

using namespace std;

void read_2d_data(Matrix & in_Matrix, ifstream & file){
	
	vector<vector<double>> in_data;

	string line;

	while(getline(file, line)){
		
		stringstream ss(line);
		double oneValue;
		vector<double> c_data;
		while(ss>> oneValue){
			c_data.push_back(oneValue);
		}
		in_data.push_back(c_data);
	}

	in_Matrix.setData(in_data);
}


void read_1d_data(Vector & in_Vector, ifstream & file){

	vector<double> in_data;

	string line;

	getline(file, line);

	stringstream ss(line);
	double oneValue;
	while(ss>> oneValue){
		in_data.push_back(oneValue);
	}

	in_Vector.setData(in_data);
}




int main(){

//	int row = 3;
//	int col = 4;
//
	vector<vector<double>> t1 = {{1,2,3,4},
						 	 	{4,5,7,3},
								{5,8,1,3}};

//
//	vector<vector<double>> t2 = {{1,2,3,2},
//							 	{1,1,7,3},
//								{5,3,1,2}};
//
//	vector<vector<double>> t6 = {{7,2,3},
//								{1,1,7},
//								{5,3,1},
//								{5,3,1}};
//
//	vector<double> t3 = {1,2,3,4};
//	vector<double> t4 = {1,2,3};
//	vector<double> t5 = {5,3,6,1};
//
//	Vector v1(t3);
//	Vector v2(t4);
//	Vector v4(t5);
//
	Matrix m1(t1);
//
//	Matrix m2(t2);
//
//	Matrix m4(t6);
//
//	Matrix m3 = m1.dotProduct(m4);
//
//	Vector v3 = v1 * v4;
//
//
//
//	vector<double>* m3_d = m3.Data();
//
//	for(uint32_t i = 0; i < m3.getRowNum(); ++i){
//		for(uint32_t j = 0; j < m3.getColNum(); ++j)
//			cout << setw(3) <<m3_d[i][j] << " ";
//		cout << endl;
//	}
//
//	cout<< endl;
//
//	double* v3_d = v3.Data();
//	for(uint32_t i = 0; i < v3.getSize(); ++i)
//		cout<< setw(3) << v3_d[i] << " ";

//	string xfile ="test_data/x.txt";
//	ifstream xstream(xfile);
//	Matrix x;
//	read_2d_data(x, xstream);
//
//	string wfile ="test_data/w.txt";
//	ifstream wstream(wfile);
//	Matrix w;
//	read_2d_data(w, wstream);
//
//	string bfile ="test_data/b.txt";
//	ifstream bstream(bfile);
//	Vector b;
//	read_1d_data(b, bstream);
//
//	string doutfile ="test_data/dout.txt";
//	ifstream doutstream(doutfile);
//	Matrix dout;
//	read_2d_data(dout, doutstream);
//
//
//	FullyConnected fc1(12, 10, "relu");
//	fc1.Test_backward(x,w,b, dout);



//	vector<vector<double>> x_data = x.getData();
//	vector<vector<double>> w_data = w.getData();
//
//	for(uint32_t i = 0; i < w.getRowNum(); ++i){
//		for(uint32_t j = 0; j < w.getColNum(); ++j)
//			cout << setw(3) <<w_data[i][j] << " ";
//		cout << endl;
//	}

	//cout << *max_element(t1[0].begin(), t1[0].end()) << endl;

//	Vector V1 = m1.ColWiseMax();
//	Vector V2 = m1.RowWiseMax();
//
//	vector<double> v1 = V1.getData();
//	vector<double> v2 = V2.getData();
//
//	for(int i = 0; i < v2.size(); ++i)
//		cout << v2[i] << " ";


//	string xfile ="test_data/sw_x.txt";
//	ifstream xstream(xfile);
//	Matrix x;
//	read_2d_data(x, xstream);
//
//	string yfile ="test_data/sw_y.txt";
//	ifstream ystream(yfile);
//	Vector target;
//	read_1d_data(target, ystream);
//
//	string w1file = "test_data/sw_w1.txt";
//	ifstream w1stream(w1file);
//	Matrix w1;
//	read_2d_data(w1,w1stream);
//
//	string w2file = "test_data/sw_w2.txt";
//	ifstream w2stream(w2file);
//	Matrix w2;
//	read_2d_data(w2,w2stream);
//
//	string b1file ="test_data/sw_b1.txt";
//	ifstream b1stream(b1file);
//	Vector b1;
//	read_1d_data(b1, b1stream);
//
//	string b2file ="test_data/sw_b2.txt";
//	ifstream b2stream(b2file);
//	Vector b2;
//	read_1d_data(b2, b2stream);
//
//	Network net;
//
//	Layer* fc1 = new FullyConnected(5, 50, "relu");
//	fc1->set_parameters(w1,b1);
//
//	Layer* fc2 = new FullyConnected(50, 7, "None");
//	fc2->set_parameters(w2,b2);
//
//	Loss* softmax_loss = new SoftmaxCrossEntropy();
//
//	net.add_layer(fc1);
//	net.add_layer(fc2);
//	net.set_loss(softmax_loss);
//
//	net.feedForward(x);
//
//	net.backProp(x, target);

//	Loss* sc1 = new SoftmaxCrossEntropy();
//
//	sc1->evaluate(scores, target);
//
//
//
//	return 0;

	string dir = "/home/yue/eclipse-workspace/Micro-DNN/test_data/CIFAR10/cifar-10-batches-bin";

	ifstream Image1File((dir + "/data_batch_1.bin").c_str(), ios::in|ios::binary);
	ifstream Image2File((dir + "/data_batch_2.bin").c_str(), ios::in|ios::binary);
	ifstream Image3File((dir + "/data_batch_3.bin").c_str(), ios::in|ios::binary);
	ifstream Image4File((dir + "/data_batch_4.bin").c_str(), ios::in|ios::binary);
	ifstream Image5File((dir + "/data_batch_5.bin").c_str(), ios::in|ios::binary);

	vector<ifstream*> ImageFiles;
	ImageFiles.push_back(&Image1File);
	ImageFiles.push_back(&Image2File);
	ImageFiles.push_back(&Image3File);
	ImageFiles.push_back(&Image4File);
	ImageFiles.push_back(&Image5File);
//
	cifar10Dataset cifar(ImageFiles);

	cifar.preprocess(49000,1000,1000);



}


