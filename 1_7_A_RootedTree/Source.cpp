
#include<iostream>
#include<vector>
#include<utility>
#include<memory>

class node {
	std::unique_ptr<node> np;
	int id_;

public:
	using leaf_list_t = std::vector<int>;

private:
	leaf_list_t  clist;

public:
	node(int _id, node*np_, const std::vector<int>&v) :id_{ _id }, np{np_}, clist{ v }{}
	node(int _id, node*np_, std::vector<int>&& v) :id_{ _id }, np{ np_ }, clist{ std::move(v) }{}
	auto id()const { return id_; }
	auto is_root()const { return np == nullptr; }
	auto is_leaf()const { return clist.empty(); }
	auto is_internode()const { return !( is_root() || is_leaf()  ); }
};


class tree {
	std::vector<node> v;
public:
	using node_t = node;
	tree() {}
	tree(int size_) :v{size_} {}
	auto push(const node&n) { v.push_back(n); }
	auto push(node&&n) { v.push_back(std::move(n)); }

};

int main() {

	std::vector<std::vector<int>>v;

	int tree_size{};
	std::cin >> tree_size;
	v.resize(tree_size);

	for (auto&e:v) {
		int id{}, k{};
		std::cin >> id >> k;
		e.resize(k+2);
		e[0] = id; e[1] = k;

		for (int i{ 2 }; i < e.size(); ++i)
			std::cin >> e[i];
	}

	for (int i{}; i < tree_size;++i) {
		auto&e = v[i];
		std::cout << "node " << e[0] << ": ";
		for (int j{}; j < tree_size; ++j) {
			if (i == j)continue;
			auto&ej = v[j];
			auto en = std::end(ej);
 			auto exist = 
				en != std::find(std::begin(ej),en, e[0]);
			
			std::cout << "parent = "
				<< (exist ? ej[0] : -1) << ", ";

			std::cout << "depth = "
				<< (!exist ? 0 : [&]() {
					int depth = 0;
					for (const auto&ee : e) {

					}
				}())
				<< ", ";
		}
		//for (auto&ee : e)
		//	std::cout << ee << " ";
		//std::cout << "\n";
	}


	return 0;
}