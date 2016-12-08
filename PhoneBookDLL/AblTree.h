#pragma once

#define K_64 65536
#define NODE_INDEX long long

template<class T>
class AblTree
{
	struct node // структура для представления узлов дерева
	{
		T key;
		NODE_INDEX left;
		NODE_INDEX right;
		node(T k, int block)
		{
			init(k, block);
		}
		void init(T k, NODE_INDEX block)
		{
			block_ = block; key = k; left = right = -1; height = 1;
		}
		NODE_INDEX block_;
		int height;
		char reverced[26];
	};

	int height(NODE_INDEX p)
	{
		if (p == -1)
			return 0;
		std::pair<node*, node*> map;
		getMap(map, p);
		int result = map.second->height;
		clearMap(map.first);
		return result;
	}

	int bfactor(NODE_INDEX p)
	{
		std::pair<node*, node*> map;
		getMap(map, p);
		int result = height(map.second->right) - height(map.second->left);
		clearMap(map.first);
		return result;
	}

	void fixheight(node* p)
	{
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	NODE_INDEX rotateright(NODE_INDEX p) // правый поворот вокруг p
	{
		std::pair<node*, node*> map_x, map_y;
		getMap(map_x, p);
		NODE_INDEX q = map_x.second->left;
		getMap(map_y, q);
		map_x.second->left = map_y.second->right;
		map_y.second->right = map_x.second->block_;
		fixheight(map_x.second);
		fixheight(map_y.second);
		clearMap(map_y.first);
		clearMap(map_x.first);
		return q;
	}

	NODE_INDEX rotateleft(NODE_INDEX q) // левый поворот вокруг q
	{
		std::pair<node*, node*> map_y, map_x;
		getMap(map_y, q);
		NODE_INDEX p = map_y.second->right;
		getMap(map_x, p);
		map_y.second->right = map_x.second->left;
		map_x.second->left = q;
		fixheight(map_y.second);
		fixheight(map_x.second);
		clearMap(map_x.first);
		clearMap(map_y.first);
		return p;
	}

	NODE_INDEX balance(node* map) // балансировка узла p
	{
		fixheight(map);
		if (bfactor(map->block_) == 2)
		{
			if (bfactor(map->right) < 0)
				map->right = rotateright(map->right);
			return rotateleft(map->block_);
		}
		if (bfactor(map->block_) == -2)
		{
			if (bfactor(map->left) > 0)
				map->left = rotateleft(map->left);
			return rotateright(map->block_);
		}
		return map->block_; // балансировка не нужна
	}

	NODE_INDEX addNode(T k)
	{
		std::pair<node*, node*> map;
		getMap(map, freeBlock);
		map.second->init(k, freeBlock);
		clearMap(map.first);
		return freeBlock++;
	}

	static void clearMap(node *&node)
	{
		if (node)
			UnmapViewOfFile(node);
	}

public:
	void insert(T k)
	{
		insert(getHeadMap(), k);
	}

	AblTree(HANDLE fileHandler, const LARGE_INTEGER& file) :fileMapping(fileHandler), size(file), head(-1), freeBlock(0) {}

	NODE_INDEX findMinHead(T key)
	{
		return findmin(key, getHeadMap(), true);
	}

	NODE_INDEX findmin(T key, NODE_INDEX p, bool isStart) // поиск узла с минимальным ключом в дереве p 
	{
		if (p == -1)
			return p;

		std::pair<node*, node*> map;
		getMap(map, p);

		NODE_INDEX result;
		if (!isStart)
			result = findmin(key, map.second->right, true);
		else
		{
			result = map.second->key == key ? map.second->block_ : findmin(key,
				(map.second->key > key ? map.second->left : map.second->right), true);
		}
		clearMap(map.first);
		return result;
	}

private:
	NODE_INDEX insert(NODE_INDEX p, T k) // вставка ключа k в дерево с корнем p
	{
		NODE_INDEX result;
		if (p == -1)
		{
			result = addNode(k);
			if (head == -1)
				head = result;
		}
		else
		{
			std::pair<node*, node*> map;
			getMap(map, p);
			if (k < map.second->key)
				map.second->left = insert(map.second->left, k);
			else
				map.second->right = insert(map.second->right, k);
			result = balance(map.second);
			clearMap(map.first);
		}
		return result;
	}

	node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	node* remove(node* p, int k) // удаление ключа k из дерева p
	{
		if (!p) return 0;
		if (k < p->key)
			p->left = remove(p->left, k);
		else if (k > p->key)
			p->right = remove(p->right, k);
		else //  k == p->key 
		{
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

private:
	void getMap(std::pair<node*, node*>& node_, NODE_INDEX index)
	{
		node_.first = (node*)MapViewOfFile(fileMapping, FILE_MAP_READ | FILE_MAP_WRITE, (index * sizeof(struct node)) / (UINT)MAXDWORD,
			((index * sizeof(struct node)) % (UINT)MAXDWORD) / K_64, K_64);

		node_.second = node_.first + (((index * sizeof(struct node)) % (UINT)MAXDWORD) % K_64) / sizeof(struct node);
	}

	NODE_INDEX getHeadMap()
	{
		return head;
	}

	HANDLE fileMapping;
	LARGE_INTEGER size;
	NODE_INDEX head;
	int freeBlock;
};
