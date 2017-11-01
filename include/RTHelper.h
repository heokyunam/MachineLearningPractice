#include <vector>
#include <string>

using namespace std;
#define BUFFER_SIZE 1000

class RTHelper {
private:
  vector<double*> datas;
  vector<double*> result;
  char header[BUFFER_SIZE];
  int size;
public:
  RTHelper();
  ~RTHelper();
  int getSize(char* header, int length);
  void load(char* filename);
  void spartial4(char* filename, double x, double y);
  void write(ofstream& of, vector<double*> data);
};