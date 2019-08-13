/*
 * Matrix.cpp
 *
 *  Created on: Aug 6, 2019
 *      Author: yue
 */
#include"Matrix.h"

Matrix::Matrix(){

	this->m_row = 0;
	this->m_col = 0;
}

Matrix::Matrix(const uint32_t row, const uint32_t col){

	this->m_row = row;
	this->m_col = col;

	for (uint32_t i = 0; i < row; ++i){
		vector<double> c_vector(col,0);
		this->m_data.push_back(c_vector);
	}

}

Matrix::Matrix(const vector<vector<double>>& in_data){
	this->m_row = in_data.size();
	this->m_col = in_data[0].size();

	this->m_data = in_data;
}

const vector<vector<double>> Matrix::getData() const{

	return this->m_data;
}

vector<double>* Matrix::Data(){

	return this->m_data.data();
}

void Matrix::setData(const vector<vector<double>> & in_data){
	this->m_row = in_data.size();
	this->m_col = in_data[0].size();

	this->m_data = in_data;
}

void Matrix::resize(const uint32_t row, const uint32_t col){

	this->m_row = row;
	this->m_col = col;

	for (uint32_t i = 0; i < row; ++i){
		vector<double> c_vector(col,0);
		this->m_data.push_back(c_vector);
	}

}

const uint32_t Matrix::getRowNum() const{
	return this->m_row;
}
	

const uint32_t Matrix::getColNum() const{

	return this->m_col;
}




const Matrix Matrix::transpose() const{

	vector<vector<double>> new_data;

	for (uint32_t i = 0; i < this->m_col; ++i){
		vector<double> c_vector;
		for(uint32_t j = 0; j < this->m_row; ++j){
			c_vector.push_back(this->m_data[j][i]);
		}
		new_data.push_back(c_vector);
	}

	Matrix new_matrix(new_data);

	return new_matrix;
}

Matrix Matrix::addColWise(Vector & in_Vector) const{

	vector<vector<double>> new_data = this->m_data;
	vector<double> in_data = in_Vector.getData();

	if(in_Vector.getSize() != this->m_row){
		throw invalid_argument("[Matrix::addColWise]: in_Vector size should be same with number of row in Matrix.");
	}


	for(uint32_t i = 0; i < this-> m_col; ++i){
		for(uint32_t j = 0; j < this-> m_row; ++j){
			new_data[j][i] += in_data[j];
		}
	}

	Matrix new_matrix(new_data);
	return new_matrix;
}

Matrix Matrix::addRowWise(Vector & in_Vector) const{

	vector<vector<double>> new_data = this->m_data;
	vector<double> in_data = in_Vector.getData();

	if(in_Vector.getSize() != this->m_col){
		throw invalid_argument("[Matrix::addRowWise]: in_Vector size should be same with number of column in Matrix.");
	}

	for(uint32_t i = 0; i < this-> m_row; ++i){
		for(uint32_t j = 0; j < this-> m_col; ++j){
			new_data[i][j] += in_data[j];
		}
	}

	Matrix new_matrix(new_data);
	return new_matrix;
}

Matrix Matrix::substractColWise(const Vector & in_Vector) const{

	vector<vector<double>> new_data = this->m_data;
	vector<double> in_data = in_Vector.getData();

	if(in_Vector.getSize() != this->m_row){
		throw invalid_argument("[Matrix::substractColWise]: in_Vector size should be same with number of row in Matrix.");
	}


	for(uint32_t i = 0; i < this-> m_col; ++i){
		for(uint32_t j = 0; j < this-> m_row; ++j){
			new_data[j][i] -= in_data[j];
		}
	}
	Matrix new_matrix(new_data);
	return new_matrix;
}

Matrix Matrix::substractRowWise(const Vector & in_Vector) const{

	vector<vector<double>> new_data = this->m_data;
	vector<double> in_data = in_Vector.getData();

	if(in_Vector.getSize() != this->m_col){
		throw invalid_argument("[Matrix::substractRowWise]: in_Vector size should be same with number of column in Matrix.");
	}

	for(uint32_t i = 0; i < this-> m_row; ++i){
		for(uint32_t j = 0; j < this-> m_col; ++j){
			new_data[i][j] -= in_data[j];
		}
	}

	Matrix new_matrix(new_data);
	return new_matrix;
}

const Vector Matrix::ColWiseMax() const{

	Vector new_Vector(this->m_row);

	double* new_data = new_Vector.Data();
	for(uint32_t i = 0; i < this->m_row; ++i){
		double max = *max_element(this->m_data[i].begin(), this->m_data[i].end());
		new_data[i] = max;
	}
	return new_Vector;
}


const Vector Matrix::RowWiseMax() const{

	Vector new_Vector(this->m_col);
	double* new_data = new_Vector.Data();

	Matrix transpose_Matrix = transpose();
	vector<vector<double>> trans_data = transpose_Matrix.getData();

	for(uint32_t i = 0; i < transpose_Matrix.getRowNum(); ++i){
		double max = *max_element(trans_data[i].begin(), trans_data[i].end());
		new_data[i] = max;
	}

	return new_Vector;

	
}

