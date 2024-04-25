// cpp file for social media platform

#include "SocialMediaPlatform.h"
#include <iostream>
#include "RegularUser.h"
#include "ContentCreator.h"
#include "Node.h"
#include "LinkedList.h"
using namespace std;

SocialMediaPlatform::SocialMediaPlatform() {}

SocialMediaPlatform::~SocialMediaPlatform() {}

bool SocialMediaPlatform::RegularUserExists(int regUserId) {
 for(int i = 1; i<=allRegUsers.getLength(); i++) {
        if(allRegUsers.getEntry(i).getId() == regUserId) {
            return true;
        }
}
return false;
}

bool SocialMediaPlatform::ContentCreatorExists(int contCreatorId) const {
    for(int i = 1; i<=allContentCreators.getLength(); i++) {
        if(allContentCreators.getEntry(i).getId() == contCreatorId) {
            return true;
        }
}
return false;
}

bool SocialMediaPlatform::ContentExists(int contId) {
    for(int i = 1; i<=allContents.getLength(); i++) {
        if(allContents.getEntry(i).getId() == contId) {
            return true;
        }
}
return false;
}

void SocialMediaPlatform::addRegularUser(const int regularUserId, const string name) {
    RegularUser a (regularUserId, name);
    if(RegularUserExists(regularUserId)) {
        cout<<"Cannot add regular user. There is already a regular user with ID ";
            cout<<regularUserId;
            cout<<"."<<endl;
    }
    else {
        Node<RegularUser>** head = allRegUsers.getHeadPtrByPointer();
       allRegUsers.linkedListInsert(*head,a);
        cout<<"Added regular user ";
        cout<<regularUserId;
        cout<<"."<<endl;
    }
}

void SocialMediaPlatform::removeRegularUser( const int regularUserId ) {
    bool userExists = false;
    for(int i = 1; i<=allRegUsers.getLength(); i++) {
        if(allRegUsers.getEntry(i).getId() == regularUserId) {
            userExists = true;
            allRegUsers.remove(i);
            for(int j = 1; j <= allContentCreators.getLength(); j++) {
                for(int k = 1; k <= allContentCreators.getObj(j)->getFollowerCount(); k++) {
                    if (*(allContentCreators.getObj(j)->getFollowers()->getObj(k)) == regularUserId) {
                        allContentCreators.getObj(j)->userUnfollowsContentCreator(regularUserId);
                    }
                }
            }
            cout<<"Removed regular user ";
            cout<<regularUserId;
            cout<<"."<<endl;
        }
    }
    if(!userExists) {
        cout<<"Cannot remove regular user. There is no regular user with ID ";
        cout<<regularUserId;
        cout<<"."<<endl;
    }

}

void SocialMediaPlatform::addContentCreator( const int contentCreatorId, const string name ) {
    ContentCreator c(name, contentCreatorId, 0);
    bool uniqueId = true;
    for(int i = 1; i<=allContentCreators.getLength(); i++) {
        if(allContentCreators.getObj(i)->getId() == contentCreatorId) {
            uniqueId = false;
            cout<<"Cannot add content creator. There is already a content creator with ID ";
            cout<<contentCreatorId;
            cout<<"."<<endl;
        }
    }
    if(uniqueId) {
       Node<ContentCreator>** head = allContentCreators.getHeadPtrByPointer();
       allContentCreators.linkedListInsert(*head,c);
        cout<<"Added content creator ";
        cout<<contentCreatorId;
        cout<<"."<<endl;
    }
}

void SocialMediaPlatform::removeContentCreator( const int contentCreatorId ) {
    bool contentCreatorExists = false;
     for(int i = 1; i<=allContentCreators.getLength(); i++) {
        if(allContentCreators.getEntry(i).getId() == contentCreatorId) {
            contentCreatorExists = true;
            allContentCreators.remove(i);
            cout<<"Removed content creator ";
            cout<<contentCreatorId;
            cout<<"."<<endl;
        }
    }
    if(!contentCreatorExists) {
        cout<<"Cannot remove content creator. There is no content creator with ID ";
        cout<<contentCreatorId;
        cout<<"."<<endl;
    }
}

void SocialMediaPlatform::addContent( const int contentCreatorId, const int contentId, const string title ) {
     if(ContentExists(contentId)) {
        cout<<"Cannot add content. There is already a content with ID ";
        cout<<contentId;
        cout<<"."<<endl;
        return;
   }
   if(!ContentCreatorExists(contentCreatorId)) {
        cout<<"Cannot add content. There is no content creator with ID ";
        cout<<contentCreatorId;
        cout<<"."<<endl;
        return;
   }
   Content c (title, contentId);
   if(ContentCreatorExists(contentCreatorId)&& !ContentExists(contentId)) {
        Node<Content>** head = allContents.getHeadPtrByPointer();
       allContents.linkedListInsert(*head,c);
        for(int i = 1; i<=allContentCreators.getLength(); i++) {
            if(allContentCreators.getEntry(i).getId() == contentCreatorId) {
                allContentCreators.getObj(i)->addContentToContentCreator(contentId);
                cout<<"Added content ";
                cout<<contentId;
                cout<<"."<<endl;
            }
        }

   }
}

