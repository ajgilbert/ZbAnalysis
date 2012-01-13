#ifndef __ajg_EventBase__
#define __ajg_EventBase__

#include <map>
#include <string>
#include <iostream>
#include "boost/any.hpp"

namespace ajg {


  class EventBase {

  private:
    std::map<std::string, boost::any> products_;

  public:
    EventBase();
    virtual ~EventBase();

    template <class T>
    unsigned int Add(std::string name, T const& product) {
      if (Exists(name)) {
        std::cerr << "Warning: Attempt to add product with name \"" 
        << name << "\" failed, a product with this name already exist."
        << std::endl;
        return 1;
      } else {
        products_[name] = product;
        return 0;
      }
    }

    template <class T>
    unsigned int ForceAdd(std::string name, T const& product) {
      products_[name] = product;
      return 0;
    }
    

    template <class T>
    T & Get(std::string name) {
      if (Exists(name)) {
        return boost::any_cast<T &>(products_[name]);
      } else {
        throw;
      }
    }

    void List();

    void Clear();

    unsigned int Remove(std::string name);

    bool Exists(std::string const& name);
    


  };
}

#endif