Vector Matrix::ColWiseSum() const{

	vector<double> new_data;

	for(uint32_t i = 0; i < this-> m_row; ++i){
		double row_sum = 0;
		for(uint32_t j = 0; j < this-> m_col; ++j){
			row_sum += this->m_data[i][j];
		}
		new_data.push_back(row_sum);
	}

	Vector new_Vector(new_data);

	return new_Vector;

}


Vector Matrix::RowWiseSum() const{

	vector<double> new_data;

	for(uint32_t i = 0; i < this-> m_col; ++i){
		double col_sum = 0;
		for(uint32_t j = 0; j < this-> m_row; ++j){
			col_sum += this->m_data[j][i];
		}
		new_data.push_back(col_sum);
	}

	Vector new_Vector(new_data);

	return new_Vector;

}


Vector Matrix::RowWiseMean() const{

	vector<double> new_data;

	for(uint32_t i = 0; i < this-> m_col; ++i){
		double col_sum = 0;
		for(uint32_t j = 0; j < this-> m_row; ++j){
			col_sum += this->m_data[j][i];
		}
		double col_mean = col_sum / this->m_row;
		new_data.push_back(col_mean);
	}

	Vector new_Vector(new_data);

	return new_Vector;

}

const double Matrix::sum() const{

	double sum = 0;

	for(uint32_t i = 0; i <this-> m_row; ++i){
		for(uint32_t j = 0; j < this-> m_col; ++j)
			sum += m_data[i][j];
	}

	return sum;

}


Matrix Matrix::dotProduct(const Matrix & in_Matrix) const {

	if(this->m_col != in_Matrix.getRowNum()){
		throw invalid_argument("[Matrix::dotProduct]: in_Matrix size should be compitable with Matrix's size.");
	}

	vector<vector<double>> in_data = in_Matrix.getData();

	Matrix new_Matrix(this->m_row, in_Matrix.getColNum());
	vector<double>* new_data = new_Matrix.Data();

	for(uint32_t i = 0; i < this->m_row; ++i){
		vector<double> c_vector;
		for (uint32_t j = 0; j < in_Matrix.getColNum(); ++j){
			double temp_sum = 0;
			for(uint32_t k = 0; k < this->m_col; ++k){
				temp_sum += this->m_data[i][k] * in_data[k][j];
			}
			c_vector.push_back(temp_sum);
		}
		new_data[i] = c_vector;
	}

	return new_Matrix;

}

Matrix Matrix::operator*(const Matrix & in_Matrix) const{

	if((this->m_row != in_Matrix.getRowNum()) || (this->m_col != in_Matrix.getColNum())){
		throw invalid_argument("[Matrix::*]: in_Vector size should be same with Matrix's size.");
	}

	vector<vector<double>> in_data = in_Matrix.getData();

	Matrix new_Matrix(this->m_row, this->m_col);

	vector<double>* new_data = new_Matrix.Data();

	for(uint32_t i = 0; i < this->m_row; ++i){
		for(uint32_t j = 0; j < this->m_col; ++j)
			new_data[i][j] = this->m_data[i][j] * in_data[i][j];
	}

	return new_Matrix;

}
	

Matrix Matrix::operator*(const double in_num) const{

	Matrix new_Matrix(m_data);

	vector<double>* new_data = new_Matrix.Data();

	for(uint32_t i = 0; i < this->m_row; ++i)
		for(uint32_t j = 0; j < this-> m_col; ++j)
			new_data[i][j] *= in_num;

	return new_Matrix;
}

Matrix Matrix::operator-(const Matrix& in_Matrix) const{

	if(in_Matrix.getRowNum() != this->m_row || in_Matrix.getColNum() != this->m_col){
		throw invalid_argument("[Matrix::operator-]: in_Matrix's size should be same with Matrix's size.");
	}

	Matrix new_Matrix = *this;
	vector<double>* new_data = new_Matrix.Data();
	vector<vector<double>> in_data = in_Matrix.getData();

	for(uint32_t i = 0; i < this-> m_row; ++i){
		for(uint32_t j = 0; j < this-> m_col; ++j)
			new_data[i][j] -= in_data[i][j];
	}
	return new_Matrix;
}

Matrix Matrix::operator+(const Matrix& in_Matrix) const{

	if(in_Matrix.getRowNum() != this->m_row || in_Matrix.getColNum() != this->m_col){
		throw invalid_argument("[Matrix::operator-]: in_Matrix's size should be same with Matrix's size.");
	}

	Matrix new_Matrix = *this;
	vector<double>* new_data = new_Matrix.Data();
	vector<vector<double>> in_data = in_Matrix.getData();

	for(uint32_t i = 0; i < this-> m_row; ++i){
		for(uint32_t j = 0; j < this-> m_col; ++j)
			new_data[i][j] += in_data[i][j];
	}
	return new_Matrix;
}
