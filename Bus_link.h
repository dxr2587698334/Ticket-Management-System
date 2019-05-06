#include<iostream>          //数据流输入／输出
#include<fstream>			//文件输入／输出
#include<string>				//字符串操作
#include<iomanip>			//参数化输入／输出
#include<time.h>				//时间库函数
using namespace std;		//命名空间
class Bus_link:public Bus_infor
{
public:
	Bus_link(){head=new Bus_infor;head->next=NULL;}			//带参数的构造函数
	~Bus_link()
	{delete head;}			//析构函数
	void input();			//录入车票信息	
	void xiugai();			//修改车票信息
	void shanchu();				//删除车票信息
	int find(Bus_infor **p,int num,char *pn);		//查找函数   
    void found();			//查询车票信息
	void xianshi();			//显示车票信息
    void dingpiao();			//定购车票信息
    void tuipiao();		//退还车票信息
    void baocun();			//保存车票信息
    void chushihua();			//初始化车票信息
    void clear();			//清除函数
    char mainmenu();				//主菜单函数
private:                                            
    Bus_infor *head;       //链表指针                     
};

void Bus_link::input()          //录入车票信息
{
	Bus_infor *p,*p2=NULL;
	p=head;                                          
	int n=1;   //int n;
	while(p->next)
		p=p->next;
	while(n)
	{
		p2=new Bus_infor;
		p2->input();
		p->next=p2;
		p2->next=NULL;
		p=p->next;                                   
		cout<<"按继续,按返回:(1/0) ";
		cin>>n;
		if(!cin)
			throw string("数据输入错误");
	}
}

void Bus_link::xianshi()          //显示车票信息
{
	cout<<"客车基本信息如下:"<<endl
		   <<"班次  发车时间  起点站  终点站  行车时间  额定载量  已定票数  当前状况"<<endl;
	Bus_infor *p;
	p=head;
	while(p->next)
	{
		(p->next)->output();
		p=p->next;
	}
}

void Bus_link::found()       //查询车票信息
{
	Bus_infor *p;
	int num,n;
	char name[20];
	do
	{
		cout<<"1:按班次查找,2:按终点站查找: ";
		cin>>n;
		if(!cin)
				throw string("数据输入错误");
	}while(n<1||n>2);
	if(n==1)
	{
		cout<<"输入班次: ";
		cin>>num;
		if(!cin)
				throw string("数据输入错误");
	}
	if(n==2)
	{
		cout<<"输入终点站: ";
		cin>>name;
	}
	if(!find(&p,num,name))
	{
		cout<<"找不到你要查找的内容!"<<endl;
		return;
	}
}

int Bus_link::find(Bus_infor **p1,int num,char *pn)        //查找函数
{
	Bus_infor *p;	
	p=head;	
	int t=0;	
	while(p->next)
	{		
		(*p1)=p;
		if((p->next)->Get_bus_number()==num|| (p->next)->Get_end()==pn )
		{			
			cout<<"客车基本信息如下:"<<endl
				   <<"班次  发车时间  起点站  终点站  行车时间 额定载量  已定票数  当前状况"<<endl;		   
			(p->next)->output(); 			
			t=1;					
		}		
		p=p->next;
	}
	return t;
}

void Bus_link::shanchu()        //删除函数
{
	Bus_infor *p,*p2;
	int num;char name[20];
	cout<<"输入班次号: ";
	cin>>num;		
	if(!cin)
			throw string("数据输入错误");
	if( !find(&p,num,name) )
	{
		cout<<"找不到你要删除的内容!"<<endl;
		return;
	}	
	cout<<"确定删除(y/n)?";
	char a;cin>>a;
	if(a=='y'||a=='Y') 
	{
		p2=p->next;		
		p->next=p2->next;
		delete p2;
	}
}

void Bus_link::xiugai()      //修改函数
{
	Bus_infor *p;
	int num;
	char name[20];		
	cout<<"输入班次号: ";
	cin>>num;	
	if(!cin)
			throw string("数据输入错误");
	if( !find(&p,num,name) )
	{
		cout<<"找不到你要修改的内容!"<<endl;
		return;
	}		
	(p->next)->input();
}

