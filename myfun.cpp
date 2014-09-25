#include<fstream>
#include<iostream>
#include<string.h>
#include<iomanip>
#include<stdlib.h>
#include<stdio.h>
#include"myfun.h"
#include"book.h"
//extern const int NUM1;
//extern const int NUM2;
const int CMD_COLS = 80;
const int CMD_LINES = 25;

using namespace std;

void SetScreenGrid()
{
    char sysSetBuf[80];
    //cout<<sysSetBuf<<"mode con cols = "<<CMD_COLS<<",lines = "<<CMD_LINES<<endl;
    sprintf(sysSetBuf,"mode con cols=%d lines=%d",CMD_COLS,CMD_LINES);
    system(sysSetBuf);

    cout<<"SetScreenGrid"<<endl;
    return ;
}

void SetSysCaption()
{
    system("title BookManager");

    cout<<"SetSysCaption"<<endl;
    return ;
}

void MainLoop()
{
    ShowWelcome();
    while(true)
    {
        ClearScreen();
        ShowWelcome();
        ShowRootMenu();
        switch(GetSelect())
        {
            case 1:
                ClearScreen();
                GuideInput();
                break;
            case 2:
                ClearScreen();
                ViewData();
                break;
            case 3:
                ClearScreen();
                DeleteBookFromFile();
                break;
        }
    }
    return ;
}

void ClearScreen()
{
    system("cls");
    cout<<"ClearScreen"<<endl;
    return ;
}
void ShowWelcome()
{
    for(int i = 0;i < 7;i++)
        cout<<endl;
    cout.width(40);
    cout<<"************"<<endl;
    cout.width(40);
    cout<<"图书管理系统"<<endl;
    cout.width(40);
    cout<<"************"<<endl;

    cout<<"ShowWelcome"<<endl;
    return ;
}
void ShowRootMenu()
{
    cout.width(40);
    cout<<"请选择功能"<<endl;
    cout<<endl;
    cout.width(38);
    cout<<" 1 添加新书"<<endl;
    cout<<endl;
    cout.width(38);
    cout<<"2 浏览全书"<<endl;
    cout<<endl;
    cout.width(38);
    cout<<"3 删除图书"<<endl;
    cout<<"ShowRootMenu"<<endl;
    return ;
}
int GetSelect()
{
    char buf[256];
    gets(buf);
    return atoi(buf);
    cout<<"GetSelect"<<endl;
    return 0;
}

void WaitUser()
{
    //int iInputPage = 0;
    cout<<"Enter---返回菜单"<<endl;
    cout<<"q-------退出"<<endl;
    char buf[256];
    gets(buf);
    if(buf[0] == 'q')
        exit(0);
    else
        ShowRootMenu();
    return ;
}
void GuideInput()
{
    char inName[NUM1];
    char inIsbn[NUM1];
    char inPrice[NUM2];
    char inAuthor[NUM2];

    cout<<"请输入书名："<<endl;
    gets(inName);
    cout<<"请输入ISBN: "<<endl;
    gets(inIsbn);
    cout<<"请输入定价："<<endl;
    gets(inPrice);
    cout<<"请输入作者："<<endl;
    gets(inAuthor);
    cout<<"GuideInput"<<endl;
    CBook book(inName, inIsbn, inPrice, inAuthor);
    book.WriteData();
    cout<<"Write Finish!"<<endl;
    WaitUser();
    return ;
}

long GetFileLength(ifstream &ifs)
{
    long tmppos;
    long respos;
    tmppos = ifs.tellg();
    ifs.seekg(0, ios::end);
    respos = ifs.tellg();
    ifs.seekg(tmppos, ios::beg);
    return respos;
}
void ViewData(int iSelectPage )
{
    int iPage = 0;
    int iCurPage = 0;
    int iDataCount = 0;
    char inName[NUM1];
    char inIsbn[NUM1];
    char inPrice[NUM2];
    char inAuthor[NUM2];
    bool bIndex = false;
    int iFileLength;
    iCurPage = iSelectPage;

    ifstream ifile;
    ifile.open("book.dat",ios::binary);
    iFileLength = GetFileLength(ifile);
    iDataCount = iFileLength/(NUM1 + NUM1 + NUM2 + NUM2);
    if(iDataCount >= 1)
        bIndex = true;
    iPage = iDataCount / 20 + 1;
    ClearScreen();
    cout<<"共有记录："<<iDataCount<<" ";
    cout<<"共有页数："<<iPage<<" ";
    cout<<"当前页数："<<iCurPage<<" ";
    cout<<"1---显示下一页"<<endl;
    cout<<"2---返回"<<endl;
    cout.width(5);
    cout<<"Index";
    cout.width(22);
    cout<<"Name";
    cout.width(22);
    cout<<"Isbn";
    cout.width(15);
    cout<<"Price";
    cout.width(15);
    cout<<"Author";
    cout<<endl;
    try
    {
        ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
        if(!ifile.fail())
        {
            for(int i = 1;i < 21;i++)
            {
                memset(inName, 0, 128);
                memset(inIsbn, 0, 128);
                memset(inPrice, 0, 50);
                memset(inAuthor, 0, 50);
                if(bIndex)
                {
                    cout.width(3);
                    cout<<((iCurPage-1) * 20 +i);
                }
                ifile.read(inName, NUM1);
                cout<<setw(24)<<inName;
                 ifile.read(inIsbn, NUM1);
                cout<<setw(24)<<inIsbn;
                 ifile.read(inPrice, NUM2);
                cout<<setw(12)<<inPrice;
                 ifile.read(inAuthor, NUM2);
                cout<<setw(12)<<inAuthor;
                cout<<endl;
                if(ifile.tellg() < 0)
                    bIndex = false;
                else
                    bIndex = true;
            }
        }
    }
    catch(...)
    {
        cout<<"throw file exception"<<endl;
        throw "file error occurred";
        ifile.close();
    }
    if(iCurPage < iPage)
    {
        iCurPage = iCurPage + 1;
        WaitView(iCurPage, iPage);
    }
    else
    {
        WaitView(iCurPage, iPage);
    }
    ifile.close();
    return ;
}

void WaitView(int nextPage, int iPage)
{
    if(nextPage == iPage)
    {
        cout<<"已到最后一页，按‘1’键回到主菜单"<<endl;
        if(GetSelect() == 1)
            MainLoop();
    }
    else
    {
        cout<<"按‘1’键回到主菜单，‘2’浏览下一页"<<endl;
        if(GetSelect() == 1)
            MainLoop();
        else
            ViewData(nextPage);
    }
    return ;
}

void DeleteBookFromFile()
{
    int iDelCount;
    cout<<"Input Delete Index:"<<endl;
    cin>>iDelCount;
    CBook tmpbook;
    tmpbook.DeleteData(iDelCount);
    cout<<"Delete Finish"<<endl;
    WaitUser();
    cout<<"DeleteBookFromFile"<<endl;
    return ;
}
