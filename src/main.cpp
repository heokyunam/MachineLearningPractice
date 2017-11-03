#include "RTHelper.h"
#include <string>
#include <iostream>

int main(void) {
    RTHelper helper;
    helper.load("data.csv");
    helper.spartial4("data2.csv", 0, 0, 0);
    helper.addTrainData("data.csv");
    helper.addTrainData("data2.csv");
    Mat mat = helper.predict("predict.csv");
    
    cout << mat << endl;
    return 0;
}