void Bus_link::dingpiao()          //订票函数
{
	Bus_infor *p;
	cout<<"确定购票(y/n)?";
	char X;cin>>X;
	if(X=='y'||X=='Y'){
		int num;
		cout<<"输入班次号: ";
		cin>>num;
		if(!cin)
			throw string("数据输入错误");
		if( !find(&p,num,"^") )
		{
			cout<<"找不到你要定票的车辆的内容!"<<endl;
			return;
		}
		if(!(p->GetTime()))				//判断要定票的车辆是否已经出发,若已经出发则不允许定票
		{
			cout<<"你要订票的车辆已出发!"<<endl;
			return;
		}
		cout<<"输入要定的票数　";
		int n;cin>>n;
		if(!cin)
			throw string("数据输入错误");
		if((p->Get_tickted()+n)<=p->Get_all_tickted())
		{	p->ding_tickt(n);cout<<”订票成功”<<endl;}
		else cout<<"对不起，没有足够的票数。"<<endl;	
	}
	else if(X=='n'||X=='N') cout<<"谢谢使用"<<endl;
	else cout<<"输入字符不确定"<<endl;
}

void Bus_link::tuipiao()        //退票函数
{
	Bus_infor *p;
	cout<<"确定退票(y/n)?";
	char X;cin>>X;
	if(X=='y'||X=='Y')
	{
		int num;
		cout<<"输入班次号: ";
		cin>>num;
		if(!cin)
			throw string("数据输入错误");
		if( !find(&p,num,"^") )
		{
			cout<<"找不到你要退票的车辆的内容!"<<endl;
			return;
		}
		if(!(p->GetTime()))						//判断要定票的车辆是否已经出发,若已经出发则不允许定票
		{
			cout<<"你要退票的车辆已出发!"<<endl;
			return;
		}
		cout<<"输入要退的票数　";
		int n;cin>>n;
		if(!cin)
			throw string("数据输入错误");
		p=p->next;
		if((p->Get_tickted()-n)>=0)
		{	p->tui_tickt(n);cout<<”退票成功”<<endl;}
		else cout<<"对不起，数据出错！。"<<endl;	
	}
	else if(X=='n'||X=='N') cout<<"谢谢使用"<<endl;
	else cout<<"输入字符不确定"<<endl;
}

void Bus_link::baocun()                   //保存车票信息
{
	Bus_infor *p;
	p=head;
	ofstream os("bus.txt",ios::out);			//文件以输出方式打开
	while(p->next)
	{
		(p->next)->output(os);
		p=p->next;
	}
	cout<<"文件已保存! "<<endl;
}

void Bus_link::chushihua()     //初始化车票信息
{
	Bus_infor *p,*p2;
	p=head;
	clear();
	long t;
	ifstream cin("bus.txt",ios::in);			//文件以输入方式打开
	if(!cin)
	{
		ofstream cout("bus.txt",ios::out);		//文件以输出方式打开
		cout.close();			//关闭文件
		return ;
	}
	int num=-1;
	while(1)
	{
        num=-1;
		t=cin.tellg();			//记录下当前位置
		cin>>num;
		cin.seekg(t);			//移动到原来位置
		if(num<0)
		{   
			cin.close();
			return;
		}
		p2=new Bus_infor;
		p2->input(cin);		//输入cin对象内容
		p->next=p2;
		p2->next=NULL;
		p=p->next;
	}
}

void Bus_link::clear()        //清除函数
{
	Bus_infor *p,*p2;
	p=head->next;
	while( p )
	{
		p2=p;
		p=p->next;
		delete p2;
	}
}

char Bus_link::mainmenu()          //主菜单
{
	struct tm *local;
	 char s1[128];
	time_t t;
	t=time(NULL);
	local=localtime(&t);
	strftime(s1,128,"%Y-%m-%d %H:%M ",local);				//按照指定的格式,把时间保存在s1字符串里面
	string s;					//定义字符串s,来判断功能选择是否输入错误
	cout<<"\n\n 欢迎使用车票管理系统"<<endl<<endl;
	cout<<"1. 录入车票信息"<<endl;  
	cout<<"2. 浏览车票信息"<<endl;
	cout<<"3. 查询车票信息"<<endl;  
	cout<<"4. 删除车票信息"<<endl;
	cout<<"5. 修改车票信息"<<endl; 
	cout<<"6. 定购车票信息"<<endl;
	cout<<"7. 退还车票信息"<<endl; 
	cout<<"8. 保存车票信息"<<endl;
	cout<<"0.  退出系统 "<<endl;
	cout<<"\t\t\t\t "<<s1<<endl<<endl;	
	cout<<"请选择功能按钮:　";
	while(true)
	{
		cin>>s;
		if(s.length()!=1||s[0]<'0'||s[0]>'8')          //s.length()返回字符串的长度,即字符个数
			cout<<"输入错误,请重新选择功能按钮: ";
		else
			break;
	}
	return s[0];
}
