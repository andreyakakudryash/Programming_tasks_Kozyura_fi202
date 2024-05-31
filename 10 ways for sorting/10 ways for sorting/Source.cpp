#include <iostream>
#include <cstdlib> 
#include <windows.h>
#include <string>
#include <vector>
#include <random>
#include <ctime>


using namespace std;

class date {
private:
	int y, m, d;
public:

	date() {

	}

	friend ostream& operator << (ostream& os, const date& dt) {
		os << dt.d << "." << dt.m << "." << dt.y;
		return os;
	}

	

	friend istream& operator >> (istream& in, date& dt) {

		string str;
		in >> str;
		int p1 = str.find(".");
		int p2 = str.find(".", p1 + 1);
		dt.d = stoi(str.substr(0, p1));
		dt.m = stoi(str.substr(p1 + 1, p2 - p1));
		dt.y = stoi(str.substr(p2 + 1, 4));


		return in;
	}

	friend class container;

	bool operator < (const date& other) {
		if (this->y < other.y) return true;
		else
		{
			if (this->y == other.y) {
				if (this->m < other.m) return true;

				else {
					if (this->m == other.m) {
						return this->d < other.d;
					}
					else return false;
				}
			}
			else return false;
		}

	}

	friend bool operator > (const date& date1, const date& date2) {
		if (date1.y > date2.y) return true;
		else
		{
			if (date1.y == date2.y) {
				if (date1.m > date2.m) return true;

				else {
					if (date1.m == date2.m) {
						return date1.d > date2.d;
					}
					else return false;
				}
			}
			else return false;
		}

	}
};

class Tpeep {
private:
	string FIO;
	date dt;
	double weight;

public:

	Tpeep() {

	}

	Tpeep(string& FIO, date& dt, double& weight) {
		this->FIO = FIO;
		this->dt = dt;
		this->weight = weight;
	}

	string getFIO() {
		return FIO;
	}

	date getDate() {
		return dt;
	}

	double getWeight() {
		return weight;
	}

};


class container {
private:
	vector<Tpeep> peep_list;
	int count;
	Tpeep person;
	date dt1;

public:

	container() {
		cout << "Установите количество элементов массива: " << endl;
		cin >> count;

		for (int i = 0; i < count; i++) {
			string F;

			for (int j = 0; j < 5; j++) {
				char n = 'A' + rand() % 26;
				F += n;
			}

			string I;

			for (int j = 0; j < 6; j++) {
				char n = 'A' + rand() % 26;
				I += n;
			}

			string O;

			for (int j = 0; j < 10; j++) {
				char n = 'A' + rand() % 26;
				O += n;
			}

			string FIO = F + " " + I + " " + O;


			int day, month, year;

			day = 1 + rand() % 31;
			month = 1 + rand() % 12;
			year = 1950 + rand() % 70;

			dt1.d = day;
			dt1.m = month;
			dt1.y = year;

			double W = 40 + (rand() % 600) / 10.0;

			Tpeep peep(FIO, dt1, W);
			peep_list.push_back(peep);
		}
	}

	void addEl() {
		cout << "ФИО - ";
		string FIO;
		cin.ignore();
		getline(cin, FIO);;
		cout << "Дата рождения - ";
		cin >> dt1;
		cout << "Вес - ";
		double W;
		cin >> W;
		Tpeep peep(FIO, dt1, W);
		peep_list.push_back(peep);
		cout << endl;
	}


	void printArr() {
		int n = 1;
		for (auto& el : peep_list) {
			cout << "Личность " << "[" << n << "]" << endl;
			cout << "ФИО - " << el.getFIO() << endl;
			cout << "Дата рождения - " << el.getDate();
			cout << endl;
			cout << "Вес - " << el.getWeight() << endl;
			cout << endl;
			n++;
		}
	}


	void sortFirst() {
		int var1;
		cout << "Выберите поле, по которому необходимо произвести сортировку: " << endl;
		cout << "[1] ФИО\n";
		cout << "[2] Дата рождения\n";
		cout << "[3] Вес\n";
		cin >> var1;

		if (var1 == 1) {
			for (int i = 0; i + 1 < peep_list.size(); i++) {
				for (int j = 0; j + 1 < peep_list.size() - i; j++) {

					if (peep_list[j + 1].getFIO() < peep_list[j].getFIO()) {
						swap(peep_list[j], peep_list[j + 1]);
					}

				}
			}

		}

		if (var1 == 2) {
			for (int i = 0; i + 1 < peep_list.size(); i++) {
				for (int j = 0; j + 1 < peep_list.size() - i; j++) {

					if (peep_list[j + 1].getDate() < peep_list[j].getDate()) {
						swap(peep_list[j], peep_list[j + 1]);
					}

				}
			}

		}

		if (var1 == 3) {
			for (int i = 0; i + 1 < peep_list.size(); i++) {
				for (int j = 0; j + 1 < peep_list.size() - i; j++) {

					if (peep_list[j + 1].getWeight() < peep_list[j].getWeight()) {
						swap(peep_list[j], peep_list[j + 1]);
					}

				}
			}

		}



	}

