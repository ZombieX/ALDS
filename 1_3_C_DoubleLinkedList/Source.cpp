
#include<iostream>
#include<utility>


template<class>
class node;

template<class >
class dlist;//double linked list



template<class T>
class node {
	T value_;
	node<T>*p, *n;//prev, next
public:
	template<class X>
	node(X&& v_, node<T>*const prev_, node<T>* const next_)
		:value_{ std::forward<X>(v_) }, p{ prev_ }, n{ next_ } {}
	auto is_head()const { this->prev == nullptr; }
	auto is_tail()const { this->next == nullptr; }
	auto value()const& { return this->value_; }
	//auto operator()()& { return this->value; }
	auto value() && { return std::move(this->value_); }
	auto& next(node<T>*const np) { n = np; return *this;}
	auto& prev(node<T>*const pp) { p = pp; return *this; }
	auto* next()const { return this->n; }
	auto* prev()const { return this->p; }

};

template<class T>
class dlist {
	node<T>* np,*last;
	std::size_t len;

public:
	dlist() :np{ nullptr }, last{nullptr}, len{ 0 } {}


	template<class X>
	auto& insert(X&&x) {
		if (this->size() == 0) {
			np = new node<T>{
				std::forward<X>(x)
				,nullptr
				,nullptr
			};
			last = np;
		}
		else {

			auto* new_ = new node<T>{
				std::forward<X>(x)
				,np
				,np->next()
			};
			np->next(new_);
//			new_->prev()
//			np->(new_);
//			new_->next(np);
//			np = new_;
			last = new_
				;
		}
		len++;
		return *this;
		/*
		np = new node<T>{
			std::forward<X>(x)
			,len == 0 ? nullptr : np + len - 1
			,nullptr
		};

		if (len != 0) {
			auto* prev = (np + len - 1);
			auto tmp = node<T>{
				std::forward<X>(x)
				,prev->prev()
				,np
			};
			*prev = tmp;
		}
		len++;
		*/

		return *this;
	}

	template<class X>
	bool del(X&&x) {
		if (0 == len) {
			return false;
		}
		else {
			auto* here = this->np;
			if (here->value() == x) {
				if (this->size() == 1)
					delete here;
				else {
					auto n = here->next();
					this->np = n;
					np->prev(nullptr);
					delete here;
				}
				--len;
				return true;
			}

			for (std::size_t i{1}; i < this->size() ; ++i) {
				if (here == nullptr) return false;
				if (here->value() == x)break;
				here = here->next();
			}
			auto* n = here->next();
			auto* p = here->prev();
			delete here;
			
			if(p != nullptr) p->next(n);
			if(n != nullptr) n->prev(p);
			else this->last = n;
			--len;
			return true;
			/*
			if (np->value() == x) {
				auto* p = here->prev();
				auto* n = here->next();
				p->next(n);

				if(n!=nullptr)n->prev(p);
				delete np;
				len--;
				return true;
			}
			else return  false;*/
		}
	}
	auto size()const { return len; }
	auto head()const { return np; }

	auto delfirst() {
		if (this->size() == 0)return false;
		if (this->size() == 1) {
			delete this->np;
		}
		else {
			auto*n = this->np->next();
			n->prev(nullptr);
			delete np;
			np = n;
		}
		len--;
		return true;
	}

	auto dellast() {
		if (this->size() == 0)return false;

		auto*p = this->last;
		if (p->prev() == nullptr)
			delete p;
		else {
			auto *pre = p->prev();
			pre->next(nullptr);
			last = pre;
			delete p;
		}
		return true;
	}


	auto empty()const { this->size() == 0; }

	auto& print()const {
		auto here = np;
		if (here == nullptr) return*this;

		for (std::size_t i{}; i < this->size(); ++i) {
			std::cout << here->value() << " ";
			here = here->next();
		}
		std::cout << "\n";
		return *this;
	}


	~dlist() {

		auto* here = np;
		auto* next = (here)->next();
		while (here!=nullptr &&next != nullptr) {
			delete here;
			here = next;
			next = here->next();
		}

	}

};



auto test() {

	std::cout << "Del \n";
	dlist<int> d;

	for (int i{}; i < 5; i++)d.insert(i);
	std::cout << d.size() << " ";
	d.print();

	for (int i{}; i < 5; i += 2)d.del(i), std::cout << "s,i " << d.size() << " " << i << "\n";
	d.print();

}

auto test2() {
	std::cout << "Del first\n";
	dlist<int> d;
	for (int i{ 5 }; i < 50; i += 10)d.insert(i);
	for (std::size_t i{}; i < d.size(); i++)d.delfirst(),d.print();
}

auto test3() {

	std::cout << "Del last\n";
	dlist<int> d;
	for (int i{ 2 }; i < 50; i += 10)d.insert(i);
	for (std::size_t i{}; i < d.size(); i++)d.dellast(),d.print();
}

int main() {
	test();
	test2();
	test3();
	return 0;
}

