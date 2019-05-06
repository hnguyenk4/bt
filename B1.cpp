#include <iostream>
using namespace std;
int main()
{
    int c=10;
    int a[3];
    char b[3];
    char v;
    for (int i=0; i<3; i++)
    {
        cout<<&a[i]<<" ";   // các ô nhớ liên tiếp nhau, cách nhau 4 byte
    }
    cout<<endl;
    for (int i=0; i<3; i++)
    {
        cout<<(void*)&b[i]<<" ";   // các ô nhớ liên tiếp cách nhau 1 byte
    }
    cout<<endl;
    cout<<&c<<" "<<(void*)&v; // ô nhớ của kí tự int được lưu sau ô nhớ của 2 mảng, ô nhớ kí tự của chả được lưu trước ô nhớ của mảng char.
}
