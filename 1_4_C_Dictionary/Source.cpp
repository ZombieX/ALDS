
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<set>


using ull = unsigned long long;

std::string in = "insert", fi = "find";


auto make_code(const std::string& s) {
	ull code{1};
	for (const auto&e : s) {
		code <<= 2;//*= 4;
		code +=
			e == 'A'?0:
			e =='T'?1:
			e =='G'?2:3;
	}
	return code;
}

auto die() {//TLE for search

	std::cout.sync_with_stdio(false);

	std::vector< std::pair<std::string, ull> > dict;
	
	std::vector<std::string> results;

	ull N{};
	std::cin >> N;
	dict.reserve(  1000000);
	results.reserve(500000);
	for (ull i{}; i < N; ++i) {
		std::string op,s;
		std::cin >> op >> s;

		auto&& c = make_code(s);
//		std::cout << ">>" << c << "\n";

		if (op == in) {
			//dict.emplace_back(s,c);
			dict.push_back({ s,c });

		}


		if (op == fi) {
			auto en_ = std::end(dict);
			auto it = std::find_if(
				std::begin(dict)
				, en_
				,[&](auto x)->bool {
					return x.second == c;
				});

			results.push_back(
				(it != en_ ? "yes" : "no")
			);
		}
	}
	for (const auto&e : results) {
		std::cout << e << "\n";
	}

}


int main() {
	std::cout.sync_with_stdio(false);

	std::set<std::string>st;
	std::vector<std::string>rv;
	rv.reserve(500000);
	ull N;
	std::cin >> N;
	for (ull i{}; i < N; ++i) {
		std::string op, tmp; std::cin >> op >> tmp;

		if (op == in) {
				st.emplace(tmp);
		}
		else if (op == fi) {
			auto en = std::end(st);
			auto it = st.find(tmp);//std::find(std::begin(st), en, tmp);
			rv.push_back(it != en ? "yes":"no");
		}
	}

	for (const auto&e : rv)
		std::cout <<e<< "\n";

}