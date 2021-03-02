#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include <fstream>
using namespace std;
ofstream fout("crypting.out");

int Crypt()
{
    int i,j,S[256],Save[256],u[256],Temp,EncryptionCode;

    for(i=0; i<256; i++)
    {
        S[i]=i;
    }

    j=0;
    for (i = 0; i<256; i++)
    {
        u[i] = (S[i] + Save[i %sizeof(Save)])%256;
        swap(S[i], S[u[i]]);
    }
    j = 0;
    for (i = 0; i< 256; i++)
    {
        j = (j + S[i] + Save[i % sizeof(Save)])% 256;
        swap(S[i], S[j]);
    }

    i=0;
    j=0;
    i=(i+1)%256;
    j=(j+S[i])%256;
    swap(S[i],S[j]);
    Temp=(S[i]+S[j])%256;
    EncryptionCode=S[Temp];

    return EncryptionCode;

}

void Encryption(int key1)
{
    stringstream TempRes;
    string Hexa = "";
    string Msg;
    string Key;
    int Iteration = 0;

    Key=key1;

    cout << "\n\nEnter the message to encrypt: \n\n";
    getline(cin, Msg);

    for (int i = 0; i < Msg.length(); i++)
    {
        int TempSol = Msg[i] ^ key1;

        TempRes << hex << setfill('0') << std::setw(2) << (int)TempSol;
        Iteration++;
        if (Iteration >= Key.length())
        {
            Iteration = 0;
        }
    }

    TempRes >> Hexa;
    cout << "\nThis is the encrypted text: \n\n" << Hexa<<"\n";
    fout << Hexa<<"   ";
}

void Decryption(int key1)
{
    string hexToUni = "";
    string textDecrypt = "";
    string Msg;
    string Key;
    int Iteration = 0;

    cout << "\nEnter the message to decrypt: \n\n";
    getline(cin, Msg);

    Key=key1;

    for (int i = 0; i < Msg.length()-1; i+=2)
    {
        string output = Msg.substr(i, 2);
        int dec = strtol(output.c_str(), NULL, 16);
        hexToUni = hexToUni + (char)dec;
    }

    for (int i = 0; i < hexToUni.length(); i++)
    {
        int temp = hexToUni[i] ^ Key[Iteration];

        textDecrypt += (char)temp;
        Iteration++;
        if (Iteration >= Key.length())
            Iteration = 0;
    }

    cout << "\nDecrypted Text: \n\n" << textDecrypt<<"\n";
    fout<< textDecrypt <<"   ";
}


int main()
{
    int key=0;
    key=Crypt();
    cout<<"This is the Encoding value: \n\n"<<key;
    fout<<key<<" ";
    Encryption(key);
    Decryption(key);

    return 0;
}
