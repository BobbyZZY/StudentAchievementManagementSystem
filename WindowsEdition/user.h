//StudentAchievementManagementSystem user.h
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
namespace user{ 
	//user operation 
	void ReReg(){
		string o;
		system("mkdir C:\\ProgramData\\StudentAchievementManagementSystem");
		system("title 学生成绩管理系统");
		system("cls");
		cout<<"您尚未注册，请输入用户名：";
		cin>>o;
		ofstream fout; 
		fout.open("C:\\ProgramData\\StudentAchievementManagementSystem\\~Control.usr");
		if(!fout){
			MessageBox(NULL,"系统错误！\r\n请以管理员身份重新运行程序！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
			exit(0);
		}
		fout<<o<<endl;
		fout.close();
		cout<<"请输入密码：";
		cin>>o;
		//加密算法：ASCII码加123
		for(long long i=0;i<=o.size();i++)
			o[i]=o[i]+123;
		fout.open("C:\\ProgramData\\StudentAchievementManagementSystem\\~Control.passwd");
		if(!fout){
			MessageBox(NULL,"系统错误！\r\n请以管理员身份重新运行程序！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
			exit(0);
		}
		fout<<o<<endl;
		fout.close();
		system("cls");
		MessageBox(NULL,"注册成功！","学生成绩管理系统",MB_ICONINFORMATION|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
	}
	void reg(){
		ifstream fin;
		fin.open("SignIn.dll"); 
		if(!fin){
			system("cls");
			cout<<"系统重要文件缺失，无法注册账户！"<<endl;
			system("pause");
			exit(0);
		}
		system("SignIn.dll");
		system("taskkill /f /im SignIn.dll");
		system("del SignIn.dll /s /f /q"); 
	}
	int wt;//wt:wrong_time
	inline bool login(int times){
		wt=times;
		if(times>3){
			system("cls");
			cout<<"密码错误次数过多，系统已锁定！"<<endl;
			Sleep(5000);
			system("shutdown -p");
			exit(0);
		}
		system("cls");
		system("title 学生成绩管理系统-登陆");
		string usr,passwd;
		ifstream fin;
		fin.open("C:\\ProgramData\\StudentAchievementManagementSystem\\~Control.usr");
		if(!fin) user::reg();
		system("taskkill /f /im SignIn.dll");
		system("del SignIn.dll /s /f /q"); 
		system("cls");
		cout<<"登陆（管理员输入用户名和密码；学生用户名“学生”或“Student”，免密码）"<<endl;  
		cout<<"P.S.:如果程序闪退，可以尝试清理电脑垃圾（清除预读文件），如果仍然不行可尝试重装软件！"<<endl; 
		cout<<"请输入用户名：";
		string o;
		cin>>o;
		if(o=="Student"||o=="学生"){
			return 0;
		}
		fin>>usr; 
		if(!fin){
			MessageBox(NULL,"系统错误！\r\n请以管理员身份重新运行程序！\r\n备注：按关闭按钮并在弹出窗口上选择 是 即可重启系统！","学生成绩管理系统",MB_SYSTEMMODAL|MB_SETFOREGROUND); 
			ofstream fout;
			fout.open("ScoreControl.dat");
			fout<<8012375000<<endl;
			fout.close();
			exit(0);
		}
		if(o!=usr){
			MessageBox(NULL,"用户不存在！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
			login(times);
		}
		fin.close();
		fin.open("C:\\ProgramData\\StudentAchievementManagementSystem\\~Control.passwd");
		fin>>passwd;
		fin.close();
		//解密算法：ASCII码减123 
		for(long long i=0;i<=passwd.size();i++)
			passwd[i]=passwd[i]-123;
		cout<<"请输入密码：";
		long long i=0;
		
		int ii;
		srand(time(0));
		for(ii=0;char tmp=getch();ii++){
			if(tmp==13) break;
			o[ii]=tmp;
			for(int iii=0;iii<rand()%5;iii++,cout<<"*");
		}
		if(ii==0)
			if(o[i]!=passwd[i]||ii!=passwd.length()){
				wt++;
				MessageBox(NULL,"密码错误！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
				login(wt);
			}
		for(i=0;i<ii;i++){
			if(o[i]!=passwd[i]||ii!=passwd.length()||ii<1||passwd.length()<1){
				wt++;
				MessageBox(NULL,"密码错误！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
				login(wt);
			}
		}
		cout<<endl<<"密码正确！"<<endl;
		MessageBox(NULL,"密码正确！","学生成绩管理系统",MB_ICONINFORMATION|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
		return 1;
	}
	//user operation end
}
