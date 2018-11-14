
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>


auto is_prime(int )->bool;

int main() {

	
	int x{}, c{0};
	std::cin >> x;

	for (int i{ 0 }; i < x; i++) {
		int tmp{ 0 };
		std::cin >> tmp;
		if ( is_prime(tmp) ) c++;
		//std::cout << i << "\n";
	}

	std::cout << (c == 0 ? -1 : c) << "\n";
//	std::cout << "end" << "\n";
	std::cin >> x;

}

auto is_prime(int x)->bool {
	if (x <= 1)		return false;
	if (x == 2)		return true;
	if (x % 2 == 0) return false;

	auto sq_x = std::sqrt(x);
	for (int i{ 3 }; i <= sq_x;i+=2) {
		if (x%i == 0)return false;
	}
	return true;
}