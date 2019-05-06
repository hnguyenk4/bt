#include <iostream>
#include <cstring>
using namespace std;
char* reverses(const char *a)
{
    int n=strlen(a);
    char *p = new char[n];
    for (int i=n-1; i>=0; i--)
        p[i]=a[n-1-i];
    return p;
}
int main()
{

    //char* c=concat(a,b);
    cout<<reverses("hello");
}

