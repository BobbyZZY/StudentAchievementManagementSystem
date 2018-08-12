//Copyright (C) 2017-2018 XiyuWang All rights reserved.
//Version: 18.1.3 

//Author: XiyuWang
//Author E-mail Address: XiyuWang_Code@hotmail.com 
//GitHub Address: https://xiyuwang2006.github.io/StudentAchievementManagementSystem 

//THIS APPLICATION CAN ONLY RUN ON WINDOWS (BEST ON X64, X32 MAY HAVE SOME RUNTIME ERROR)

/* 学生成绩管理系统 功能：
1.录入+更改+删除 学生信息 
2.文件 输入+输出
3.五种 查询方式
4.可更改 用户信息
5.可锁定系统  
6.班级模式 
最新推出：批量删除信息 
更多功能，敬请期待！ 
*/

#include "include.h"
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)  
using namespace std;

BOOL CtrlHandler(DWORD fdwCtrlType);
bool ROSid=1,ROSname=1,ROSnum=1;
long long i,j,n,ti;
int menl,midl,mnl;//menl:max exam_name length	midl:max id length	mnl:max name length
string o;//o:order
long long ScoreControl,ScoreControlFI;//FI:FileInput 

time_t tt = time(NULL);
tm* t=localtime(&tt);

struct student{
	double S;//S:Score
	string name,id,exam_name;
};
student z;
struct cmp_ss/*ss:student score*/{
	bool operator()(const student&x,const student&y)const{
		if(x.exam_name<y.exam_name) return 1;
		if(x.exam_name>y.exam_name) return 0;
		if(x.S>y.S) return 1;
		if(x.S<y.S) return 0;
		if(x.id<y.id) return 1;
		if(x.id>y.id) return 0;
		return 0;
	}
};
set<student,cmp_ss> stu;
set<student,cmp_ss>::iterator it;

struct student_info{
	string name,id;
};
student_info zz;
struct cmp_si/*si:student info*/{
	bool operator()(const student_info&x,const student_info&y)const{
		if(x.id>y.id) return 0;
		if(x.id<y.id) return 1;
		return 0;
	}
};
set<student_info,cmp_si> stuinfo;
set<student_info,cmp_si>::iterator siit;//student info iterator

int max(int a,int b){
	if(a>b) return a;
	return b;
}

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

