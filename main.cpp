#include <iostream>
#include <fstream>
#include <string>
#include<iomanip>
#include <vector>
#include <Windows.h>
using namespace std;

//Глобальные переменные
int stateMenu = 0;
string filename;
int N, M;
int num = 1;


//Класс хранящий данные о минимуме(индексы, значение)
class Min {
public:
	int i, j, value;
	Min(int i, int j,int value) {
		this->i = i; this->j = j; this->value = value;
	}
};


//Класс матриц
class matrix {
public:

	//Конструктор по умолчанию
	matrix(){
		N = M = 1;
		arr = new int* [N]; 
		for (int i = 0; i < 1; i++) {
			arr[i] = new int[M];
		}
	};


	//Конструктор с двумя параметрами, размерами матрицы
	matrix(int N, int M) {
		this->N = N; this->M = M; 
		arr = new int* [N];
		for (int i = 0; i < N; i++) {
			arr[i] = new int[M];
		}
		int** ptr = arr;
		cout << "Введите " << N * M << " элементов:" << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> ptr[i][j];
			}
		}
	}


	//метод записи матрицы в файл 
	void fprint(string filename) {
		ofstream out(filename,ios::app); out << "Матрица " << num++ << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				out << arr[i][j] << "\t";
			}
			out << endl;
		}
		out << endl;
		out << "Количество минимумов: " << local_mins.size() << endl;
		for (int k = 0; k < local_mins.size(); k++) {
			out << "[" << local_mins[k].i << "]" << "[" << local_mins[k].j << "]" << " " << local_mins[k].value << endl;	
		}
		out << endl << "--------------------------------------------------" << endl;
	}


	//Метод нахождения локальных минимумов в матрице
	void local_min() {
		int** ptr = arr;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {

				int flag = 1;

				if (i != 0) {
					if (!(ptr[i][j] < ptr[i - 1][j]))
						flag = 0;
				}
				if (flag == 0) continue;


				if (i != N - 1) {
					if (!(ptr[i][j] < ptr[i + 1][j]))
						flag = 0;
				}
				if (flag == 0) continue;


				if (j != 0) {
					if (!(ptr[i][j] < ptr[i][j - 1]))
						flag = 0;
				}
				if (flag == 0) continue;


				if (j != M - 1) {
					if (!(ptr[i][j] < ptr[i][j + 1]))
						flag = 0;
				}
				if (flag == 0) continue;


				//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
				
				__asm {
					mov eax, flag
					mov ebx, 1
					cmp eax, ebx
					je endif
					mov flag, 0

					endif:

				}
				if (flag) {
					Min temp(i, j, ptr[i][j]);
					local_mins.push_back(temp);
				}
			}
		}
		
	}


private:
	int N, M; //Размеры матрицы

	int** arr; //Указатель на матрицу

	vector <Min> local_mins; //Вектор локальных минимумов
};


void menu() {
	cout << "Выберите действие:" << endl;
	cout << "(1) Создать матрицу " << endl;
	cout << "(0) Выход из программы, сохранение в файл " << filename << endl;
	cin >> stateMenu;
	if (stateMenu != 0 && stateMenu != 1) {
		cout << "Неизвестное действие!";
		system("pause"); system("cls");
		menu();
	}
	system("cls");
}


int main() {
	system("chcp 1251");
	//setlocale(LC_ALL, "Rus");
	cout << "Введите название результирующего файла: "; cin >> filename;
	if (filename.find(".txt")==string::npos) {
		filename += ".txt";
	}
	system("cls");

	matrix* matrixes;
	menu();
	while (stateMenu) {
		cout << "Введите размеры матрицы: " << endl << "N: "; cin >> N; cout << "M: "; cin >> M;
		matrixes = new matrix(N, M);
		matrixes->local_min();
		matrixes->fprint(filename);
		system("cls");
		menu();
	}
	return 0;
}