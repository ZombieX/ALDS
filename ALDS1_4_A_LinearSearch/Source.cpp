
#include<iostream>
#include<vector>
#include<algorithm>

using ull = unsigned long long;
using sll = signed long long;

auto submit1() {

	ull q{}, n{};
	std::vector<ull> S, T;

	std::cin >> n;
	for (ull i{}; i < n; i++) {
		ull tmp{};
		std::cin >> tmp;
		S.emplace_back(tmp);
	}

	std::cin >> q;
	for (ull i{}; i < q; i++) {
		ull tmp{};
		std::cin >> tmp;
		T.emplace_back(tmp);
	}

	std::sort(std::begin(S), std::end(S));
	auto es = std::unique(std::begin(S), std::end(S));
	std::sort(std::begin(T), std::end(T));
	auto et = std::unique(std::begin(T), std::end(T));


	ull c{};
	for (auto its = std::begin(S); its != es; ++its)
		for (auto itt = std::begin(T); itt != et; ++itt)
			if (*its == *itt)c++;

	std::cout << c << "\n";

}


auto submit2() {
	ull stab[10000]{0};
	ull ttab[500]{0};
	ull log[10000]{0};

	ull n{}, q{};
	std::cin >> n;
	for (ull i{}; i < n; ++i) {
		ull tmp; std::cin >> tmp;
		stab[i] = tmp;
	}

	std::cin >> q;
	for (ull i{}; i < q; ++i) {
		ull tmp; std::cin >> tmp;
		ttab[i] = tmp;
	}

	for (const auto&et : ttab) {
		for (const auto&es : stab) {
			if (et != 0 && es!=0 && et == es) {
				log[es]++;
			}
		}
	}
	
	ull sum{0};
	for (const auto& el : log) {
		if (el > 0 )sum++;
	}
	std::cout << sum << "\n";
}
int main() {
	submit2();
	return 0;
}