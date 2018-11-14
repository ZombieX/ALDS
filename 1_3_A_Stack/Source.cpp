
#include<iostream>
#include<iterator>
#include<memory>
#include<string>
#include<sstream>


//class element_{};
//class operand_{};
template<class T, std::size_t N>
class stack {
	T tab[N];
	T* point;
public:
	stack() :tab{}, point{ &tab[0] } {}
	auto size()const { return std::distance(this->begin(), this->end()); }
	auto& push(const T& x) {

		++this->point;
		*(this->point) = x;
		return *this;
	}

	auto pop() {
		auto tmp = *this->point;
		this->point--;
//		*this->point = -1;
		return tmp;
	}

	auto empty()const {
		return this->size() == 0;
	}

	decltype(auto) begin() { return std::begin(tab); }
	decltype(auto) end() { return (this->point + 1); }

	decltype(auto) begin()const { return std::cbegin(tab); }
	decltype(auto) end()const { return this->point + 1; }

	decltype(auto) cbegin()const { return this->begin(); }
	decltype(auto) cend()const { return this->end(); }

	auto top()const->const T& { return *(this->point); }
	auto bottom()const->const T& { return tab[0]; }//???

};


template<class Stack>
class operation{
public:
	virtual auto operate(Stack*const sp)->operation& = 0;
	virtual ~operation() {}
};

template<class Stack>
class plus final :public operation<Stack> {
	using super = operation<Stack>;
public :
	virtual auto operate(Stack*const sp)->plus<Stack>& override{
		auto x = sp->pop();
		auto y = sp->pop();
		sp->push(x + y);
		return *this;
	}
};

template<class Stack>
class minus final :public operation<Stack> {
	using super = operation<Stack>;
public:
	virtual auto operate(Stack*const sp)->minus<Stack>& override{
		auto x = sp->pop();//right
		auto y = sp->pop();//left
		sp->push(y - x);
		return *this;
	}
};

template<class Stack>
class multi final :public operation<Stack> {
	using super = operation<Stack>;
public:
	virtual auto operate(Stack*const sp)->multi<Stack>& override{
		auto x = sp->pop();
		auto y = sp->pop();
		sp->push(x * y);
		return *this;
	}
};




template<class T,std::size_t N>
auto add(stack<T, N>*const sp) {
	auto& s= *sp;
	auto x = s.pop();
	auto y = s.pop();
	s.push(x + y);
	return sp;
}



int main() {

	stack<int, 200> s;

	
	std::unique_ptr<operation<decltype(s)>> op{nullptr};

	std::string x;
	std::getline(std::cin, x);
	std::stringstream ss{ x };
	while ( ss >> x ) {
		
//		std::cout << x << "\n";

		if (x == "+") {
			op.reset(new plus<decltype(s)>{});
			op->operate(&s);
		}else if (x == "*") {
			op.reset(new multi<decltype(s)>{});
			op->operate(&s);
		}else if (x == "-") {
			op.reset(new minus<decltype(s)>{});
			op->operate(&s);
		}else s.push(std::stoi(x));

//		if (op != nullptr)
/*
		for (auto&e : s) {
			std::cout << e << " ";
		}std::cout << "\n";
*/
	}


//	for (auto&e : s) {
//		std::cout << e << " ";
//	}std::cout << "\n";

	std::cout << s.pop() << "\n";
	return 0;
}

