#include<iostream>
#include<complex>
#include<math.h>
#include<vector>
using namespace std;

typedef complex<double> Complex;
int N;

complex<float> Exponent(double a)
{
    complex<float> b;

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
        b.imag(sin((a*M_PI)/180 ));
    }

    return b;
}

vector<complex<float> > fft(vector<complex<float> >X)
{
     complex<float> a(0.0,0.0),b(0.0,0.0),c,d,e;
     vector<complex<float> > Y(N);

    for(int k = 0;k<N/2;k++)
    {
        d = Exponent((2*180*k)/(N));
        for(int n=0;n<N/2;n++)
        {
            c = Exponent((4*180*k*n)/(N));
            a += X[2*n]*c;
            e = X[(2*n)+1]*c;
            b += e*d;
        }
        Y[k] = a+b;
        Y[k+N/2]=a-b;
    	a.real(0.0);
		a.imag(0.0);
		b.real(0.0);
		b.imag(0.0);
    }
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

    double a[N];
    int c;
    vector<complex<float> > x;
    if(n==1)
    {
        for(int i=0;i<N;i++)
        {
            cin>>c;
            x.push_back( complex<float>( c, 0 ) );
        }

    }
    else
    {
        for(int i=0;i<N;i++)
            cin>>x[i].real()>>x[i].imag();
    }
    vector<complex<float> > b(N);
        b=fft(x);
        for(int i=0;i<N;i++)
            cout<<b[i]<<endl;

}





