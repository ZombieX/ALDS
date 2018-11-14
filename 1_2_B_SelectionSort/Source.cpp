
#include<iostream>
#include<vector>

template<class Container>
auto print(const Container&c) {

	auto it = std::begin(c);
	auto end_ = std::end(c);

	if (it != end_) {
		std::cout << (*it);
	}

	++it;
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
		std::cin >> tmp;
		v.emplace_back(tmp);
	}

//	print(v);

	int c{0};
	for (int i{ 0 }; i < N; i++) {
		int mini = i;
		for (int j{ i }; j < N; j++) {
			
			if (v[j] < v[mini]) {
				mini = j;//index of minimum value
//				std::cout << "i, j = " << i << " " << j << "\n";
			}
		}
		if (i == mini)continue;// It is no-mean to swap it and itself.
//		std::cout << "swapped:" << v[i] << " and " << v[mini] << "\n";
		std::swap(v[i], v[mini]);//swap to index i and minimum
		c++;
	}

//	std::cout << v[0];
	print(v);
	std::cout << c << "\n";
	
	int n;
	std::cin >> n;
}