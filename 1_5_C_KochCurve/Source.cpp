
#include<iostream>
#include<cmath>
#include<cassert>
#include<iomanip>
#include<vector>
#include<utility>
#include<algorithm>

const auto pi = std::acos(-1.0);

struct vec {
	double x, y;
	vec(double dx = 0, double dy = 0 ) :x{dx}, y{dy} {}
	auto operator+(const vec&v)const{
		return vec{ x + v.x, y + v.y }; 
	}
	auto& operator+=(const vec&v) {
		return *this = *this + v;
	}
	
	auto operator*(double d)const {
		return vec{ x*d,y*d };
	}
	auto& operator*=(double d) {
		*this = *this*d;
		return *this;
	}

	auto operator*(const vec&v)const {
		return vec{ x*v.x, y*v.y };
	}
	auto& operator*=(const vec&v) {
		return *this = *this * v;
	}

	auto operator-(const vec&v)const {
		return vec{ x - v.x, y - v.y };
	}
	auto& operator-=(const vec&v) {
		return *this = *this - v;
	}

	auto operator/(double d)const {
		assert(std::abs(d) > 0.000001);
			//std::assert();
		return vec{ x / d,y / d };
	}
	auto& operator/=(double d) {
		return *this = *this / d;
	}
	
	friend auto operator<<(std::ostream&os, const vec&v)->std::ostream& {
		return os << v.x << " " << v.y << "\n";
	}

	auto rotated(double rad)const{
		vec tmp{};
		tmp.x = (x*std::cos(rad) - y*std::sin(rad));
		tmp.y = (x*std::sin(rad) + y*std::cos(rad));
		return tmp;
	}

	auto& rotate(double rad) {
		return *this = rotated(rad);
	}
};


double tab[] = { 0,1/3,-1/3, 0 };

void koch(std::vector<vec> *const vp, int deg) {
	if (deg == 0)return;

	auto &v   = *vp;
	auto init = v.front();
	auto end  = v.back();
	auto unit = (end - init) / 3;
	auto mid  = (end - init) / 2;

	vec vtab[4]{ {}, unit,mid,unit * 2 };
	
	auto tmp  = std::move(v);v.clear();
	unsigned dn = deg * 4 - 3;
	if(v.capacity()<dn )
		v.reserve(deg * 4 - 3);

	for (auto&e : tmp) {
		e /= 3;
	}
	auto up = tmp; //tmp.pop_back();
	auto down = tmp;
	auto tmp2 = tmp;

	auto b = tmp.back();
	for (auto&e : up) {
		e.rotate( 1.0 / 3 * pi);
		e += b;
	}b = up.back();
	
	for (auto&e : down) {
		e.rotate(-1.0 / 3 * pi);
		e += b;
	}b = down.back();
	
	for (auto&e : tmp2) {
		e += b;
	}


	std::vector<std::vector<vec>*> vps{ &tmp,&up,&down,&tmp2 };

	for (unsigned int i{}; i < 4; i++) {
		auto& here = *vps[i];
		//std::cout << here.size();
		v.insert(std::end(v), std::begin(here), std::end(here)-1);
	}
	v.push_back(end);
	/*
	auto p = init;

	std::cout << p;

	p += unit.rotated(0);
	std::cout << p;
	
	p += unit.rotated(pi / 3);
	std::cout << p;

	p += unit.rotated( -1*pi/3 );
	std::cout << p ;

	p += unit.rotated( 0 );// .rotated(pi / 3);
	std::cout << p;
	*/
}


void rec(const vec&a, const vec&b, int n) {
	if (n == 0)return;
	auto init = a;
	auto end = b;
	auto unit = (end-init)/3;

	auto s1 = init + unit;
	auto mid = s1 + unit.rotated( 1.0 / 3 * pi);
	auto s2 = s1 + unit;//mid + mid.rotated( 5.0 / 3 * pi);

	rec(init, s1 , n - 1);
	std::cout << s1;

	rec(s1  , mid, n - 1);
	std::cout << mid;
	
	rec(mid , s2 , n - 1);
	std::cout << s2;

	rec(s2  , end, n - 1);
}

int main() {
	int n;// = 1;
	std::cin >> n;
	std::cout << std::fixed << std::setprecision(5);

	std::cout << vec{ 0,0 };
	rec({ 0,0 }, { 100,0 }, n);
	std::cout << vec{ 100,0 };

/*
	std::vector<vec> v{ {0, 0}, {100,0}};
	for (int i{}; i < n; i++) {
		koch(&v, n);
	}
	for (const auto&e : v) {
		std::cout << e;
	}
*/

	return 0;
}