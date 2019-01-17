
#include<iostream>
#include<string>
#include<vector>
#include<memory>

template<class T>
struct node {
	T key;
	node* parent;
	std::unique_ptr<node<T>> left, right;
	bool valid_;


	bool nil()const {
		return !valid_;
	}

	bool valid()const {
		return valid_;
	}

	void validate() {
		valid_ = true;
	}

	void invalidate() {
		this->valid_ = false;
	}

	node() :key{}
		, parent{ nullptr }
		, left{ nullptr }
		, right{ nullptr }
		, valid_{ false }
	{}

	template<class X>
	node(X&&t) :key{ t }
		, parent{ nullptr }
		, left{ nullptr }
		, right{ nullptr }
		, valid_{ false }
	{}

};



template<class T>
void inorder(const node<T>* const root) {
	if (root == nullptr)
		return;

	inorder(root->left.get());
	std::cout << " " << root->key;
	inorder(root->right.get());
}

template<class T>
void preorder(const node<T>* const root) {
	if (root == nullptr)
		return;

	std::cout << " " << root->key;
	preorder(root->left.get());
	preorder(root->right.get());
}


template<class T>
void print(const node<T>*const root) {
	inorder(root);
	std::cout << "\n";
	preorder(root);
	std::cout << "\n";
}


template<class T>
void insert(node<T>* root, const T&value_) {
	decltype(root) parent = nullptr;
	decltype(root) here = root;

	auto z = std::make_unique<node<T>>(value_);
	z->validate();

	//値が最も近い、有効なノード(parent)へ移動
	while (here != nullptr && here->valid()) {
		parent = here;
		//		std::cout << here->key << " ";

		if (z->key < here->key) {
			here = here->left.get();
			//			std::cout << "> ";
		}
		else {
			here = here->right.get();
			//			std::cout << "< ";
		}
		//		std::cout << value_ << "\n";
	}

	//zはparentの left か right になる
	z->parent = parent;

	auto& up
		= z->key < parent->key ?
		parent->left
		: parent->right;

	up = std::move(z);

}

template<class T>
auto find(node<T>* root, const T& value_)->node<T>* {
	if (root == nullptr)
		return nullptr;

	if (root->key == value_)
		return root;

	auto& child = value_ < root->key ? root->left : root->right;
	return find(child.get(), value_);

}


template<class T>
auto& which(node<T>*np) {
	return  np->left  ? np->left : np->right;
}

template<class T>
auto& which(node<T>*np,const T&key) {
	return np->left->key == key
		? np->left : np->right;
}


template<class T>
auto del(node<T>*node) {
	auto lb = !!node->left;
	auto rb = !!node->right;

	auto chs = (lb ? 1 : 0) + (rb ? 1 : 0);

	auto& p = node->parent;
	if(node->parent != nullptr)
	if (chs == 0) {
		/*
		auto&dying = p->left->key == node->key
			? p->left : p->right;
		dying.reset();
		*/
		//親のLとRでKeyが同じほうを消去
//		std::cout << "chs == 0\n";
		if (p->left && p->right)
			which(p, node->key).reset();
		else
			(p->left && !p->right ? p->left : p->right).reset();
	}
	else if (chs == 1) {

		//std::cout << "chs == 1\n";

		//どちらかだけ有効、もう一方はnullptr
		//childの親を書き換え
		auto&child = which(node);
		auto& cp = child->parent;
		//parentのchildを書き換え
		cp = node->parent;

		/*
		auto& p = child->parent;
		p->left->key == node->key
			? p->left : p->right
			= std::move(child);*/
		
		/*
		std::cout << "node " << node->key << "\n";
		std::cout <<"node->parent "<< child->parent->key << "\n";
		std::cout <<"node->child "<< child->key << "\n";
		*/

		//少なくとも一方はnode自身であるので有効なはず。
		//両方とも有効ならnode->keyが同じほう(つまりnode)を、
		//一方のみ有効なら有効な方(つまりnode)にchildをmove
		/*
		if(cp->left == nullptr){
			std::cout << "cp->left == null\n";
		}
		if (cp->right == nullptr) {
			std::cout << "cp->right == null\n";
		}
		*/
		/*
		if (cp->left && cp->right) {
			std::cout <<"LR "<< cp->left->key << " " << cp->right->key << "\n";
			std::cout << "this is me >> "<<which(cp, node->key)->key << "\n";
		}*/

		auto& dying_node = cp->left && cp->right ?
			which(cp, node->key)
			: cp->left != nullptr ?
			cp->left : cp->right;

		//std::cout <<"dying "<< dying_node->key << "\n";
		dying_node = std::move(child);
		/*
		if (cp->left && cp->right) {
			std::cout << "LR " << cp->left->key << " " << cp->right->key << "\n";
			//std::cout << "this is me >> " << which(cp, node->key)->key << "\n";
		}*/
		
	}
	else {
	//	node->key<p->key
//		std::cout << "chs == 2\n";

		//first <- child, second <- successor
		auto& nl = node->left;
		auto& nr = node->right;
		auto b = node->key < node->parent->key;


//		std::cout << "nl->key " << nl->key << "\n";
//		std::cout << "nr->key " << nr->key << "\n";

//		std::cout <<"comp node vs node->parent "<<
//			node->key << " " << node->parent->key << "\n";

		auto& child = b ? nr : nl;

//		std::cout << "child " << child->key << "\n";

		
//		std::cout << "suc is " << (b ? "nl" : "nr") << " side\n";
		auto& suc = b ?
			(nl->right != nullptr ? nl->right : nl)
			: (nr->left != nullptr ? nr->left : nr);

//		std::cout << "nr->left->key " << nr->left->key << "\n";
//		std::cout << "succ " << suc->key<<"\n";


		//link switch ver
		//消えるノードの親と子を後継者に渡す。
		//親を渡す
		/*
		suc->parent = node->parent;

		//消えるノードの2つの子のうち、後継者にならないほうは、後継者の子となる
		(b ? suc->left : suc->right) = std::move(child);

		//子を渡す
		which(node->parent,node->key) = std::move(suc);
		*/

		// こっちでもいい。けどkeyの=が高コストな時は良くないだろう。
		// assignment ver

		node->key = suc->key;
		suc.reset();
		
	}

}

int main() {
	int n;
	std::cin >> n;

	//	std::vector<node<int>> tree;
	//	tree.emplace_back(node<int>{});
	std::unique_ptr<node<int>> root{ nullptr };


	for (int i{}; i < n; ++i) {
		std::string s;
		std::cin >> s;
		if (s == "insert") {
			int k;
			std::cin >> k;
			if (!root) {
				root = std::make_unique<node<int>>(k);
				root->validate();
			}
			else
				insert(root.get(), k);
		}
		else if (s == "find") {
			int k;
			std::cin >> k;
			std::cout << (find(root.get(), k) ? "yes" : "no") << "\n";
		}
		else if (s == "delete") {
			int k;
			std::cin >> k;
			auto*p = find(root.get(), k);
			/*if (p == nullptr) {
				std::cout << ">>>>  error\n";
			}
			else*/
				del(p);
		}
		else
			print(root.get());
	}

	return 0;
}