bool ACTIVATION(){
	string code;
	ifstream fin;
	fin.open("Activation.dat");
	getline(fin,code);
	if(!fin||code!="SYSTEM ACTIVATED! ALLOWED TO RUN ON THIS COMPUTER! CODE:ck~.jj=T5Nif%h![utA#P[xvbQWH#-=c"){
		MessageBox(NULL,"系统尚未激活，请按确定键前往激活！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND);
		system("Activation.dll");
		exit(0);
	}
}

void start(int len){
	srand(time(0));
	string key,ans;
	system("cls");
	system("title 学生成绩管理系统");
	cout<<"验证码："; 
	for(i=0;i<len;i++){
		key[i]=char(65+rand()%(65-122+1));
		cout<<key[i];
	}	
	cout<<endl<<"请输入验证码：";
	cin>>ans;
	for(i=0;i<len;i++)
		if(ans[i]!=key[i]) start(len+1);
	cout<<"验证码正确！"<<endl; 
}

void load(){
	system("cls");
	system("title 学生成绩管理系统-加载中......");
	cout<<"Copyright (C) 2017-2018 XiyuWang All rights reserved."<<endl;
	cout<<"Version:18.1.3"<<endl; 
	cout<<"注意：所有数据输入时不可添加空格，否则系统会出错！"<<endl; 
	cout<<"小提示：您可以按 Ctrl+Z 停止输入数据！"<<endl; 
	cout<<"加载中......"<<endl; 
	for(i=1;i<=10;i++){
		cout<<"■";
		Sleep(188);
	}
	system("title 学生成绩管理系统"); 
}

void hint(){
	system("cls");
	system("title 学生成绩管理系统"); 
	cout<<"亲，Windows10系统可以按 F11 全屏，体验最佳效果哦！"<<endl;
	Sleep(2000);
}

namespace ClassEdition{
	//Class Edition
	int reg(){
		stuinfo.clear();
		string passwd,name,id;
		int n;
		system("cls");
		char source[1000],classname[1000],finclssnm[1000];
		string s,fins;
		cout<<"请输入旧班级名称：";
		cin>>source; 
		cout<<"请输入新班级名称：";
		cin>>s;
		strncpy(classname,s.c_str(),s.length()+1);
		fins="ClassEdition\\"+s+".dat";
		strncpy(finclssnm,fins.c_str(),fins.length()+1);		
		if(rename(source,classname)){
			cout<<"无法修改班级名称，请重试！"<<endl;
			system("pause");
			return 1;
		}
		else{
			ifstream fin;
			fin.open(finclssnm);
			fin>>classname>>passwd;
			ofstream fout;
			fout.open(classname);
			fout<<classname<<passwd;
			cout<<"请输入新班级管理员密码：";
			cin>>passwd;
			//加密算法 
			for(i=0;i<passwd.length();i++)
				passwd[i]+=18;
			fout<<classname<<" "<<passwd<<" "<<n<<endl;
			for(i=1;i<=n;i++){
				fin>>name>>id;
				fout<<name<<" "<<id<<endl;
			}
		}
		system("cls");
	} 
	int make(string value){
		ifstream fin;
		ofstream fout;
		stuinfo.clear();
		system("cls");
		if(value=="remake"){
			set<student_info,cmp_si> stmp;
			set<student_info,cmp_si>::iterator stmpit;
			char oclssnm[1000],str[1000];
			cout<<"请输入旧班级名称：";
			gets(oclssnm);
			strcat(str,oclssnm);
			remove(str);
			cout<<"请输入新班级名称："; 
		}
		if(value=="make"){
			string classname,passwd;
			int n;
			cout<<"请输入班级名称：";
		}
		string s,passwd;
		char classname[1000],finclssnm[1000];
		cin>>s;
		strncpy(classname,s.c_str(),s.length()+1);
		s="ClassEdition\\"+s+".dat";
		strncpy(finclssnm,s.c_str(),s.length()+1);		
		fin.open(finclssnm);
		fout.open(finclssnm);;
		cout<<"请输入班级管理员密码：";
		cin>>passwd;
		//加密算法 
		for(i=0;i<passwd.length();i++)
			passwd[i]+=18;
		system("cls");
		cout<<"请输入班级人数：";
		cin>>n;
		if(n+stu.size()>=10000){
			cout<<"班级人数过多！"<<endl;
			system("pause");
			return 1;
		}
		fout<<classname<<" "<<passwd<<" "<<n<<endl; 
		for(i=1;i<=n;i++){
			system("cls");
			cout<<"正在输入第"<<i<<"个学生的信息，共"<<n<<"项......"<<endl;
			cout<<"请输入学生学号："; 
			cin>>zz.id;
			cout<<"请输入学生姓名：";
			cin>>zz.name;
			stuinfo.insert(zz);
			for(j=0;j<zz.id.length();j++)
				zz.id[j]+=10;
			for(j=0;j<zz.name.length();j++)
				zz.name[j]+=10;
			fout<<zz.name<<" "<<zz.id<<endl;
		}
		fout.close();
		system("cls");
		cout<<"班级创建完成！"<<endl;
		system("pause");
		return 0;
	}
	int main(){
		system("cls");
		stuinfo.clear();
		string s,ipwd,clssnm,pwd,classname,passwd;
		char iclssnm[1000],finclssnm[1000];
		int n=0;
		ifstream fin;
		cout<<"班级模式-登陆"<<endl; 
		cout<<"班级名称：";
		cin>>s;
		strncpy(iclssnm,s.c_str(),s.length()+1);
		s="ClassEdition\\"+s+".dat";
		strncpy(finclssnm,s.c_str(),s.length()+1);		
		fin.open(finclssnm);
		if(!fin){
			cout<<"班级 "<<iclssnm<<" 不存在！"<<endl;
			system("pause");
			return 1;
		}
		fin>>clssnm>>passwd>>n;
		cout<<"密码：";
		for(i=0;i<clssnm.length();i++)
			clssnm[i]-=18;
		for(i=0;i<passwd.length();i++)
			passwd[i]-=18;
		int ii;
		srand(time(0));
		for(ii=0;char tmp=getch();ii++){
			if(tmp==13) break;
			o[ii]=tmp;
			for(int iii=0;iii<rand()%5;iii++,cout<<"*");
		}
		for(i=0;i<ii;i++){
			if(o[i]!=passwd[i]||ii!=passwd.length()){
				MessageBox(NULL,"密码错误！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
				return 1;
			}
		}
		system("cls");
		cout<<"请输入考试名称：";
		cin>>z.exam_name; 
		for(i=1;i<=n;i++){
			fin>>zz.name>>zz.id;
			for(j=0;j<zz.id.length();j++)
				zz.id[j]-=10;
			for(j=0;j<zz.name.length();j++)
				zz.name[j]-=10;
			stuinfo.insert(zz);
		}
		for(siit=stuinfo.begin(),i=1;siit!=stuinfo.end();siit++,i++){
			system("cls");
			cout<<"正在输入 "<<iclssnm<<" 中第"<<i<<"个学生的成绩，共"<<n<<"项......"<<endl; 
			z.id=siit->id;
			z.name=siit->name;
			cout<<"学号："<<z.id<<endl;
			cout<<"姓名："<<z.name<<endl;
			cout<<"考试名称："<<z.exam_name<<endl;
			string tmp; 
			inputScore:
			cout<<"请输入成绩：";
			cin>>tmp;
			for(int iii=0;iii<tmp.size();iii++)
				if((tmp[iii]<'0'||tmp[iii]>'9')&&tmp[iii]!='.'){
					system("cls");
					cout<<endl<<"成绩不合法！请重新输入！"<<endl; 
					system("pause");
					system("cls");
					goto inputScore;
				}
			z.S=atof(tmp.c_str());
			for(it=stu.begin();it!=stu.end();it++)
				if(it->id==z.id&&it->name==z.name&&it->exam_name==z.exam_name){
					ef:
					system("cls");
					cout<<"学号："<<it->id<<endl;
					cout<<"姓名："<<it->name<<endl;
					cout<<"考试名称："<<it->exam_name<<endl; 
					cout<<"本地成绩："<<fixed<<setprecision(0)<<it->S<<endl; 
					cout<<"输入成绩："<<tmp<<endl; 
					cout<<"错误：该学生信息已存在！"<<endl;
					cout<<"================================="<<endl;
					cout<<"1.保存本地信息     2.保存输入信息"<<endl; 
					cin>>o;
					if(o[0]=='1') z.S=it->S;
					if(o[0]!='1'&&o[0]!='2') goto ef;
					break;  
				}
			if(z.S>ScoreControl+0.999999){
				system("cls");
				cout<<"成绩超过最大限制！"<<endl;
				getch();
				goto inputScore; 
			}
			else stu.insert(z);
		}
		system("cls");
		cout<<"班级模式数据录入结束！"<<endl;
		system("pause"); 
	}
	//Class Edition
}

namespace file{
	//file operation
	int output(bool save){
		double Average,All;
		ofstream fout;
		system("cls");
		z.exam_name=' ';
		fout.open("StudentScore.dat"); 
		if(!fout)
			MessageBox(NULL,"错误：\r\n无法保存加密数据文件！请检查本系统是否已经获得管理员权限！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
		else{	
			fout<<"18.1.3"<<endl;
			fout<<stu.size()<<endl;
			for(it=stu.begin(),i=1;it!=stu.end();it++,i++){
				z.exam_name=it->exam_name;
				for(int i=0;i<=z.exam_name.size();i++)
					z.exam_name[i]=z.exam_name[i]+1;
				z.name=it->name;
				for(int i=0;i<=z.name.size();i++)
					z.name[i]=z.name[i]+2;
				z.id=it->id;
				for(int i=0;i<=z.id.size();i++)
					z.id[i]=z.id[i]+3;
				z.S=it->S;
				fout<<z.exam_name<<" "<<z.name<<" "<<z.id<<" "<<char(((int) z.S)+5)<<" ";
			}
			fout.close();
		}
		fout.open("D:\\学生成绩信息.csv",ios::out|ios::trunc); 
		if(!fout)
			MessageBox(NULL,"错误：\r\n无法保存Excel表格文件！请检查驱动器D（D盘）是否存在！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
		else{ 
			if(stu.size()==0) fout<<"暂无记录！"<<endl;
			else{
				fout<<"排名"<<","<<"学号"<<","<<"成绩"<<","<<"姓名"<<","<<"考试名称"<<endl;
				for(it=stu.begin(),i=1;it!=stu.end();it++,i++){
					if(z.exam_name!=it->exam_name&&i!=1){
						Average=All/(i-1);
						All=0;
						i=1;
						fout<<"平均分："<<Average<<endl;
						fout<<endl;
					}
					if(i<10) fout<<i<<"   "<<","<<"";
					if(i>=10&&i<100) fout<<i<<"  "<<","<<"";
					if(i>=100&&i<1000) fout<<i<<" "<<","<<"";
					if(i>=1000&&i<10000) fout<<i<<""<<","<<"";
			 		if(i>=10000&&i<100000) fout<<i<<"|";
					if((it->id).length()==1) fout<<it->id<<"   "<<","<<" ";
					if((it->id).length()==2) fout<<it->id<<"  "<<","<<" ";
					if((it->id).length()==3) fout<<it->id<<" "<<","<<" ";
					if((it->id).length()==4) fout<<it->id<<""<<","<<" ";
					fout<<" "<<","<<" "<<it->name<<" "<<","<<" "<<it->exam_name<<endl;
					fout<<setprecision(0)<<fixed<<it->S;
					z.exam_name=it->exam_name;
					All+=it->S; 
				}
			Average=All/(i-1);
			fout<<"平均分："<<Average<<endl;
			}
			fout.close();
		}
		if(!save&&fout){
			cout<<"完成！请关闭预览窗口（Excel表格窗口）后继续！"<<endl;
			system("D:\\学生成绩信息.csv");
			system("pause");
		}
	}
	int input(bool w){
		bool found;
		system("cls");
		unsigned long long int num;
		string version;
		ifstream fin;
		fin.open("StudentScore.dat"); 
		if(!fin&&!w){
			MessageBox(NULL,"文件\"StudentScore.dat\"不存在！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND);
			return 1;
		}
		if(!fin&&w) return 1; 
		fin>>version>>num;
		if((version!="18.1.3"&&version!="17.2.6")&&!w){
			cout<<"文件版本与系统不符，无法录入信息！"<<endl;
			cout<<"文件版本："<<version<<endl; 
			cout<<"系统版本：18.1.3"<<endl;
			cout<<"另外，V17.2.6和V18.1.3版本系统使用相同文件加密方式！"<<endl; 
			cout<<"部分版本的文件支持使用修复程序转码！"<<endl; 
			system("pause");
			return 1;
		}
		if(version!="18.1.3"&&version!="17.2.6"&&w) return 1;
		if((num+stu.size())>=10000&&!w){
			cout<<"文件数据量过大，无法录入系统！"<<endl;
			cout<<"文件数据量： "<<num<<endl;
			cout<<"系统当前数据量："<<stu.size()<<endl;
			cout<<"录入后数据量："<<num+stu.size()<<endl;
			cout<<"超过标准："<<num+stu.size()-10000<<endl;
			system("pause");
			return 1;
		}
		if((num+stu.size())>=10000&&w) return 1;
		if(version=="17.2.6") cout<<"检测到17.2.6版本文件，将在下一次保存文件时转码！"<<endl; 
		bool allFile=0,allSave=0,File=0,Save=0; 
		for(int iiii=1;iiii<=num;iiii++,File=0,Save=0){
			char Stmp;
			fin>>z.exam_name>>z.name>>z.id>>Stmp; 
			for(i=0;i<=z.exam_name.size();i++)
				z.exam_name[i]=z.exam_name[i]-1;
			menl=max(menl,z.exam_name.length());
			for(i=0;i<=z.name.size();i++)
				z.name[i]=z.name[i]-2;
			mnl=max(mnl,z.name.length());
			for(i=0;i<=z.id.size();i++)
				z.id[i]=z.id[i]-3;
			z.S=((int) Stmp)-5;
			midl=max(midl,z.id.length());
			cout<<z.exam_name<<z.name<<z.id<<z.S;
			for(it=stu.begin();it!=stu.end();it++){
				if(it->exam_name==z.exam_name&&it->name==z.name&&it->id==z.id&&!allFile&&!allSave){
					fileInputError:
					system("cls");
					cout<<"文件";
					if(w) cout<<"自动";
					cout<<"引入时出错：检测到相同学生信息！"<<endl;
					cout<<"学号："<<it->id<<endl; 
					cout<<"姓名："<<it->name<<endl;
					cout<<"考试名称："<<it->exam_name<<endl;
					cout<<"本地成绩："<<fixed<<setprecision(0)<<it->S<<endl;
					cout<<"文件成绩："<<fixed<<setprecision(0)<<z.S<<endl; 
					cout<<"============================================"<<endl;
					cout<<"1.本地    2.全选本地    3.文件    4.全选文件"<<endl; 
					cout<<"请选择要保留的信息（序号）："; 
					cin>>o;
					if(o[0]=='1') Save=1;
					else if(o[0]=='2') allSave=1;
					else if(o[0]=='3') File=1;
					else if(o[0]=='4') allFile=1;
					else goto fileInputError;
				}
			}
			if(((File||allFile)&&!Save&&!allSave)||w) stu.insert(z);
		}
		if(!w) MessageBox(NULL,"完成！","学生成绩管理系统",MB_ICONINFORMATION|MB_SYSTEMMODAL|MB_SETFOREGROUND);
	}
	int backup(){
		system("mkdir D:\\StudentAchievementManagementSystem_BACKUP\\");
		system("copy C:\\ProgramData\\StudentAchievementManagementSystem\\~Control.usr D:\\StudentAchievementManagementSystem_BACKUP\\~Control.usr");
		system("copy C:\\ProgramData\\StudentAchievementManagementSystem\\~Control.passwd D:\\StudentAchievementManagementSystem_BACKUP\\~Control.passwd");
		system("copy StudentScore.dat D:\\StudentAchievementManagementSystem_BACKUP\\StudentScore.dat");
		system("copy ClassEdition\\* D:\\StudentAchievementManagementSystem_BACKUP\\ClassEdition\\");
		system("copy Backup.dll D:\\StudentAchievementManagementSystem_BACKUP\\Backup.exe");
		system("cls");
		cout<<"备份成功，所有文件都储存于文件夹“D:\\StudentAchievementManagementSystem_BACKUP”中！"<<endl;
		cout<<"如需导入其它计算机，则须将储存文件的文件夹（注意：直接复制文件夹）复制到另外一台计算机，然后 以管理员身份 运行文件夹中的Backup.exe，即会自动导入，导入完成后将会删除备份文件！"<<endl;
		cout<<"                                                                                            ~~~~~~~~~~~~~~"<<endl;
		getch(); 
	}
	//file operation end
}

namespace record_input{ 
	//record operation (input,change,delete)
	int rinput(){
		ris: 
		o[0]=0; 
		bool found=false;
		ri:
		system("cls");
		cout<<"请输入学号：";
		cin>>z.id;
		midl=max(midl,z.id.length());
		cout<<"请输入姓名：";
		cin>>z.name;
		mnl=max(mnl,z.name.length());
		cout<<"请输入考试名称：";
		cin>>z.exam_name; 
		menl=max(menl,z.exam_name.length());
		string tmp; 
		inputScore:
		cout<<"请输入成绩：";
		cin>>tmp;
		for(int iii=0;iii<tmp.size();iii++)
			if((tmp[iii]<'0'||tmp[iii]>'9')&&tmp[iii]!='.'){
				system("cls");
				cout<<endl<<"成绩不合法！请重新输入！"<<endl; 
				system("pause");
				system("cls");
				goto inputScore;
			}
		z.S=atof(tmp.c_str());
		for(it=stu.begin();it!=stu.end();it++)
			if(it->id==z.id&&it->name==z.name&&it->exam_name==z.exam_name){
				system("cls");
				cout<<"错误：该记录已存在！"<<endl;
				cout<<"学号："<<it->id<<endl;
				cout<<"姓名："<<it->name<<endl;
				cout<<"考试名称："<<it->exam_name<<endl;
				cout<<"本地成绩："<<fixed<<setprecision(0)<<it->S<<endl;
				cout<<"输入成绩："<<fixed<<setprecision(0)<<z.S<<endl;
				cout<<"===================="<<endl;
				cout<<"是否替换？(Y/N)"; 
				cin>>o;
				o[0]=='Y'||o[0]=='y'?found=false:found=true;
				break;
			}
		if(z.S>ScoreControl){
			system("cls");
			cout<<"成绩超过最大限制！"<<endl;
			getch();
			return 0;
		}
		else{
			stu.insert(z);
			system("cls");
			cout<<"输入完成！是否继续输入？(Y/N)"<<endl;
			cin>>o;
			if(o[0]=='y'||o[0]=='Y') goto ris;
			else return 0;
		}
	}
	int rchange(){
		rcs:
		o[0]=0;
		system("cls");
		string tmp;
		j=1;
		cout<<"请输入学生学号或姓名：";
		cin>>tmp;
		cout<<"请输入考试名称：";
		cin>>z.exam_name; 
		for(it=stu.begin();it!=stu.end();it++,j++){
			if((it->id==tmp||it->name==tmp)&&it->exam_name==z.exam_name){
				system("cls"); 
				cout<<"该学生原信息"<<endl;
				cout<<"学号："<<it->id<<endl;
				cout<<"姓名："<<it->name<<endl;
				cout<<"考试名称："<<it->exam_name<<endl; 
				cout<<"成绩："<<it->S<<endl;
				if(MessageBox(NULL,"您确定要更改该学生的信息吗？","学生成绩管理系统",MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES){
					z.id=it->id;
					z.name=it->name;
					stu.erase(it);
					break;
				}
				else return 1;
			}
			if(j==stu.size()){
				system("cls");
				MessageBox(NULL,"未找到该学生的信息，请检查信息是否已经录入系统！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND);
				return 1;
			}
		}
		rc:
		cout<<"请输入新考试名称：";
		cin>>z.exam_name; 
		menl=max(menl,z.exam_name.length());
		string ttmp;
		inputScore:
		cout<<"请输入成绩：";
		cin>>ttmp;
		for(int iii=0;iii<ttmp.size();iii++)
			if((ttmp[iii]<'0'||ttmp[iii]>'9')&&ttmp[iii]!='.'){
				system("cls");
				cout<<endl<<"成绩不合法！请重新输入！"<<endl; 
				system("pause");
				system("cls");
				goto inputScore;
			}
		z.S=atof(ttmp.c_str());
		stu.insert(z);
		system("cls");
		cout<<"更改完成！是否继续更改？(Y/N)"<<endl;
		cin>>o;
		if(o[0]=='Y'||o[0]=='y') goto rcs;
		else return 0; 
	}
	int rdelete(){
		rds:
		system("cls");
		string tmp;
		j=1;
		cout<<"请输入学生学号或姓名：";
		cin>>tmp;
		cout<<"请输入考试名称：";
		cin>>z.exam_name; 
		for(it=stu.begin();it!=stu.end();it++,j++){
			if((it->id==tmp||it->name==tmp)&&z.exam_name==it->exam_name){
				system("cls"); 
				cout<<"该学生原信息"<<endl;
				cout<<"学号："<<it->id<<endl;
				cout<<"姓名："<<it->name<<endl;
				cout<<"考试名称："<<it->exam_name<<endl; 
				cout<<"成绩："<<fixed<<setprecision(0)<<it->S<<endl;
				if(MessageBox(NULL,"您确定要删除该学生的信息吗？","学生成绩管理系统",MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES){
					z.id=it->id;
					stu.erase(it);
					break;
				}
				else return 1;
			}
			if(j==stu.size()){
				system("cls");
				MessageBox(NULL,"未找到该学生的信息，请检查信息是否已经录入系统！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
				return 1;
			}
		}
		system("cls");
		cout<<"删除完成！是否继续删除？(Y/N)"<<endl;
		cin>>o;
		if(o[0]=='Y'||o[0]=='y') goto rds;
		else return 0; 
	}
	int rexam_nameDelete(){
		 system("cls");
		 cout<<"请输入考试名称：";
		 cin>>z.exam_name;
		 system("cls");	
		 cout<<"日志："<<endl;
		 cout<<"正在删除考试名称为 "<<z.exam_name<<" 的所有信息"<<endl;
		 bool found=false;
		 for(it=stu.begin(),i=1;it!=stu.end();it++,i++){
			if(it->exam_name==z.exam_name){
				cout<<"已删除"<<i<<"条信息（学号："<<it->id<<" 姓名："<<it->name<<" 分数："<<fixed<<setprecision(0)<<it->S<<"）"<<endl;
				stu.erase(it);
				it=stu.begin();
				found=true;
			}
		}
		if(!found){
			system("cls");
			MessageBox(NULL,"未找到符合的考试，请检查信息是否已经录入系统！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
			return 1;
		}
		getch();
		return 0;
	}
	//record operation end
}

namespace record_output{
	//record output settings
	void Settings(){
		while(1){
			system("cls");
			while(1){
				ifstream fin;
				fin.open("ROS.dat");
				fin>>ROSnum>>ROSid>>ROSname;
				fin.close();
				break;
			}
			cout<<"学生成绩管理系统-查询设置"<<endl;
			if(ROSnum) cout<<"(√) ";
			else cout<<"(×) "; 
			cout<<"1.显示排名"<<endl; 
			if(ROSid) cout<<"(√) ";
			else cout<<"(×) "; 
			cout<<"2.显示学号"<<endl; 
			if(ROSname) cout<<"(√) ";
			else cout<<"(×) "; 
			cout<<"3.显示姓名"<<endl;
			cout<<"(√) 4.退出设置"<<endl; 
			o[0]=getch();
			if(o[0]=='1'){
				if(ROSnum) ROSnum=0;
				else ROSnum=1;
			}
			if(o[0]=='2'){
				ROSid?ROSid=0:ROSid=1;
				if(!ROSid&&!ROSname){
					MessageBox(NULL,"学号和姓名中必须有一项选中！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
					ROSid=1;
				}
			}
			if(o[0]=='3'){
				ROSname?ROSname=0:ROSname=1;
				if(!ROSid&&!ROSname){
					MessageBox(NULL,"学号和姓名中必须有一项选中！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
					ROSname=1;
				}
			}
			while(1){
				ofstream fout;
				fout.open("ROS.dat");
				fout<<ROSnum<<" "<<ROSid<<" "<<ROSname;
				fout.close();
				break;
			}
			if(o[0]=='4'){
				system("cls");
				cout<<"学生成绩管理系统-查询设置"<<endl;
				if(ROSnum) cout<<"(√) ";
				else cout<<"(×) "; 
				cout<<"1.显示排名"<<endl; 
				if(ROSid) cout<<"(√) ";
				else cout<<"(×) "; 
				cout<<"2.显示学号"<<endl; 
				if(ROSname) cout<<"(√) ";
				else cout<<"(×) "; 
				cout<<"3.显示姓名"<<endl;
				cout<<"(×) 4.退出设置"<<endl; 
				Sleep(500);
				break;
			}
			o[0]=0;
		}
	}
	//record output (five ways)
	//output all information
	int output(){
		double All,Average;
		system("cls");
		if(stu.size()<1){
			MessageBox(NULL,"暂无记录！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND);
			return 1;
		}
		clock_t start = clock();
		z.exam_name=' ';
		if(ROSnum) cout<<"排名 |";
		if(ROSid){
			cout<<"学号 ";
			for(i=midl;i>4;i--) cout<<" ";
			cout<<"|";
		}
		if(ROSname){
			cout<<"姓名 ";
			for(i=mnl;i>4;i--) cout<<" ";
			cout<<"|";
		}
		cout<<"考试名称 ";
		for(i=menl;i>8;i--) cout<<" ";
		cout<<"|成绩"<<endl;
		double STmp=-1;
		int sum;
		for(it=stu.begin(),i=0,sum=1;it!=stu.end();it++,sum++){
			if(STmp!=it->S) i++;
			if(z.exam_name!=it->exam_name&&z.exam_name.length()>0){
				Average=All/(sum-1);
				if((sum-1)!=0)cout<<"平均分："<<setprecision(2)<<fixed<<Average<<endl;
				if((sum-1)!=0)cout<<endl;
				All=0;
				i=1;
				sum=1;
			}
			if(ROSnum){
				if(i<10) cout<<i<<"    |";
				if(i>=10&&i<100) cout<<i<<"   |";
				if(i>=100&&i<1000) cout<<i<<"  |";
				if(i>=1000&&i<10000) cout<<i<<" |";
				if(i>=10000&&i<100000) cout<<i<<"|";
			}
			if(ROSid){
				cout<<it->id;
				for(j=midl;j>=it->id.length();j--) cout<<" ";
				cout<<"|";
			}
			if(ROSname){
				cout<<it->name;
				for(j=mnl;j>=it->name.length();j--) cout<<" ";
				cout<<"|";
			}
			cout<<it->exam_name;
			for(j=menl;j>=it->exam_name.length();j--) cout<<" ";
			cout<<"|"<<setprecision(0)<<fixed<<it->S;
			cout<<endl;
			STmp=it->S; 
			All+=it->S;
			z.exam_name=it->exam_name;
		}
		Average=All/(sum-1);
		if(sum-1!=0) cout<<"平均分："<<setprecision(2)<<fixed<<Average<<endl<<endl;
		clock_t end   = clock();
		cout << "使用时间：" <<setprecision(2)<<fixed<<(double)(end - start) / CLOCKS_PER_SEC << " 秒" << endl;
		system("pause");
	}
	//output only one student's information
	int find(){
		system("cls");
		if(stu.size()<1){
			MessageBox(NULL,"暂无记录！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND);
			return 1;
		}
		double Average,All;
		z.exam_name=' ';
		string tmp;
		bool f=false; 
		cout<<"请输入学生学号或姓名：";
		cin>>tmp;
		clock_t start = clock();
		if(ROSnum) cout<<"排名 |";
		if(ROSid){
			cout<<"学号 ";
			for(i=midl;i>4;i--) cout<<" ";
			cout<<"|";
		}
		if(ROSname){
			cout<<"姓名 ";
			for(i=mnl;i>4;i--) cout<<" ";
			cout<<"|";
		}
		cout<<"考试名称 ";
		for(i=menl;i>8;i--) cout<<" ";
		cout<<"|成绩"<<endl;
		double STmp;
		int sum,rank=1;
		bool appered=0;
		for(it=stu.begin(),i=0,sum=1;it!=stu.end();it++,sum++,rank++){
			if(STmp!=it->S) i=rank;
			if(z.exam_name!=it->exam_name&&z.exam_name.length()>0){
				Average=All/(sum-1);
				All=0,i=rank=sum=1;
				if(appered){
					appered=0;
					cout<<"平均分："<<setprecision(2)<<fixed<<Average<<endl;
					cout<<endl;
				}
			}
			if(it->id==tmp||it->name==tmp){
				if(ROSnum){
					if(i<10) cout<<i<<"    |";
					if(i>=10&&i<100) cout<<i<<"   |";
					if(i>=100&&i<1000) cout<<i<<"  |";
					if(i>=1000&&i<10000) cout<<i<<" |";
					if(i>=10000&&i<100000) cout<<i<<"|";
				}
				if(ROSid){
					cout<<it->id;
					for(j=midl;j>=it->id.length();j--) cout<<" ";
					cout<<"|";
				}
				if(ROSname){
					cout<<it->name;
					for(j=mnl;j>=it->name.length();j--) cout<<" ";
					cout<<"|";
				}
				cout<<it->exam_name;
				for(j=menl;j>=it->exam_name.length();j--) cout<<" ";
				cout<<"|"<<setprecision(0)<<fixed<<it->S;
				cout<<endl;
				f=true;
				appered=1;
			}
			STmp=it->S; 
			All+=it->S; 
			z.exam_name=it->exam_name;
		}
		Average=All/(sum-1);
		if(appered) cout<<"平均分："<<setprecision(2)<<fixed<<Average<<endl<<endl;
		if(f==true){
			clock_t end   = clock();
			cout << "使用时间：" <<setprecision(2)<<fixed<< (double)(end - start) / CLOCKS_PER_SEC << " 秒" << endl;
			system("pause");
			return 1;
		}
		system("cls");
		MessageBox(NULL,"未找到该学生的信息，请检查信息是否已经录入系统！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
		return 1;
	}
	//output information in given examname
	int find_examname(){
		system("cls");
		if(stu.size()<1){
			MessageBox(NULL,"暂无记录！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND);
			return 1;
		}
		double Average,All;
		bool f=false; 
		z.exam_name=' ';
		string tmp;
		cout<<"请输入考试名称：";
		cin>>tmp;
		clock_t start = clock();
		if(ROSnum) cout<<"排名 |";
		if(ROSid){
			cout<<"学号 ";
			for(i=midl;i>4;i--) cout<<" ";
			cout<<"|";
		}
		if(ROSname){
			cout<<"姓名 ";
			for(i=mnl;i>4;i--) cout<<" ";
			cout<<"|";
		}
		cout<<"考试名称 ";
		for(i=menl;i>8;i--) cout<<" ";
		cout<<"|成绩"<<endl;
		double STmp;
		int sum=1,rank=1;
		bool appered=0;
		for(it=stu.begin(),i=0;it!=stu.end();it++,sum++,rank++){
			if(STmp!=it->S) i=rank;
			if(z.exam_name!=it->exam_name&&z.exam_name.length()>0){
				Average=All/(sum-1);
				All=0,i=rank=sum=1;
				if(appered){
					appered=0;
					if(z.exam_name==tmp) cout<<setprecision(2)<<fixed<<"平均分："<<Average<<endl;
					cout<<endl;
				}
			}
			if(it->exam_name==tmp){	
				if(ROSnum){
					if(i<10) cout<<i<<"    |";
					if(i>=10&&i<100) cout<<i<<"   |";
					if(i>=100&&i<1000) cout<<i<<"  |";
					if(i>=1000&&i<10000) cout<<i<<" |";
					if(i>=10000&&i<100000) cout<<i<<"|";
				}
				if(ROSid){
					cout<<it->id;
					for(j=midl;j>=it->id.length();j--) cout<<" ";
					cout<<"|";
				}
				if(ROSname){
					cout<<it->name;
					for(j=mnl;j>=it->name.length();j--) cout<<" ";
					cout<<"|";
				}
				cout<<it->exam_name;
				for(j=menl;j>=it->exam_name.length();j--) cout<<" ";
				cout<<"|"<<setprecision(0)<<fixed<<it->S;
				cout<<endl;
				f=true;
				appered=1;
			}
			else appered=0;
			All+=it->S; 
			STmp=it->S; 
			z.exam_name=it->exam_name;
		}
		if(f==true){
			Average=All/(sum-1);
			if(appered) cout<<"平均分："<<setprecision(2)<<fixed<<Average<<endl<<endl;
			clock_t end   = clock();
			cout << "使用时间：" << setprecision(2)<<fixed<<(double)(end - start) / CLOCKS_PER_SEC << " 秒" << endl;
			system("pause");
			return 1;
		}
		system("cls");
		MessageBox(NULL,"未找到该考试中任何学生的信息，请检查信息是否已经录入系统！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
		return 1;
	}
	//output information between given lowest score and given highest score
	int find_score(){
		system("cls");
		if(stu.size()<1){
			MessageBox(NULL,"暂无记录！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND);
			return 1;
		}
		double Average,All;
		bool f=false; 
		z.exam_name=' ';
		int l,h;//l:lowest,h:highest
		cout<<"请输入最低分数：";
		cin>>l;
		cout<<"请输入最高分数：";
		cin>>h; 
		clock_t start = clock();
		if(ROSnum) cout<<"排名 |";
		if(ROSid){
			cout<<"学号 ";
			for(i=midl;i>4;i--) cout<<" ";
			cout<<"|";
		}
		if(ROSname){
			cout<<"姓名 ";
			for(i=mnl;i>4;i--) cout<<" ";
			cout<<"|";
		}
		cout<<"考试名称 ";
		for(i=menl;i>8;i--) cout<<" ";
		cout<<"|成绩"<<endl;
		double STmp;
		int sum=1,rank=1;
		bool appered=0;
		for(it=stu.begin(),i=0;it!=stu.end();it++,sum++,rank++){
			if(STmp!=it->S) i=rank;
			if(z.exam_name!=it->exam_name&&z.exam_name.length()>0){
				Average=All/(sum-1);
				All=0,i=rank=sum=1;
				if(appered){
					appered=0;
					cout<<"平均分："<<setprecision(2)<<fixed<<Average<<endl;
					cout<<endl;
				}
			}
			if(it->S>=l&&it->S<=h){	
				if(ROSnum){
					if(i<10) cout<<i<<"    |";
					if(i>=10&&i<100) cout<<i<<"   |";
					if(i>=100&&i<1000) cout<<i<<"  |";
					if(i>=1000&&i<10000) cout<<i<<" |";
					if(i>=10000&&i<100000) cout<<i<<"|";
				}
				if(ROSid){
					cout<<it->id;
					for(j=midl;j>=it->id.length();j--) cout<<" ";
					cout<<"|";
				}
				if(ROSname){
					cout<<it->name;
					for(j=mnl;j>=it->name.length();j--) cout<<" ";
					cout<<"|";
				}
				cout<<it->exam_name;
				for(j=menl;j>=it->exam_name.length();j--) cout<<" ";
				cout<<"|"<<setprecision(0)<<fixed<<it->S;
				cout<<endl;
				f=true;
				appered=1;
			}
			else appered=0;
			STmp=it->S; 
			All+=it->S;
			z.exam_name=it->exam_name;
		}
		Average=All/(sum-1);
		if(appered) cout<<"平均分："<<setprecision(2)<<fixed<<Average<<endl<<endl;
		if(f==true){
			clock_t end   = clock();
			cout << "使用时间：" << setprecision(2)<<fixed<<(double)(end - start) / CLOCKS_PER_SEC << " 秒" << endl;
			system("pause");
			return 1;
		}
		system("cls");
		MessageBox(NULL,"未找到该分数段中任何学生的信息，请检查信息是否已经录入系统！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
		return 1;
	}
	//output information in given classname 
	int find_clssnm(){
		ifstream fin;
		system("cls");
		if(stu.size()<1){
			MessageBox(NULL,"暂无记录！","学生成绩管理系统",MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND);
			return 1;
		}
		string clssnm,pwd,s;
		char iclssnm[1000],finclssnm[1000];
		int n;
		cout<<"班级模式查询"<<endl;
		cout<<"班级名称：";
		cin>>s;
		strncpy(iclssnm,s.c_str(),s.length()+1);
		s="ClassEdition\\"+s+".dat";
		strncpy(finclssnm,s.c_str(),s.length()+1);			
		fin.open(finclssnm);
		stuinfo.clear();
		if(!fin){
			cout<<"班级不存在！"<<endl;
			system("pause");
			return 1;
		}
		fin>>clssnm>>pwd>>n;
		for(i=1;i<=n;i++){
			fin>>zz.name>>zz.id;
			for(j=0;j<zz.id.length();j++)
				zz.id[j]-=10;
			z.id=zz.id;
			for(j=0;j<zz.name.length();j++)
				zz.name[j]-=10;
			stuinfo.insert(zz);
		}
		double Average,All;
		bool f=false; 
		z.exam_name=' ';
		cin.clear(); cin.sync();
		clock_t start = clock();
		if(ROSnum) cout<<"排名 |";
		if(ROSid){
			cout<<"学号 ";
			for(i=midl;i>4;i--) cout<<" ";
			cout<<"|";
		}
		if(ROSname){
			cout<<"姓名 ";
			for(i=mnl;i>4;i--) cout<<" ";
			cout<<"|";
		}
		cout<<"考试名称 ";
		for(i=menl;i>8;i--) cout<<" ";
		cout<<"|成绩"<<endl;
		double STmp;
		int sum=1,rank=1;
		bool appeared=0;
		for(it=stu.begin(),i=0;it!=stu.end();it++,sum++){
			if(STmp!=it->S) i++;
			if(z.exam_name!=it->exam_name&&z.exam_name.length()>0){
				Average=All/(sum-1);
				All=0,i=rank=sum=1;
				if(appeared){
					appeared=0;
					cout<<"平均分："<<setprecision(2)<<fixed<<Average<<endl;
					cout<<endl;
				}
			}
			for(siit=stuinfo.begin();siit!=stuinfo.end();siit++){
				if(siit->name==it->name&&siit->id==it->id){	
					if(ROSnum){
						if(i<10) cout<<i<<"    |";
						if(i>=10&&i<100) cout<<i<<"   |";
						if(i>=100&&i<1000) cout<<i<<"  |";
						if(i>=1000&&i<10000) cout<<i<<" |";
						if(i>=10000&&i<100000) cout<<i<<"|";
					}
					if(ROSid){
						cout<<it->id;
						for(j=midl;j>=it->id.length();j--) cout<<" ";
						cout<<"|";
					}
					if(ROSname){
						cout<<it->name;
						for(j=mnl;j>=it->name.length();j--) cout<<" ";
						cout<<"|";
					}
					cout<<it->exam_name;
					for(j=menl;j>=it->exam_name.length();j--) cout<<" ";
					cout<<"|"<<setprecision(0)<<fixed<<it->S;
					cout<<endl;
					appeared=1;
					break;
				}
				else appeared=0;
			}
			STmp=it->S; 
			All+=it->S; 
			z.exam_name=it->exam_name;
		}
		Average=All/(sum-1);
		if(appeared) cout<<"平均分："<<setprecision(2)<<fixed<<Average<<endl<<endl;
		clock_t end   = clock();
		cout << "使用时间：" << setprecision(2)<<fixed<<(double)(end - start) / CLOCKS_PER_SEC << " 秒" << endl;
		system("pause");
		return 1;
	}
	//record output end
}

int main(int argc,char *argv[]){	
	//===============init===============
	system("mkdir ClassEdition");
	system("cls");
	system("color f0");
	ti=t->tm_min; 
	bool usr,adminAccess,DriverExist;
	bool SetFocus=0;
	adminAccess=adminCheck(); 
	if(!adminAccess){
		MessageBox(NULL,"系统未获得管理员权限，为保障学生信息不会丢失，请使用管理员权限启动系统！\r\n注意：按确定键后系统会关闭！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
		exit(0);
	}
	DriverExist=DriverCheck();
	if(!DriverExist){
		MessageBox(NULL,"系统未未找到D盘，由于系统会在 表格文件保存 ， 备份信息 和  下载安装包 时会用到D盘，请创建D盘（方法请自行查找）！\r\n注意：按确定键后系统会关闭！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
		exit(0);
	}
	cin.clear();
	cin.sync(); 
	ACTIVATION();
	load(); hint(); start(4); usr=user::login(1); load(); file::input(1);
	ifstream fin;
	fin.open("ROS.dat");
	fin>>ROSnum>>ROSid>>ROSname;
	fin.close();
	if(!ROSid&&!ROSname) ROSid=ROSname=1;
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
	string clssnm,pwd;
	int n;
	int size,sizetmp;
	if(usr){
		ifstream fin;
		fin.open("ScoreControl.dat");
		if(!fin){
			cout<<"请输入最高分数限制（默认为100分，最高1000000分）："<<endl;
			cin>>ScoreControl;
			if(ScoreControl<1||ScoreControl>1000000)
				MessageBox(NULL,"无效分数！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
			else{
				ofstream fout;
				fout.open("ScoreControl.dat");
				if(!fout)
					MessageBox(NULL,"无法保存设置，请检查系统是否已经获得管理员权限！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
				else{
					fout<<ScoreControl*80123750<<endl;
					fout.close();
					system("cls");
					cout<<"您已设置 最高分数限制："<<ScoreControl<<"分，如果输入数据超过该限制，将会报错！"<<endl;
					getch();
				}
			}
		}
		else{ 
			fin>>ScoreControlFI; 
			ScoreControl=ScoreControlFI/80123750;
		}
	}
	//===============init===============
	while(o[0]!='E'){
		cin.clear();
		cin.sync(); 
		time_t tt = time(NULL);	
		tm* t=localtime(&tt);
		if(t->tm_min!=ti&&stu.size()>0){
			file::output(1);
			ti=t->tm_min;
		}
		mnl=menl=midl=0;
		for(it=stu.begin();it!=stu.end();it++){
			mnl=max(mnl,it->name.length());
			if(mnl<5) mnl=5;
			menl=max(menl,it->exam_name.length());
			if(menl<5) menl=9;
			midl=max(midl,it->id.length());
			if(midl<5) midl=5;
		}
  	    HWND hWnd=GetForegroundWindow();
		system("cls");
		if(usr) system("title 学生成绩管理系统");
		if(!usr) system("title 学生成绩查询系统"); 
		if(usr) cout<<"学生成绩管理系统 ";
		if(!usr) cout<<"学生成绩查询系统"; 
		cout<<" 日期："<<t->tm_year+1900<<"/"<<t->tm_mon+1<<"/"<<t->tm_mday;
		cout<<" 时间："<<t->tm_hour<<":";
		if(t->tm_min<10) cout<<"0"<<t->tm_min<<endl;
		else cout<<t->tm_min<<endl;
		if(usr) cout<<"1.学生信息操作"<<endl;
		if(usr) cout<<"2.文件操作"<<endl; 
		if(usr) cout<<"3.查询"<<endl;
		if(!usr) cout<<"1.查询"<<endl; 
		if(usr) cout<<"4.设置"<<endl; 
		if(usr) cout<<"h.帮助"<<endl; 
		cout<<"E.退出系统"<<endl; 
		cout<<"L.锁定系统"<<endl; 
		if(!SetFocus) cout<<"S.置顶窗口"<<endl; 
		cout<<"H.隐藏窗口"<<endl; 
		if(usr) cout<<"R.重置数据"<<endl;
		cout<<"@.关于"<<endl; 
		cout<<"请输入命令代码："; 
		o[0]=getch();
		if(o[0]=='S'){SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE); SetFocus=1;}
		if(o[0]=='E') if(MessageBox(NULL,"您确定要退出吗？","学生成绩管理系统",MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) break;
		if(o[0]=='h') system("HELP_zh-cn.chm");
		if(o[0]=='L'){load();start(4);usr=user::login(1);}
		if(o[0]=='H'){
			ShowWindow(hWnd,0);
			MessageBox(NULL,"您可以按空格显示窗口！","学生成绩管理系统",MB_ICONINFORMATION|MB_SYSTEMMODAL|MB_SETFOREGROUND);
		    while(1){
				Sleep(8); 
		        if(KEY_DOWN(VK_SPACE)){
					ShowWindow(hWnd,1);
					break;
				} 
		    }
		}
		if(o[0]=='R'&&usr){
			o[0]=0; 
			system("cls");
			if(MessageBox(NULL,"您确定要重置数据吗？\r\n此操作不可逆！","学生成绩管理系统",MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES){
				while(1){
					bool admin;
					system("cls");
					start(4);
					if(MessageBox(NULL,"您需要验证管理员身份！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) admin=user::login(1);
					else break;
					if(!admin){
						MessageBox(NULL,"不可使用学生模式登陆！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
						break;
					}
					if(MessageBox(NULL,"验证通过！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) stu.clear();
					else break;
					MessageBox(NULL,"完成！","学生成绩管理系统",MB_ICONINFORMATION|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
					break;
				}
			}
			o[0]=0; 
		}
		if(o[0]=='@'){
			o[0]=0; 
			system("cls");	
			cout<<"Copyright (C) 2017-2018 XiyuWang All rights reserved."<<endl;
			cout<<"Version:18.1.3"<<endl; 
			system("pause");
			o[0]=0; 
		}
		if(o[0]=='1'&&usr){
			o[0]=0; 
			system("cls");
			cout<<"学生成绩管理系统-学生信息操作";
			cout<<" 日期："<<t->tm_year+1900<<"/"<<t->tm_mon+1<<"/"<<t->tm_mday;
			cout<<" 时间："<<t->tm_hour<<":";
			if(t->tm_min<10) cout<<"0"<<t->tm_min<<endl;
			else cout<<t->tm_min<<endl;
			cout<<"1.录入学生信息"<<endl;
			cout<<"2.更改学生信息"<<endl; 
			cout<<"3.删除学生信息"<<endl; 
			cout<<"4.删除特定考试内所有学生的信息"<<endl; 
			cout<<"5.班级模式录入信息"<<endl; 
			cout<<"按其他键 返回"<<endl;
			cout<<"请输入命令代码：";
			o[0]=getch(); 
			if(o[0]=='1'&&stu.size()<100000) record_input::rinput();
			if(o[0]=='1'&&stu.size()>=100000){
				system("cls");
				cout<<"数据量过大，不可继续录入信息！"<<endl;
				system("pause");
			}
			if(o[0]=='2'){
				if(stu.size()<=0) MessageBox(NULL,"暂无数据，无法进行更改操作！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
				else record_input::rchange();
			} 
			if(o[0]=='3'){
				if(stu.size()<=0) MessageBox(NULL,"暂无数据，无法进行删除操作！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
				else record_input::rdelete();
			}
			if(o[0]=='4'){
				if(stu.size()<=0) MessageBox(NULL,"暂无数据，无法进行删除操作！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
				while(stu.size()>0){
					bool admin;
					system("cls");
					start(4);
					if(MessageBox(NULL,"您需要验证管理员身份！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) admin=user::login(1);
					else break;
					if(!admin){
						MessageBox(NULL,"不可使用学生模式登陆！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
						break;
					}
					if(MessageBox(NULL,"验证通过！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) record_input::rexam_nameDelete(); 
					else break;
					MessageBox(NULL,"完成！","学生成绩管理系统",MB_ICONINFORMATION|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
					break;
				}
			}
			if(o[0]=='5'){
				system("cls");
				ClassEdition::main();
			}
			o[0]=0; 
		} 
		if(o[0]=='2'&&usr){
			o[0]=0; 
			system("cls");
			cout<<"学生成绩管理系统-文件操作";
			cout<<" 日期："<<t->tm_year+1900<<"/"<<t->tm_mon+1<<"/"<<t->tm_mday;
			cout<<" 时间："<<t->tm_hour<<":";
			if(t->tm_min<10) cout<<"0"<<t->tm_min<<endl;
			else cout<<t->tm_min<<endl;
			cout<<"1.保存信息到文件（自动）"<<endl;
			cout<<"2.从文件读取信息 "<<endl;
			cout<<"3.导出所有数据文件"<<endl;
			cout<<"4.运行转码程序"<<endl; 
			cout<<"按其他键 返回"<<endl;
			cout<<"请输入命令代码：";
			o[0]=getch(); 
			if(o[0]=='1') file::output(0);
			if(o[0]=='2') file::input(0);
			if(o[0]=='3') file::backup(); 
			if(o[0]=='4'){
				o[0]=0;
				system("cls");
				cout<<"学生成绩管理系统-文件操作-运行转码程序";
				cout<<" 日期："<<t->tm_year+1900<<"/"<<t->tm_mon+1<<"/"<<t->tm_mday;
				cout<<" 时间："<<t->tm_hour<<":";
				if(t->tm_min<10) cout<<"0"<<t->tm_min<<endl;
				else cout<<t->tm_min<<endl;
				cout<<"1.V16.9.18转至V17.2.6（V17.2.6与V18.1.3使用相同文件加密方式）"<<endl;
				cout<<"按其他键 返回"<<endl;
				cout<<"请输入命令代码：";
				o[0]=getch();
				if(o[0]=='1') system("FileCodeConvert\\FileCodeConvert-16.9.18_To_18.1.3.dll");
			}
			o[0]=0;
		}
		if(o[0]=='3'&&usr||o[0]=='1'&&!usr){
			o[0]=0; 
			system("cls");
			if(usr) cout<<"学生成绩管理系统-查询";
			if(!usr) cout<<"学生成绩查询系统-查询"; 
			cout<<" 日期："<<t->tm_year+1900<<"/"<<t->tm_mon+1<<"/"<<t->tm_mday;
			cout<<" 时间："<<t->tm_hour<<":";
			if(t->tm_min<10) cout<<"0"<<t->tm_min<<endl;
			else cout<<t->tm_min<<endl;
			cout<<"1.查看所有学生的排名"<<endl;
			cout<<"2.查看单个学生详细信息"<<endl; 
			cout<<"3.查看特定考试学生的排名"<<endl; 
			cout<<"4.查看特定分数段内学生的排名"<<endl; 
			cout<<"5.查看特定班级内学生的排名"<<endl; 
			cout<<"6.查询设置"<<endl; 
			cout<<"按其他键 返回"<<endl; 
			cout<<"请输入命令代码：";
			o[0]=getch(); 
			if(o[0]=='1') record_output::output(); 
			if(o[0]=='2') record_output::find();
			if(o[0]=='3') record_output::find_examname(); 
			if(o[0]=='4') record_output::find_score();
			if(o[0]=='5') record_output::find_clssnm();
			if(o[0]=='6') record_output::Settings();
			o[0]=0;
		}
		if(o[0]=='4'&&usr){
			o[0]=0;
			system("cls");
			cout<<"学生成绩管理系统-设置";
			cout<<" 日期："<<t->tm_year+1900<<"/"<<t->tm_mon+1<<"/"<<t->tm_mday;
			cout<<" 时间："<<t->tm_hour<<":";
			if(t->tm_min<10) cout<<"0"<<t->tm_min<<endl;
			else cout<<t->tm_min<<endl;
			cout<<"1.更改用户信息"<<endl;
			cout<<"2.更改班级信息"<<endl; 
			cout<<"3.创建班级"<<endl; 
			cout<<"4.重建班级（暂不支持）"<<endl; 
			cout<<"5.设置分数限制"<<endl; 
			cout<<"6.联系作者"<<endl; 
			cout<<"7.查看数据量"<<endl; 
			cout<<"8.更新"<<endl; 
			cout<<"按其他键 返回"<<endl; 
			cout<<"请输入命令代码：";
			o[0]=getch();
			if(o[0]=='1'){
				while(1){
					bool admin;
					system("cls");
					start(4);
					if(MessageBox(NULL,"您需要验证管理员身份！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) admin=user::login(1);
					else break;
					if(!admin){
						MessageBox(NULL,"不可使用学生模式登陆！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
						break;
					}
					if(MessageBox(NULL,"验证通过！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) user::ReReg();
					else break;
					MessageBox(NULL,"完成！","学生成绩管理系统",MB_ICONINFORMATION|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
					break;
				}
			}
			if(o[0]=='2'){
				while(1){ 
					bool admin;
					system("cls");
					start(4);
					if(MessageBox(NULL,"您需要验证管理员身份！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) admin=user::login(1);
					else break;
					if(!admin){
						MessageBox(NULL,"不可使用学生模式登陆！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
						break;
					}
					if(MessageBox(NULL,"验证通过！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) ClassEdition::reg();
					break; 
				}
			}
			if(o[0]=='3'){
				while(1){ 
					bool admin;
					system("cls");
					start(4);
					if(MessageBox(NULL,"您需要验证管理员身份！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) admin=user::login(1);
					else break;
					if(!admin){
						MessageBox(NULL,"不可使用学生模式登陆！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
						break;
					}
					if(MessageBox(NULL,"验证通过！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) ClassEdition::make("make");
					break;
				}
			}
			if(o[0]=='4'){
				while(1){ 
					bool admin;
					system("cls");
					start(4);
					if(MessageBox(NULL,"您需要验证管理员身份！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) admin=user::login(1);
					else break;
					if(!admin){
						MessageBox(NULL,"不可使用学生模式登陆！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
						break;
					}
					if(MessageBox(NULL,"验证通过！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) ClassEdition::make("remake");
					break;
				}
			}
			if(o[0]=='5'){
				system("cls");
				while(1){ 
					bool admin;
					system("cls");
					start(4);
					if(MessageBox(NULL,"您需要验证管理员身份！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES) admin=user::login(1);
					else break;
					if(!admin){
						MessageBox(NULL,"不可使用学生模式登陆！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
						break;
					}
					if(MessageBox(NULL,"验证通过！\r\n按是继续，按否停止更改！","学生成绩管理系统",MB_YESNO|MB_ICONWARNING|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDNO) break;
					system("cls");
					cout<<"请输入最高分数限制（默认为100分，最高1000000分）："<<endl;
					cin>>ScoreControl;
					if(ScoreControl<1||ScoreControl>1000000)
						MessageBox(NULL,"无效分数！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
					else{
						ofstream fout;
						fout.open("ScoreControl.dat");
						if(!fout)
							MessageBox(NULL,"无法保存设置，请检查系统是否已经获得管理员权限！","学生成绩管理系统",MB_ICONERROR|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
						else{
							fout<<ScoreControl*80123750<<endl;
							fout.close();
							system("cls");
							cout<<"您已设置 最高分数限制："<<ScoreControl<<"分，如果输入数据超过该限制，将会报错！"<<endl;
							getch();
							break;
						}
					}
					break;
				}
			}
			if(o[0]=='6'){
				system("cls");
				MessageBox(NULL,"请发送邮件至：\r\nXiyuWang_Code@hotmail.com","学生成绩管理系统",MB_ICONINFORMATION|MB_SYSTEMMODAL|MB_SETFOREGROUND); 
			}
			if(o[0]=='7'){
				ifstream fin;
				fin.open("ClassEdition.dat");
				if(fin){
					fin>>clssnm;
					for(i=0;i<clssnm.length();i++)
						clssnm[i]-=18;
				}
				system("cls");
				cout<<"当前数据量："<<stu.size()<<endl; 
				if(fin&&stuinfo.size()!=0) cout<<"班级 "<<clssnm<<" 中的学生量："<<stuinfo.size()<<endl; 
				system("pause");
			}
			if(o[0]=='8'){
				system("cls");
				system("del D:\\SAMS_zh-cn_installer.rar");
				system("cls");
				cout<<"正在下载最新的安装程序，请勿关闭程序......"<<endl;
				system("wget https://xiyuwang2006.github.io/MyWork/StudentAchievementManagementSystem/SAMS_zh-cn_installer.rar -q");
				system("copy SAMS_zh-cn_installer.rar D:\\SAMS_zh-cn_installer.rar");
				system("del SAMS_zh-cn_installer.rar /s/f/q"); 
				system("cls"); 
				ifstream fin;
				fin.open("D:\\SAMS_zh-cn_installer.rar") ;
				if(!fin){
					cout<<"无法下载安装包！请检查网络和D盘是否存在！如果网络正常，则可能是服务器维护，10~30分钟内将修复！"<<endl;
					getch(); 
				}
				else{
					cout<<"最新资源包已经存放在D盘，文件名“SAMS_zh-cn_installer.rar”！"<<endl;
					cout<<"请先卸载旧软件，然后解压压缩包，运行安装程序，重装本系统！"<<endl;
					cout<<"注意：正常重装系统不会导致学生信息的丢失（当然，如果您不放心，也可以先备份信息）！"<<endl; 
					getch();
				}
			}
		}
		o[0]=0; 
	}
	if(stu.size()>0) file::output(1);
	system("cls");
	system("title 学生成绩管理系统-正在退出"); 
	load();
	system("title 学生成绩管理系统-正在退出"); 
	Sleep(1000);
	return 0; 
}

BOOL CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
        /* handle the CTRL-C signal */
    case CTRL_C_EVENT:
        Beep(750, 300);
		return TRUE; 
 
        /* handle the CTRL-BREAK signal */
    case CTRL_BREAK_EVENT:
        Beep(750, 300);
		return TRUE; 
 
        /* handle the CTRL-CLOSE signal */
    case CTRL_CLOSE_EVENT:
		//点击了关闭窗口键
        Beep(750, 300);
		if(stu.size()>0) file::output(1);
		if(MessageBox(NULL,"您确定要重启系统或退出系统吗？（按是退出，按否重启）","学生成绩管理系统",MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES){
			system("cls");
			system("title 学生成绩管理系统-正在退出"); 
			load();
	    	cout<<endl<<"正在退出......"<<endl; 
			system("title 学生成绩管理系统-正在退出"); 
			Sleep(1000);
			exit(0); 
		}
		else system("SAMS.exe");
 
        /* handle the CTRL-LOGOFF signal */
    case CTRL_LOGOFF_EVENT:
        Beep(750, 300);
		if(stu.size()>0) file::output(1);
		if(MessageBox(NULL,"您确定要重启系统或退出系统吗？（按是退出，按否重启）","学生成绩管理系统",MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES){
			system("cls");
			system("title 学生成绩管理系统-正在退出"); 
			load();
	    	cout<<endl<<"正在退出......"<<endl; 
			system("title 学生成绩管理系统-正在退出"); 
			Sleep(1000);
			exit(0); 
		}
		else system("SAMS.exe");
 
        /* handle the CTRL-SHUTDOWN signal */
    case CTRL_SHUTDOWN_EVENT:
        Beep(750, 300);
		if(stu.size()>0) file::output(1);
		if(MessageBox(NULL,"您确定要重启系统或退出系统吗？（按是退出，按否重启）","学生成绩管理系统",MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL|MB_SETFOREGROUND)==IDYES){
			system("cls");
			system("title 学生成绩管理系统-正在退出"); 
			load();
	    	cout<<endl<<"正在退出......"<<endl; 
			system("title 学生成绩管理系统-正在退出"); 
			Sleep(1000);
			exit(0); 
		}
		else system("SAMS.exe");
 
    default:
        return FALSE;
    }
}
