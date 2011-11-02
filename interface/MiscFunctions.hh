#include <stdarg.h>
#include <vector>
#include <string>

namespace HbbAnalysis {

  std::vector<std::string> StringVecify(unsigned numArgs, ... ) {
    std::vector<std::string> vec;
    vec.resize(numArgs);
    va_list listPointer;
    va_start(listPointer, numArgs);
    for (unsigned i = 0; i < numArgs; ++i){
      vec[i] = (std::string(va_arg(listPointer,char*))); 
    }
    return vec;
  }

template <class T>
std::vector<T> Vecify(unsigned numArgs, ... ) {
    std::vector<T> vec;
    vec.resize(numArgs);
    va_list listPointer;
    va_start(listPointer, numArgs);
    for (unsigned i = 0; i < numArgs; ++i){
      vec[i] = (T(va_arg(listPointer,T))); 
    }
    return vec;
  }
}
