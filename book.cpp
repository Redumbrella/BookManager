#include"book.h"
#include<string.h>
#include<iomanip>
#include<iostream>
#include<fstream>
using namespace std;
CBook::CBook(char *cName, char *cIsbn, char *cPrice, char *cAuthor)
{
    strncpy(m_cName, cName, NUM1);
    strncpy(m_cIsbn, cIsbn, NUM1);
    strncpy(m_cPrice, cPrice, NUM2);
    strncpy(m_cAuthor, cAuthor, NUM2);
}

void CBook::WriteData()
{
    ofstream ofile;
    ofile.open("book.dat",ios::binary|ios::app);
    try
    {
        ofile.write(m_cName,NUM1);
        ofile.write(m_cIsbn,NUM1);
        ofile.write(m_cPrice,NUM2);
        ofile.write(m_cAuthor,NUM2);
    }
    catch(const char*)//?
    {
        throw"file error occured";
        ofile.close();
    }
    ofile.close();
    return ;
}

void CBook::DeleteData(int iCount)
{
    long respos;
    int iDataCount = 0;
    fstream file;
    fstream tmpfile;
    ofstream ofile;
    char cTempBuf[NUM1 + NUM1 + NUM2 + NUM2];
    file.open("book.dat", ios::binary|ios::out|ios::in);
    tmpfile.open("temp.dat", ios::binary|ios::in|ios::out|ios::trunc);
    file.seekg(0, ios::end);
    respos = file.tellg();
    iDataCount = respos / (NUM1 + NUM1 + NUM2 + NUM2);
    if(iCount < 0 && iCount > iDataCount)
    {
        throw "Input number error";
    }
    else
    {
        file.seekg(iCount * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
        for(int j = 0;j < (iDataCount - iCount);j++)
        {
            memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2);
            file.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
            tmpfile.write(cTempBuf,NUM1 + NUM1 + NUM2 + NUM2);
        }
        file.close();
        tmpfile.seekg(0, ios::beg);
        ofile.open("book.dat");
        ofile.seekp((iCount - 1) * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
        for(int i = 0;i < (iDataCount - iCount);i++)
        {
            memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2);
            tmpfile.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
            ofile.write(cTempBuf,NUM1 + NUM1 + NUM2 + NUM2);
        }
    }
    tmpfile.close();
    ofile.close();
    remove("temp.dat");
}
