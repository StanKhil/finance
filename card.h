#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
using namespace std;
class Card
{
	int sumMoney;
	int creditLimit;
	int nowLimit;
public:
	Card();
	int getSum();
	int getCreditLimit();
	int getNowLimit();
	void setCreditLimit(int x);
	void setNowlimit(int x);
	void putMoney(int i);
	void getMoney(int i);
	void report(int i);
	int getWeekNumber(int day, int month, int year);
	void setSum(int x);
	void setLimit(int x);
	string to_string(int x);
};