	void sortSecond() {

		int var1;
		cout << "Выберите поле, по которому необходимо произвести сортировку: " << endl;
		cout << "[1] ФИО\n";
		cout << "[2] Дата рождения\n";
		cout << "[3] Вес\n";
		cin >> var1;

		if (var1 == 1) {
			for (int i = 0; i < peep_list.size() - 1; i++) {

				int min = i;

				for (int j = i + 1; j < peep_list.size(); j++) {

					if (peep_list[j].getFIO() < peep_list[min].getFIO()) {

						swap(peep_list[j], peep_list[min]);

					}
				}


			}

		}
		for (int i = 0; i < peep_list.size() - 1; i++) {

			int min = i;

			for (int j = i + 1; j < peep_list.size(); j++) {

				if (peep_list[j].getDate() < peep_list[min].getDate()) {

					swap(peep_list[j], peep_list[min]);

				}
			}


		}

		for (int i = 0; i < peep_list.size() - 1; i++) {

			int min = i;

			for (int j = i + 1; j < peep_list.size(); j++) {

				if (peep_list[j].getWeight() < peep_list[min].getWeight()) {

					swap(peep_list[j], peep_list[min]);

				}
			}


		}

	}

	void sortThird() {

		int var1;
		cout << "Выберите поле, по которому необходимо произвести сортировку: " << endl;
		cout << "[1] ФИО\n";
		cout << "[2] Дата рождения\n";
		cout << "[3] Вес\n";
		cin >> var1;

		if (var1 == 1) {

			int left = 0;
			int right = peep_list.size() - 1;


			//Бежим слево направо

			while (left <= right) {

				for (int i = left; i < right; i++) {

					if(peep_list[i].getFIO() > peep_list[i+1].getFIO())
					{
						swap(peep_list[i], peep_list[i + 1]);
					}

				}

				--right;

				//Бежим справа на лево

				for (int i = right; i > left; i--) {
					
					if (peep_list[i].getFIO() < peep_list[i - 1].getFIO()) {

						swap(peep_list[i], peep_list[i - 1]);

					}

				}

				left++;
			}


		}

		if (var1 == 2) {

			int left = 0;
			int right = peep_list.size() - 1;


			//Бежим слево направо

			while (left <= right) {

				for (int i = left; i < right; i++) {

					if (peep_list[i].getDate() > peep_list[i + 1].getDate())
					{
						swap(peep_list[i], peep_list[i + 1]);
					}

				}

				--right;

				//Бежим справа на лево

				for (int i = right; i > left; i--) {

					if (peep_list[i].getDate() < peep_list[i - 1].getDate()) {

						swap(peep_list[i], peep_list[i - 1]);

					}

				}

				left++;
			}


		}

		if (var1 == 3) {

			int left = 0;
			int right = peep_list.size() - 1;


			//Бежим слево направо

			while (left <= right) {

				for (int i = left; i < right; i++) {

					if (peep_list[i].getWeight() > peep_list[i + 1].getWeight())
					{
						swap(peep_list[i], peep_list[i + 1]);
					}

				}

				--right;

				//Бежим справа на лево

				for (int i = right; i > left; i--) {

					if (peep_list[i].getWeight() < peep_list[i - 1].getWeight()) {

						swap(peep_list[i], peep_list[i - 1]);

					}

				}

				left++;
			}


		}

	}
		void sortFourth() {
			int var1;
			cout << "Выберите поле, по которому необходимо произвести сортировку: " << endl;
			cout << "[1] ФИО\n";
			cout << "[2] Дата рождения\n";
			cout << "[3] Вес\n";
			cin >> var1;

			const double factor = 1.247;
			double step = peep_list.size() - 1;

			if (var1 == 1) {
				while (step >= 1) {
					for (int i = 0; i + step < peep_list.size(); i++) {
						if (peep_list[i].getFIO() > peep_list[i + step].getFIO()) {
							swap(peep_list[i], peep_list[i + step]);
						}
					}

					step = step / factor;
				}
			}

			if (var1 == 2) {
				while (step >= 1) {
					for (int i = 0; i + step < peep_list.size(); i++) {
						if (peep_list[i].getDate() > peep_list[i + step].getDate()) {
							swap(peep_list[i], peep_list[i + step]);
						}
					}

					step = step / factor;
				}
			}

			if (var1 == 3) {
				while (step >= 1) {
					for (int i = 0; i + step < peep_list.size(); i++) {
						if (peep_list[i].getWeight() > peep_list[i + step].getWeight()) {
							swap(peep_list[i], peep_list[i + step]);
						}
					}

					step = step / factor;
				}
			}

		}


