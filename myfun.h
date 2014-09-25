#ifndef MYFUN_H
#define MYFUN_h
#include<fstream>
using namespace std;
void SetScreenGrid();
void SetSysCaption();
void MainLoop();
void ClearScreen();
void ShowWelcome();
void ShowRootMenu();
int GetSelect();
void WaitUser();
void GuideInput();
long GetFileLength(ifstream &ifs);
void WaitView(int nextPage, int iPage);
void ViewData(int iSelectPage = 1);
void DeleteBookFromFile();
#endif // MYFUN

