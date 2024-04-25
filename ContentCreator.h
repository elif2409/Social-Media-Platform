// h file for content creator

#ifndef __CONTENT_CREATOR_H
#define __CONTENT_CREATOR_H
#include <string>
#include "LinkedList.h"
#include "RegularUser.h"

class ContentCreator {
public:
    ContentCreator();
    ~ContentCreator();
    ContentCreator(const string name, const int id, int contentNo);
    string getName();
    int getId() const;
    int getFollowerCount();
    int getContentNo();
    void setName(string n);
    void setId(int i);
    void addContentToContentCreator(int contentId);
    bool contentExistsForCreator(int contId);
    LinkedList<int>* getContents();
    void addFollowerToContentCreator(int follwerId);
    bool userFollowsContentCreator(int regUserId);
    void userUnfollowsContentCreator(int followerId);
    void removeContentFromContentCreator(int contentPos);
    LinkedList<int>* getFollowers();
    bool operator<(const ContentCreator& right) const;


private:
    string name;
    int id;
    int contentNo;
    LinkedList<int> contents;
    LinkedList<int> followers;
};

#endif // __CONTENTCREATOR_H
