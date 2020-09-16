#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <regex>

/**
 * vector include all values
 *  Example where ab + c = d
 *  a - values[0][0] = 0
 *  b - values[0][1] = 1
 *  c - values[1][0] = 2
 *  d - values[2][0] = 3
 */
std::vector< std::vector<int> > MAIN_VALUES(3);

static const int EMPTY = -1;

struct expression {
	int first;
	int second;
	int result;

	expression()
		: first(EMPTY)
		, second(EMPTY)
		, result(EMPTY)
	{}
};

bool isCorrectString(const std::string& str) {
	if (str.empty()) return false;

	std::regex regular("(\\s*)([a-z]+)(\\s*)(\\+)(\\s*)([a-z]+)(\\s*)(\\=)(\\s*)([a-z]+)(\\s*)");
	return std::regex_match(str.c_str(), regular);
}

/**
 * @brief Возвращает вектор всех выражений
 */
std::vector<expression> getVectorExpression(const std::vector< std::vector<int> >& values) {

	typedef std::reverse_iterator< std::vector<int>::const_iterator > RIterator;

	std::vector<expression> result;

	auto firstIt = values[0].crbegin();
	auto secondIt = values[1].crbegin();
	auto resultIt = values[2].crbegin();

	for (int isExit = 0; isExit < values.size();) {
		isExit = 0;
		expression expr;

		auto getValue{ [&isExit](RIterator& beginIter, const RIterator& endIter)
		{
				 if (beginIter != endIter) {
					  return *(beginIter++);
				  }
				  else {
					  ++isExit;
					  return EMPTY;
				  }
		} };

		expr.first = getValue(firstIt, values[0].crend());
		expr.second = getValue(secondIt, values[1].crend());
		expr.result = getValue(resultIt, values[2].crend());

		if (isExit < values.size()) {
			result.push_back(expr);
		}
	}

	return result;
}

void print(const std::vector<int>& symbols) {

	int count = 0;

	for (auto it : MAIN_VALUES) {
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


/**
 * @brief Проверяет является ли выражение истинным (f + s) % 10 == r
 */
bool isCorrectValue(const expression& exp) {
	if ((exp.first + exp.second) % 10 == exp.result) {
		return true;
	}
	return false;
}

/**
 * @brief Главная функция подбора значений
 *
 * @param values Вектор свободных цифр
 * @param symbols Вектор индексов символов
 * @param currIterator Итератор на текущее выражение
 * @param endIterator Итератор на конец выражения
 * @param rest В этот параметр передается 1, если (first + second) > 9
 */
void function(std::vector<int>& values, std::vector<int>& symbols, std::vector<expression>::iterator currIterator, std::vector<expression>::iterator endIterator, int rest = 0) {

	for (int i = 0; i < values.size(); ++i) {

		expression mainExpress;

		bool isFindValueF = false;
		mainExpress.first = (currIterator->first != EMPTY) ? symbols[currIterator->first] : 0;

		if (mainExpress.first == EMPTY && values[i] != EMPTY) {
			mainExpress.first = values[i];
			values[i] = EMPTY;
			symbols[currIterator->first] = mainExpress.first;
			isFindValueF = true;
		}
		else if (mainExpress.first != EMPTY) { i = values.size() - 1; }
		else continue;

		for (int j = 0; j < values.size(); ++j) {

			bool isFindValueS = false;
			mainExpress.second = (currIterator->second != EMPTY) ? symbols[currIterator->second] : 0;

			if (mainExpress.second == EMPTY && values[j] != EMPTY) {
				mainExpress.second = values[j];
				values[j] = EMPTY;
				symbols[currIterator->second] = mainExpress.second;
				isFindValueS = true;
			}
			else if (mainExpress.second != EMPTY) { j = values.size() - 1; }
			else continue;

			for (int k = 0; k < values.size(); ++k) {

				bool isFindValueR = false;
				mainExpress.result = (currIterator->result != EMPTY) ? symbols[currIterator->result] : 0;

				if (mainExpress.result == EMPTY && values[k] != EMPTY) {
					mainExpress.result = values[k];
					values[k] = EMPTY;
					symbols[currIterator->result] = mainExpress.result;
					isFindValueR = true;
				}
				else if (mainExpress.result != EMPTY) { k = values.size() - 1; }
				else continue;

				mainExpress.first += rest;

				if (isCorrectValue(mainExpress)) {
					int val = (mainExpress.first + mainExpress.second) / 10 + mainExpress.result / 10;

					if (++currIterator == endIterator && val == 0) {
						print(symbols);

					}
					else if (currIterator != endIterator) {
						function(values, symbols, currIterator, endIterator, val);
					}
					--currIterator;
				}
				else if (currIterator->first == EMPTY && currIterator->second == EMPTY) {
					if (mainExpress.result - rest == 0) {
						int val = (mainExpress.first + mainExpress.second) / 10;

						if (++currIterator == endIterator && val == 0) {
							print(symbols);
						}
						--currIterator;
					}
				}

				mainExpress.first -= rest;

				if (isFindValueR) {
					values[k] = mainExpress.result;
					mainExpress.result = EMPTY;
					symbols[currIterator->result] = EMPTY;
				}
			}

			if (isFindValueS) {
				values[j] = mainExpress.second;
				mainExpress.second = EMPTY;
				symbols[currIterator->second] = EMPTY;
			}
		}

		if (isFindValueF) {
			values[i] = mainExpress.first;
			mainExpress.first = EMPTY;
			symbols[currIterator->first] = EMPTY;
		}
	}
}