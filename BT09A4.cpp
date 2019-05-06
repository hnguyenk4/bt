#include <iostream>
using namespace std;

int* hello()
{
    int h=10;
    int* p= new int;

    cout<<p<<endl;//trả về địa chỉ ô nhớ được cấp phát
    p=&h;
    delete p;// không xóa ô nhớ được cấp phát vì con trỏ đã trỏ đến ô nhớ khác

    return p; // trả về địa chỉ của h
}
int main()
{
    cout<<hello();

}

