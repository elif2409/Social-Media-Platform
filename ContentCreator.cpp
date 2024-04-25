// cpp file for content creator

#include <iostream>
using namespace std;
#include "ContentCreator.h"
#include "LinkedList.h"

ContentCreator::ContentCreator() {}

ContentCreator::~ContentCreator() {}

ContentCreator::ContentCreator(const string name, const int id, int contentNo) {
    setName(name);
    setId(id);
    contentNo = 0;
}

void ContentCreator::setName(string n) {
    name = n;
}

int ContentCreator::getFollowerCount() {
    return followers.getLength();
}

void ContentCreator::setId(int i) {
    id = i;
}

string ContentCreator::getName() {
    return name;
}

int ContentCreator::getId() const {
    return id;
}

int ContentCreator::getContentNo() {
    return contents.getLength();
}

bool ContentCreator::contentExistsForCreator(int contId) {
    for(int i = 0; i<=contents.getLength(); i++) {
        if(contents.getEntry(i) == contId) {
            return true;
        }
    }
    return false;
}

void ContentCreator::addContentToContentCreator(int contentId) {
    int a = contentId;
     Node<int>** head = contents.getHeadPtrByPointer();
    contents.linkedListInsert(*head,a);
}

void ContentCreator::removeContentFromContentCreator(int contentPos) {
    contents.remove(contentPos);
}

void ContentCreator::addFollowerToContentCreator(int followerId) {
     Node<int>** head = followers.getHeadPtrByPointer();
       followers.linkedListInsert(*head,followerId);
}

bool ContentCreator::userFollowsContentCreator(int regUserId) {
    for(int i = 1; i<=followers.getLength(); i++) {
        if(*(followers.getObj(i))==regUserId) {return true;}
    }
    return false;
}

void ContentCreator::userUnfollowsContentCreator(int followerId) {
    for(int i = 1; i<=followers.getLength(); i++) {
        if(*(followers.getObj(i))==followerId) {
            followers.remove(i);
        }
    }
}

LinkedList<int>* ContentCreator::getFollowers() {
    return &followers;
}

LinkedList<int>* ContentCreator::getContents() {
    return &contents;
}

bool ContentCreator::operator<(const ContentCreator& right) const {
    if(this->getId() < right.getId()) {
        return true;
    }
    else {return false;}
}

