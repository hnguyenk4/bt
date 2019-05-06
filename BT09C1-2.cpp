#include <iostream>
#include <cstring>
using namespace std;
char* delete_char(const char* a, char c)
{
    int n=strlen(a);
    char *p = new char[n];
    int s=0;
    for (int i=0; i<n; i++)
        if (a[i]!=c)
        {
            p[i-s]=a[i];
        }
        else
            s++;

    return p;
}
int main()
{

    //char* c=concat(a,b);
    cout<<delete_char("hello", 'e');
}


