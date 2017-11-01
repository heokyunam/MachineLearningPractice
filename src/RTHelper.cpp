#include "RTHelper.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>


RTHelper::RTHelper() {
}

RTHelper::~RTHelper() {
    for(int i =0 ; i < datas.size(); i++) {
	delete[] datas[i];
    }
    datas.clear();
}

int RTHelper::getSize(char* header, int length) {
    char* temp = header;
    int size = 1;
    for(int i = 0; i < length; i++) {
	if(*temp == ',') {
	    size++;
	}
	temp++;
    }
    return size;
}

void RTHelper::load(char* filename) {
    ifstream is(filename);
    char buffer[BUFFER_SIZE];
    is.getline(buffer, BUFFER_SIZE);
    this->size = getSize(buffer, BUFFER_SIZE);
    
    while(!is.eof()) {
	is.getline(buffer, BUFFER_SIZE);
	
	stringstream ss;	
	ss.str(buffer);
	
	double* data = new double[size];
	double temp;
	for(int i = 0; i < size; i++) {
	    char comma;
	    ss >> temp;
	    ss >> comma;
	    data[i] = temp;
	}
	//cout << temp << endl;
	datas.push_back(data);
    }
}


void RTHelper::spartial4(char* filename, double x, double y) {
    //데이터 파일 하나에 다 넣을 예정
    vector<double*> writeDataVec;
    for(int i = 0; i < datas.size(); i++) {
	double* temp[4];
	for(int j = 0; j < 4; j++) {
	    double* tempD = new double[this->size];
	    memset(tempD, 0, this->size * sizeof(double));
	    temp[j] = tempD;
	    
	    writeDataVec.push_back(tempD);
	}
	
	for(int j = 0; j < this->size; j+=3) {
	    double tempX = datas[i][j];
	    double tempY = datas[i][j+1];
	    if(tempX > x) {
		if(tempY > y) {
		    temp[0][j] = tempX;
		    temp[0][j+1] = tempY;
		    temp[0][j+2] = datas[i][j+2];
		}
		else {
		    temp[1][j] = tempX;
		    temp[1][j+1] = tempY;
		    temp[1][j+2] = datas[i][j+2];
		}
	    }
	    else {
		if(tempY > x) {
		    temp[2][j] = tempX;
		    temp[2][j+1] = tempY;
		    temp[2][j+2] = datas[i][j+2];
		}
		else {
		    temp[3][j] = tempX;
		    temp[3][j+1] = tempY;
		    temp[3][j+2] = datas[i][j+2];
		}
	    }
	}
    }
    
    /*
    ofstream os(filename);
    write(os, data);
    os.flush();*/
}


void RTHelper::write(ofstream& of, vector<double*> data)
{
    for(int i = 0; i < data.size(); i++) {
	double* arr = data[i];/*
	for(int j = 0; j < this->size; j++) {
	    //of << arr[j];
	    if(j == this->size - 1) {
		//of << endl;
	    }
	    else {
		//of << ",";
	    }
	}*/
    }
}