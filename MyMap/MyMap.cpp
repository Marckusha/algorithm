#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstdio>
#include <sstream>

using namespace std;

const int MAXSYMBOLS = 10;

void print(const std::vector<int>& symbols, const std::vector< std::vector<int>>& values) {

	int count = 0;

	for (auto it : values) {
		for (auto jt : it) {
			printf("%d", symbols[jt]);
		}
		if (count == 0) {
			printf("%s", " + ");
			count++;
		}
		else if (count == 1) {
			printf("%s", " = ");
			count++;
		}
	}
	printf("%s", "\n");
}

//check values
void result(const std::vector<int>& symbols, const std::vector< std::vector<int>>& values) {
	std::vector<int> res(values.size(), 0);

	for (int i = 0; i < values.size(); ++i) {
		for (int j = 0; j < values[i].size(); ++j) {
			int valueMap = symbols[values[i][j]];
			int valuePow = pow(10, values[i].size() - 1 - j);
			res[i] += (valueMap * valuePow);
		}
	}

	if (res[0] + res[1] == res[2]) {
		print(symbols, values);
	}
}

void generateNum(std::vector<int>& vect, int& i) {
	if (vect[vect.size() - 1] == MAXSYMBOLS && i > 0) {
		--i;
		++vect[i];
		for (int j = i; j < vect.size() - 1; ++j) {
			vect[j + 1] = vect[j] + 1;
		}
		if (vect[vect.size() - 1] == MAXSYMBOLS && i > 0) {
			generateNum(vect, i);
		}
		i = vect.size() - 1;
	}
}

int main()
{
	std::string mainString = "";

	printf("%s", "Enter a expression: ");
	getline(std::cin, mainString);

	//последовательно считанные, неповторяющиеся символы
	//a - symbols[0]
	//b - symbols[1]
	//c - symbols[2]
	//d - symbols[3]
	std::vector<int> symbols;

	//vector include all values: where ab + c = d
	//a - values[0]
	//b - values[1]
	//c - values[2]
	//d - values[3]
	std::vector< std::vector<int> > values(3);

	//init values, symbols
	int newCount = 0;
	int indexValue = 0;
	std::string allValues = "";
	for (auto it = mainString.begin(); it != mainString.end(); ++it) {
		if (isalpha(*it)) {

			if (allValues.find(*it) == std::string::npos) {
				allValues += *it;
				symbols.push_back(indexValue++);
				values[newCount].push_back(symbols.size() - 1);
			}
			else {
				int j = allValues.find(*it);
				values[newCount].push_back(j);
			}
		}
		else if (!isspace(*it) && (*it == '+' || *it == '=')) {
			++newCount;
		}
	}

	if (symbols.size() > MAXSYMBOLS) {
		printf("%s", "More then 10 variables cann't");
		return 1;
	}

	//equal count num arg and result
	bool isContinue = (values[2].size() > values[0].size());
	int index = symbols.size() - 1;

	do {
		do {

			//if sum first num more then num result then continue
			if (!isContinue) {
				if (symbols.at(values[0][0]) + symbols.at(values[1][0]) > symbols.at(values[2][0])) {
					continue;
				}
			}
			else {
				if ((symbols.at(values[2][0]) > 1) ||
					(symbols.at(values[2][0]) == 0 && symbols.at(values[0][0]) + symbols.at(values[1][0]) > symbols.at(values[2][1]))) {
					continue;
				}
			}


			result(symbols, values);
		} while (next_permutation(symbols.begin(), symbols.end()));

		symbols[index]++;
		generateNum(symbols, index);
	} while (symbols[symbols.size() - 1] != 10);

	return 0;
}