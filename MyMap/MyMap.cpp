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
		//std::cout << res[i] << std::endl;
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
	std::map<char, int> myMap;
	std::string str = "abcd + efgd = efhdi";
	std::vector<std::vector<char>> expres(3);
	int count = 0;
	int countVal = 0;
	for (auto it = str.begin(); it != str.end(); ++it) {
		if (isalpha(*it)) {
			myMap.insert(std::pair<char, int>(*it, 0));
			expres[count].push_back(*it);
		}
		else if (!isspace(*it)) {
			++count;
		}
	}

	for (auto it = myMap.begin(); it != myMap.end(); ++it) {
		it->second = countVal++;
	}

	std::vector<int> vectс = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	do {
		int i = 0;
		for (auto it = myMap.begin(); it != myMap.end(); ++it) {
			it->second = vectс[i++];
		}
		result(myMap, expres);
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