
#include<iostream>

template<class T,std::size_t N>
class queue{
	T tab[N];
	T* head;
	T* tail;
public:
	static const auto capasity() { return N; }
	constexpr auto capacity()const { return N; }

	queue():tab{},head{tab},tail{head}{}

	auto size()const {
		if (head <= tail) {
			return head - tail;
		}else {
			return (N - head + tail);
		}
	}

	auto& next(){
		if (head == tab + N-1) {
			head = tab;
		}else {
			head++;
		}
		return *this;
	}

	auto& pop() {  return *(head++); }

	auto& push(const T&t) { *(++tail) = t; return *this; }

};

int main() {

	int x[5]{0};
	for (int i{ 0 }; i < 5;i++) {
		x[i] = i;
	}
	for (int i{ 0 }; i < 20; i++) {
		std::cout << x[i % 5];
		if ((i+1) % 5 == 0)std::cout << "\n";
	}
//	queue<int, 5> Q;
	/*
	for (int h{ 0 }; h < 5; h++) {
		for (int i{ 0 }; i < 5; i++) {
			Q.push(i);
		}
		for (int i{ 0 }; i < 5; i++) {
			std::cout << Q.pop() << " ";
		}std::cout << "\n";
	}*/
}