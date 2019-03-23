#include<iostream>
#include<complex>
#include<math.h>
using namespace std;

typedef complex<double> Complex;
int N;

Complex Exponent(double a)
{
    Complex b;

    if(a==0||((int)a%180==0&&(int)a%360==0))
    {
    	b.real(1.0);
    	b.imag(0.0);
    }

    else if((int)a%180==0&&(int)a%360!=0)
    {
    	b.real(-1.0);
    	b.imag(0.0);
    }

    else if((int)a%90==0)
    {
    	int x;
    	x=a/90;
    	if((((x-1)/2)%2)==0)
    	{
    	b.real(0.0);
    	b.imag(1.0);
    	}
    	else
        {
            b.real(0.0);
            b.imag(-1.0);
        }
    }

    else
    {
        double c,d;
        b.real(cos((a*M_PI)/180));
    	b.imag(sin((a*M_PI)/180));
    }

    return b;
}

Complex* fft(Complex X[])
{
    Complex a(0.0,0.0),b(0.0,0.0),c,d,e;
    Complex *Y = new Complex[N];
    for(int k = 0;k<N/2;k++)
    {
        d = Exponent((2*180*k)/(N));
        for(int n=0;n<N/2;n++)
        {
            //c = exponent((2*M_PI*k*n)/(N));

            c = Exponent((4*180*k*n)/(N));
            //d = exponent((2*M_PI*k)/(N));

            a += X[2*n]*c;
            e = X[(2*n)+1]*c;
            b += e*d;
        }
        Y[k] = a+b;
        Y[k+N/2]=a-b;
		a=(0.0,0.0);
		b=(0.0,0.0);
    }

    Complex z;
    //z=cos((90*M_PI)/180),sin((90*M_PI)/180);
    //cout<<cos((90*M_PI)/180);

    return Y;
}

int main(void)
{
    int n;
    cout<<"1.FFT on double data points\n2.FFT on complex data points"<<endl;
    cout<<"Enter choice: "<<endl;
    cin>>n;
    cout<<"How many points: ";
    cin>>N;
    while(true)
    {
        if(ceil(log2(N))==floor(log2(N)))
            break;
        else
        {
            cout<<"Enter 2^N points: ";
            cin>>N;
        }

    }
    cout<<"Enter the points:"<<endl;
    //Complex a[N];
    double a[N];
    Complex x[N];
    if(n==1)
    {
        for(int i=0;i<N;i++)
        {
            cin>>a[i];
            x[i].real(a[i]);
            x[i].imag(0);
        }
    }
    else
    {
        for(int i=0;i<N;i++)
            cin>>x[i].real()>>x[i].imag();
    }

    Complex *b = new Complex[N];
        b=fft(x);
        for(int i=0;i<N;i++)
            cout<<b[i]<<endl;
            //cout<<M_PI<<endl;
        //cout<<sin(150*M_PI/180)<<endl;
}
