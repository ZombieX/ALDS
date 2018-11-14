
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>

using ui = unsigned int;

template<class Tab>
auto solve(const Tab&t, ui i, ui m,ui imax) {
	if (m == 0)
		return true;

	if (imax <= i)//�͈͊O�܂Œ��ׂ�
		return false;

	//���ׂĂ̑g�ݍ��킹�̓��A�ǂꂩ��ł����������Ȃ�OK
	return solve(t, i + 1, m, imax)			//t[i]���g��Ȃ�
		|| solve(t, i + 1, m - t[i],imax);	//t[i]���g��

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