#include "Header.h"

int main()
{
	std::vector<int> vectFreeValues = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	std::string mainString = "";

	printf("%s", "Enter a expression: ");
	getline(std::cin, mainString);

	//последовательно считанные, неповторяющиеся символы
	//a - symbols[0]
	//b - symbols[1]
	//c - symbols[2]
	//d - symbols[3]
	std::vector<int> symbols;

	int newCount = 0;
	int indexValue = 0;
	static const int MAXSYMBOLS = 10;
	std::string allValues = "";

	try {
		if (!isCorrectString(mainString)) {
			throw std::exception("uncorrected input expression\n");
		}

		for (auto it = mainString.begin(); it != mainString.end(); ++it) {
			if (isalpha(*it)) {

				if (allValues.find(*it) == std::string::npos) {
					allValues += *it;
					symbols.push_back(EMPTY);
					indexValue++;
					MAIN_VALUES[newCount].push_back(symbols.size() - 1);
				}
				else {
					int j = allValues.find(*it);
					MAIN_VALUES[newCount].push_back(j);
				}
			}
			else if (!isspace(*it) && (*it == '+' || *it == '=')) {
				++newCount;
			}
		}

		if (symbols.size() > MAXSYMBOLS) {
			throw std::exception("more then 10 variables cann't");
		}
	}
	catch (const std::exception& exc) {
		std::cerr << exc.what() << std::endl;
		return 1;
	}

	/**
	 *	Пример: ab+cd=adg, где 01 + 23 = 034,
	 *	где каждому символу присваивается уникальный символ
	 *	vectExpress[0] - first=1, second=3, result=4
	 *	vectExpress[1] - first=0, second=2, result=3
	 * 	vectExpress[2] - first=EMPTY(-1), second=EMPTY(-1), result=0
	*/
	auto vectorExpression = getVectorExpression(MAIN_VALUES);

	function(vectFreeValues, symbols, vectorExpression.begin(), vectorExpression.end());

	return 0;
}