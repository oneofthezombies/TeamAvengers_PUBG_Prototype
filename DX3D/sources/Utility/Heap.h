#pragma once

class AStarNode;

class Heap
{
public:
	vector<AStarNode*> m_vecNode;

	Heap();
	~Heap();

	void Insert(AStarNode* pNode);
	AStarNode* ExtractMin();
	void Clear();
private:
	void Upheap(int targetIdx);
	void DownHeap(int targetIdx);
	void Swap(int idx1, int idx2);
};

