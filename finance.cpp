#include "wallet.h"
#include "Array.h"
#include "card.h"
#include <string>

void saveData(DynamicArray<Wallet> &wallets, DynamicArray<Card> &cards) {
	fstream f;
	f.open("Wallets_data.txt", ios::out | ios::trunc);
	f << wallets.getSize() << "\n";
	for (int i = 0; i < wallets.getSize(); i++) {
		//cout << wallets.getElement(i).getBanknotesList() << '\n';
		f << wallets.getElement(i).getSum() << " " << wallets.getElement(i).getBanknotesList();
		if (i != wallets.getSize() - 1) f<< "\n";
	}
		
	f.close();
	f.open("Cards_data.txt", ios::out | ios::trunc);
	f << cards.getSize() << "\n";
	for (int i = 0; i < cards.getSize(); i++) {
		f << cards.getElement(i).getSum() << " " << cards.getElement(i).getCreditLimit()<<" "<<cards.getElement(i).getNowLimit();
		if (i != cards.getSize() - 1)f << "\n";
	}
		
	f.close();
}

void getData(DynamicArray<Wallet> &wallets, DynamicArray<Card> &cards) {
	fstream f;

	string text;
	int ind;
	f.open("Wallets_data.txt", ios::in);
	f.seekg(0, ios::beg);
	char buf[100];
	f.getline(buf, 100);
	while (!f.eof()) {
		f.getline(buf, 100);
		Wallet temp;
		text = buf;
		string num="";
		for (int i = 0; i < text.size(); i++) {
			if (text[i] == ' ') {
				ind = i;
				break;
			}num += text[i];
		}
		temp.setSum(stoi(num));
		num = "";
		int c = 0;
		for (int i = ind+2; i < text.size(); i++) {
			if (text[i] == ' ' or text[i]=='\n') {
				temp.setBanknote(c, stoi(num));
				c++;
				num = "";
			}
			else num += text[i];
		}
		wallets.addElement(temp);
	}
	f.close();

	f.open("Cards_data.txt", ios::in);
	//char buf[30];
	f.getline(buf, 100);
	while (!f.eof()) {
		Card temp;
		f.getline(buf, 100);
		text = buf;
		string num = "";
		for (int i = 0; i < text.size(); i++) {
			if (text[i] == ' ') {
				ind = i;
				break;
			}num += text[i];
		}
		temp.setSum(stoi(num));
		num = "";
		for (int i = ind + 1; i < text.size(); i++) {
			if (text[i] == '\n' or text[i] == ' ') { ind = i + 1; break; }
			num += text[i];
		}

		temp.setLimit(stoi(num));
		num = "";
		for (int i = ind; i < text.size(); i++) {
			if (text[i] == '\n' or text[i] == ' ') { ind = i; break; }
			num += text[i];
		}
		//cout << num << "\n";
		temp.setNowlimit(stoi(num));
		cards.addElement(temp);
	}
	f.close();
}

