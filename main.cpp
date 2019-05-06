#include<iostream>          //数据流输入／输出
#include<fstream>			//文件输入／输出
#include<string>				//字符串操作
#include<iomanip>			//参数化输入／输出
#include<time.h>				//时间库函数
#include”Bus_infor.h”
#include”Bus_link.h”
using namespace std;		//命名空间
int main()              //主函数
{	
	Bus_link pp;        
	int k=1;
	string s;
	pp.chushihua();          //初始化车票信息
	 while(k==1)
	 {
		 system("cls");
		 s=pp.mainmenu();                       //调用主菜单函数
		 switch(s[0])
		 {
		 case '1':pp.input(); break;            //录入车票信息
		 case '2':pp.xianshi(); break;           //浏览车票信息
		 case '3':pp.found(); break;          //查询车票信息
		 case '4':pp.shanchu(); break;              //删除车票信息
		 case '5':pp.xiugai(); break;          //修改车票信息
		 case '6':pp.dingpiao(); break;          //订购车票信息
		 case '7':pp.tuipiao(); break;      //退还车票信息
		 case '8':pp.baocun(); break;           //保存车票信息
		 case '0':k=0;break;                    //退出系统
		 }
		 if(k==1)
		 {
			 cout<<"是否返回主菜单?   1.是 2.不是: ";
			 cin>>k;
			 if(!cin)
				throw string("数据输入错误");
		 }
		 if(k==0)
		 {
			 cout<<"是否保存?  1 . 保存0.不保存: ";
			 cin>>k;
			 if(!cin)
				throw string("数据输入错误");
			 if(k==1)
				 pp.baocun();
			 pp.clear();
			 k=0;	
		 }		
	 }
 return 0;
}
