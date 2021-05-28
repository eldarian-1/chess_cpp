#pragma once

class QJsonObject;
class QString;

class LPlayer;
class LSquare;

class LPath
{
private:
	static LSquare* nullSquare;

	LPlayer* playerActive;
	LPlayer* playerPassive;
	LSquare*& from;
	LSquare*& to;
	int _isPossible;

public:
	LPath(
		LSquare*& from = nullSquare,
		LSquare*& to = nullSquare
	);

	LPath(
		LPlayer* act = nullptr,
		LPlayer* pass = nullptr,
		LSquare*& from = nullSquare,
		LSquare*& to = nullSquare
	);

	LPath(const LPath& path);

	~LPath();

	static LPath* pathFromJson(QJsonObject* document);

	LPath* getClone() const;

	QString toUriString() const;
	QString toJsonString() const;

	LPlayer* getActive() const;
	LPlayer* getPassive() const;
	LSquare*& getFrom() const;
	LSquare*& getTo() const;
	int isPossible() const;

	void setActive(LPlayer* active);
	void setPassive(LPlayer* passive);
	void setPossible(int isPossible);

	void clear();

};