void getReport(DynamicArray<Wallet>& wallets, DynamicArray<Card>& cards) {
	int wc, spending;
	string text = "";
	string category;
	cout << "Оберіть:\n(1) Звіт по гаманцю\n(2) Звіт по картці\n";
	cin >> wc;
	cout << "Оберіть:\n(1) Звіт по затратам\n(2) Звіт по отриманням\n";
	cin >> spending;
	if (wc < 1 or wc>2 or spending<1 or spending>2) {
		cout << "Помилка вводу\n";
		getchar();
		return;
	}
	int c;
	cout << "Пошук по:\n(1) Числу\n(2) Тиждню\n(3) Місяцю\n(4) Року\n";
	if (spending == 1)cout << "(5) Категорію\n";
	cin >> c;
	if (c < 1 or c>5) {
		cout << "Помилка вводу\n";
		getchar();
		return;
	}
	int day, week, month, year;
	if (c == 1) {
		cout << "Оберіть день\n";
		cin >> day;
		cout << "Оберіть місяць\n";
		cin >> month;
		cout << "Оберіть рік\n";
		cin >> year;
	}
	else if (c == 2) {
		cout << "Оберіть тиждень\n";
		cin >> week;
		cout << "Оберіть рік\n";
		cin >> year;
	}
	else if (c == 3) {
		cout << "Оберіть місяць\n";
		cin >> month;
		cout << "Оберіть рік\n";
		cin >> year;
	}
	else if (c == 4) {
		cout << "Оберіть рік\n";
		cin >> year;
	}
	else if (c == 5) {
		cout << "Оберіть категорію\n";
		cin >> category;
	}

	if (wc == 1) {
		for (int i = 0; i < wallets.getSize(); i++) {
			string name = "wallet";
			name += wallets.getElement(i).to_string(i + 1);
			name += ".txt";
			fstream f;
			f.open(name, ios::in);
			char buf[100];
			string buff;
			while (!f.eof()) {
				f.getline(buf, 100);
				buff = buf;
				if (buff == "")break;
				int d, w, m, y;
				int ind = -1;
				int count_ = 0;
				string num = "";
				for (int i = 0; i < buff.size(); i++) {
					if (buff[i] == ' ') { count_++; }
					if (count_ == 4) { ind = i + 1; break; }
				}
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				d = stoi(num);
				num = "";
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				w = stoi(num);
				num = "";
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				m = stoi(num);
				num = "";
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				y = stoi(num);
				num = "";
				if (buff[5] == 'д' and spending == 2) {
					if (c == 1 and day == d and month == m and year == y)text += buff + '\n';
					else if (c == 2 and week == w and year == y)text += buff + '\n';
					else if (c == 3 and month == m and year == y)text += buff + '\n';
					else if (c == 4 and year == y)text += buff + '\n';
				}
				else if (buff[5] == 'в' and spending == 1) {
					if (c == 1 and day == d and month == m and year == y)text += buff + '\n';
					else if (c == 2 and week == w and year == y)text += buff + '\n';
					else if (c == 3 and month == m and year == y)text += buff + '\n';
					else if (c == 4 and year == y)text += buff+'\n';
					else if (c == 5) {
						string cat = "";
						count_ = 0;
						for (int i = 0; i < buff.size(); i++) {
							if (buff[i] == ' ') { count_++; }
							if (count_ == 6) { ind = i + 1; break; }
						}
						for (int i = ind; i < buff.size(); i++) cat += buff[i];
						if (cat == category)text += buff + '\n';
					}
				}
			}
			f.close();
		}
	}
	else if (wc == 2) {
		for (int i = 0; i < cards.getSize(); i++) {
			string name = "card";
			name += cards.getElement(i).to_string(i + 1);
			name += ".txt";
			fstream f;
			f.open(name, ios::in);
			char buf[100];
			string buff;
			while (!f.eof()) {
				f.getline(buf, 100);
				buff = buf;
				if (buff == "")break;
				int d, w, m, y;
				int ind = -1;
				int count_ = 0;
				string num = "";
				for (int i = 0; i < buff.size(); i++) {
					if (buff[i] == ' ') { count_++; }
					if (count_ == 4) { ind = i + 1; break; }
				}
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				//cout << num << '\n';
				d = stoi(num);
				num = "";
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				w = stoi(num);
				num = "";
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				m = stoi(num);
				num = "";
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				y = stoi(num);
				num = "";
				if (buff[5] == 'д' and spending == 2) {
					if (c == 1 and day == d and month == m and year == y)text += buff + '\n';
					else if (c == 2 and week == w and year == y)text += buff + '\n';
					else if (c == 3 and month == m and year == y)text += buff + '\n';
					else if (c == 4 and year == y)text += buff + '\n';
				}
				else if (buff[5] == 'в' and spending == 1) {
					if (c == 1 and day == d and month == m and year == y)text += buff + '\n';
					else if (c == 2 and week == w and year == y)text += buff + '\n';
					else if (c == 3 and month == m and year == y)text += buff + '\n';
					else if (c == 4 and year == y)text += buff + '\n';
					else if (c == 5) {
						string cat = "";
						count_ = 0;
						for (int i = 0; i < buff.size(); i++) {
							if (buff[i] == ' ') { count_++; }
							if (count_ == 6) { ind = i + 1; break; }
						}
						for (int i = ind; i < buff.size(); i++) cat += buff[i];
						if (cat == category)text += buff + '\n';
					}
				}
			}
			f.close();
		}
	}
	fstream f;
	f.open("Reports.txt", ios::out | ios::app);
	cout << text << "\n\n";
	f << text << "\n\n";
	f.close();
}

