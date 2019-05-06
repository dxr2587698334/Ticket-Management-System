#include<iostream>          //数据流输入／输出
#include<fstream>			//文件输入／输出
#include<string>				//字符串操作
#include<iomanip>			//参数化输入／输出
#include<time.h>				//时间库函数
using namespace std;		//命名空间

class Bus_infor
{
private:	
    static int Bus_No;		//静态数据成员,统计当前所有的Bus_infor对象的数目
	char start[20];			//起点站
	char end[20];			//终点站
	int Bus_number;			//班次号
    int all_tickted;			//额定载量
	int tickted;				//已定票人数
	int  Hour_start,Minute_start;			//发车时间
	float GoHour;			//行车时间
public:	
	Bus_infor();
	~Bus_infor();
	Bus_infor *next;
	void input();				//录入函数
    void input(ifstream & cin);			//读取函数
    void output();			//输出函数
	void output(ofstream & cout);		//写入函数
	void ding_tickt(int n);				//定票函数
	void tui_tickt(int n);			//退票函数
	void GetTime_start();				//获取发车时间函数
	bool GetTime();						//判断当前班次状况函数
	int Get_all_tickted()
	{ return all_tickted;  }            //内联函数,返回额定载量
    int Get_tickted()
	{	return tickted; }				//返回已定票人数
	int Get_bus_number()
	{ return Bus_number;  }			//返回班次号
	string Get_end()const;				//返回终点站的字符串
};


int Bus_infor::Bus_No=1;

Bus_infor::Bus_infor()      //车票数目构造函数
{
    Bus_No++;
    tickted=0;
}

Bus_infor::~Bus_infor()      //车票数目析构函数
{ 
    Bus_No--;
}

void Bus_infor::input()        //录入车票信息
{
	cout<<"按提示输入:"<<endl;
		cout<<"输入班次: ";
		while(1)
		{
			cin>>Bus_number;
			if (cin.fail())						//判断输入的数据类型是否有错
			{
				cout << "\n班次输入错误,请重新输入:";
				cin.clear();
				cin.get();			
			}
			else 
				break;
		}
		cout<<"请输入车的额定座位数: ";		
		while(1)
		{
			cin>>all_tickted;
			if (cin.fail())						//判断输入的数据类型是否有错
			{
				cout << "座位数输入错误,请重新输入:";
				cin.clear();
				cin.get();			
			}
			else 
				break;
		}
		GetTime_start();
		cout<<"请输入行车时间：";		
		while(1)
		{
			cin>>GoHour;
			if (cin.fail())						//判断输入的数据类型是否有错
			{
				cout << "行车时间输入错误,请重新输入:";
				cin.clear();
				cin.get();			
			}
			else 
				break;
		}
		cout<<"请输入起始站与终点站：";	
        cin>>start;cin>>end;		
}

void Bus_infor::input(ifstream & cin)            //以文件输入信息               
{
	cin>>Bus_number>>Hour_start>>Minute_start>>start>>end>>GoHour>>all_tickted>>tickted;
	cin.get();                                    
}

void  Bus_infor::output()                  
{
	cout<<" "<<Bus_number<<"\t";
	if(Minute_start==0)						//判断发车时的分钟时刻,若为分则在后面多显示个,以符合时间格式
	{
		cout<<Hour_start<<":"<< Minute_start<<"0\t";
	}
	else
	{
		cout<<Hour_start<<":"<< Minute_start<<"\t";
	}
	cout<<start<<"\t"<<end<< "\t"<<GoHour<<"\t   "<<all_tickted<<"\t     "<<tickted; 		
    if(!GetTime())
		cout<<"   此班已出发"<<endl;
	else
		cout<<"   此班未出发"<<endl;
}

void Bus_infor::output(ofstream & cout)                //以文件显示信息             
{
	cout<<"\t"<<Bus_number				
		<<"\t"<<Hour_start
		<<"\t"<<Minute_start
		<<"\t"<<start
		<<"\t"<<end
		<<"\t"<<GoHour
		<<"\t"<<all_tickted
		<<"\t"<<tickted		
		<<endl;
}

void Bus_infor::GetTime_start()       //获取发车时间
{	
	cout<<"请输入始发时间(时分)：";
	while(1)
	{		
		cin>>Hour_start>>Minute_start;
		if (cin.fail())						//判断输入的数据类型是否有错
			{
				cout << "\n时间输入错误,请重新输入:";
				cin.clear();
				cin.get();			
			}			
		else if(Hour_start<0||Hour_start>24||Minute_start<0||Minute_start>60)				
			cout<<"时间格式出错,请重新输入:";			//判断时间格式是否出错,小时不能小于大于,分钟不能小于大于
		else
			break;
	}	
}

bool Bus_infor::GetTime()       //用bool类型有两种输出格式选择输出
{
	struct tm *local;  
    time_t t;
    t=time(NULL);
    local=localtime(&t);			//获取当前系统时间
	if(local->tm_hour<Hour_start||(local->tm_hour==Hour_start && local->tm_min<=Minute_start))
		return 1;                      //比较当前时间与发车时间,获得班次的当前状况,返回表示班次未出发
	else
		return 0;						//返回表示班次已出发
}

void Bus_infor::ding_tickt(int n)           //提供的车票总数函数
{
	tickted=tickted+n;
}

void Bus_infor::tui_tickt(int n)        //提供余下车票数目
{
	tickted=tickted-n;
}

string Bus_infor::Get_end()const          //得到终点站字符串函数
{
	string s=end;
	return s;
}


