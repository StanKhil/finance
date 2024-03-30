#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
using namespace std;
struct Banknotes {
	int count;
	int denomination;
};
class Wallet
{
	int sumMoney;
	Banknotes* banknotes;
public:
	Wallet();
	int getSum();
	Banknotes* getBanknotes();
	string getBanknotesList();
	void putMoney(int i);
	void getMoney(int i);
	void report(int i);
	int getWeekNumber(int day, int month, int year);
	void setSum(int x);
	void setBanknote(int i, int c);
	string to_string(int x);
};

