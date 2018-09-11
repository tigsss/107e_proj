#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
using namespace std;
using std::string;
using std::fstream;

int get_file_size(FILE* inFile);

int main()

{
    //open the file
    FILE* file = fopen("moves.wav", "r" );
    char* oData;
    if (file)
    {
        cout << "file opened" << endl;
    }
    else
    {
        cout << "didn't work" << endl;
    }

    //this is the file we write to
    ofstream outputFile;
    outputFile.open("moves.h");

    outputFile << "#include <stdint.h>" << endl;

    outputFile << "const int16_t moves[] = " << endl;
    outputFile<< "{" << endl;


    int size = get_file_size(file);
    int* ptr = (int *)malloc(2);
    int val;
    int temp;

    printf("Size of file: %x\n", size);

    for (int i = 1; i <= size / 2; i++)
    {
	//the actual formatting portion of the program
        fread (ptr, 1, 1, file);
        val = *ptr;
        outputFile << "0x";

        temp = *ptr;


        fread (ptr, 1, 1, file);
        val = *ptr;
        if (val < 0x10)
        {
            outputFile << "0";
        }
        outputFile <<std::hex << *ptr;

        if (temp < 0x10)
        {
            outputFile << "0";
        }
        outputFile <<std::hex << temp << ", ";

        if (i % 16 == 0)
            outputFile << endl;
    }
    outputFile << endl << "};";

    cout << "done";

}

int get_file_size(FILE* inFile)
{
    fseek(inFile, 0, SEEK_END);
    int size = ftell(inFile);
    rewind(inFile);
    return size;
}
