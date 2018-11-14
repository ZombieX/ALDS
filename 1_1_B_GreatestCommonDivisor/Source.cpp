
#include<iostream>
#include<algorithm>
using ull = unsigned long long;

decltype(auto) a1() {

	ull a{}, b{};
	std::cin >> a >> b;

	ull r{ 9999 };
	while (r != 0) {
		r = std::max(a, b) % std::min(a, b);
		a = std::min(a, b);
		b = r;
	}
	std::cout << a << "\n";

}

auto rec(ull min_, ull max_, ull r)->decltype(std::minmax(r,min_)) {
	r = max_ % min_;
	std::pair<ull,ull> mm = std::minmax(r, min_);
//	std::cout << min_ << " " << max_ << " " << r << "\n";
	if (r != 0) {
		return rec(mm.first, mm.second, mm.second%mm.first);
	}
	else {
		return mm;
	}
}

decltype(auto) a2() {
	ull a{}, b{};
	std::cin >> a >> b;
	auto mm = std::minmax(a, b);
	auto x = rec(mm.first, mm.second, mm.second%mm.first);

	std::cout << x.second << "\n";
//	std::cin >> a;
}

int main() {
	a2();
	return 0;
}