#include <iostream>
using namespace std;

class complex
{
public:
    complex();
    complex(double a);
    complex(double a, double b);
    complex operator+(const complex & A)const;
    complex operator-(const complex & A)const;
    complex operator*(const complex & A)const;
    complex operator/(const complex & A)const;
    void display()const;
private:
    double real;   //复数的实部
    double imag;   //复数的虚部
};

complex::complex()
{
    real = 0.0;
    imag = 0.0;
}

complex::complex(double a)
{
    real = a;
    imag = 0.0;
}

complex::complex(double a, double b)
{
    real = a;
    imag = b;
}

//打印复数
void complex::display()const
{
    cout<<real<<" + "<<imag<<" i ";
}

//重载加法操作符
complex complex::operator+(const complex & A)const
{
    complex B;
    B.real = real + A.real;
    B.imag = imag + A.imag;
    return B;
}

//重载减法操作符
complex complex::operator-(const complex & A)const
{
    complex B;
    B.real = real - A.real;
    B.imag = imag - A.imag;
    return B;
}

//重载乘法操作符
complex complex::operator*(const complex & A)const
{
    complex B;
    B.real = real * A.real - imag * A.imag;
    B.imag = imag * A.real + real * A.imag;
    return B;
}

//重载除法操作符
complex complex::operator/(const complex & A)const
{
    complex B;
    double square = A.real * A.real + A.imag * A.imag;
    B.real = (real * A.real + imag * A.imag)/square;
    B.imag = (imag * A.real - real * A.imag)/square;
    return B;
}

int main()
{
    complex c1(4.3, -5.8);
    complex c2(8.4, 6.7);
    complex c3;
   
    //复数的加法
    c3 = c1 + c2;
    cout<<"c1 + c2 = ";
    c3.display();
    cout<<endl;
   
    //复数的减法
    c3 = c1 - c2;
    cout<<"c1 - c2 = ";
    c3.display();
    cout<<endl;
   
    //复数的乘法
    c3 = c1 * c2;
    cout<<"c1 * c2 = ";
    c3.display();
    cout<<endl;
   
    //复数的除法
    c3 = c1 / c2;
    cout<<"c1 / c2 = ";
    c3.display();
    cout<<endl;
   
    return 0;
}
