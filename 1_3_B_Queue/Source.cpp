
#include<iostream>
#include<string>
#include<utility>

template<class T,std::size_t N>
class queue {
	constexpr static const auto array_size = N + 5;
	T tab[array_size];//array size has to be larger than the number of elements.
	decltype(N) head, tail;
public:
	queue() :tab{}, head{ 0 }, tail{0} {}

	auto empty()const { 
		return this->head == this->tail; 
		//return this->size() == 0;
	}

	auto size()const {
//		std::cout << "h,t " << head << ", " << tail<<"\n";
		return tail <= head ?
			head - tail : array_size - tail + head;
	}

	auto full()const { return N == this->size(); }


	template<class X>
	auto& push(X&&x){
		tab[head] = std::forward<X>(x);
		head = (head+1)%(array_size);
//		std::cout << "push:" << x << "\n";
//		std::cout <<"h,t = "<< this->head << "," << this->tail << "\n";
		return *this;
	}

	auto pop() {
		auto x = tab[tail];
		tail = (tail+1)%array_size;
//		std::cout << "pop:" << x << "\n";
		return x;
	}

	//template<class F>
	auto print() {
				
		if (head <= tail) {
			if (this->empty()) {
				std::cout << "empty !\n";
				return;
			}
			for (std::size_t i{ tail }; i < array_size ; i++) {
				std::cout << tab[i];
				std::cout << (i%10==0?"\n":" ");
			}
			auto x = (N - 1 - tail) % 10;
			for (std::size_t i{ 0 }; i < head; i++) {
				std::cout << tab[i];
				x += i; x %= 10;
				std::cout << (x % 10 == 0&&i!=0 ? "\n" : " ");
			}
			if (x % 10 != 0)std::cout << "\n";
		}
		else {
			std::size_t i{ tail };
			for (; i < head; i++) {
				std::cout << tab[i];
				std::cout << (i%10==0&&i!=0?"\n":" ");
			}
			if (i % 10 != 0)std::cout << "\n";
		}
	}


};

constexpr static const auto size{ 100000 };

struct element {
	std::string name;
	int resource;
	//	bool finished =false;
	int lap;
	element() :element{"",0} {}
	element(const std::string& s, int r) :name{ s }, resource{ r },lap{} {}
	friend std::ostream& operator<<(std::ostream& os, const element& e) {
		return os << e.name << " " << e.resource;
	}
	auto result() {
		std::cout << name << " " << lap;
	} 
};

auto test() {

	queue<int, 5> Q;
	for (int i{1}; i <= 5; i++) {
		Q.push(i);
	}

	Q.print();//1,2,3,4,5
//	std::cout << Q.size() << "\n";

	int accum{};
	while (!Q.empty()) {
		auto x = Q.pop();
	//	std::cout << x << "\n";

		if (x  > 1) {
			Q.push(x-1);
			std::cout << "size : " << Q.size();
			std::cout << ", x : " << x << ", all : ";
			Q.print();
		}

		++accum;
	}
	std::cout <<accum<<"\n";

}

int main() {

	int N{}, cost{};
	std::cin >> N >> cost;

	queue<element, size> que;

	for (int i{}; i < N; i++) {
		std::string name{};
		int time{};
		std::cin >> name >> time;
		que.push(element{name,time});
	}

	//que.print();

	unsigned long long acc{};
	while (!que.empty()) {
		auto x = que.pop();
		if (x.resource <= cost) {
			acc += x.resource;
			x.resource = 0;
//			std::cout << x;
			std::cout << x.name << " " << acc << "\n";
		}
		else {
			x.resource -= cost;
			acc += cost;
			que.push(x);
		}
	}

	return 0;
}