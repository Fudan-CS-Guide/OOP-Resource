#ifndef FAMILYMART_H
#define FAMILYMART_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <istream>
using namespace std;
int dnumber[12]={31,28,31,30,31,30,31,31,30,31,30,31};//一年中每月天数
int num=0;//进入的商品总数
int today=738152;//从第一年开始至今的天数
double turnover=0;//销售额
class commodity{//商品类
public:
    string name;//商品名字
    double price;//商品价格
    int life;//商品保质期
    string product_date;//商品生产日期
    int lifespan;//从第一年开始计算的保质期天数
};



commodity *good=new commodity[100000];//商品库
commodity example;//商品类模版————用于覆盖删除已经售出的商品



class FamilyMart {
public:
    FamilyMart(){};
    FamilyMart(const string& cmmodity_file_name){};
    void purchase_file(const string& cmmodity_file_name);//进货
    void sell_file(const string& sell_file_name);//售卖
    double show_turnover();//营业额
    int total_days(string &date);//计算从第一年开始计算的保质期天数
    void expiration();//判断过期
    double search(const string& cmmodity_name, double discount);//在商品库中寻找最邻近保质期的商品
};



double FamilyMart::show_turnover(){
    return turnover;
}



void FamilyMart::purchase_file(const string& cmmodity_file_name){
    today++;
    char title[100];//去除抬头
    ifstream input;
    input.open(cmmodity_file_name);
    input.getline(title,100,'\n');//去除抬头
    for(;;num++){//输入商品信息
        input>>good[num].name;
        input>>good[num].price;
        input>>good[num].life;
        input>>good[num].product_date;
        good[num].lifespan=total_days(good[num].product_date)+good[num].life;
        if(input.eof()) break;
        
    }
    expiration();//判断是否过期
}



int FamilyMart::total_days(string &date){
    int sum=0;//从第一年开始计算的保质期天数
    int year[4]={0,0,0,0};
    int month[2]={0,0};
    int day[2]={0,0};
    for(int i=0; i<4; i++){
        year[i]=date[i]-'0';
    }
    for(int i=0; i<2; i++){
        month[i]=date[i+5]-'0';
    }
    for(int i=0; i<2; i++){
        day[i]=date[i+8]-'0';
    }
    for(int i=0; i<10*month[0]+month[1]-1; i++){
        sum+=dnumber[i];
    }
    sum+=(1000*year[0]+100*year[1]+10*year[2]+year[3])*365+10*day[0]+day[1];
    return sum;
}



void FamilyMart::expiration(){
    for(int i=0; i<num; i++){
        if(good[i].lifespan<today)
            good[i]=example;//用空白模版覆盖删除
    }
}



double FamilyMart::search(const string& cmmodity_name, double discount){
    int lifespan=1000000;
    int key=0;//记录找到的商品数组序号
    double sale=0;
    for(int i=0; i<num; i++){//查找最邻近保质期的先售卖
        if((!good[i].name.compare(cmmodity_name))&&(good[i].lifespan<lifespan)){
            lifespan=good[i].lifespan;
            key=i;
        }
    }
    sale=good[key].price*discount;
    if(lifespan==1000000) return 0;//如果商品库中没有此类商品，销售额为0
    good[key]=example;//删除已售卖商品
    return sale;
}



void FamilyMart::sell_file(const string& sell_file_name){
    char head[100];//去除抬头
    char title[100];//一行信息
    char nam[100];//截取商品名
    char dis[100];//截取折扣
    double discount;
    ifstream input;
    input.open(sell_file_name);
    input.getline(head,100,'\n');//去除抬头
    for(;;){
        for(int i=0; i<100; i++){
            title[i]='\n';
            nam[i]='\n';
            dis[i]='\n';
        }
        input.getline(title,50,'\n');
        for(int i=0; title[i]!='\n'; i++){//截取顾客要购买的商品名字和商品折扣
            if(title[i]!='\t')
                nam[i]=title[i];
            if(title[i]=='\t'){
                i++;
                for(int j=0; title[i]!='\n'; i++)
                    dis[j++]=title[i+1];
                    break;
            }
        }
        for(int i=0; ; i++){
            if(nam[i]=='\n'){
                nam[i]='\0';
                break;
            }
        }
        string name=nam;
        if(dis[0]=='\0')
            discount=1;
        else
            discount=atof(dis);
        turnover+=search(name,discount);
        cout<<turnover<<endl;
        if(input.eof()) break;
    }
}



#endif

