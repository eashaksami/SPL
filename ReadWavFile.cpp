#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <windows.h>
using namespace std;


void fopen_s(FILE ** file_pointer, const char * fname, const char * mode)
{
    *file_pointer = fopen(fname, mode);
}

int main()
{
    // create a file pointer
    FILE *file_pointer = NULL;


    fopen_s(&file_pointer,"C:/Users/Acer/Desktop/new.wav", "rb"); // binary mode

    if (!file_pointer)
    {
        cout <<"Error: missing / bad file" << endl;
        return 1;
    }

    char type_1[5] = {0}; // "RIFF"
    char type_2[5] = {0}; // "WAVE"
    char type_3[5] = {0}; // "fmt "
    DWORD size,chunk_size;
    short format_type,channels;
    DWORD sample_rate,avg_bytes_per_sec;
    short bytes_per_sample,bits_per_sample;
    char type_4[5]={0}; // "data"
    DWORD data_size;

    // check for RIFF format
    fread(type_1,sizeof(char),4,file_pointer);
    if (strcmp(type_1,"RIFF"))
    {
        cout <<"Error: not RIFF format";
        return 1;
    }

    // data size
    fread(&size,sizeof(DWORD),1,file_pointer);

    // check for WAVE format
    fread(type_2,sizeof(char),4,file_pointer);
    if (strcmp(type_2,"WAVE"))
    {
        cout <<"Error: not WAVE format";
        return 1;
    }

    // check for "fmt " string
    fread(type_3,sizeof(char),4,file_pointer);
    if (strcmp(type_3, "fmt "))
    {
        cout <<"Error: missing format string";
        return 1;
    }

    // chunk size
    fread(&chunk_size,sizeof(DWORD),1,file_pointer);

    // format type
    fread(&format_type,sizeof(short),1,file_pointer);

    // number of channels
    fread(&channels,sizeof(short),1,file_pointer);

    // sample rate
    fread(&sample_rate,sizeof(DWORD),1,file_pointer);

    // average bytes per second
    fread(&avg_bytes_per_sec,sizeof(DWORD),1,file_pointer);

    // bytes per sample
    fread(&bytes_per_sample,sizeof(short),1,file_pointer);

    // bits per sample
    fread(&bits_per_sample,sizeof(short),1,file_pointer);

    // check for "data" string
    fread(type_4,sizeof(char),4,file_pointer);
    if (strcmp(type_4,"data"))
    {
        cout <<"Error: missing data string";
        return 1;
    }

    fread(&data_size,sizeof(DWORD),1,file_pointer);


    cout<<"chunk size "<<chunk_size<<endl;
    cout<<"format type "<<format_type<<endl;
    cout<<"channels "<<channels<<endl;
    cout<<"sample rate "<<sample_rate<<endl;
    cout<<"average bytes per second "<<avg_bytes_per_sec<<endl;
    cout<<"bytes per sample "<<bytes_per_sample<<endl;
    cout <<"bits per sample "<<bits_per_sample<<endl;
    cout <<"data size "<<data_size<<endl;

    Sleep(100);


    cout<<"attempting data collection"<<endl;
    unsigned long number_of_samples = data_size/bytes_per_sample;
    std::cout << "number of samples = " << number_of_samples << '\n';

    std::vector<short> samples(number_of_samples);
    size_t elements_read = fread(samples.data(), sizeof(short), number_of_samples, file_pointer);


    fclose(file_pointer);

    /*for (size_t i = 0; i<samples.size(); ++i)
    {
        cout << setw(10) << i << setw(10) << samples[i] << '\n';
    }*/

    return 0;
}




