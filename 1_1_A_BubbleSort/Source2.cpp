
#include<iostream>
#include<iterator>
#include<algorithm>
#include<vector>

template<class Iterator>
auto bubble(const Iterator first, const Iterator last) {
	auto it = first;
	int c{0};
	auto time = last - first;
	for (int i{}; i < time; i++) {
		for (int j{ 0 }; j < time - (i + 1); j++) {
//			std::cout << "i, j = " << i << "," << j << "\n";
			auto& x = *(it + j);
			auto& y = *(it + j + 1);
			if (y < x) {
				std::swap(x,y);
				c++;
			}
		}
	}

	return c;
}
/*
template<class Iterator>
auto is_sorted(const Iterator first, const Iterator last) {
	auto it = first;
	while (it + 1 != last) {

	}
}*/
int main() {
	int N{};
	std::cin >> N;
	/*
	for (int i{ 0 }; i < 5; i++) {
//		std::cout << "i, j = " << i << "\n";

		for (int j{ 0 }; j<5-(i+1); j++) {
			std::cout <<"i, j = "<< i << "," << j << "\n";
		}
	}*/

	
	std::vector<int> v;
	for (int i{ 0 }; i < N; i++) {
		int tmp{};
		std::cin >> tmp;
		v.emplace_back(tmp);
	}

	auto n = bubble(std::begin(v), std::end(v));

	std::cout << v[0];
	for (int i{ 1 }; i < N; i++ ) {
		std::cout << " " << v[i] ;
	}std::cout << "\n";
	std::cout << n << "\n";
	
	int n_;
	std::cin >> n_;
}