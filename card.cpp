#include "card.h"

Card::Card():sumMoney(0),creditLimit(10000),nowLimit(10000){}

int Card::getSum()
{
	return sumMoney;
}

int Card::getCreditLimit()
{
	return creditLimit;
}

int Card::getNowLimit()
{
	return nowLimit;
}

void Card::setCreditLimit(int x)
{
	creditLimit = x;
	cout << "¬и встановили новий кредитний л≥м≥т\n";
	getchar();
}

void Card::setNowlimit(int x)
{
	nowLimit = x;
}

void Card::putMoney(int i)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true) {
		system("cls");
		cout << "ќбер≥ть к≥льк≥сть грошей €к≥ хочете покласти на картку\n";
		int amount;
		cin >> amount;
		if (amount < 0) {
			cout << "ѕомилка вводу\n";
			getchar();
			continue;
		}
		sumMoney += amount;
		if (sumMoney < 0)nowLimit = creditLimit + sumMoney;
		else nowLimit = creditLimit;
		int dn, mn, yn;
		cout << "¬вед≥ть номер дн€ у м≥с€ц≥\n";
		cin >> dn;
		cout << "¬вед≥ть номер м≥с€ц€\n";
		cin >> mn;
		cout << "¬вед≥ть номер року\n";
		cin >> yn;
		fstream f;
		string name = "card";
		name += to_string(i);
		name += ".txt";
		f.open(name, ios::out | ios::app);
		f << "Ѕуло додано: " << amount << "грн ƒата: " << dn << "/" << getWeekNumber(dn, mn, yn) << "/" << mn << "/" << yn << "\n";
		f.close();
		cout << "¬и поклали грош≥ на картку. якжо бажаЇте покласти ще - натисн≥ть (1)\n";
		int mode;
		cin >> mode;
		if (mode != 1)break;
	}
	getchar();
}

void Card::getMoney(int i)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true) {
		//system("cls");
		cout << "ќбер≥ть к≥льк≥сть грошей €к≥ хочете зн€ти з картки\n";
		int amount;
		cin >> amount;
		if (amount < 0) {
			cout << "ѕомилка вводу\n";
			getchar();
			continue;
		}
		if (amount > sumMoney + nowLimit) {
			cout << "Ќе достатньо кошт≥в. ќбер≥ть ≥ншу суму\n";
			getchar();
			continue;
		}
		sumMoney -= amount;
		if (sumMoney < 0)nowLimit =creditLimit+ sumMoney;
		else {
			nowLimit = creditLimit;
		}
		string category;
		cout << "ќбер≥ть категор≥ю\n";
		cin >> category;
		int dn, mn, yn;
		cout << "¬вед≥ть номер дн€ у м≥с€ц≥\n";
		cin >> dn;
		cout << "¬вед≥ть номер м≥с€ц€\n";
		cin >> mn;
		cout << "¬вед≥ть номер року\n";
		cin >> yn;
		fstream f;
		string name = "card";
		name += to_string(i);
		name += ".txt";
		f.open(name, ios::out | ios::app);
		f << "Ѕуло вз€то: " << amount << "грн ƒата: " << dn << "/" << getWeekNumber(dn, mn, yn) << "/" << mn << "/" << yn<<"  атегор≥€: "<<category << "\n";
		f.close();
		cout << "¬и зн€ли грош≥ з картки. якжо бажаЇте зн€ти ще - натисн≥ть (1)\n";
		int mode;
		cin >> mode;
		if (mode != 1)break;
	}
	getchar();
}

void Card::report(int i)
{
	system("cls");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "” вас на рахунку: " << sumMoney << "\t¬аш кредитний л≥м≥т: " << nowLimit << "\n";
	getchar();
}

int Card::getWeekNumber(int day, int month, int year)
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

void Card::setSum(int x)
{
	sumMoney=x;
}

void Card::setLimit(int x)
{
	nowLimit -= creditLimit - x;
	creditLimit = x;
}

string Card::to_string(int x)
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

