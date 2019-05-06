#include <iostream>
#include <cstring>
using namespace std;
char* trim_right(const char* a)
{
    int n=strlen(a);

    int k=n;
    while (a[k-1]=='_')
    {
        k--;
    }
    char *p = new char[n-k];
    for (int i=0; i<k; i++)
            p[i]=a[i];
    return p;
}
int main()
{

    //char* c=concat(a,b);
    cout<<trim_right("hello_____");
}







