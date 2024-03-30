#include "wallet.h"

Wallet::Wallet() :sumMoney(0){
	banknotes = new Banknotes[10];
	for (int i = 0; i < 10; i++)banknotes[i].count = 0;
	banknotes[0].denomination = 1;
	banknotes[1].denomination = 2;
	banknotes[2].denomination = 5;
	banknotes[3].denomination = 10;
	banknotes[4].denomination = 20;
	banknotes[5].denomination = 50;
	banknotes[6].denomination = 100;
	banknotes[7].denomination = 200;
	banknotes[8].denomination = 500;
	banknotes[9].denomination = 1000;
}

int Wallet::getSum() { return sumMoney; }

Banknotes* Wallet::getBanknotes() { return banknotes; }

string Wallet::getBanknotesList()
{
	string list = " ";
	for (int i = 0; i < 10; i++) {
		list += to_string(banknotes[i].count);
		list += " ";
	}
	return list;
}

void Wallet::putMoney(int i)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true) {
		system("cls");
		cout << "������, ���� ����� ������ ������:\n(1) 1 ���\n(2) 2 ���\n(3) 5 ���\n(4) 10 ���\n(5) 20 ���\n(6) 50 ���\n(7) 100 ���\n(8) 200 ���\n(9) 500 ���\n(10) 1000 ���\n";
		int mode;
		cin >> mode;
		if (mode < 1 or mode>10) {
			cout << "������� �����\n";
			getchar();
			continue;
		}
		cout << "������ ������� �����, �� ������ �������� �� �������\n";
		int count;
		cin >> count;
		if(count<0) {
			cout << "������� �����\n";
			getchar();
			continue;
		}
		banknotes[mode - 1].count += count;
		sumMoney += count * banknotes[mode - 1].denomination;
		int dn, mn, yn;
		cout << "������ ����� ��� � �����\n";
		cin >> dn;
		cout << "������ ����� �����\n";
		cin >> mn;
		cout << "������ ����� ����\n";
		cin >> yn;
		fstream f;
		string name = "wallet";
		name += to_string(i);
		name += ".txt";
		f.open(name, ios::out | ios::app);
		f << "���� ������: " << count * banknotes[mode - 1].denomination << "��� ����: " << dn << "/" << getWeekNumber(dn, mn, yn) << "/" << mn << "/" << yn<<"\n";
		f.close();
		cout << "�� ������� ����� � ��������. ���� ������ �������� �� - �������� (1)\n";
		cin >> mode;
		if (mode != 1)break;
	}
	getchar();
}

void Wallet::getMoney(int i)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true) {
		system("cls");
		cout << "������ ���� ����� ��� ������ �����\n";
		int amount,amount2;
		cin >> amount;
		amount2 = amount;
		if (amount < 0) {
			cout << "������� �����\n";
			getchar();
			continue;
		}
		int bufSum = sumMoney;
		int bufCount[10];
		for (int i = 0; i < 10; i++) {
			bufCount[i] = banknotes[i].count;
		}
		/*for (int i = 0; i < 10; ++i) {
			if (amount >= banknotes[i].denomination && banknotes[i].count > 0) {
				int count = min(amount / banknotes[i].denomination, banknotes[i].count);
				amount -= count * banknotes[i].denomination;
				banknotes[i].count -= count;
			}
		}*/
		for (int i = 9; i >= 0; i--) {
			if(bufCount[i]>0 && banknotes[i].denomination * bufCount[i]>=amount) {
				//cout << i << " " << bufSum << " " << (amount / banknotes[i].denomination) * banknotes[i].denomination << '\n';
				bufSum -= (amount / banknotes[i].denomination) * banknotes[i].denomination;
				bufCount[i] -= amount / banknotes[i].denomination;
				amount -= (amount / banknotes[i].denomination) * banknotes[i].denomination;
			}
		}
		if (amount > 0) cout << "��������� ������ �����.\n���� ������ ����� ���� ���� - �������� (1)";
		else {
			sumMoney = bufSum;
			for (int i = 0; i < 10; i++) {
				banknotes[i].count = bufCount[i];
			}
			string category;
			cout << "������ ��������\n";
			cin >> category;
			int dn, mn, yn;
			cout << "������ ����� ��� � �����\n";
			cin >> dn;
			cout << "������ ����� �����\n";
			cin >> mn;
			cout << "������ ����� ����\n";
			cin >> yn;
			fstream f;
			string name = "wallet";
			name += to_string(i);
			name += ".txt";
			f.open(name, ios::out | ios::app);
			f << "���� �����: " << amount2 << "��� ����: " << dn << "/" << getWeekNumber(dn,mn,yn) << "/" << mn << "/" << yn<<" ��������: "<<category << "\n";
			f.close();
			cout << "�� ����� ����� � �������. ���� ������ ����� �� - �������� (1)\n";
			//sumMoney -= amount2;
		}
		int m;
		cin >> m;
		if (m != 1)break;
	}
	getchar();
	
}

void Wallet::report(int i)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("cls");
	cout << "�� ����� ������ � ��� �:\n";
	cout << "������ ������ � �������: " << sumMoney << "\n���� ����������� ������ ��������\n";
	for (int i = 0; i < 10; i++) 
		cout << "������ �����: " << banknotes[i].denomination << "\t ʳ������: " << banknotes[i].count << "\n";
	getchar();
}

int Wallet::getWeekNumber(int day, int month, int year)
{
	int jan1Weekday = (year * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;
	int dayOfYear = 0;
	static const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	for (int i = 1; i < month; ++i)
		dayOfYear += daysInMonth[i];
	dayOfYear += day;
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0 && year % 100 == 0))
		dayOfYear++;
	int weekNumber = (dayOfYear + jan1Weekday) / 7 + 1;
	if (jan1Weekday > 4 && dayOfYear < 8 - jan1Weekday)
		weekNumber--;
	return weekNumber;
}

void Wallet::setSum(int x)
{
	sumMoney = x;
}

void Wallet::setBanknote(int i, int c)
{
	banknotes[i].count = c;
}

string Wallet::to_string(int x)
{
	
	string ans = "";
	if (x == 0) {
		ans = '0';
		return ans;
	}
	while (x > 0) {
		ans += char((x % 10) + '0');
		x /= 10;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

