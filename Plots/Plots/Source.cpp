#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Plots {

private:

    int l, s, p;

    vector <string> mas;

public:

    Plots() {

        ifstream fin;
        ofstream fout("output.txt");
        fin.open("input.txt");

        if (fin.is_open()) {
            string str;
            fin >> l >> s;
            for (int i = 0; i < l; i++) {
                fin >> str;
                mas.push_back(str);
            }
        }

        for (int i = 0; i < l; i++) {
            for (int j = 0; j < s; j++) {
                if (mas[i][j] == *"#") {
                    p++;
                    del_plots(i, j);
                }
            }
        }

        fout << "Количество участков на поле " << p;

    }

    void del_plots(int i, int j) {
        if (i < 0 || i >= l || j < 0 || j >= s || mas[i][j] != '#') {
            return;
        }

        mas[i][j] = '.';

        del_plots(i - 1, j);
        del_plots(i + 1, j);
        del_plots(i, j - 1);
        del_plots(i, j + 1);
    }
};



int main() {

    setlocale(LC_ALL, "RU");

    Plots plot;

}