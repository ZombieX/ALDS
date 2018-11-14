
#include<iostream>
#include<vector>

using ull = unsigned long long;
using ul = unsigned long;
using sl = signed long;

template<class Container>
auto print(const Container& c) {
	auto end_ = std::end(c);
	for (auto it = std::begin(c);
		it != (end_-1);
		++it) {
		std::cout << *it << " ";
	}std::cout << *(end_ - 1)<< "\n";
}

int main() {
	std::vector<ul> v;

	ul N{};
	std::cin >> N;

	for (ul i{ 0 }; i < N; i++) {
		ul x{};
		std::cin >> x;
		v.emplace_back(std::move(x));
	}

//	print(v);

	for (ul i{ 1 }; i < N; i++) {

		print(v);

		sl k = i - 1;
		ul key = v[i];
		while (k >= 0 && v[k] > key) {
			v[k + 1] = v[k];
			k--;
		}
		v[k + 1] = key;

	}
	print(v);
	return 0;
}