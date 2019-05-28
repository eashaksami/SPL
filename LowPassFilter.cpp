#include<iostream>
#include<vector>
using namespace std;

void lowPassFilter(vector<double> arr)
{
    double maxFrequency;

    cin>>maxFrequency;
    for(int i=0;i<arr.size();i++)
    {
        if(arr[i]>maxFrequency)
        {
            arr.erase(arr.begin()+i);
            i=0;
        }

    }
    cout<<arr.size()<<endl;
    for(int i=0;i<arr.size();i++)
        cout<<arr[i]<<endl;


}

int main()
{
    double arr[] = {100.0,90.9,50.0,70.5,90.3,110.2,150.7,86.9,
                123.7,127.5,122.2,129.3,92.5,99.7,111.1,77.02,
                55.07,77.23,59.89,62.66,67.57,97.98,87.7,85.54,
                88.92,77.32,74.23,52.34,74.43,30.08,45.99,75.55,
                25.55,69.97,98.85,47.8,21.12,79.5,67.56,95.52};
       int n = sizeof(arr) / sizeof(arr[0]);

        vector<double> vect(arr, arr + n);

        lowPassFilter(vect);
}
