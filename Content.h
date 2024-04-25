// h file for content

#ifndef CONTENT_H
#define CONTENT_H
class Content {
public:
    Content();
    ~Content();
    Content(const string title, const int id);
    string getTitle();
    int getId() const;
    void setTitle(string n);
    void setId(int i);
    bool operator<(const Content& right) const;

private:
    string tirle;
    int id;
};

#endif // CONTENT_H

