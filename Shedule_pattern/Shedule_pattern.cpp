#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
using namespace std;

bool CheckingNumbers(const string& s) {
	bool b = true;
	for (auto& a : s) {
		if (!isdigit(a)) {
			b = false;
			break;
		}
	}
	return b;
}

class Deals
{
public:
	virtual void insert() = 0;
	virtual void input(string) = 0;
	virtual void info() = 0;
	virtual ~Deals() {};
};
class Priority
{
public:
	virtual void insert() = 0;
	virtual void input(string) = 0;
	virtual void info() = 0;
	virtual ~Priority() {};
};
class Time
{
public:
	virtual void insert() = 0;
	virtual void input(string) = 0;
	virtual void info() = 0;
	virtual ~Time() {};
};



class YuriyDeals : public Deals
{
	string s;
public:

	void insert() override {
		cout << "Enter your deal: ";
		getline(cin, s);
	}
	void input(string ss) override {
		s == ss;
	}
	void info() override
	{
		cout << "Deal: " << s << endl;
	}
};
class YuriyPriority :public Priority
{
	string s;
public:

	void insert() override {
		cout << "Enter priority of this deal: ";
		getline(cin, s);
	}
	void input(string ss) override {
		s == ss;
	}
	void info() override
	{
		cout << "Priority: " << s << endl;
	}

};
class YuriyTime : public Time
{
	string s;
public:

	void insert() override {
		cout << "Enter time for doing this deal done: ";
		getline(cin, s);
	}
	void input(string ss) override {
		s == ss;
	}
	void info() override
	{
		cout << "Time: " << s << endl;
	}
};



class SheduleFactory
{
public:
	virtual	Deals* createDeal() = 0;
	virtual	Priority* createPriority() = 0;
	virtual	Time* createTime() = 0;
	virtual ~SheduleFactory() {};

};

class YuriyShedule : public SheduleFactory
{
public:
	Deals* createDeal() override
	{
		YuriyDeals* d = new YuriyDeals();

		d->insert();
		return d;
	}
	Priority* createPriority() override
	{
		YuriyPriority* d = new YuriyPriority();

		d->insert();
		return d;
	}
	Time* createTime() override
	{
		YuriyTime* d = new YuriyTime();

		d->insert();
		return d;
	}
};

class Shedule
{
public:
	vector<Deals* > d;
	vector<Priority* > p;
	vector<Time* > t;
	~Shedule()
	{
		for (int i = 0; i < d.size(); i++) delete d[i];
		for (int i = 0; i < p.size(); i++) delete p[i];
		for (int i = 0; i < t.size(); i++) delete t[i];
	}
	bool Empty() {
		if (d.size() == 0) {
			cout << "Shedule is empty!\n";
			return true;
		}
		else
			return false;
	}
	void info()
	{
		if (Empty())
			return;
		for (int i = 0; i < d.size(); i++) {
			cout << "Deal# " << i + 1 << "\n";
			d[i]->info();
			p[i]->info();
			t[i]->info();
			cout << "\n";
		}
	}
	void Deleting() {
		if (Empty())
			return;
		string s;
		int a;
		do {
			cout << "Enter index of deal to delete: ";
			cin >> s;
			if (CheckingNumbers(s))
				a = stoi(s);
			else
				system("cls");
		} while (!CheckingNumbers(s));
		if (a > d.size()) {
			cout << "Index out of range\n";
			return;
		}
		a--;
		auto iterd = d.cbegin();
		auto iterp = p.cbegin();
		auto itert = t.cbegin();
		d.erase(iterd + a);
		p.erase(iterp + a);
		t.erase(itert + a);
		cout << "Deleted!\n";
	}
	void Change() {
		if (Empty())
			return;
		string s;
		int a;
		do {
			cout << "Enter index of deal to delete: ";
			cin >> s;
			if (CheckingNumbers(s))
				a = stoi(s);
			else
				system("cls");
		} while (!CheckingNumbers(s));
		if (a > d.size()) {
			cout << "Index out of range\n";
			return;
		}
		a--;
		cin.ignore();
		d[a]->insert();
		p[a]->insert();
		t[a]->insert();
	}

	void Save() {
		ofstream file("Shedule.txt");
		if (!file.is_open())
			cout << "error!";
		else
			file << d.size() << "\n";
		for (int i = 0; i < d.size(); i++) {
			file << d[i] << "\t" << p[i] << "\t" << t[i] << "\n";
		}
		file.close();
		cout << "Saved!\n";
	}
	void Load() { //doesn`t work
		int n;
		string s;
		ifstream file("Shedule.txt");
		file >> n;
		d.resize(n);
		p.resize(n);
		t.resize(n);
		for (int i = 0; i < n; i++) {
			file >> s;
			d[i]->input(s);
			file >> s;
			p[i]->input(s);
			file >> s;
			t[i]->input(s);
		}
		cout << "Loaded!\n";
		return;
	}

};


class Game
{
public:
	void Insert(Shedule* p, YuriyShedule& factory)
	{
		p->d.push_back(factory.createDeal());
		p->p.push_back(factory.createPriority());
		p->t.push_back(factory.createTime());
	}
};

int main()
{
	char ch;
	Game shed;
	YuriyShedule shedule;
	Shedule* sh = new Shedule();
	do {
		system("cls");
		cout << "Menu.\n1 - Add deal\n2 - Show shedule\n3 - Delete by index\n4 - Change deal\n5 - Save(save adress:-( )\n6 - Load(doesn`t work)\n";
		ch = _getch();
		switch (ch)
		{
		case'1':
			system("cls");
			shed.Insert(sh, shedule);
			cout << "Added!\n";
			system("pause");
			break;
		case'2':
			system("cls");
			sh->info();
			system("pause");
			break;
		case'3':
			system("cls");
			sh->Deleting();
			system("pause");
			break;
		case'4':
			system("cls");
			sh->Change();
			system("pause");
			break;
		case'5':
			system("cls");
			sh->Save();
			system("pause");
			break;
		case'6':
			system("cls");
			sh->Load();
			system("pause");
			break;
		}

	} while (ch != 27);

}