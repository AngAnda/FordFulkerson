#pragma once
#include <qpoint.h>
#include <qstring.h>
#include <QPainter>
#include <qbrush.h>

class Node
{
public:
	const static int kradius = 10;

	Node() = default;

	Node(QPoint p, int value);

	QPoint GetCoordinates() const;

	QString GetName() const;

	void SetCoordinates(const QPoint& p);

	void DrawNode( QPainter& p);

private:
	QPoint m_coord;
	QString m_name;

};

