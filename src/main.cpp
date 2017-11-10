#include "RTHelper.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void spatial(RTHelper& helper) {
    vector<double*> writeDataVec;
    helper.load("data.csv");
    helper.spartial4(writeDataVec, 0, 0, 0);
    helper.spartial4(writeDataVec, 0.5, 0.5, 0.5);
    helper.spartial4(writeDataVec, 0.5, 0.5, -0.5);
    helper.spartial4(writeDataVec, 0.5, -0.5, -0.5);
    helper.spartial4(writeDataVec, -0.5, -0.5, -0.5);
    
    
    std::ofstream of("data2.csv");
    cout << "count : " << writeDataVec.size() << endl;
    helper.write(of, writeDataVec);
    of.flush();
}

void train(RTHelper& helper) {
    helper.addTrainData("data.csv");
    helper.addTrainData("data2.csv");
    helper.save("tree.json");
    Mat mat = helper.predict("predict.csv");
    
    cout << mat << endl;
}

int main(void) {
    RTHelper helper;
    
    train(helper);
    
    return 0;
}