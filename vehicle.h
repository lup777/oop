//vehicle.h
#include <string>
using namespace std;
class vehicle
{
private:
  string brand;
  string color;
  
public:
  vehicle(const char * brand);
  void setColor(const char* color);
  ~vehicle();
};
