#include "Node.h"

Node::Node(QPoint p, int value): m_coord(p), m_name(QString::number(value))
{
	// empty
}

QPoint Node::GetCoordinates() const
{
	return m_coord;
}

QString Node::GetName() const
{
	return m_name;
}

void Node::SetCoordinates(const QPoint& p)
{
	m_coord = p;
}

void Node::DrawNode(QPainter& p)
{
	p.setBrush(QBrush(Qt::white));
	QRect r(GetCoordinates().x() - Node::kradius / 2, GetCoordinates().y() - Node::kradius / 2, Node::kradius, Node::kradius);
	p.drawEllipse(r);
	p.drawText(r, Qt::AlignCenter, GetName());
	p.setPen(QPen(Qt::black));
}
