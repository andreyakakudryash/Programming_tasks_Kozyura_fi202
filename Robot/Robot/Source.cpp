#include <iostream>
#include<fstream>
#include<vector>
#include<queue>


using namespace std;

struct State {
	int x, y;

	State(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

class Robot {
private:
	int N, M, K;
	int** map;


public:
	Robot() {

		ifstream fin;
		ofstream fout("output.txt");
		fin.open("input.txt");
		if (fin.is_open()) {
			fin >> N >> M;

			if (N > 20 || M > 20) {
				cout << " Ошибка! Количество строк и столбцов не должно превышать 20 " << endl;
			}

			else {

				map = new int* [N];

				for (int i = 0; i < N; i++) {
					map[i] = new int[M];
				}

				for (int i = 0; i < N; i++) {
					for (int j = 0; j < M; j++) {

						int value;
						fin >> value;
						map[i][j] = value;
					}
				}

				fin >> K;
			}

		}

		else {
			cout << "Не удалось считать данные из файла! " << endl;
		}

		fin.close();

		int startX, startY, endX, endY;
		vector<vector<int>>visited(N, vector<int>(N, 0));
		queue<State>q;
		int time = 0;
		bool found = false;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[i][j] == 2) {
					startX = i;
					startY = j;
				}

				else if (map[i][j] == 3) {
					endX = i;
					endY = j;
				}

				else if (map[i][j] == 1) {
					visited[i][j] = 1;
				}
			}
		}

		State start(startX, startY);

		q.push(start);

		while (!q.empty()) {

			int size = q.size();

			for (int i = 0; i < size; i++) {
				State curr = q.front();
				q.pop();

				if (curr.x == endX && curr.y == endY) {
					found = true;
					break;
				}

				if (curr.x - 1 >= 0 && visited[curr.x - 1][curr.y] == 0 && map[curr.x - 1][curr.y] != 1) {
					q.push(State(curr.x - 1, curr.y));
					visited[curr.x - 1][curr.y] = 1;
				}

				if (curr.x + 1 < N && visited[curr.x + 1][curr.y] == 0 && map[curr.x + 1][curr.y] != 1) {
					q.push(State(curr.x + 1, curr.y));
					visited[curr.x + 1][curr.y] = 1;
				}

				if (curr.y - 1 >= 0 && visited[curr.x][curr.y - 1] == 0 && map[curr.x][curr.y - 1] != 1) {
					q.push(State(curr.x, curr.y - 1));
					visited[curr.x][curr.y - 1] = 1;
				}

				if (curr.y + 1 < M && visited[curr.x][curr.y + 1] == 0 && map[curr.x][curr.y + 1] != 1) {
					q.push(State(curr.x, curr.y + 1));
					visited[curr.x][curr.y + 1] = 1;
				}
			}

			if (found) {
				break;
			}
			time++;

		}

		if (found) {

			fout << "Минимальный путь составляет " << time;

		}
		
		else {
			fout << "Путь не найден";
		}

		fout.close();

	}

	~Robot() {
		for (int i = 0; i < N; i++) {
			delete[]map[i];
		}

		delete[]map;
	}
};


int main() {
	setlocale(LC_ALL, "RU");

	Robot r;

	return 0;
}