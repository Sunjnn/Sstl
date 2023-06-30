#include "test.h"
#include "stl_map.h"
#include "stl_pair.h"

#include <iostream>
#include <string>
#include <assert.h>
using std::cout, std::endl, std::string;

class testMap : public testBase {
    virtual void test_func() {
        Sstl::map<string, int> simap;
        simap[string("jjhou")] = 1;
        simap[string("jerry")] = 2;
        simap[string("jason")] = 3;
        simap[string("jimmy")] = 4;

        Sstl::pair<const string, int> value(string("david"), 5);
        simap.insert(value);

        auto it = simap.begin();
        assert(it->first == "david");
        assert(it->second == 5);
        ++it;
        assert(it->first == "jason");
        assert(it->second == 3);
        ++it;
        assert(it->first == "jerry");
        assert(it->second == 2);
        ++it;
        assert(it->first == "jimmy");
        assert(it->second == 4);
        ++it;
        assert(it->first == "jjhou");
        assert(it->second == 1);

        it = simap.find("mchen");
        assert(it == simap.end());

        it = simap.find("jerry");
        assert(it != simap.end());
        it->second = 9;
        assert(simap["jerry"] == 9);
    }

public:
    testMap(string s) : testBase(s) {}
};

int main() {
    testMap t("test case of set from the book");
    test_run(&t);

    return 0;
}
