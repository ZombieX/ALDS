
#include<iostream>
#include<algorithm>

int R[200000];

int main() {
	int N;
	std::cin >> N;

	for (int i{ 0 }; i < N; i++)std::cin >> R[i];


	auto max_{ -1000000000 };
	auto min_{ R[0] };
	for (int i{ 1 }; i < N;i++) {

		max_ = std::max(max_, R[i] - min_);
		min_ = std::min(min_, R[i]);

//		std::cout << min_ << " " << max_<<"\n";
	}

	std::cout << (max_) << "\n";
	std::cin >> N;
	return 0;
}