#pragma once

#include <QVector>

class LBoard;
class LPath;

class LBotTree
{
private:
	LBotTree* pParent;
	QVector<LBotTree*> pChilds;
	LBoard* pBoard;
	LPath* pPath;
	int value;
	int number;
	bool _isClean;

	void setValue(int value);

public:

	LBotTree();
	LBotTree(LBotTree* parent, LBoard* board, LPath* path, int value, int number);
	~LBotTree();

	LBotTree* addChild(LBoard* board, LPath* pPath, int value);

	int getSize() const;
	LBotTree* operator [] (int index) const;
	LBoard* getBoard() const;
	LPath* getPath() const;
	int getValue() const;
	bool isClean() const;

	void clear();

};
