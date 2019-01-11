
#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>

struct node {

	int index;
	int depth;
	int parent;
	std::vector<int> id_list;
	node() :index{ -1 }, depth{ 0 }, parent{-1}, id_list{}{}
};


void set_depth(std::vector<node>*const list_, int index) {
	auto&ref = *list_;
	for (auto e : ref[index].id_list) {
//		std::cout << index << "\n";
/*		auto it = std::find_if(std::begin(ref), std::end(ref)
			, [=](auto&x) {return x.index == e; }
		);

		if (it != std::end(ref)) {
			it->depth = ref[index].depth + 1;
			set_depth(list_, it->index);
		}*/

		//more faster
		ref[e].depth += ref[index].depth + 1;
		set_depth(list_, ref[e].index);
	}

}


int main() {
	int n;
	std::cin >> n;

	std::vector<node> tree;
	tree.resize(n);


	for (int i{}; i < n;++i) {
		int index_;
		std::cin >> index_;
		tree[index_].index = index_;

		int size_;
		std::cin >> size_;
		tree[index_].id_list.resize(size_);
		
//		std::cout << index_<<" "<<size_<<" ";
		for (auto& ce : tree[index_].id_list) {
			std::cin >> ce;
			tree[ce].parent = index_;
//			std::cout << ce << " ";
		}//std::cout << "\n";
	}

	/*
	for (auto&e : tree) {
		std::cout << e.index<<" "<<e.id_list.size() << "\n";
	}*/

	int root_id{};
	for (int i{}; i < n; ++i) {
		if (tree[i].parent == -1) {
			root_id = i;
//			std::cout << i << "\n";
			break;
		}
	}
//	std::cout << root_id << "\n";
	set_depth(&tree, root_id);

	for (const auto&e : tree) {
		std::cout << "node " << e.index << ": ";
		std::cout << "parent = " << e.parent<<", ";
		std::cout << "depth = " << e.depth << ", ";
		std::cout << (e.parent == -1 ? "root"
			: e.id_list.empty() ? "leaf" : "internal node") << ", ";

		std::cout << "[";
		if (!e.id_list.empty()) {
			std::cout << e.id_list[0];
			if (e.id_list.size() != 1)
				for (unsigned i{ 1 }; i < e.id_list.size(); ++i)
					std::cout << ", " << e.id_list[i];
		}
		std::cout << "]\n";

	}
	return 0; 
}
