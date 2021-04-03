#pragma once

struct treeNode
{
	char ch;
	treeNode* lchild;
	treeNode* rchild;
	treeNode() :ch('\0'), lchild(nullptr), rchild(nullptr) {}
	treeNode(char c) :ch(c), lchild(nullptr), rchild(nullptr) {}
	treeNode(char c, treeNode* lc, treeNode* rc) :ch(c), lchild(lc), rchild(rc) {}
	~treeNode() = default;
};

