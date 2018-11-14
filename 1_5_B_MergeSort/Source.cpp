
#include<iostream>
#include<vector>
using ui = unsigned int;



template<class T,std::size_t N>
constexpr auto size(const T(&arr)[N]) {
	return N;
}

ui x[]{ 5,3,7,4,6,8,0,2,9,1};




template<class Container , class F>
auto merge(Container& arr, ui first, ui mid, ui last,F f) {
//	std::cout << first << " " << last << "\n";
	auto a = mid - first;
	auto b = last - mid;

	std::vector<ui> larr, rarr;
	larr.resize(a+1);
	rarr.resize(b+1);

	for (ui i{}; i < a; ++i) {
		larr[i] = arr[first + i];
//		std::cout << ">> L:" << larr[i]<<"\n";
	}
	for (ui i{}; i < b; ++i) {
		rarr[i] = arr[mid + i];
//		std::cout << ">> R:" << rarr[i] << "\n";
	}

	larr[a] = -1 ;//”ñ•‰®”‚ÌÅ‘å’l
	rarr[b] = -1 ;//“¯ã

//	for (const auto&e : larr)
//		std::cout << e << " ";
//	std::cout << "\n";

	ui i{}, j{};
	for (ui k{ first }; k < last; ++k) {
		if ( f(larr[i] , rarr[j] ) ){
			arr[k] = larr[i];
			++i;
		}
		else {
			arr[k] = rarr[j];
			++j;
		}
	}
}

template<class Container,class F>
void merge_sort(Container &tab, ui first, ui last, F f) {

	if(first +1 <last ){

		auto mid = (first + last) / 2;
		merge_sort(tab, first, mid , f);
		merge_sort(tab, mid, last, f);
		merge(tab, first, mid, last ,f);

	}
}

template<class Container>
void merge_sort(Container &tab, ui first, ui last) {
	merge_sort(tab, first, last, [](auto x, auto y) {return x <= y; });
}


void indexer(ui left, ui right) {

	std::cout << left << " " << right << "\n";
	if (right <= left + 1)return;

	ui mid = (left + right) / 2;
	indexer(left, mid);		
	indexer(mid, right);
}

int main() {
	
/*
	for (const auto&e : x)
		std::cout << e << " ";
	std::cout << "\n";
*/

//	indexer(0, 15);

	ui n; std::cin >> n;

	std::vector<ui>v; v.resize(n);
	for (auto&e:v) {
		std::cin >> e;
	}
	//ui A[500000];

	ui count{};

	merge_sort(v, 0, n
		, [&](auto x,auto y) {
		++count;
		return x <= y;
	});

	std::cout << v.front();
	for (ui i{ 1 }; i < n; i++) 
		std::cout << " " << v[i];
	std::cout << "\n";

	std::cout << count << "\n";
/*	for (const auto&e : x)
		std::cout << e << " ";
	std::cout << "\n";
	*/

	return 0;
}