void getRating(DynamicArray<Wallet>& wallets, DynamicArray<Card>& cards) {
	int wc, spending;
	string text = "";
	string category;
	cout << "Оберіть:\n(1) Рейтинг по гаманцю\n(2) Звіт по картці\n";
	cin >> wc;
	cout << "Оберіть:\n(1) Рейтинг по затратам\n(2) Звіт по отриманням\n";
	cin >> spending;
	if (wc < 1 or wc>2 or spending < 1 or spending>2) {
		cout << "Помилка вводу\n";
		getchar();
		return;
	}
	int c;
	cout << "Пошук по:\n(1) Числу\n(2) Тиждню\n(3) Місяцю\n(4) Року\n";
	if (spending == 1)cout << "(5) Категорію\n";
	cin >> c;
	if (c < 1 or c>5) {
		cout << "Помилка вводу\n";
		getchar();
		return;
	}
	int day, week, month, year;
	if (c == 1) {
		cout << "Оберіть день\n";
		cin >> day;
		cout << "Оберіть місяць\n";
		cin >> month;
		cout << "Оберіть рік\n";
		cin >> year;
	}
	else if (c == 2) {
		cout << "Оберіть тиждень\n";
		cin >> week;
		cout << "Оберіть рік\n";
		cin >> year;
	}
	else if (c == 3) {
		cout << "Оберіть місяць\n";
		cin >> month;
		cout << "Оберіть рік\n";
		cin >> year;
	}
	else if (c == 4) {
		cout << "Оберіть рік\n";
		cin >> year;
	}
	else if (c == 5) {
		cout << "Оберіть категорію\n";
		cin >> category;
	}

	if (wc == 1) {
		for (int i = 0; i < wallets.getSize(); i++) {
			string name = "wallet";
			name += wallets.getElement(i).to_string(i + 1);
			name += ".txt";
			fstream f;
			f.open(name, ios::in);
			char buf[100];
			string buff;
			while (!f.eof()) {
				f.getline(buf, 100);
				buff = buf;
				if (buff == "")break;
				int d, w, m, y;
				int ind = -1;
				int count_ = 0;
				string num = "";
				for (int i = 0; i < buff.size(); i++) {
					if (buff[i] == ' ') { count_++; }
					if (count_ == 4) { ind = i + 1; break; }
				}
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				d = stoi(num);
				num = "";
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				w = stoi(num);
				num = "";
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				m = stoi(num);
				num = "";
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				y = stoi(num);
				num = "";
				if (buff[5] == 'д' and spending == 2) {
					if (c == 1 and day == d and month == m and year == y)text += buff + '\n';
					else if (c == 2 and week == w and year == y)text += buff + '\n';
					else if (c == 3 and month == m and year == y)text += buff + '\n';
					else if (c == 4 and year == y)text += buff + '\n';
				}
				else if (buff[5] == 'в' and spending == 1) {
					if (c == 1 and day == d and month == m and year == y)text += buff + '\n';
					else if (c == 2 and week == w and year == y)text += buff + '\n';
					else if (c == 3 and month == m and year == y)text += buff + '\n';
					else if (c == 4 and year == y)text += buff + '\n';
					else if (c == 5) {
						string cat = "";
						count_ = 0;
						for (int i = 0; i < buff.size(); i++) {
							if (buff[i] == ' ') { count_++; }
							if (count_ == 6) { ind = i + 1; break; }
						}
						for (int i = ind; i < buff.size(); i++) cat += buff[i];
						if (cat == category)text += buff + '\n';
					}
				}
			}
			f.close();
		}
	}
	else if (wc == 2) {
		for (int i = 0; i < cards.getSize(); i++) {
			string name = "card";
			name += cards.getElement(i).to_string(i + 1);
			name += ".txt";
			fstream f;
			f.open(name, ios::in);
			char buf[100];
			string buff;
			while (!f.eof()) {
				f.getline(buf, 100);
				buff = buf;
				if (buff == "")break;
				int d, w, m, y;
				int ind = -1;
				int count_ = 0;
				string num = "";
				for (int i = 0; i < buff.size(); i++) {
					if (buff[i] == ' ') { count_++; }
					if (count_ == 4) { ind = i + 1; break; }
				}
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				d = stoi(num);
				num = "";
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				w = stoi(num);
				num = "";
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				m = stoi(num);
				num = "";
				for (int i = ind; i < buff.size(); i++) {
					if (buff[i] == '/' or buff[i] == ' ') { ind = i + 1; break; }
					num += buff[i];
				}
				y = stoi(num);
				num = "";
				if (buff[5] == 'д' and spending == 2) {
					if (c == 1 and day == d and month == m and year == y)text += buff + '\n';
					else if (c == 2 and week == w and year == y)text += buff + '\n';
					else if (c == 3 and month == m and year == y)text += buff + '\n';
					else if (c == 4 and year == y)text += buff + '\n';
				}
				else if (buff[5] == 'в' and spending == 1) {
					if (c == 1 and day == d and month == m and year == y)text += buff + '\n';
					else if (c == 2 and week == w and year == y)text += buff + '\n';
					else if (c == 3 and month == m and year == y)text += buff + '\n';
					else if (c == 4 and year == y)text += buff + '\n';
					else if (c == 5) {
						string cat = "";
						count_ = 0;
						for (int i = 0; i < buff.size(); i++) {
							if (buff[i] == ' ') { count_++; }
							if (count_ == 6) { ind = i + 1; break; }
						}
						for (int i = ind; i < buff.size(); i++) cat += buff[i];
						if (cat == category)text += buff + '\n';
					}
				}
			}
			f.close();
		}
	}

	int count = 0,c2=0;
	string lines[100];
	int sum[100];
	string buf = "";
	for (int i = 0; i < text.size(); i++) {
		if (text[i] == '\n') { 
			lines[c2] = buf;
			buf = "";
			c2++;
			count++; 
		}
		else buf += text[i];
	}
	for (int i = 0; i < count; i++){
		string num = "";
		int ind = -1;
		for (int j = 0; j < lines[i].size(); j++) {
			if (lines[i][j] == ':') {
				ind = j + 2;
				break;
			}
		}
		for (int j = ind; j < lines[i].size(); j++) {
			if (lines[i][j] == 'г')break;
			num += lines[i][j];
		}
		//cout<<ind<<' ' << num << "\n";
		sum[i] = stoi(num);
	}
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count - 1; j++) {
			if (sum[j] < sum[j + 1]) {
				swap(sum[j], sum[j + 1]);
				swap(lines[j], lines[j + 1]);
			}
		}
	}
	fstream f;
	f.open("Reports.txt", ios::out | ios::app);
	for (int i = 0;i< min(count, 3); i++) {
		cout << lines[i] << '\n';
		f << lines[i] << '\n';
	}
	cout << "\n\n";
	f << "\n\n";
	f.close();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	DynamicArray<Wallet> wallets;
	DynamicArray<Card>cards;
	getData(wallets,cards);
	while (true) {
		//system("cls");
		cout << "Зараз у вас:\tКарток: " << cards.getSize() << "\tГаманців: " << wallets.getSize() << "\n";
		int mode;
		cout << "\nОберіть що ви хочите зробити:\n(1) додати гаманець\n(2) додати картку\n(3) Інша дія з гаманцями\n(4) інша дія з картками\n(5) Зробити звіт\n(6) Вийти з програми\n";
		cin >> mode;
		if (mode < 1 or mode>6) {
			cout << "Помилка вводу\n";
			getchar();
			//system("cls");
			continue;
		}
		else if (mode == 1) {
			Wallet T;
			wallets.addElement(T);
			cout << "Ви додали новий гаманець\n";
			getchar();
			//system("cls");
			continue;
		}
		else if (mode == 2) {
			Card T;
			cards.addElement(T);
			cout << "Ви додали нову картку\n";
			getchar();
			//system("cls");
			continue;
		}
		else if (mode == 3) {
			if (wallets.getSize() == 0) {
				cout << "У вас ще не має жодного гаманця\n";
				getchar();
				continue;
			}
			int m;
			cout << "Оберіть один варіант:\n(1) Додати гроші\n(2) Забрати гроші\n(3) Побачити кількість грошей в гаманці\n";
			cin >> m;
			if (m < 1 or m>3) {
				cout << "Помилка вводу\n";
				getchar();
				continue;
			}
			int n;
			cout << "Вкажіть номер гаманця. У вас є "<<wallets.getSize()<<"\n";
			cin >> n;
			if (n<1 or n>wallets.getSize()) {
				cout << "Помилка вводу\n";
				getchar();
				continue;
			}
			if (m == 1)wallets.getElement(n - 1).putMoney(n);
			else if (m == 2)wallets.getElement(n - 1).getMoney(n);
			else if (m == 3)wallets.getElement(n - 1).report(n);
			//system("cls");
		}
		else if (mode == 4) {
			if (cards.getSize() == 0) {
				cout << "У вас ще не має жодної картки\n";
				getchar();
				continue;
			}
			int m;
			cout << "Оберіть один варіант:\n(1) Додати гроші\n(2) Забрати гроші\n(3) Побачити кількість грошей на картці\n(4) Змінити кредитний ліміт\n";
			cin >> m;
			if (m < 1 or m>4) {
				cout << "Помилка вводу\n";
				getchar();
				continue;
			}
			int n;
			cout << "Вкажіть номер картки. У вас є " << cards.getSize() << "\n";
			cin >> n;
			if (n<1 or n>cards.getSize()) {
				cout << "Помилка вводу\n";
				getchar();
				continue;
			}
			if (m == 1)cards.getElement(n - 1).putMoney(n);
			else if (m == 2)cards.getElement(n - 1).getMoney(n);
			else if (m == 3)cards.getElement(n - 1).report(n);
			else if (m == 4) {
				cout << "Оберіть новий кредитний ліміт\n";
				int newlimit;
				cin >> newlimit;
				if (newlimit < 0) {
					cout << "Помилка вводу\n";
					getchar();
					continue;
				}
				cards.getElement(n - 1).setLimit(newlimit);
			}
				
			//system("cls");
		}
		else if(mode==5){
			cout << "Оберіть:\n(1) Звіт\n(2) Рейтинг\n";
			int mode;
			cin >> mode;
			if (mode < 1 or mode>2) {
				cout << "Помилка вводу\n";
				getchar();
				continue;
			}
			if (mode == 1)getReport(wallets, cards);
			else if (mode == 2)getRating(wallets, cards);
		}
		else if (mode == 6) {
			cout << "До побачення\n";
			saveData(wallets,cards);
			return 0;
		}
	}
}


