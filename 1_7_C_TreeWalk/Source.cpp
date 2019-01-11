
#include<iostream>
#include<memory>
#include<vector>

struct node{
	int id;
	int parent;
	int left, right;
	node(int id_,int parent_ = -1, int l_ = -1, int r_ = -1):
		id{id_}
		, parent{parent_}
		, left{ l_ }
		, right{r_}{}


	node() : id{}, parent{-1}, left{}, right{}{}

	friend
	std::istream& operator>>(std::istream&is, node&n) {
		return is >> n.id >> n.left >> n.right;
	}

	friend
		std::ostream& operator<<(std::ostream&os, const node&n) {
		return os << n.id << n.left << n.right;
	}
};

auto pre_order(const std::vector<node>& v,int index)->void {
	if (index == -1)
		return;

	auto& here = v[index];
	std::cout << " " << v[index].id;
	pre_order(v, here.left);
	pre_order(v, here.right);
}

auto in_order(const std::vector<node>& v, int index)->void {
	if (index == -1)
		return;
	
	auto& here = v[index];
	in_order(v, here.left);
	std::cout << " " << v[index].id;
	in_order(v, here.right);

}

auto post_order(const std::vector<node>& v, int index)->void {

	if (index == -1)
		return;
	auto& here = v[index];
	post_order(v, here.left);
	post_order(v, here.right);
	std::cout << " " << v[index].id;
}

int main(){
	int n;
	std::cin >> n;
	std::vector<node> tree;
	tree.resize(n);

	for (int i{}; i < n; ++i) {
		int id;
		std::cin >> id; //tree[i];

		tree[id].id = id;
		std::cin >> tree[id].left >> tree[id].right;

//		std::cout << tree[id]<<"\n";

		if(tree[id].left != -1)
			tree[tree[id].left].parent = id;

		if (tree[id].right != -1)
			tree[tree[id].right].parent = id;
	}
	
/*	for (auto&e : tree) 
		std::cout << e << " parent = " <<e.parent<< "\n";
	*/

	auto root_i = 0;
	for (int i{}; i < n; ++i) {
		if (tree[i].parent == -1) {
			root_i = i;
			break;
		}
	}
//	std::cout << "ROOT = " << root_i<<"\n";


	std::cout << "Preorder\n";
	pre_order(tree, root_i);
	std::cout << "\n";


	std::cout << "Inorder\n";
	in_order(tree, root_i);
	std::cout << "\n";


	std::cout << "Postorder\n";
	post_order(tree, root_i);
	std::cout << "\n";
}
