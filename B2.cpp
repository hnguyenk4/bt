#include <iostream>
using namespace std;
int factorial(int x)
{
    if (x>1)
    {
        cout<< "x = " << x << " at "<< &x << endl;
        return x*factorial(x-1);
    }
    else
    {
        cout<< "x = " << x << " at " << &x << endl; // Chuỗi giá trị tăng dần; Các biến địa phương được lưu lần lượt và được giải phóng theo chiều ngược lại sau khi đã được thực hiện;
        return 1;                                   // 0X28FEA0 - 0X28FE70 = 48; =>> kích thước của một stack frame cho hàm factorial là 6 byte.
    }

}
int main()
{
    int N;
    cin>>N;
    cout<<factorial(N);
}
