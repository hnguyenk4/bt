 #include <iostream>
#include <cstring>
using namespace std;
char* truncate(const char* a, int n)
{

    char *p = new char[n];
    for (int i=0; i<n; i++)
        p[i]=a[i];
    return p;
}
int main()
{

    //char* c=concat(a,b);
    cout<<truncate("hello", 2);
}






