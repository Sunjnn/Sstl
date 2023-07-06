#include "test.h"
#include "stl_hash_map.h"
#include "stl_hash_fun.h"

#include <cstring>
#include <iostream>
#include <string>

struct eqstr {
    bool operator()(const char* s1, const char* s2) const {
        return strcmp(s1, s2) == 0;
    }
};

class testHashMap : public testBase {
    virtual void test_func() {
        Sstl::hash_map<const char*, int, Sstl::hash<const char*>, eqstr> days;

        days["january"] = 31;
        days["february"] = 28;
        days["march"] = 31;
        days["april"] = 30;
        days["may"] = 31;
        days["june"] = 30;
        days["july"] = 31;
        days["august"] = 31;
        days["september"] = 30;
        days["october"] = 31;
        days["november"] = 30;
        days["december"] = 31;

        std::cout << "september ->" << days["september"] << std::endl;
        std::cout << "june      ->" << days["june"] << std::endl;
        std::cout << "february  ->" << days["february"] << std::endl;
        std::cout << "december  ->" << days["december"] << std::endl;
    }
public:
    testHashMap(std::string s) : testBase(s) {}
};

int main() {
    testHashMap *t = new testHashMap("test case from the book");
    test_run(t);
    return 0;
}
