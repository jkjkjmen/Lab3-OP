#include "wave.h"

Wave::Wave()
{

}

void Wave::read_wave( string  input_name  )
{
    ifstream fin( input_name ,ios::binary);
    fin.read((char*)&input1, sizeof(RIFFHEADER));
    fin.read((char*)&input2, sizeof(SUBCHUNK1));
    fin.read((char*)&input3, sizeof(SUBCHUNK2));

    int8_t data[input3.subchunk2Size];
    fin.read((char*)&data, input3.subchunk2Size);
    for(int i = 0; i < input3.subchunk2Size; ++i)
    {
        sample.push_back(data[i]);
       printf("%d\n", sample[i]);
    }
}


void Wave::resize(double n)
{

    if( n < 0 )
    {
        vector<int8_t> reverse;
        for(size_t i = input3.subchunk2Size; i > 0; --i )
        {
            reverse.push_back(sample[i]);
        }
        n*= -1;
        input3.subchunk2Size *= n;
        for(int i = 0; i < input3.subchunk2Size/2; ++i)
        {
            double x = i/n;
            double factor = x - floor(x);
            //cout << factor << endl;
            for(int k = 0; k < input2.numChannels; ++k)
            {
                result.push_back(interpolation(reverse[floor(x)*2 + k], reverse[(floor(x) + 1)*2 +k], factor));
                cout << interpolation(reverse[floor(x)*2 + k], reverse[(floor(x) + 1)*2 +k], factor) << endl;
                //cout << floor(x) << endl;
            }
        }

    }
    else
    {

    //cout << sample.size( ) << endl;
    cout << input3.subchunk2Size << endl;
    input3.subchunk2Size *= n;
    cout << input3.subchunk2Size << endl;

    for(int i = 0; i < input3.subchunk2Size/2; ++i)
    {
        double x = i/n;
        double factor = x - floor(x);
        //cout << factor << endl;

        for(size_t k = 0; k < input2.numChannels; ++k)
        {
            result.push_back(interpolation(sample[floor(x)*2 + k], sample[(floor(x) + 1)*2 +k], factor));
            //printf("%u\n ", interpolation(sample[floor(x)*2 + k], sample[(floor(x) + 1)*2 +k], factor));
            //cout << floor(x) << endl;
        }
     }
    }
  //  cout<< " Audio Format" << input2.audioFormat << input2.numChannels << endl;
}

void Wave::write_wave( string   out_name)
{
    int8_t last_arr[result.size()];
//    cout << sample.size() << endl;
//    cout << result.size() << endl;
    for(size_t i = 0; i < result.size(); ++i)
    {
        last_arr[i] = result[i];
    }
    ofstream fout(out_name,ios::binary);
    fout.write((char*)&input1, sizeof(RIFFHEADER));
    fout.write((char*)&input2, sizeof(SUBCHUNK1));
    fout.write((char*)&input3, sizeof(input3));
    fout.write((char*)&last_arr, input3.subchunk2Size);
}

int8_t Wave::interpolation(int8_t a , int8_t b , float n )
{
    return (float(b))*(1-n) + n*(float(a)) ;
}
