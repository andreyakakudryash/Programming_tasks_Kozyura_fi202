#include <iostream>
#include <vector>
#include <queue>
#include <stack>


using namespace std;

//Обход в глубину (методом стека и рекурсия)

class Graph {
protected:
	stack<int> s;
	stack<int> s_bip;
	int* visited;
	int num = 4;
	int* color;
	
	int mas[4][4] = { {0, 1, 1, 0},
						{ 0, 0, 1, 0},
						{ 1, 0, 0, 1},
						{ 0, 0, 0, 0},
						};

public:



	Graph() {

		visited = new int[num];
		color = new int[num];


		for (int i = 0; i < num; i++) {
			visited[i] = 0;
		}

		for (int j = 0; j < num; j++) {
			color[j] = 0;
		}

		s.push(0);
	}


	void stack() {

		while (!s.empty()) {
			int tek = s.top();
			s.pop();
			visited[tek] = 1;
			
			for (int i = num -1 ; i >=0 ; i--) {
				if (mas[tek][i] == 1 && visited[i] != 1) {
					s.push(i);
					visited[i] = 1;
				}
			}

			cout << tek + 1 << endl;

		}
	}

	void recur(int start) {

		

		visited[start] = 1;
		cout << start + 1<< endl;

		for (int i = 0; i < num; i++) {
			if (mas[start][i] == 1 && visited[i] != 1) {

				recur(i);

			}
		}

	}

	int invert(int c) {
		if (c == 1) {
			return 2;
		}

		else {
			return 1;
		}
	}


	 bool isBipartite(int start) {

		 s_bip.push(start);

		 color[start] = 1;

		 while (!s_bip.empty()) {

			 int tek = s_bip.top();
			 s_bip.pop();

			for (int i = 0; i < num; i++) {
				if (mas[tek][i] == 1) {

					if (color[i] == 0) {
						s_bip.push(i);
						color[i] = 3 - color[tek];
					}


					else if (color[i] == color[tek]) {
						return false;
					}
				}
			}

		}

		 return true;
	}

	 void isCycle(int start, bool& hasCycle) {

		 color[start] = 1;

		 for (int i = 0; i < num; i++) {
			 if (mas[start][i] == 1) {
				 if (color[i] == 0) {

					 isCycle(i, hasCycle);
					 
				 }

				 else if (color[i] == 1) {
					
					 hasCycle = true;
				 }
			 }

		 }

		 color[start] = 2;

		
	 }



	~Graph() {

		delete[] visited;
		delete[]color;
	}

};


int main() {
	
	setlocale(LC_ALL, "RU");

	Graph g;

	cout << "Как желаете отобразить граф при обходе в ширину?" << endl;

	cout << "1. Отобразить граф через стэк\n" << "2. Отобразить граф рекурсивным методом\n" << "3. Проверка графа на двудольность\n" << "4. Поиск цикла в графе" << endl;
	int choose;

	cin >> choose;

	if (choose == 1) {
		Graph g;
		g.stack();
	}

	else if (choose == 2) {
		Graph g;
		g.recur(0);
	}


	else if (choose == 3) {
		Graph g;
		

		if (g.isBipartite(0)) {
			cout << "Graph is bipartite" << endl;
		}

		else {
			cout << "Graph is not bipartite" << endl;
		}
	}

	else if (choose == 4) {
		Graph g;
		bool hasCycle = false;
		
		g.isCycle(0, hasCycle);

		if(hasCycle)
		{
			cout << " This graph has cycle" << endl;
		}

		else {
			cout << "This graph doesn't have cycle" << endl;
		}


	}

}