void SocialMediaPlatform::removeContent( const int contentCreatorId, const int contentId ){
    bool contExists = false;
    if(!ContentCreatorExists(contentCreatorId)) {
        cout<<"Cannot remove content. There is no content creator with ID ";
        cout<<contentCreatorId;
        cout<<"."<<endl;
        return;
    }
    for(int j = 1; j<=allContentCreators.getLength(); j++) {
        if(allContentCreators.getEntry(j).contentExistsForCreator(contentId)) {
            contExists = true;
            for(int k = 1; k<=allContentCreators.getObj(j)->getContents()->getLength(); k++) {
                if(*(allContentCreators.getObj(j)->getContents()->getObj(k)) == contentId) {
                    allContentCreators.getObj(j)->removeContentFromContentCreator(k);
                }
            }
        }
    }
    if(contExists) {
            for(int i = 1; i<=allContents.getLength(); i++) {
                if(allContents.getEntry(i).getId() == contentId) {
                    allContents.remove(i);
                    cout<<"Removed content ";
                    cout<<contentId;
                    cout<<"."<<endl;
                }
            }
        }

    if(!contExists)  {
        cout<<"Cannot remove content. There is no content with ID ";
        cout<<contentId;
        cout<<" shared by content creator with ID ";
        cout<<contentCreatorId;
        cout<<"."<<endl;
    }

}

void SocialMediaPlatform::followContentCreator( const int regularUserId, const int contentCreatorId ) {
     if(!RegularUserExists(regularUserId) || !ContentCreatorExists(contentCreatorId)) {
        cout<<"Cannot follow. Regular user and/or content creator ID does not exist."<<endl;
        return;
    }
    for(int i = 1; i<=allContentCreators.getLength(); i++) {
        if(allContentCreators.getObj(i)->getId() == contentCreatorId) {
            if(allContentCreators.getObj(i)->userFollowsContentCreator(regularUserId)) {
                cout<<"Cannot follow. The user is already following the content creator."<<endl;
                return;
            }
            else {
                allContentCreators.getObj(i)->addFollowerToContentCreator(regularUserId);
                cout<<"Regular user with ID ";
                cout<<regularUserId;
                cout<<" followed content creator with ID ";
                cout<<contentCreatorId;
                cout<<"."<<endl;
                return;
            }
        }
    }

}

void SocialMediaPlatform::unfollowContentCreator( const int regularUserId, const int contentCreatorId) {
    if(!RegularUserExists(regularUserId) || !ContentCreatorExists(contentCreatorId)) {
        cout<<"Cannot unfollow. Regular user and/or content creator ID does not exist."<<endl;
        return;
    }
    for(int i = 1; i<=allContentCreators.getLength(); i++) {
        if(allContentCreators.getObj(i)->getId() == contentCreatorId) {
            if(allContentCreators.getObj(i)->userFollowsContentCreator(regularUserId)) {
                allContentCreators.getObj(i)->userUnfollowsContentCreator(regularUserId);
                cout<<"Regular user with ID ";
                cout<<regularUserId;
                cout<<" unfollowed content creator with ID ";
                cout<<contentCreatorId;
                cout<<"."<<endl;
                return;
            }
            else {
                cout<<"Cannot unfollow. The user is not following the content creator."<<endl;
                return;
            }
        }
    }

}

void SocialMediaPlatform::showContentsOf( const int contentCreatorId ) const {
    if(!ContentCreatorExists(contentCreatorId)) {
        cout<<"Cannot show. There is no content creator with ID ";
        cout<<contentCreatorId;
        cout<<"."<<endl;
    }
    else {
        cout<<"Contents of content creator with ID ";
        cout<<contentCreatorId;
        cout<<":"<<endl;
        for(int i = 1; i<=allContentCreators.getLength(); i++) {
            if(allContentCreators.getObj(i)->getId() == contentCreatorId) {
                if(allContentCreators.getObj(i)->getContentNo() == 0) {
                    cout<<"None"<<endl;
                }
                else {
                    for(int j = 1; j<=allContentCreators.getObj(i)->getContentNo(); j++) {
                        cout<<*(allContentCreators.getObj(i)->getContents()->getObj(j))<<endl;
                    }
                }
            }
        }
    }
}

void SocialMediaPlatform::showFollowersOf( const int contentCreatorId ) const {
    if(!ContentCreatorExists(contentCreatorId)) {
        cout<<"Cannot show. There is no content creator with ID ";
        cout<<contentCreatorId;
        cout<<"."<<endl;
    }
    else {
        cout<<"Regular users following content creator with ID ";
        cout<<contentCreatorId;
        cout<<":"<<endl;
        for(int i = 1; i<=allContentCreators.getLength(); i++) {
            if(allContentCreators.getObj(i)->getId() == contentCreatorId) {
                if(allContentCreators.getObj(i)->getFollowerCount() == 0) {
                    cout<<"None"<<endl;
                }
                else {
                    for(int j = 1; j<=allContentCreators.getObj(i)->getFollowerCount(); j++) {
                        cout<<*(allContentCreators.getObj(i)->getFollowers()->getObj(j))<<endl;
                    }
                }
            }
        }
    }
}

void SocialMediaPlatform::showAllRegularUsers() const {
    cout<<"Regular users in the social media platform:"<<endl;
    if(allRegUsers.isEmpty()) {cout<<"None"<<endl ;}
    else{
        for(int i = 1; i<=allRegUsers.getLength(); i++) {
            cout<<(allRegUsers.getEntry(i)).getId();
            cout<<", ";
            cout<<allRegUsers.getEntry(i).getName()<<endl;
        }
    }
}

void SocialMediaPlatform::showAllContentCreators() const {
    cout<<"Content creators in the social media platform:"<<endl;
    if(allContentCreators.isEmpty()) {cout<<"None"<<endl;}
    else {
        for(int i = 1; i<=allContentCreators.getLength(); i++) {
            cout<<allContentCreators.getEntry(i).getId();
            cout<<", ";
            cout<<allContentCreators.getEntry(i).getName();
            cout<<", ";
            cout<<allContentCreators.getObj(i)->getFollowerCount();
            cout<<" follower(s), ";
            cout<<allContentCreators.getEntry(i).getContentNo();
            cout<<" content(s)"<<endl;
        }
    }
}