		void sortFifth() {
			int var1;
			cout << "Выберите поле, по которому необходимо произвести сортировку: " << endl;
			cout << "[1] ФИО\n";
			cout << "[2] Дата рождения\n";
			cout << "[3] Вес\n";
			cin >> var1;

			if (var1 == 1) {
				heapSortFIO();
			}

			if (var1 == 2) {
				heapSortDate();
			}

			if (var1 == 3) {
				heapSortWeight();
			}

		}

		void heapifyFIO(vector<Tpeep>& arr, int n, int i) {
			int largest = i;
			int left = 2 * i + 1;
			int right = 2 * i + 2;


			if (left < n && arr[left].getFIO() > arr[largest].getFIO()) {
				largest = left;
			}

			if (right < n && arr[right].getFIO() > arr[largest].getFIO()) {
				largest = right;
			}

			if (largest != i) {
				swap(arr[i], arr[largest]);
				heapifyFIO(arr, n, largest);
			}
		}


		void heapSortFIO() {
			int n = peep_list.size();

			for (int i = n / 2 - 1; i >= 0; i--) {
				heapifyFIO(peep_list, n, i);
			}

			for (int i = n - 1; i >= 0; i--) {
				swap(peep_list[0], peep_list[i]);
				heapifyFIO(peep_list, i, 0);

			}

		}

		void heapifyDate(vector<Tpeep>& arr, int n, int i) {
			int largest = i;
			int left = 2 * i + 1;
			int right = 2 * i + 2;


			if (left < n && arr[left].getDate() > arr[largest].getDate()) {
				largest = left;
			}

			if (right < n && arr[right].getDate() > arr[largest].getDate()) {
				largest = right;
			}

			if (largest != i) {
				swap(arr[i], arr[largest]);
				heapifyDate(arr, n, largest);
			}
		}


		void heapSortDate() {
			int n = peep_list.size();

			for (int i = n / 2 - 1; i >= 0; i--) {
				heapifyDate(peep_list, n, i);
			}

			for (int i = n - 1; i >= 0; i--) {
				swap(peep_list[0], peep_list[i]);
				heapifyDate(peep_list, i, 0);

			}

		}

		void heapifyWeight(vector<Tpeep>& arr, int n, int i) {
			int largest = i;
			int left = 2 * i + 1;
			int right = 2 * i + 2;


			if (left < n && arr[left].getWeight() > arr[largest].getWeight()) {
				largest = left;
			}

			if (right < n && arr[right].getWeight() > arr[largest].getWeight()) {
				largest = right;
			}

			if (largest != i) {
				swap(arr[i], arr[largest]);
				heapifyDate(arr, n, largest);
			}
		}


		void heapSortWeight() {
			int n = peep_list.size();

			for (int i = n / 2 - 1; i >= 0; i--) {
				heapifyWeight(peep_list, n, i);
			}

			for (int i = n - 1; i >= 0; i--) {
				swap(peep_list[0], peep_list[i]);
				heapifyWeight(peep_list, i, 0);

			}

		}


};

class controller {
	private:
		int state = 1;
		container obj;

	public:

		controller()
		{

		}

		~controller() {

		}

		void execute() {
			while (state) {
				menu();
				int var;
				cin >> var;

				while (var < 1 || var > 12) {
					cout << "Был введён номер,который не входит в диапазон предоставленных команд. Пожалуйста, попробуйте ещё раз!\n";
					cin >> var;
				}

				if (var == 1) {
					obj.addEl();
				}

				if (var == 2) {
					obj.printArr();
				}

				if (var == 3) {
					obj.sortFirst();

				}

				if (var == 4) {
					obj.sortSecond();
				}

				if (var == 5) {
					obj.sortThird();
				}

				if (var == 6) {
					obj.sortFourth();
				}

				if (var == 7) {
					obj.sortFifth();
				}
			}
		}
		void menu() {
			cout << "Меню команд:\n";
			cout << "1. Добавить человека\n";
			cout << "2. Вывести всех людей\n";
			cout << "3. Сортировка [1] Пузырёк\n";
			cout << "4. Сортировка [2] Выбора\n";
			cout << "5. Сортировка [3] Шейкерная\n";
			cout << "6. Сортировка [4] Расчёска\n";
			cout << "7. Сортировка [5] Пирамидальная сортировка\n";

		}
	};





int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	controller cont;
	cont.execute();

}