//StudentAchievementManagementSystem Check.h
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <conio.h> 
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <time.h> 
#include <cmath>
#include <set> 
//11 Files included
using namespace std;
bool adminCheck(){
	ofstream fout;
	fout.open("AdminAccess.txt");
	if(!fout) return 0;
	fout<<"SAMS has alreay gotten the admin access!"<<endl;
	fout<<"This file will be deleted by SAMS program in 1 minute!"<<endl;
	fout.close();
	system("del AdminAccess.txt /f/q");
	return 1;
}

bool DriverCheck(){
	ofstream fout;
	fout.open("D:\\DriverExist.txt");
	if(!fout) return 0;
	fout<<"SAMS is checking if Drive 'D:' exists!"<<endl;
	fout<<"Result: Exist!"<<endl;
	fout<<"This file will be deleted by SAMS program in 1 minute!"<<endl;
	fout.close();
	system("del D:\\DriverExist.txt /f/q");
	return 1;
}
