#include "LBotTree.h"

#include "LBoard.h"
#include "LPath.h"

LBotTree::LBotTree()
	:
	pParent(nullptr),
	pChilds(),
	pBoard(nullptr),
	pPath(nullptr),
	value(0),
	number(0),
	_isClean(true)
{

}

LBotTree::LBotTree(LBotTree* parent, LBoard* board, LPath* path, int value, int number)
	:
	pParent(parent),
	pChilds(),
	pBoard(nullptr),
	pPath(path),
	value(0),
	number(number),
	_isClean(true)
{
	LBoard* tempBoard = board;
	tempBoard->completePath(path);
	this->pBoard = tempBoard;
	this->setValue(value);
}

LBotTree::~LBotTree()
{
	this->clear();
}

LBotTree* LBotTree::addChild(LBoard* board, LPath* path, int value)
{
	int number = this->pChilds.size();

	LBotTree* pChild = new LBotTree(this, board, path, value, number);

	this->pChilds.push_back(pChild);

	if (this->_isClean)
	{
		this->_isClean = false;
	}

	return pChild;
}

int LBotTree::getSize() const
{
	return this->pChilds.size();
}

LBotTree* LBotTree::operator [] (int index) const
{
	LBotTree* temp = nullptr;

	if (!this->_isClean)
	{
		temp = this->pChilds[index];
	}

	return temp;
}

LBoard* LBotTree::getBoard() const
{
	return this->pBoard;
}

LPath* LBotTree::getPath() const
{
	return this->pPath;
}

int LBotTree::getValue() const
{
	return this->value;
}

bool LBotTree::isClean() const
{
	return this->_isClean;
}

void LBotTree::setValue(int value)
{
	this->value += value;

	if (this->pParent)
	{
		this->pParent->setValue(value);
	}
}

void LBotTree::clear()
{
	int size = this->pChilds.size();

	for (int i = 0; i < size; i++)
	{
		this->pChilds[i]->clear();
		delete this->pChilds[i];
	}

	delete this->pPath;

	this->pChilds.clear();
	this->pPath = nullptr;
	this->value = 0;
	this->number = 0;
	this->_isClean = true;
}
