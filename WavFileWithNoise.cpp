#include <cmath>
#include <fstream>
#include <iostream>
#include <graphics.h>
#include <dos.h>
using namespace std;

namespace little_endian_io
{
  template <typename Word>
  std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
  {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
  }
}
using namespace little_endian_io;

int main()
{
  ofstream file( "C:/Users/Acer/Desktop/new.wav", ios::binary );

  file << "RIFF----WAVEfmt ";     
  write_word( file,     16, 4 );
  write_word( file,      1, 2 );  // PCM - integer samples
  write_word( file,      2, 2 );  // number of channels

  write_word( file,  44100, 4 );  // sampling frequency

  write_word( file, 176400, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8

  write_word( file,      4, 2 );  // data block size (size of two integer samples, one for each channel, in bytes)
  write_word( file,     16, 2 );  // bits per sample

  // Write the data chunk header
  size_t data_chunk_pos = file.tellp();
  file << "data----"; 

  double two_pi = 6.2831;
  double max_amplitude =360;


  double hz        = 44100;
  double frequency = 261.626;
  double seconds   = 5.0;

  int N = hz * seconds;
  for (int n = 0; n < N; n++)
  {
    double amplitude = (double)n / N * max_amplitude;
    double value     = sin( (two_pi * n * frequency) / hz );
    write_word( file, (int)( rand()%9 + (amplitude  * value)), 2 );
    write_word( file, (int)(rand()%9+((max_amplitude - amplitude) * value)), 2 );
  }


  // (We'll need the final file size to fix the chunk sizes above)
  size_t file_length = file.tellp();

  // Fix the data chunk header to contain the data size
  file.seekp( data_chunk_pos + 4 );
  write_word( file, file_length - data_chunk_pos + 8 );

  // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
  file.seekp( 0 + 4 );
  write_word( file, file_length - 8, 4 );

}
