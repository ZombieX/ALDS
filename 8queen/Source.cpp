
#include<iostream>
#include<vector>

struct grid{
	int x, y;
	grid(int x_= -1, int y_= -1) :x{ x_ }, y{y_} {}
	friend std::istream&operator>>(std::istream&is, grid&g) {
		return is >> g.x >> g.y;
	}
};


int main() {

	int n;
	std::vector<grid> v;
	
	for (int i{}; i < 8; i++) {
		for (int j{}; j < 8; j++) {
			v.emplace_back(i, j);
		}
	}

	for (int i{}; i < n; ++i) {
		grid tmp{};
		std::cin >> tmp;
	}

	return;
}