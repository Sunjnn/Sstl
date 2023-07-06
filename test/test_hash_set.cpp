#include "test.h"
#include "stl_hash_set.h"
#include "stl_hash_fun.h"

#include <cstring>
#include <iostream>
#include <string>

struct eqstr {
    bool operator()(const char* s1, const char* s2) const {
        return strcmp(s1, s2) == 0;
    }
};

void lookup(Sstl::hash_set<char*, Sstl::hash<char*>, eqstr>& set, char* word) {
    Sstl::hash_set<char*, Sstl::hash<char*>, eqstr>::iterator it = set.find(word);
    std::cout << " " << word << ": " << (it != set.end() ? "present" : "not present") << std::endl;
}

class testHastSet : public testBase {
    virtual void test_func() {
        Sstl::hash_set<char*, Sstl::hash<char*>, eqstr> set;
        set.insert("kiwi");
        set.insert("plum");
        set.insert("apple");
        set.insert("mango");
        set.insert("apricot");
        set.insert("banana");

        lookup(set, "mango");
        lookup(set, "apple");
        lookup(set, "durian");
    }
public:
    testHastSet(std::string s) : testBase(s) {}
};

int main() {
    testHastSet *t = new testHastSet("test case from the book");
    test_run(t);
    return 0;
}
