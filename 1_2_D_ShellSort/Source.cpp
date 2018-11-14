
#include<iostream>
#include<vector>

template<class Container>
auto print(const Container&c) {
	auto it = std::begin(c);
	auto end_ = std::end(c);
	if (it != end_) {
		std::cout << (*it);
		++it;
	}
	for (; it != end_; ++it) {
		std::cout << " " << (*it);
	}std::cout << "\n";
}

int main() {
	int N{};
	std::cin >> N;
	std::vector<int> v;
	
	for (int i{ 0 }; i < N; i++) {
		int tmp{};
		v.emplace_back(
			(std::cin >> tmp, tmp)
			);
	}

	//
	print(v);
	return 0;
}