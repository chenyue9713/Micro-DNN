/*
 * Matrix.cpp
 *
 *  Created on: Aug 19, 2019
 *      Author: yue
 */
#include "Matrix.h"


Matrix::Matrix(){
	this->m_row = 0;
	this->m_col = 0;

	this->m_size = this->m_row * this->m_col;
}

Matrix::~Matrix(){

}

Matrix::Matrix(const uint32_t row, const uint32_t col){
	this->m_row = row;
	this->m_col = col;
	this->m_size = this->m_row * this->m_col;

	this->m_data.resize(row*col);
}

Matrix::Matrix(const uint32_t row, const uint32_t col, vector<double>& in_data){
	if(row*col != in_data.size()){
		throw invalid_argument("[Matrix::constructor]: in_data size should be same with row X column.");
	}

	this->m_row = row;
	this->m_col = col;
	this->m_size = this->m_row * this->m_col;

	this->m_data = in_data;
}

void Matrix::resize(const uint32_t row, const uint32_t col){

	this->m_row = row;
	this->m_col = col;
	this->m_size = this->m_row * this->m_col;

	this->m_data.resize(row*col);
}

void Matrix::setData(const uint32_t row, const uint32_t col, vector<double>& in_data){
	if(row*col != in_data.size()){
		throw invalid_argument("[Matrix::constructor]: in_data size should be same with row X column.");
	}

	this->m_row = row;
	this->m_col = col;
	this->m_size = this->m_row * this->m_col;

	this->m_data = in_data;

}

double* Matrix::Data(){
	return this->m_data.data();
}


const uint32_t Matrix::getRowNum() const{
	return this->m_row;
}

const uint32_t Matrix::getColNum() const{
	return this->m_col;
}

const vector<double> Matrix::getData() const{
	return this->m_data;
}

Matrix Matrix::transpose() const{

	Matrix new_Matrix(this->m_col, this->m_row);

	double* new_Matrix_pt = new_Matrix.Data();

	for(uint32_t i = 0; i < this->m_col; ++i){
		for(uint32_t j = 0; j < this->m_row; ++j){
			*new_Matrix_pt = *(this->m_data.data() + j*this->m_col + i);
			++new_Matrix_pt;
		}
	}
	return new_Matrix;
}


Matrix Matrix::addColWise(Vector & in_Vector) const{

	if(in_Vector.getSize() != this->m_row){
		throw invalid_argument("[Matrix::addColWise]: in_Vector size should be same with number of row in Matrix.");
	}

	Matrix new_Matrix = *this;

	double* new_data_pt = new_Matrix.Data();
	double* in_data_pt = in_Vector.Data();

	for(uint32_t i = 0; i <this->m_col; ++i){
		for(uint32_t j = 0; j < this-> m_row; ++j){
			*(new_data_pt + j*this->m_col + i) += *in_data_pt;
			++in_data_pt;
		}
		in_data_pt = in_data_pt - this-> m_row;
	}

	return new_Matrix;
}

Matrix Matrix::addRowWise(Vector & in_Vector) const{

	if(in_Vector.getSize() != this->m_col){
		throw invalid_argument("[Matrix::addRowWise]: in_Vector size should be same with number of col in Matrix.");
	}

	Matrix new_Matrix = *this;

	double* new_data_pt = new_Matrix.Data();
	double* in_data_pt = in_Vector.Data();

	for(uint32_t i = 0; i <this->m_row; ++i){
		for(uint32_t j = 0; j < this->m_col; ++j){
			*(new_data_pt + i*this->m_col + j) += *in_data_pt;
			++in_data_pt;
		}
		in_data_pt = in_data_pt - this->m_col;
	}

	return new_Matrix;
}

Matrix Matrix::substractColWise(Vector & in_Vector) const{
	if(in_Vector.getSize() != this->m_row){
		throw invalid_argument("[Matrix::substractColWise]: in_Vector size should be same with number of row in Matrix.");
	}

	Matrix new_Matrix = *this;

	double* new_data_pt = new_Matrix.Data();
	double* in_data_pt = in_Vector.Data();

	for(uint32_t i = 0; i <this->m_col; ++i){
		for(uint32_t j = 0; j < this-> m_row; ++j){
			*(new_data_pt + j*this->m_col + i) -= *in_data_pt;
			++in_data_pt;
		}
		in_data_pt = in_data_pt - this-> m_row;
	}

	return new_Matrix;


}
Matrix Matrix::substractRowWise(Vector & in_Vector) const{
	if(in_Vector.getSize() != this->m_col){
		throw invalid_argument("[Matrix::substractRowWise]: in_Vector size should be same with number of col in Matrix.");
	}

	Matrix new_Matrix = *this;

	double* new_data_pt = new_Matrix.Data();
	double* in_data_pt = in_Vector.Data();

	for(uint32_t i = 0; i <this->m_row; ++i){
		for(uint32_t j = 0; j < this->m_col; ++j){
			*(new_data_pt + i*this->m_col + j) -= *in_data_pt;
			++in_data_pt;
		}
		in_data_pt = in_data_pt - this->m_col;
	}

	return new_Matrix;
}

