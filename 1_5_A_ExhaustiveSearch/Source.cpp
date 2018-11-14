
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>

using ui = unsigned int;

template<class Tab>
auto solve(const Tab&t, ui i, ui m,ui imax) {
	if (m == 0)
		return true;

	if (imax <= i)//範囲外まで調べた
		return false;

	//すべての組み合わせの内、どれか一つでも満たされるならOK
	return solve(t, i + 1, m, imax)			//t[i]を使わない
		|| solve(t, i + 1, m - t[i],imax);	//t[i]を使う

}
auto answer() {

	ui A[20]{};	ui M[200]{};
	bool log[200]{ false };

	ui n{}, q{};
	std::cin >> n;
	for (ui i{}; i < n; i++)
		std::cin >> A[i];

	std::cin >> q;
	for (ui i{}; i < q; i++)
		std::cin >> M[i];

	for (ui j{}; j < q; j++) {

		auto b = false;
		for (ui i{}; i < n; i++) {
	
			b |= solve(A, i, M[j], n);
		//	std::cout << " " << i << " " << j << " " << M[j] << "\n";
		}
		std::cout << (b ? "yes" : "no")<<"\n";

	}
		
}

int main() {

	answer();


	return 0;
}