
#include<iostream>
#include<vector>
#include<string>

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


template<class Container>
auto bubble_sort(Container*const c) {
	return bubble_sort(c, [](auto x, auto y)->bool {
		return y < x;
	});
}

template<class Container,class F>
auto bubble_sort(Container*const c,F f) {
	auto it = std::begin(*c);
	auto end_ = std::end(*c);
	auto times = end_ - it;
	int c_{ 0 };
	for (int i{ 0 }; i < times; i++) {
		for (long int j{ times - 1 }; j > i ; j--) {
			auto &x = *(it + j - 1);
			auto &y = *(it + j);
			if ( f(x,y) ) {
				std::swap(x, y);
				c_++;
//				std::cout << x << " " << y << "\n";
			}
		}
//		print(*c);
	}
	return c_;
}


template<class Container>
auto selection_sort(Container*const con) {
	return selection_sort(con, [](auto x, auto y) {
		return x > y;
	});
}

template<class Container,class F>
auto selection_sort(Container*const con, F f) {
	auto it = std::begin(*con);
	auto end_ = std::end(*con);
	auto times = end_ - it;

	int c{ 0 };
	for (int i{ 0 }; i < times; i++) {
		int min_ = i;

		for (int j{ i }; j < times; j++) {
			auto& x = *(it + min_);
			auto& y = *(it + j);
			if ( f(x, y) ){
				min_ = j;
			}
		}
		if (min_ == i)continue;
//		std::cout << *(it + min_) << "\n";
		std::iter_swap(it + min_, it + i);
		c++;
//		print(*con);
	}
	return 0;
}

template<class Container,class F>
auto is_stable(const Container &base, const Container& con,F f) {
	bool result{ true };


	using vec = std::vector<typename Container::value_type>;
	for (auto&e : base) {

		auto bit = std::begin(base);
		auto bend = std::end(base);

		auto cit = std::begin(con);
		auto cend_ = std::end(con);

	
		vec v1, v2;

		while (bit != bend) {
			if( f(*bit, e) ){
				v1.emplace_back(*bit);
			}
			++bit;
		}

		while (cit != cend_) {
			if ( f( *cit, e) ){
				v2.emplace_back(*cit);
			}
			++cit;
		}

		for (unsigned i{ 0 }; i < v1.size(); i++) {
			if (!(v1[i]== v2[i])) {//•¶š—ñ‚ğ”äŠr‚·‚éB
	//			std::cout << v1[i] << " " << v2[i] << "\n";
				return false;
			}
	//		std::cout << v1[i] << " " << v2[i] << "\n";

		}
//		print(v1);
//		print(v2);
		
	}

	return result;
}

int main() {
	int N{};
	std::cin >> N;
	std::vector<std::string> vs;

	for (int i{ 0 }; i < N; i++) {
		std::string tmp;
		std::cin >> tmp;
		vs.emplace_back(tmp);
	}
	auto vs1 = vs;
	auto vs2 = vs;

	auto comp = [](auto x, auto y)->bool {
		auto a = x[1];
		auto b = y[1];
		return a > b;
	};

	auto comp2 = [](auto x, auto y)->bool {
		return x[1] == y[1];
	};//sort‚µ‚½‚à‚Ì‚ğ”äŠr‚·‚éB

	auto x = bubble_sort(&vs1, comp);
	print(vs1);
	std::cout << (is_stable(vs, vs1, comp2) ? "S" : "Not s") << "table\n";

	auto y = selection_sort(&vs2, comp);
	print(vs2);
	std::cout << (is_stable(vs, vs2,comp2) ? "S" : "Not s")<<"table\n";

	std::cin >> N;

}