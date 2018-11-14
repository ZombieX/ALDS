
#include<iostream>
#include<cmath>
int board[8][8]{};


auto paint(int(&arr)[8][8], int x, int y) {
	auto d = x - y;
	auto sum = x + y;

	for (int ri{}; ri < 8; ri++) {
		for (int ci{}; ci < 8; ci++) {

			if (ri == x || ci == y)
				board[ri][ci] = 1;

			if (ri + ci == sum || ri - ci == d)
				board[ri][ci] = 1;

			if (ri == x && ci == y)
				board[ri][ci] = 9;
		}
	}
}

int main() {

	int x{}, y{};
	std::cin >> x >> y;


	

	for (auto&e : board) {
		for (auto&ee : e)
			std::cout << ee<<" ";
		std::cout << "\n";
	}

	return 0;
}