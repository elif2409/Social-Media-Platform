// cpp file for regular user

#ifndef __REGULARUSER_H
#define __REGULARUSER_H
#include <string>
#include "LinkedList.h"
class RegularUser {
public:
    RegularUser();
    ~RegularUser();
    RegularUser(const int id, const string name);
    string getName() const;
    int getId() const;
    void setName(string n);
    void setId(int i);

    bool operator<(const RegularUser& right) const;

private:
    string name;
    int id;
};

#endif // __REGULARUSER_H
