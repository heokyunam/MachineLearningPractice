#include <vector>
#include <string>
#include <opencv/ml.h>

using namespace std;
using namespace cv;
using namespace ml;
#define BUFFER_SIZE 1000

class RTHelper {
private:
  vector<double*> datas;
  char header[BUFFER_SIZE];
  int size;
  
  Ptr<RTrees> random_tree;
public:
  RTHelper();
  ~RTHelper();
  int getSize(char* header, int length);
  void load(char* filename);
  void spartial4(
    vector<double*>& writeDataVec, double x, double y, double z);
  void write(ofstream& of, vector<double*> data);
  void addTrainData(char* filename);
  void save(char* filename);
  Mat predict(char* filename);
};