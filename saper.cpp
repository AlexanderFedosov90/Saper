#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>

using namespace std;

int field[100][100];
int field_p[100][100];
const int N = 11, M = 11, K = 10;

void print_field() {
    setlocale(LC_ALL, "ru");
    system("cls");
    cout << "  ";
    for (int i = 0; i < M; i++) {
        cout << " " << i + 1;
        if (i + 1 < 10) cout << ' ';
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << i + 1 << " ";
        if (i + 1 < 10) cout << ' ';
        for (int j = 0; j < M; j++) {
            if (field_p[i][j] == -2) cout << "_  ";
            else if (field_p[i][j] == -1) cout << "f  ";
            else if (field_p[i][j] == -3) cout << "*  ";
            else cout << field_p[i][j] << "  ";
        }
        cout << endl;
    }
}

void dfs(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] != -2) return;
    field_p[x][y] = field[x][y];
    if (field[x][y] > 0) return;
    for (int i2 = x - 1; i2 <= x + 1; i2++) {
        for (int j2 = y - 1; j2 <= y + 1; j2++) {
            if (i2 != x || j2 != y) dfs(i2, j2);
        }
    }
}

bool open_cell(int x, int y) {
    if (field[x][y] == -1) return false;
    if (field[x][y] > 0) {
        field_p[x][y] = field[x][y];
        return true;
    }
    dfs(x, y);
    return true;
}

bool is_win() {
    int opened = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (field[i][j] >= 0 && field_p[i][j] != -2) opened++;
        }
    }
    return (N * M - K == opened);
}

int main() {
    while (true) {
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                field[i][j] = 0;
                field_p[i][j] = -2;
            }
        }
        for (int i = 0; i < K; i++) {
            while (true) {
                int x = rand() % N;
                int y = rand() % M;
                if (field[x][y] != -1) {
                    field[x][y] = -1;
                    break;
                }
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (field[i][j] != -1) {
                    field[i][j] = 0;
                    for (int i2 = i - 1; i2 <= i + 1; i2++) {
                        for (int j2 = j - 1; j2 <= j + 1; j2++) {
                            if (i2 >= 0 && i2 < N && j2 >= 0 && j2 < M && field[i2][j2] == -1) ++field[i][j];
                        }
                    }
                }
            }
        }
        while (true) {
            print_field();
            cout << "Введите команду: " << endl << "чтобы открыть клетку введите \\o и координаты;" << endl 
                << "чтобы поставить флажок введите \\f и координаты;" << endl
                << "чтобы начать новую игру введите \\n;" << endl 
                <<"чтобы выйти из игры введите \\q." << endl << endl;
            string command;
            cin >> command;
            if (command == "\\o") {
                int x, y;
                cin >> x >> y;
                x--; y--;
                if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] != -2) continue;
                if (!open_cell(x, y)) {
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < M; j++) {
                            if (field_p[i][j] == -1) field_p[i][j] = -2;
                            if (field[i][j] == -1) field_p[i][j] = -3;
                        }
                    }
                    print_field();
                    cout << "Вы проиграли. Чтобы начать новую игру, введите любую строку: ";
                    string s;
                    cin >> s;
                    break;
                }
                if (is_win()) {
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < M; j++) {
                            if (field_p[i][j] == -1) field_p[i][j] = -2;
                            if (field[i][j] == -1) field_p[i][j] = -3;
                        }
                    }
                    print_field();
                    cout << "Вы выиграли. Чтобы начать новую игру, введите любую строку: ";
                    string s;
                    cin >> s;
                    break;
                }
            }
            else if (command == "\\f") {
                int x, y;
                cin >> x >> y;
                x--; y--;
                if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] != -2) continue;
                if (field_p[x][y] == -1) field_p[x][y] = -2;
                else field_p[x][y] = -1;
            }
            else if (command == "\\n") {
                break;
            }
            else if (command == "\\q") {
                return 0;
            }
        }
    }
}
