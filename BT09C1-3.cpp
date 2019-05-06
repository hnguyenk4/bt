#include <iostream>
#include <cstring>
using namespace std;
char* pad_right(const char* a, int n)
{
    int l=strlen(a);
    char *p = new char[n];
    for (int i=0; i<l; i++)
        p[i]=a[i];
    for (int i=l; i<n; i++)
        p[i]='_';
    return p;
}
int main()
{

    //char* c=concat(a,b);
    cout<<pad_right("hello", 10);
}



