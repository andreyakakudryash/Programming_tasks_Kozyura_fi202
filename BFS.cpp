
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <queue>
#include <vector>



using namespace std;

class Graph {
private:
    int** mas;
    int rows;
    int cols;
    int start;
    int end;
    queue <int> q;
    int* p;
    int* used;

public:
    Graph() {
        int num;
        cout << "¬ведите кол-во вершин" << endl;
        cin >> num;

        rows = num;
        cols = num;
        cout << "—оздайте матрицу смежности" << endl;
        mas = new int* [rows];
        used = new int[num];
        p = new int[num];

        for (int i = 0; i < rows; i++) {
            mas[i] = new int[cols];
        }



        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int el;
                cout << "Ёлемент " << "[" << i << "] " << "[" << j << "]" << endl;
                cin >> el;
                mas[i][j] = el;
            }
        }

        for (int i = 0; i < num; i++) {
            used[i] = 0;
        }

        q.push(0);
        p[0] = -1;

        cout << "¬ведите вершину с которой необходимо найти кратчайший путь ";

        cin >> start;

        cout << endl;

        cout << "¬ведите вершину, до которой необходимо найти кратчайший путь ";


        cin >> end;
        end--;

        while (!q.empty()) {

            int tek = q.front();
            q.pop(); 
            used[tek] = 1;

            for (int i = 0; i < num; i++) {

                if (mas[tek][i] == 1 && used[i] == 0) {

                    used[i] = 1;

                    q.push(i);

                    p[i] = tek +1;
                }
            }
        }


    }

    void print() {

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << mas[i][j] << ' ';
            }

            cout << endl;
        }

        cout << endl;
        cout << endl;


        cout << " ратчайший путь: ";

        cout << end + 1;


        while (end != start-1) {
            
            cout << " <- ";

            cout << p[end];

            end = p[end];


            end--;

            
        }


    }

    ~Graph() {

        delete[] p;

        delete[] used;

        for (int i = 0; i < rows; i++) {
            delete[]mas[i];
        }

        delete[] mas;
    }
};

class Cycle_short {
private:
    int mas;
    int num;
    int again;
    queue <int> q;
    vector <int> p;
    int* used;
    int count_used;
    int min = 10000000;

public:
    Cycle_short() {


        int mas[5][5] = { {0, 1, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 1},
            {0, 0, 1, 0, 0}
        };

        used = new int[5];
        
        for (int i = 0; i < 5; i++) {

           

            while (!q.empty()) {
                q.pop();
            }

            count_used = 0;

            p.clear();




            for (int j = 0; j < 5; j++) {
                used[j] = 0;
            }

            q.push(i);

            p.push_back(i);

            while (!q.empty()) {

                int tek = q.front();

                q.pop();

                used[tek] = 1;

                for (int g = 0; g < 5; g++) {

                    if (mas[tek][g] == 1 && used[g] == 0) {

                        q.push(g);

                        used[g] = 1;

                        p.push_back(tek + 1);
                    }

                    else if (mas[tek][g] == 1 && used[g] == 1) {
                        break;
                    }
                }


            }

            for (int j = 0; j < 5; j++) {
                if (used[j] == 1) {
                    count_used += 1;
                }
            }

            if (count_used == min) {
                break;
            }

            if (count_used < min) {
                min = count_used;
            }

        }

    }

    void print() {

        cout << endl;
        cout << "ƒлина кратчайшего цикла равна " << min << endl;

        cout << " ратчайший цикл ";
        
   

        for (int i = 0; i < min; i++) {

            cout << p[i];

            if (i != min - 1) {
                cout << " <- ";
            }
        }

    }


    ~Cycle_short() {

        delete[] used;

    }
};






int main() {
    setlocale(LC_ALL, "ru");

    int choice;
    cout << "Ўо нада сделать? " << endl;
    cout << "1 - найти кратчайшее рассто€ние между точками " << endl;
    cout << "2 - найти кратчайший цикл " << endl;

    cin >> choice;

    if (choice == 1) {

        Graph g;
        cout << endl;
        g.print();
    }

    else if (choice == 2) {
        Cycle_short s;

        s.print();
    }

}
