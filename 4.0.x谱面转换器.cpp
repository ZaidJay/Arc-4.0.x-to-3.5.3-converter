#include<iostream>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<string>
#include<string.h>
using namespace std;

char tmp[1000];
char SceneType[1000];

void fun(const string &str)
{
	for(int i=0;i<str.length();i++)
	{
		if(str[i]==',') tmp[i]=' ';
		else tmp[i]=str[i];
	}
	tmp[str.length()]='\0';
}

void AFF_Read()
{
	freopen("aff.aff","r",stdin);
	freopen("aff[3.5.3].aff","w",stdout);
	
	string str;
	int Start,End,wait=0;
	
	while(cin>>str)
	{
		string object,code;
		int len;
		for(len=0;len<str.length();len++)
		{
			if(str[len]=='(') break;
		}
		
		object.assign(str,0,len);
		if(object=="scenecontrol")
		{
			code.assign(str,len+1,str.length()-len-3);
			int Time,state;
			double Duration;
			
			fun(code);
			sscanf(tmp,"%d %s %lf %d",&Time,SceneType,&Duration,&state);
			if(strcmp(SceneType,"enwidencamera")==0) 
			{
				if(state==1) cout<<"camera("<<Time<<",0.00,450.00,450.00,0.00,0.00,0.00,s,"<<(int)Duration<<");"<<endl;
				else if(state==0) cout<<"camera("<<Time<<",0.00,-450.00,-450.00,0.00,0.00,0.00,s,"<<(int)Duration<<");"<<endl;
				continue;
			}
			else if(strcmp(SceneType,"enwidenlanes")==0)  
			{
				if(state==1) 
				{
					Start=Time;
					wait=1;
					continue;
				}
				else if(state==0)
				{
					End=Time+(int)Duration;
					for(double x=-1.0;x<=-0.6;x+=0.03)
					{
						cout<<"arc("<<Start<<","<<End;
						cout<<","<<fixed<<setprecision(2)<<x;
						cout<<","<<fixed<<setprecision(2)<<x;
						cout<<",s,-0.22,-0.22,0,none,true);"<<endl;
						cout<<"arc("<<Start<<","<<End;
						cout<<","<<fixed<<setprecision(2)<<(1.00-x);
						cout<<","<<fixed<<setprecision(2)<<(1.00-x);
						cout<<",s,-0.22,-0.22,0,none,true);"<<endl;
					}
					wait=0;
					continue;
				}
			}
		}
		else if(object.length()==0) 
		{ 
			code.assign(str,1,str.length()-3);
			int Time,Lane;
			
			fun(code);
			sscanf(tmp,"%d %d",&Time,&Lane);
			if(Lane==0)
			{	
				cout<<"arc("<<Time<<","<<(Time+1);
				cout<<",-0.75,-0.75,s,0.00,0.00,0,none,true)[arctap("<<Time<<")];"<<endl;
				continue;
			}
			else if(Lane==5)
			{
				cout<<"arc("<<Time<<","<<(Time+1);
				cout<<",1.75,1.75,s,0.00,0.00,0,none,true)[arctap("<<Time<<")];"<<endl;
				continue;
			}			
		}
		else if(object=="hold")
		{
			code.assign(str,5,str.length()-7);
			int StartTime,EndTime,Lane;
			
			fun(code);
			sscanf(tmp,"%d %d %d",&StartTime,&EndTime,&Lane);
			if(Lane==0)
			{
				cout<<"arc("<<StartTime<<","<<(StartTime+1);
				cout<<",-0.75,-0.75,s,0.00,0.00,0,none,true)[arctap("<<StartTime<<")];"<<endl;
				cout<<"arc("<<StartTime<<","<<EndTime;
				cout<<",-0.75,-0.75,s,0.00,0.00,2,none,false);"<<endl;
				continue;
			}
			else if(Lane==5)
			{
				cout<<"arc("<<StartTime<<","<<(StartTime+1);
				cout<<",1.75,1.75,s,0.00,0.00,0,none,true)[arctap("<<StartTime<<")];"<<endl;
				cout<<"arc("<<StartTime<<","<<EndTime;
				cout<<",1.75,1.75,s,0.00,0.00,2,none,false);"<<endl;
				continue;
			}
		}
		cout<<str<<endl;
	}
	if(wait==1)
	{
		End=Start+40000;
		for(double x=-1.0;x<=-0.6;x+=0.03)
		{
			cout<<"arc("<<Start<<","<<End;
			cout<<","<<fixed<<setprecision(2)<<x;
			cout<<","<<fixed<<setprecision(2)<<x;
			cout<<",s,-0.22,-0.22,0,none,true);"<<endl;
			cout<<"arc("<<Start<<","<<End;
			cout<<","<<fixed<<setprecision(2)<<(1.00-x);
			cout<<","<<fixed<<setprecision(2)<<(1.00-x);
			cout<<",s,-0.22,-0.22,0,none,true);"<<endl;
		}
		wait=0;
	}		
}

void fuck_616()
{
	cout<<"食用指南:"<<endl;
	cout<<"此程序用于将4.0.x版本有enwidenlane和enwidencamera的谱面转换为3.5.3可游玩谱面"<<endl;
	cout<<"将需要转换的谱面修改为aff.aff,将本程序与此谱面放在同一个文件夹下，再次运行后将会获得一个aff[3.5.3].aff"<<endl<<endl; 
	cout<<"在此鸣谢塌方F4llensqvare的思路与smarthehe技术支持,b站关注他们"<<endl;
	cout<<"616!nmsl!616!nmsl!616!nmsl!616!nmsl!616!nmsl!616!nmsl!616!nmsl!616!nmsl!616!"<<endl;
} 

int main()
{
	fuck_616();
	AFF_Read();
	return 0;
}

