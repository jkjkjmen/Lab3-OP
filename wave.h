#ifndef WAVE_H
#define WAVE_H

#include<fstream>
#include<vector>
#include <iostream>
#include<string>
#include<math.h>
#include<iterator>
#include<stdio.h>

using namespace std;

class Wave
{
private:
    typedef struct {
        int32_t chunkId;   // Завжди містить значення 0x52494646 (літери "RIFF")
        int32_t chunkSize; // 36 + розмір другого підрозділу в байтах
                           // Іншими словами 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
                           // Це розмір всього файла мінус 8 байтів які займають поля chunkId та chunkSize
        int32_t format;    // Для wav-файла це завжди 0x57415645 (літери "WAVE")
    } RIFFHEADER;
    typedef struct {
        int32_t subchunk1Id;   // Завжди 0x666d7420 – літери "fmt "
        int32_t subchunk1Size; // Завжди 16 для аудіо PCM. Це розмір частини підрозділу, що слідує після цього числа
        int16_t audioFormat;   // PCM = 1
        int16_t numChannels;   // Mono = 1, Stereo = 2
        int32_t sampleRate;    // Наприклад 44100
        int32_t byteRate;      // == SampleRate * NumChannels * BitsPerSample/8
        int16_t blockAlign;    // == NumChannels * BitsPerSample/8
        int16_t bitsPerSample; // 8 bits = 8, 16 bits = 16, etc.
    } SUBCHUNK1;
    typedef struct {
        int32_t subchunk2Id;
        int32_t subchunk2Size;
        int8_t data[];
    } SUBCHUNK2;
    RIFFHEADER input1;
    SUBCHUNK1 input2;
    SUBCHUNK2 input3;
    vector<int8_t> sample;
    vector<int8_t> result;
public:
    Wave();
    void read_wave(string );
    void write_wave(string );
    int8_t interpolation(int8_t , int8_t , float );
    void resize(double);
};

#endif // WAVE_H
