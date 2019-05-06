#include <iostream>
#include <cstring>
using namespace std;
char* concat(const char* t, const char* h)
{
    int n=strlen(t)+strlen(h);
    char *p = new char[n];
    strcpy(p, t);
    strcat(p, h);
    return p;
}
int main()
{
    const char* a="Hello";
    const char* b="World";
    char* c=concat(a,b);
    cout<<c;
}
