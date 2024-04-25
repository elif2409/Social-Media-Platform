// cpp file for content

#include <iostream>
using namespace std;
#include "Content.h"

Content::Content() {}

Content::Content(const string title, const int id) {
    setTitle(title);
    setId(id);
}

Content::~Content(){}

void Content::setTitle(string n) {
    tirle = n;
}

void Content::setId(int i) {
    id = i;
}

string Content::getTitle() {
    return tirle;
}

int Content::getId() const {
    return id;
}

bool Content::operator<(const Content& right) const {
    if(this->getId() < right.getId()) {
        return true;
    }
    else {return false;}
}