Matrix Matrix::divideRowWise(Vector & in_Vector) const{
	if(in_Vector.getSize() != this->m_col){
		throw invalid_argument("[Matrix::substractRowWise]: in_Vector size should be same with number of col in Matrix.");
	}

	Matrix new_Matrix = *this;

	double* new_data_pt = new_Matrix.Data();
	double* in_data_pt = in_Vector.Data();

	for(uint32_t i = 0; i <this->m_row; ++i){
		for(uint32_t j = 0; j < this->m_col; ++j){
			*(new_data_pt + i*this->m_col + j) /= *in_data_pt;
			++in_data_pt;
		}
		in_data_pt = in_data_pt - this->m_col;
	}

	return new_Matrix;

}

Vector Matrix::ColWiseMax() const{

	Vector new_Vector(this->m_row);

	double* new_data_pt = new_Vector.Data();
	for (uint32_t i = 0; i <this->m_row; ++i){
		*(new_data_pt) = *max_element(this->m_data.begin()+i*this->m_col, this->m_data.begin()+(i+1)*this->m_col);
		++new_data_pt;
	}

	return new_Vector;

}

Vector Matrix::RowWiseMax() const{

	Vector new_Vector(this->m_col);

	double* new_data_pt = new_Vector.Data();

	for (uint32_t i = 0; i <this->m_col; ++i){
		double max = 0;
		for(uint32_t j = 0; j <this-> m_row; ++j){
			double col_num = *(this->m_data.begin() + j*(this->m_col) + i);
			if(max < col_num)
				max = col_num;
		}
		*(new_data_pt) = max;
		++new_data_pt;
	}

	return new_Vector;
}

Vector Matrix::ColWiseSum() const{
	Vector new_Vector(this->m_row);

	double* new_data_pt = new_Vector.Data();
	for (uint32_t i = 0; i <this->m_row; ++i){
		*(new_data_pt) = accumulate(this->m_data.begin()+i*this->m_col, this->m_data.begin()+(i+1)*this->m_col,0.0);
		++new_data_pt;
	}

	return new_Vector;
}

Vector Matrix::RowWiseSum() const{

	Vector new_Vector(this->m_col);

	double* new_data_pt = new_Vector.Data();

	for (uint32_t i = 0; i <this->m_col; ++i){
		double sum = 0;
		for(uint32_t j = 0; j <this->m_row; ++j){
			sum += *(this->m_data.begin() + j*(this->m_col) + i);
		}
		*(new_data_pt) = sum;
		++new_data_pt;
	}
	return new_Vector;
}

Vector Matrix::RowWiseMean() const{

	Vector new_Vector(this->m_col);

	double* new_data_pt = new_Vector.Data();

	for (uint32_t i = 0; i <this->m_col; ++i){
		double sum = 0;
		for(uint32_t j = 0; j <this->m_row; ++j){
			sum += *(this->m_data.begin() + j*(this->m_col) + i);
		}
		*(new_data_pt) = sum / this->m_row;
		++new_data_pt;
	}
	return new_Vector;
}


Vector Matrix::RowWiseStdev() const{

	Vector new_Vector(this->m_col);

	double* new_data_pt = new_Vector.Data();

	for (uint32_t i = 0; i <this->m_col; ++i){
		double col_sum = 0.0;
		double var = 0.0;
		for(uint32_t j = 0; j <this->m_row; ++j){
			col_sum += *(this->m_data.begin() + j*(this->m_col) + i);
		}
		double col_mean = col_sum / this->m_row;
		for(uint32_t j = 0; j <this->m_row; ++j){
			double col_num = *(this->m_data.begin() + j*(this->m_col) + i);
			var += pow(col_num - col_mean,2);
		}
		var /= this->m_row;
		*(new_data_pt) = sqrt(var);
		++new_data_pt;
	}
	return new_Vector;

}

const double Matrix::sum() const{

	double sum = accumulate(this->m_data.begin(),this->m_data.end(),0.0);

	return sum;
}

