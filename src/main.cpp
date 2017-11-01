#include "RTHelper.h"
#include <string>

int main(void) {
    RTHelper helper;
    helper.load("data.csv");
    helper.spartial4("data2.csv", 0, 0);
    
    return 0;
}