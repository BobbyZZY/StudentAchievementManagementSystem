#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h> 
using namespace std;
int main(){
	string o;
	system("mkdir C:\\ProgramData\\StudentAchievementManagementSystem");
	system("title ѧ���ɼ�����ϵͳ");
	system("cls");
	cout<<"����δע�ᣬ�������û�����";
	cin>>o;
	ofstream fout; 
	fout.open("C:\\ProgramData\\StudentAchievementManagementSystem\\~Control.usr");
	if(!fout){
		MessageBox(NULL,"ϵͳ����\r\n���Թ���Ա����������г���","ѧ���ɼ�����ϵͳ",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
		exit(0);
	}
	fout<<o<<endl;
	fout.close();
	cout<<"���������룺";
	cin>>o;
	//�����㷨��ASCII���123
	for(long long i=0;i<=o.size();i++)
		o[i]=o[i]+123;
	fout.open("C:\\ProgramData\\StudentAchievementManagementSystem\\~Control.passwd");
	if(!fout){
		MessageBox(NULL,"ϵͳ����\r\n���Թ���Ա����������г���","ѧ���ɼ�����ϵͳ",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
		exit(0);
	}
	fout<<o<<endl;
	fout.close();
	system("cls");
	MessageBox(NULL,"ע��ɹ���","ѧ���ɼ�����ϵͳ",MB_ICONINFORMATION|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
	return 0;
}