Matrix Matrix::dotProduct(Matrix & in_Matrix) const{

	if(this->m_col != in_Matrix.getRowNum()){
		throw invalid_argument("[Matrix::dotProduct]: in_Matrix size should be compitable with Matrix's size.");
	}

	uint32_t new_col = in_Matrix.getColNum();

	Matrix new_Matrix(this->m_row, new_col);

	double* new_data_pt = new_Matrix.Data();
	double* in_data_pt = in_Matrix.Data();
	vector<double> m_data_cp = this->m_data;
	double* m_data_pt = m_data_cp.data();

	for(uint32_t i = 0; i <this->m_row; i += 2){
		for(uint32_t j = 0; j < new_col; j += 2){
			double acc00 = 0.0;
			double acc01 = 0.0;
			double acc10 = 0.0;
			double acc11 = 0.0;
			for(uint32_t k = 0; k <this->m_col; ++k){
				//*(new_data_pt + i*new_col + j) += *(m_data_pt + i*this->m_col + k) * (*(in_data_pt + k*new_col + j));
				acc00 += *(m_data_pt + i*this->m_col + k) * (*(in_data_pt + k*new_col + j));
				if(!(j == new_col - 1))
					acc01 += *(m_data_pt + i*this->m_col + k) * (*(in_data_pt + k*new_col + j + 1));
				if(!(i == this->m_row - 1))
					acc10 += *(m_data_pt + (i+1)*this->m_col + k) * (*(in_data_pt + k*new_col + j));
				if(!(j == new_col - 1) && !(i == this->m_row - 1))
					acc11 += *(m_data_pt + (i+1)*this->m_col + k) * (*(in_data_pt + k*new_col + j + 1));
			}
			*(new_data_pt + i*new_col + j) = acc00;
			if(!(j == new_col - 1))
				*(new_data_pt + i*new_col + j+1) = acc01;
			if(!(i == this->m_row - 1))
				*(new_data_pt + (i+1)*new_col + j) = acc10;
			if(!(j == new_col - 1) && !(i == this->m_row - 1))
				*(new_data_pt + (i+1)*new_col + j+1) = acc11;
		}
	}

	return new_Matrix;	
}

Matrix Matrix::operator*(Matrix & in_Matrix) const{

	if((this->m_row != in_Matrix.getRowNum()) || (this->m_col != in_Matrix.getColNum())){
		throw invalid_argument("[Matrix::*]: in_Vector size should be same with Matrix's size.");
	}

	Matrix new_Matrix = *this;

	double* new_data_pt = new_Matrix.Data();
	double* in_data_pt = in_Matrix.Data();

	for(uint32_t i = 0; i <this->m_row; ++i){
		for(uint32_t j = 0; j <this->m_col; ++j){
			*new_data_pt *= *in_data_pt;
			++new_data_pt;
			++in_data_pt;
		}
	}
	return new_Matrix;
}


Matrix Matrix::operator*(const double in_num) const{

	Matrix new_Matrix = *this;

	double* new_data_pt = new_Matrix.Data();

	for(uint32_t i = 0; i <this->m_row; ++i){
		for(uint32_t j = 0; j <this->m_col; ++j){
			*new_data_pt *= in_num;
			++new_data_pt;
		}
	}
	return new_Matrix;
}


Matrix Matrix::operator-(Matrix& in_Matrix) const{

	if(in_Matrix.getRowNum() != this->m_row || in_Matrix.getColNum() != this->m_col){
		throw invalid_argument("[Matrix::operator-]: in_Matrix's size should be same with Matrix's size.");
	}

	Matrix new_Matrix = *this;

	double* new_data_pt = new_Matrix.Data();

	double* in_data_pt = in_Matrix.Data();

	for(uint32_t i = 0; i < this->m_size; ++i, ++new_data_pt, ++in_data_pt){
		*new_data_pt -= *in_data_pt;
	}
	return new_Matrix;

}

Matrix Matrix::operator+(Matrix& in_Matrix) const{
	
	if(in_Matrix.getRowNum() != this->m_row || in_Matrix.getColNum() != this->m_col){
		throw invalid_argument("[Matrix::operator-]: in_Matrix's size should be same with Matrix's size.");
	}

	Matrix new_Matrix = *this;

	double* new_data_pt = new_Matrix.Data();

	double* in_data_pt = in_Matrix.Data();

	for(uint32_t i = 0; i < this->m_size; ++i,++new_data_pt, ++in_data_pt){
		*new_data_pt += *in_data_pt;
	}

	return new_Matrix;
}















