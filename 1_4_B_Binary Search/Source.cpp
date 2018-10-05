
#include<iostream>
#include<vector>
#include<tuple>
#include<set>

using ull = unsigned long long;
template<class C,class T>
auto bs(const C& c, const T&key) {
	using ix_t = decltype(c.size());
	auto size = c.size();
	ix_t imin = 0;
	auto imax = size - 1;
	auto ip = (imax + imin) / 2;
	while (imin <= imax) {
		if (c[ip] == key) {
			return std::make_tuple(true, ix_t{ ip },c[ip]);
		}
		else if (c[ip] < key) {
			imin = ip + 1;
			ip = (imax + imin) / 2;
		}
		else if (key < c[ip]) {
			imax = ip - 1;
			ip = ( imax + imin ) / 2;
		}
	}
	return std::make_tuple(false, ix_t{ 0 },c[0]);
}

int main() {
	ull n{}, q{};
	std::vector<ull> s;//s is sorted
	ull qlog[50000]{};

	std::cin >> n;
	for (ull i{}; i < n; i++) {
		ull tmp; std::cin >> tmp;
		s.emplace_back(tmp);
	}
	
	//std::vector<ull> t;//
	std::set<ull> st;
	std::cin >> q;
	for (ull i{}; i < q; i++) {
		ull tmp; std::cin >> tmp;
		auto tpl = bs(s, tmp);
		if (std::get<0>(tpl)) {
			st.emplace( std::get<1>(tpl) );
		}
	}
	
	std::cout << st.size() << "\n";
/*	ull sum{};
	for (ull i{}; i < q : t) {
		auto t = bs(s, e);
//		if (std::get<0>(t))
	}

	ull sum{};
	/*
	for (const auto&e : qlog)
		if (e > 0)++sum;
	
	std::cout << sum << "\n";
*/
}