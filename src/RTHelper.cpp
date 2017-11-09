#include "RTHelper.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>


RTHelper::RTHelper() {
  random_tree = RTrees::create();
}

RTHelper::~RTHelper() {/*
    for(int i =0 ; i < datas.size(); i++) {
	delete[] datas[i];
    }
    datas.clear();*/
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
    memcpy(header, buffer, BUFFER_SIZE);
    
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


void RTHelper::spartial4(char* filename, double x, double y, double z) {
    //데이터 파일 하나에 다 넣을 예정
    vector<double*> writeDataVec;
    for(int i = 0; i < datas.size(); i++) {
	double* temp[8];
	bool notZero[8];
	for(int j = 0; j < 8; j++) {
	    double* tempD = new double[this->size];
	    memset(tempD, 0, this->size * sizeof(double));
	    tempD[this->size-1] = datas[i][this->size-1];
	    temp[j] = tempD;
	    notZero[j] = false;
	}
	
	for(int j = 0; j < this->size - 1; j+=3) {
	    double tempX = datas[i][j];
	    double tempY = datas[i][j+1];
	    double tempZ = datas[i][j+2];
	    
	    int idxX = (tempX > x)? 0 : 1;
	    int idxY = (tempY > y)? 0 : 1;
	    int idxZ = (tempZ > z)? 0 : 1;
	    
	    int idx = idxX + 2 * idxY + 4 * idxZ;
	    temp[idx][j] = tempX;
	    temp[idx][j+1] = tempY;
	    temp[idx][j+2] = tempZ;
	    
	    notZero[idx] = true;
	}
	for(int j = 0; j < 8; j++) {
	    if(notZero[j])
		writeDataVec.push_back(temp[j]);
	    else
		cout << "e";
	}
	cout << endl;
    }
    
    
    ofstream os(filename);
    write(os, writeDataVec);
    os.flush();
}


void RTHelper::write(ofstream& of, vector<double*> data)
{
    of << header << endl;
    for(int i = 0; i < data.size(); i++) {
	double* arr = data[i];
	for(int j = 0; j < this->size; j++) {
	    of << arr[j];
	    if(j == this->size - 1) {
		of << endl;
	    }
	    else {
		of << ",";
	    }
	}
    }
}


void RTHelper::addTrainData(char* filename) {
    Ptr<TrainData> train = TrainData::loadFromCSV(filename, 1, -1, -1);
    random_tree->train(train);
}


void RTHelper::save(char* filename) {
    random_tree->save(filename);
}


Mat RTHelper::predict(char* filename) {
    Mat mat;
    Ptr<TrainData> predict = TrainData::loadFromCSV(filename, 1, -1, -1);
    random_tree->predict(predict->getSamples(), mat);
    return mat;
}