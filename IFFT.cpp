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

vector<complex<float> > ifft(vector<complex<float> >X)
{
    vector<complex<float> > Y(N);
    Y = fft(X);

    complex<float> b = Y[0];
    for(int i=0;i<N;i++)
    {
        Y[i]=(Y[i+1]);
        //cout<<Y[i].real()<<" "<<Y[i].imag()<<endl;
        Y[i].real()=Y[i].real()/N;
        Y[i].imag()=Y[i].imag()/N;
    }

    Y[N-1]=b;
    //cout<<b.real()<<" "<<b.imag()<<endl;
    Y[N-1].real()/=N;
    Y[N-1].imag()/=N;
    //for(int i=0;i<N;i++)cout<<Y[i]<<endl;
    return Y;
}


int main(void)
{
    int n;
    cout<<"1.IFFT on double data points\n2.IFFT on complex data points"<<endl;
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
    vector<complex<float> > x;
    vector<complex<float> > b(N);
    vector<complex<float> > y(N);
    int z;
    if(n==1)
    {
        for(int i=0;i<N;i++)
        {
            cin>>z;
            x.push_back( complex<float>(z , 0 ) );
            b=ifft(x);
        }

    }
    else
    {
        for(int i=0;i<N;i++)
        {
            cin>>y[i].real()>>y[i].imag();
            x.push_back( complex<float>(y[i].real(), y[i].imag() ));
            b=ifft(y);
        }

    }
     //c = ifft(b);

     for(int i=N-1;i>=0;i--)
         cout<<b[i]<<endl;


}





