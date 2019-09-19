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
#include <chrono>
#include "Matrix.h"
#include "Vector.h"

using namespace std;

//void read_2d_data(Matrix & in_Matrix, ifstream & file){
//
//	vector<vector<double>> in_data;
//
//	string line;
//
//	while(getline(file, line)){
//
//		stringstream ss(line);
//		double oneValue;
//		vector<double> c_data;
//		while(ss>> oneValue){
//			c_data.push_back(oneValue);
//		}
//		in_data.push_back(c_data);
//	}
//
//	in_Matrix.setData(in_data);
//}
//
//void read_1d_data(Vector & in_Vector, ifstream & file){
//
//	vector<double> in_data;
//
//	string line;
//
//	getline(file, line);
//
//	stringstream ss(line);
//	double oneValue;
//	while(ss>> oneValue){
//		in_data.push_back(oneValue);
//	}
//
//	in_Vector.setData(in_data);
//}

void read_2d_data(Matrix & in_Matrix, ifstream & file){
	
	vector<double> in_data;

	uint32_t row = 0;
	uint32_t col = 0;


	string line;

	while(getline(file, line)){
		
		stringstream ss(line);
		double oneValue;
		while(ss>> oneValue){
			in_data.push_back(oneValue);
			col++;
		}
		row++;
	}
	col /= row;
	in_Matrix.setData(row, col, in_data);
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



//void check_Matrix_correct(Matrix & old_Matrix, Matrix_opt & new_Matrix){
//
//	if( (old_Matrix.getRowNum() != new_Matrix.getRowNum()) || (old_Matrix.getColNum() != new_Matrix.getColNum()))
//		cout << "dimissions are not match" << endl;
//
//	double sum = 0.0;
//
//	vector<vector<double>> old_data = old_Matrix.getData();
//	double* new_data = new_Matrix.Data();
//
//	for(uint32_t i = 0; i < old_Matrix.getRowNum(); ++i){
//		for(uint32_t j = 0; j < old_Matrix.getColNum(); ++j){
//			if(old_data[i][j] - *new_data){
//				cout << "error" << endl;
//				return;
//			}
//			++new_data;
//		}
//	}
//	cout << "correct" << endl;
//}

//void check_Vector_correct(Vector & old_Vector, Vector_opt & new_Vector){
//	if(old_Vector.getSize() != new_Vector.getSize())
//		cout << "length are not match" << endl;
//
//	double sum = 0.0;
//
//	vector<double> old_data = old_Vector.getData();
//	double* new_data = new_Vector.Data();
//
//	for(uint32_t i = 0; i < old_Vector.getSize(); ++i){
//		if(old_data[i] - *new_data){
//			cout << "error" << endl;
//			return;
//		}
//		++new_data;
//	}
//	cout << "correct" << endl;
//}

void check_Matrix_correct(Matrix & old_Matrix, Matrix & new_Matrix){
	if( (old_Matrix.getRowNum() != new_Matrix.getRowNum()) || (old_Matrix.getColNum() != new_Matrix.getColNum()))
			cout << "dimissions are not match" << endl;
	double* old_Matrix_data_pt = old_Matrix.Data();
	double* new_Matrix_data_pt = new_Matrix.Data();
	for(uint32_t i = 0; i < old_Matrix.getRowNum()*old_Matrix.getColNum(); ++i){
		if(abs(*old_Matrix_data_pt - *new_Matrix_data_pt) > 0.000001){
			cout << "error" << endl;
			cout << *old_Matrix_data_pt << "vs" << *new_Matrix_data_pt <<endl;
			return;
		}
		++old_Matrix_data_pt;
		++new_Matrix_data_pt;
	}
	cout << "correct" << endl;
}

void check_Vector_correct(Vector & old_Vector, Vector & new_Vector){
	if(old_Vector.getSize() != new_Vector.getSize())
		cout << "length are not match" << endl;

	double* old_Vector_data_pt = old_Vector.Data();
	double* new_Vector_data_pt = new_Vector.Data();

	for(uint32_t i = 0; i < old_Vector.getSize(); ++i){
		if(abs(*old_Vector_data_pt - *new_Vector_data_pt) > 0.000001){
			cout << "error" << endl;
			cout << *old_Vector_data_pt << "vs" << *new_Vector_data_pt <<endl;
			return;
		}
		++old_Vector_data_pt;
		++new_Vector_data_pt;
	}
	cout << "correct" << endl;


}



int main(){

//	int row = 3;
//	int col = 4;
//
//	vector<vector<double>> t1 = {{1,2,3,4,2,5},
//						 	 	{4,5,7,3,5,3},
//								{5,8,1,3,2,5},
//								{5,1,1,3,2,5},
//								{5,1,1,3,2,5}};
//
//	vector<vector<double>> t3 = {{1,2,3,4,2,5},
//						 	 	{4,4,7,2,6,3},
//								{5,8,1,3,2,5},
//								{5,1,1,3,2,5},
//								{5,1,2,3,2,5}};
//
////
//	vector<vector<double>> t2 = {{1,2,3,2,5},
//							 	{1,1,7,3,8},
//								{5,3,1,2,9},
//								{5,3,1,2,4},
//								{5,3,1,2,8}};
////
////	vector<vector<double>> t6 = {{7,2,3},
////								{1,1,7},
////								{5,3,1},
////								{5,3,1}};
////
//	vector<double> v1 = {1,2,3,4,2,5,4,5,7,3,5,3,5,8,1,3,2,5,5,1,1,3,2,5,5,1,1,3,2,5};
//	vector<double> t4 = {1,2,3,4,2,5};
//	vector<double> t5 = {1,2,3,2,5,1,1,7,3,8,5,3,1,2,9,5,3,1,2,4,5,3,1,2,8};
//	vector<double> v6 = {1,2,3,4,2,5,4,4,7,2,6,3,5,8,1,3,2,5,5,1,1,3,2,5,5,1,2,3,2,5};
//
////
//	Vector_opt v2(v1);
//	Vector v3(v1);
//	Vector_opt v4(t4);
//	Vector v5;
//
//	Vector v_org1(t4);
////
//	Matrix m1_org(t1);
//	Matrix m3_org(t2);
//	Matrix m5_org(t3);
//
//	Matrix m2_org = m1_org.divideRowWise(v_org1);
//	Matrix m4_org = m1_org * 5;
//
//
//	Matrix m3_opt(5,6,v1);
//	Vector v3_opt = m3_opt.ColWiseSum();

//	Matrix_opt m4_opt(5,6,v6);
//	Matrix_opt m5_opt(5,5,t5);
//	Matrix_opt m6_opt = m3_opt * 5;
//
////	Matrix_opt m4 = m3_opt.divideRowWise(v4);
////
////	Vector v_org2 = m1_org.RowWiseStdev();
////	double sum_org = m1_org.sum();
////
////	Vector_opt v_opt2 = m3_opt.RowWiseStdev();
////	double sum_opt = m3_opt.sum();
////
////	cout << "sum : " << sum_org - sum_opt << endl;
//
//	check_Matrix_correct(m4_org, m6_opt);
////	check_Vector_correct(v_org2,v_opt2);
//
//	auto timer1 = chrono::high_resolution_clock::now();
//	for(int i = 0 ; i < 10000; ++i)
//		Matrix m4_org = m5_org * m1_org;
//	auto timer2 = chrono::high_resolution_clock::now();
//
//	auto duration = chrono::duration_cast<std::chrono::microseconds>( timer2 - timer1 ).count();
//
//	cout << duration << endl;
//
//	auto timer3 = chrono::high_resolution_clock::now();
//	for(int i = 0 ; i < 10000; ++i)
//		Matrix_opt m6_opt = m3_opt * m4_opt;
//	auto timer4 = chrono::high_resolution_clock::now();
//
//	auto duration2 = chrono::duration_cast<std::chrono::microseconds>( timer4 - timer3 ).count();
//
//	cout << duration2;

//	for(int i = 0; i < 4; ++i){
//		for(int j = 0 ; j < 3; ++j){
//			cout << m2.Data()[i][j] << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//
////	vector<double> m4_data = m4.getData();
//	double* m4_data = m4.Data();
//
//	for(int i = 0; i < 4; ++i){
//		for(int j = 0 ; j < 3; ++j){
//			cout << *m4_data << " ";
//			++m4_data;
//		}
//		cout << endl;
//	}


//
//	Vector v2 = m1.RowWiseStdev();
//
//	Matrix m2 = m1.divideRowWise(v2);
//
//	vector<double>* m2_data = m2.Data();
//
//	double* v2_data = v2.Data();
//
//	for(uint32_t i = 0; i < v2.getSize(); ++i)
//		cout << setw(3) <<v2_data[i] << " ";
//	cout << endl;
//	cout << endl;
//
//	for(uint32_t i = 0; i < m2.getRowNum(); ++i){
//		for(uint32_t j = 0; j < m2.getColNum(); ++j){
//			cout << setw(3) <<m2_data[i][j] << " ";
//		}
//		cout << endl;
//	}



//	vector<vector<double>> t3(3, vector<double>(4,0));
//
//	for(uint32_t i = 0; i < 3; ++i){
//		t3.data()[i]= t1[i];
//	}




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
//	vector<double>* m1_d = m1.Data();
//
//	for(uint32_t i = 0; i < m1.getRowNum(); ++i){
//		for(uint32_t j = 0; j < m1.getColNum(); ++j)
//			cout << setw(3) <<m1_d[i][j] << " ";
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
//	string dxfile ="test_data/dx.txt";
//	ifstream dxstream(dxfile);
//	Matrix dx;
//	read_2d_data(dx, dxstream);
//
//	string dwfile ="test_data/dw.txt";
//	ifstream dwstream(dwfile);
//	Matrix dw;
//	read_2d_data(dw, dwstream);
//
//	string dbfile ="test_data/db.txt";
//	ifstream dbstream(dbfile);
//	Vector db;
//	read_1d_data(db, dbstream);
//
//
//	FullyConnected fc1(12, 10, "relu");
//	fc1.Test_backward(x,w,b, dout);
//
//	Matrix m_dw = fc1.get_dw();
//	Vector m_db = fc1.get_db();
//	Matrix m_dx = fc1.get_dx();
//
//	cout << "check dx: " << endl;
//	check_Matrix_correct(m_dx,dx);
//	cout << "check dw: " << endl;
//	check_Matrix_correct(m_dw,dw);
//	cout << "check db: " << endl;
//	check_Vector_correct(m_db, db);

//	string xfile ="test_data/scores.txt";
//	ifstream xstream(xfile);
//	Matrix x;
//	read_2d_data(x, xstream);
//
//	string yfile ="test_data/target.txt";
//	ifstream ystream(yfile);
//	Vector y;
//	read_1d_data(y, ystream);
//
//	string dxfile ="test_data/dx_softmax.txt";
//	ifstream dxstream(dxfile);
//	Matrix dx_old;
//	read_2d_data(dx_old, dxstream);
//
//	SoftmaxCrossEntropy sc;
//	sc.evaluate(x,y);
//
//	double loss = sc.get_loss();
//	Matrix dx = sc.get_derivative();
//
//	check_Matrix_correct(dx_old,dx);
//	cout << loss << endl;

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
//	string dw1file = "test_data/sw_dw1.txt";
//	ifstream dw1stream(dw1file);
//	Matrix dw1;
//	read_2d_data(dw1,dw1stream);
//
//	string dw2file = "test_data/sw_dw2.txt";
//	ifstream dw2stream(dw2file);
//	Matrix dw2;
//	read_2d_data(dw2,dw2stream);
//
//	string db1file ="test_data/sw_db1.txt";
//	ifstream db1stream(db1file);
//	Vector db1;
//	read_1d_data(db1, db1stream);
//
//	string db2file ="test_data/sw_db2.txt";
//	ifstream db2stream(db2file);
//	Vector db2;
//	read_1d_data(db2, db2stream);
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
//
//	Matrix dw1_net = net.get_dw1();
//	Matrix dw2_net = net.get_dw2();
//	Vector db1_net = net.get_db1();
//	Vector db2_net = net.get_db2();
//
//	cout << "dw1:" <<endl;
//	check_Matrix_correct(dw1, dw1_net);
//	cout << "dw2:" <<endl;
//	check_Matrix_correct(dw2, dw2_net);
//	cout << "db1" << endl;
//	check_Vector_correct(db1, db1_net);
//	cout << "db2" << endl;
//	check_Vector_correct(db2, db2_net);


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
//
	cifar.preprocess(49000,1000,1000,false);
//
	Network net;
//
	Layer* fc1 = new FullyConnected(3072, 100, "relu");
	fc1->init(0.0, 0.001);
//	//fc1->set_parameters(w1,b1);
//
	Layer* fc2 = new FullyConnected(100, 10, "None");
	fc2->init(0.0, 0.001);
//	//fc2->set_parameters(w2,b2);
//
	Loss* softmax_loss = new SoftmaxCrossEntropy();

	net.add_layer(fc1);
	net.add_layer(fc2);
	net.set_loss(softmax_loss);

	SGD opt;
	opt.m_lr = 0.001;
	opt.m_decay = 0.9995;

	net.fit(opt,cifar.getTrainset(), cifar.getTrainLabels(), 200, 9);








}


