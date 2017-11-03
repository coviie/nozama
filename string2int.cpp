#include <sstream>
#include <stdexcept>
#include <string>

using std::string;
using std::stringstream;
using std::runtime_error;


int string2int(string s)
{
        stringstream ss(s);
        int result;

        ss >> result;
        if (ss.fail())
                throw(runtime_error("string2int: non-numeric value: " + s));

        return result;
}
