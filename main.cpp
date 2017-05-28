#include <iostream>
#include"wave.h"


using namespace std;

int main(int argc, char *argv[])
{/*
    if (argc != 4) {
            cerr << "Error!" << endl;
            system("PAUSE");
            return -1;
        }

    string in = argv[1];
    string out = argv[2];
    double n = atof(argv[3]);*/

//        if (n > 10 || n <= 0) {
//            cerr << "Incorrect n!" << endl;
//            return -1;
//        }
    Wave audio;
    string in = "synus.wav";
    string out = "output.wav";
    audio.read_wave(in);
    cout << "Scaling sound file... ";
    int n = 1;
    audio.resize(n);

    cout << "Done." << endl;
    audio.write_wave(out);
    cout << "Result saved to " << out << endl;
    return 0;
}
