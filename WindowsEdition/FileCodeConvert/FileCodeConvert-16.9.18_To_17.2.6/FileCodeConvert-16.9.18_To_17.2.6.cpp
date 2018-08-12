//Copyright (C) 2018 XiyuWang All rights reserved.
//WARNING: WHO COPY WITHOUT PERMISION WILL GET A PUNISHMENT!
//THIS IS A PATCH FOR SAMS 
//DISCRIBITION:CONVERT FILE FROM V16.9.18 TO V17.2.6
//PATCH VERSION:V1
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int main(){
	system("cls");
	cout<<"StudentAchievementManagementSystem Patch Started!"<<endl;
	cout<<"FILE PATCH V1"<<endl;
	cout<<"CONVERT V16.9.18 FILE TO 17.2.6 FILE"<<endl;
	
	time_t tt = time(NULL);	
	tm* t=localtime(&tt);
	ifstream fin;
	
	cout<<endl<<"["<<(t->tm_year+1900)<<"/"<<(t->tm_mon+1)<<"/"<<(t->tm_mday)<<"-"<<(t->tm_hour)<<":";
	if(t->tm_min<10) cout<<"0"<<t->tm_min;
	else cout<<t->tm_min;
	cout<<":";
	if(t->tm_sec<10) cout<<"0"<<t->tm_sec;
	else cout<<t->tm_sec;
	fin.open("StudentScore.dat");
	cout<<"] Checking file version..."<<endl;
	string version;
	int num; 
	fin>>version>>num;
	if(version=="16.9.18")
		cout<<"Version correct!"<<endl;
	else if(version=="17.2.6"){
		cout<<"WARNING:"<<endl;
		cout<<"File version:17.2.6"<<endl;
		cout<<"Alreay the newest version!"<<endl;
		cout<<"Cannot convert!"<<endl;
		cout<<"Exiting..."<<endl;
		Sleep(1000);
		return 0;
	}
	else{
		cout<<"Invalid version! Cannot convert!"<<endl;
		cout<<"File version:"<<version<<endl;
		cout<<"Exiting..."<<endl;
		Sleep(1000);
		return 0;
	}
	fin.close(); 
	
	cout<<endl<<"["<<(t->tm_year+1900)<<"/"<<(t->tm_mon+1)<<"/"<<(t->tm_mday)<<"-"<<(t->tm_hour)<<":";
	if(t->tm_min<10) cout<<"0"<<t->tm_min;
	else cout<<t->tm_min;
	cout<<":";
	if(t->tm_sec<10) cout<<"0"<<t->tm_sec;
	else cout<<t->tm_sec;
	cout<<"] Copying file..."<<endl;
	system("copy StudentScore.dat StudentScore.dat.bak");
	
	cout<<endl<<"["<<(t->tm_year+1900)<<"/"<<(t->tm_mon+1)<<"/"<<(t->tm_mday)<<"-"<<(t->tm_hour)<<":";
	if(t->tm_min<10) cout<<"0"<<t->tm_min;
	else cout<<t->tm_min;
	cout<<":";
	if(t->tm_sec<10) cout<<"0"<<t->tm_sec;
	else cout<<t->tm_sec;
	cout<<"] Deleting old file..."<<endl;
	system("del StudentScore.dat/q/s/f");
	
	cout<<endl<<"["<<(t->tm_year+1900)<<"/"<<(t->tm_mon+1)<<"/"<<(t->tm_mday)<<"-"<<(t->tm_hour)<<":";
	if(t->tm_min<10) cout<<"0"<<t->tm_min;
	else cout<<t->tm_min;
	cout<<":";
	if(t->tm_sec<10) cout<<"0"<<t->tm_sec;
	else cout<<t->tm_sec;
	cout<<"] Checking file..."<<endl;
	fin.open("StudentScore.dat.bak");
	fin>>version>>num;
	if(fin)
		cout<<"Checked successfully!"<<endl;
	if(!fin){
		cout<<"Check failed!"<<endl;
		cout<<"Exiting..."<<endl;
		Sleep(1000);
		return 0;
	}
	
	cout<<endl<<"["<<(t->tm_year+1900)<<"/"<<(t->tm_mon+1)<<"/"<<(t->tm_mday)<<"-"<<(t->tm_hour)<<":";
	if(t->tm_min<10) cout<<"0"<<t->tm_min;
	else cout<<t->tm_min;
	cout<<":";
	if(t->tm_sec<10) cout<<"0"<<t->tm_sec;
	else cout<<t->tm_sec;
	cout<<"] Getting ready to convert and output..."<<endl;
	ofstream fout;
	fout.open("StudentScore.dat");
	fout<<"17.2.6"<<endl;
	fout<<num<<endl;
	 
	cout<<endl<<"["<<(t->tm_year+1900)<<"/"<<(t->tm_mon+1)<<"/"<<(t->tm_mday)<<"-"<<(t->tm_hour)<<":";
	if(t->tm_min<10) cout<<"0"<<t->tm_min;
	else cout<<t->tm_min;
	cout<<":";
	if(t->tm_sec<10) cout<<"0"<<t->tm_sec;
	else cout<<t->tm_sec;
	cout<<"] Converting and outputing new file..."<<endl;
	cout<<"Log:"<<endl;
	for(int ii=0;ii<num;ii++){
		cout<<"["<<(t->tm_year+1900)<<"/"<<(t->tm_mon+1)<<"/"<<(t->tm_mday)<<"-"<<(t->tm_hour)<<":";
		if(t->tm_min<10) cout<<"0"<<t->tm_min;
		else cout<<t->tm_min;
		cout<<":";
		if(t->tm_sec<10) cout<<"0"<<t->tm_sec;
		else cout<<t->tm_sec;
		cout<<"]"<<endl;
		cout<<"Information No."<<ii+1<<endl;
		cout<<"Inputing file..."<<endl;
		string exam_name,id,name;
		double S;
		int i;
		fin>>exam_name>>id>>name>>S;
		cout<<"Converting file..."<<endl;
		S=S-12397;
		cout<<"Outputing result..."<<endl;
		cout<<"Exam_name:"<<exam_name<<" Name:"<<name<<" Id:"<<id<<" Score:"<<S<<endl;
		cout<<"Outputing file..."<<endl;
		fout<<exam_name<<" "<<name<<" "<<id<<" "<<char(((int) S)+5)<<" ";
		cout<<"===================="<<endl;
	}
	
	cout<<endl<<"["<<(t->tm_year+1900)<<"/"<<(t->tm_mon+1)<<"/"<<(t->tm_mday)<<"-"<<(t->tm_hour)<<":";
	if(t->tm_min<10) cout<<"0"<<t->tm_min;
	else cout<<t->tm_min;
	cout<<":";
	if(t->tm_sec<10) cout<<"0"<<t->tm_sec;
	else cout<<t->tm_sec;
	cout<<"] Finishing..."<<endl;
	fin.close();
	fout.close();
	system("del StudentScore.dat.bak/s/f/q");
	fin.open("StudentScore.dat");
	if(!fin){
		cout<<"ERROR: OUTPUT FAILED!"<<endl;
		cout<<"Exiting..."<<endl;
		Sleep(1000);
		return 0;
	}
	fin.close();
	
	cout<<endl<<"["<<(t->tm_year+1900)<<"/"<<(t->tm_mon+1)<<"/"<<(t->tm_mday)<<"-"<<(t->tm_hour)<<":";
	if(t->tm_min<10) cout<<"0"<<t->tm_min;
	else cout<<t->tm_min;
	cout<<":";
	if(t->tm_sec<10) cout<<"0"<<t->tm_sec;
	else cout<<t->tm_sec;
	cout<<"] Finished! Program will exit in 5 seconds!"<<endl;
	Sleep(5000);
	return 0;
}
