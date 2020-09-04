#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

void result(const std::map<char, int>& mmap, const std::vector < std::vector<char>>& vect) {
	std::vector<int> res(vect.size(), 0);

	for (int i = 0; i < vect.size(); ++i) {
		for (int j = 0; j < vect[i].size(); ++j) {
			int valueMap = mmap.at(vect[i][j]);
			int valuePow = pow(10, vect[i].size() - 1 - j);
			res[i] += (valueMap * valuePow);
		}
	}
	if (res[0] + res[1] == res[2]) {
		int count = 0;
		for (auto it : vect) {
			for (auto jt : it) {
				std::cout << mmap.at(jt);
			}
			if (count == 0) {
				std::cout << " + ";
				count++;
			}
			else if (count == 1) {
				std::cout << " = ";
				count++;
			}
		}
		std::cout << '\n';
	}
}

int main()
{
	std::string mainString = "abcd + efgd = efhdi";
	
	//все символы из строки
	std::map<char, int> charInString;

	//вектор, содержащий по-отдельности каждое число (набор символов), которое представлено в строке mainString
	std::vector<std::vector<char>> expres(3);
	int count = 0;
	for (auto it = mainString.begin(); it != mainString.end(); ++it) {
		if (isalpha(*it)) {
			charInString.insert(std::pair<char, int>(*it, 0));
			expres[count].push_back(*it);
		}
		else if (!isspace(*it)) {
			++count;
		}
	}

	//инициализируем все переменные цифрами от 0 до 8
	int countVal = 0;
	for (auto it = charInString.begin(); it != charInString.end(); ++it) {
		it->second = countVal++;
	}

	//вектор необходим для генерации чисел функции next_permutation
	//короче код говно, нужно заново все писать
	std::vector<int> vectс = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	do {
		int i = 0;
		for (auto it = charInString.begin(); it != charInString.end(); ++it) {
			it->second = vectс[i++];
		}
		result(charInString, expres);
	} while (next_permutation(vectс.begin(), vectс.end()));

	/*myMap.at('a') = 2;
	myMap.at('b') = 7;
	myMap.at('c') = 5;
	myMap.at('d') = 4;
	myMap.at('e') = 0;
	myMap.at('f') = 3;
	myMap.at('g') = 9;
	myMap.at('h') = 1;
	myMap.at('i') = 8;*/


	/*auto mmmm = myMap;
	auto vvvv = expres;
	auto test1 = 0;
	result(myMap, expres);*/
}