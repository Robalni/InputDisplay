#ifndef CONF_H
#define CONF_H

#include <fstream>
#include <string>
#include <map>


using namespace std;
class Conf
{
  public:
    Conf(string fname);
    virtual ~Conf();
    bool readfile();
    string get_value(string key);
    bool reload();
  protected:
  private:
    string fname;
    map<string, string> settings;
    void trim(string& str);
};

#endif // CONF_H
