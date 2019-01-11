
#include<iostream>
#include<vector>
#include<algorithm>

struct node {
	int id, parent;
	int children[2];
	int deg, depth, height;

	node() :id{ -1 }, parent{ -1 }
		, children{ -1 }
		, deg{0}
		, depth{ 0 }
		, height{ 0 }
	{}
};

void set_depth(std::vector<node>*const tp, int index ) {
	auto& tree = *tp;
	for (int i{}; i < 2; i++) {
		auto x = tree[index].children[i];
		if (x == -1)continue;
		tree[x].depth = tree[index].depth + 1;
		set_depth(tp, tree[x].id);
	}
}

int get_height(std::vector<node>*const tp,int index) {
	auto& tree = *tp;
	auto& here = tree[index];
	return  here.deg == 0 ?
		0 :
		std::max(
			get_height(tp, here.children[0])
			, get_height(tp, here.children[1])
		) + 1;
}

int main() {
	int n;
	std::cin >> n;
	std::vector<node> bt;
	bt.resize(n);
//	std::cout <<"size = "<< bt.size() << "\n";

	for (int i{}; i < n; ++i) {
		int index;
		std::cin >> index;
		
		auto& nd = bt[index];
		auto& chd = nd.children;
		nd.id = index;
		std::cin >> chd[0] >> chd[1];
		
		if (chd[0] != -1)
			bt[chd[0]].parent = index;
		if(chd[1] != -1)
			bt[chd[1]].parent = index;

		nd.deg = (chd[0] == -1 ? 0:1)
			+ (chd[1] == -1 ? 0:1);

		if (nd.deg == 0)
			nd.height = 0;
	}
	/*
	for (const auto&e : bt) {
		std::cout << e.id << " " << e.deg<<" "<<e.parent << "\n";
	}*/

	int root_id{ 0 };
	while (bt[root_id].parent != -1)
		++root_id;


	set_depth(&bt, root_id);

	for (int i{}; i < n; ++i) {
		bt[i].height = get_height(&bt, i);
	}

	for (auto&e : bt) {
		std::cout << "node " << e.id << ": ";
		std::cout << "parent = " << e.parent << ", ";
		std::cout << "sibling = " <<
			[&]()->int {
			if (e.parent == -1)
				return -1;//親がいないならsiblingはいない


			auto& pair = bt[e.parent].children;
			//自分と異なるsiblingをreturn
			return pair[pair[0] == e.id ? 1 : 0];
		}();
		std::cout << ", ";


		std::cout << "degree = " << e.deg << ", ";
		std::cout << "depth = " << e.depth << ", ";
		std::cout << "height = " << e.height << ", ";
		std::cout << (e.parent==-1?"root":e.deg==0?"leaf":"internal node")<<"\n";
	}

	return 0;
}
