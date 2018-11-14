
#include<iostream>
#include<vector>
#include<bitset>

int main() {
	std::vector<int> v;
	std::vector<int> ls;
	int n;
	std::cin >> n;

	v.resize(n);
	ls.resize(n);
	
	for (auto&e : v) {
		std::cin >> e;
	}

	int lis{};
	for (int i{ 1 }; i < n; i++) {
		if (v[i - 1] < v[i])
			++lis,std::cout << lis;
	}
		
	std::cout << lis << "\n";

	return 0;
}