#include "Graph.h"
#include <queue>
#include "qinputdialog.h"

int Graph::FordFulkerson(int source, int sink)
{
	int maxFlow = 0;
	std::vector<int> parent(m_nodes.size(), -1);
	ClearFlow();

	while (FindAugmentingPath(source, sink, parent)) {
		int minCapacity = INT_MAX;
		int v = sink;

		while (v != source) {
			int u = parent[v];
			for (Arch& arch : m_arches[u]) {
				if (arch.GetNodeTo() == v) {
					minCapacity = std::min(minCapacity, arch.UpdateMinCapacity(minCapacity));
					//break;
				}
			}
			v = u;
		}

		v = sink;
		while (v != source) {
			int u = parent[v];
			for (Arch& arch : m_arches[u]) {
				if (arch.GetNodeTo() == v) {
					arch.UpdateFlow(minCapacity);
					for (Arch& reverseArch : m_arches[v]) {
						if (reverseArch.GetNodeTo() == u) {
							reverseArch.UpdateFlow(-minCapacity);
							//break;
						}
					}
					//break;
				}
			}
			v = u;
		}

		maxFlow += minCapacity;
	}

	return maxFlow;
}

void Graph::CalculateMinCut(int source, int sink)
{
	std::vector<bool> reachable(m_nodes.size(), false);
	FindReachableNodes(source, reachable);

	std::vector<Arch> minCut;
	for (int u = 0; u < m_nodes.size(); ++u) {
		for (const Arch& arch : m_arches[u]) {
			int v = arch.GetNodeTo();
			if (reachable[u] && !reachable[v] && arch.GetCapacity() > 0) {
				minCut.push_back(arch);
			}
		}
	}

	m_minCut = std::move(minCut);

}

void Graph::DrawArch(const QPoint& startCenter, const QPoint& endCenter, const QString& label, QPainter& p, bool emphasized = false)
{
	if (emphasized) {
		p.setBrush(QBrush(Qt::red));
		p.setPen(QPen(Qt::red));
	}
	else {
		p.setBrush(QBrush(Qt::black));
		p.setPen(QPen(Qt::black));

	}

	double angle = std::atan2((endCenter.y() - startCenter.y()), (endCenter.x() - startCenter.x()));

	const double arrowSize = 10;

	QPoint startBorder = startCenter + QPoint(cos(angle) * Node::kradius / 2, sin(angle) * Node::kradius / 2);
	QPoint endBorder = endCenter - QPoint(cos(angle) * (Node::kradius / 2 + arrowSize), sin(angle) * (Node::kradius / 2 + arrowSize));

	p.drawLine(startBorder, endBorder);

	QPolygon arrowHead;
	arrowHead << endCenter - QPoint(cos(angle) * Node::kradius / 2, sin(angle) * Node::kradius / 2)
		<< endCenter - QPoint(cos(angle + M_PI / 6) * arrowSize + cos(angle) * Node::kradius / 2,
			sin(angle + M_PI / 6) * arrowSize + sin(angle) * Node::kradius / 2)
		<< endCenter - QPoint(cos(angle - M_PI / 6) * arrowSize + cos(angle) * Node::kradius / 2,
			sin(angle - M_PI / 6) * arrowSize + sin(angle) * Node::kradius / 2);
	p.drawPolygon(arrowHead);

	QPointF midPoint = (startBorder + endBorder) / 2.0;

	double textOffset = 10;
	QPointF perpOffset(-sin(angle) * textOffset, cos(angle) * textOffset);

	midPoint += perpOffset;

	QFont font = p.font();
	QFontMetrics metrics(font);

	// Calculate the bounding rectangle for the label
	QRect textRect = metrics.boundingRect(label);
	textRect.moveCenter(midPoint.toPoint());

	// Draw a background rectangle behind the label
	QRect backgroundRect = textRect.adjusted(-5, -2, 5, 2);
	p.setBrush(QColor(255, 255, 255, 200));
	p.setPen(Qt::NoPen);
	p.drawRect(backgroundRect);

	p.setPen(Qt::black);
	p.drawText(textRect, Qt::AlignCenter, label);
	p.setBrush(QBrush(Qt::black));
}

void Graph::DrawArches(QPainter& p)
{
	for (auto& nodeGroup : m_arches) {
		const auto& [nodeIndex, archesGroup] = nodeGroup;
		const QPoint& firstNodeCoord = m_nodes[nodeIndex].GetCoordinates();
		for (auto& arch : archesGroup) {
			const QPoint& secondNodeCoord = m_nodes[arch.GetNodeTo()].GetCoordinates();
			const QString& archData = arch.GetArchData();
			DrawArch(firstNodeCoord, secondNodeCoord, archData, p);
		}
	}
}

void Graph::DrawEmphasizedArches(QPainter& p)
{
	for (const auto& arch : m_minCut.value()) {
		const QPoint& pointTo = m_nodes[arch.GetNodeTo()].GetCoordinates();
		const QPoint& pointFrom = m_nodes[arch.GetNodeFrom()].GetCoordinates();
		DrawArch(pointFrom, pointTo, arch.GetArchData(), p, true);
	}
}

void Graph::ClearFlow()
{
	for (auto& node : m_arches) {
		for (auto& arch : node.second) {
			arch.ResetFlow();
		}
	}
}

bool Graph::FindAugmentingPath(int source, int sink, std::vector<int>& parent)
{
	std::map<int, bool> visited;
	std::queue<int> q;
	q.push(source);
	visited[source] = true;
	parent[source] = -1;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (const Arch& arch : m_arches[u]) {
			int v = arch.GetNodeTo();
			if (!visited[v] && arch.HasPositiveResidualCapacity()) {
				parent[v] = u;
				visited[v] = true;
				q.push(v);
			}
		}
	}

	return visited[sink]; // Returnează true dacă am găsit un drum augmenting de la source la sink

}

void Graph::FindReachableNodes(int u, std::vector<bool>& reachable)
{
	reachable[u] = true;
	for (const Arch& arch : m_arches[u]) {
		int v = arch.GetNodeTo();
		if (!reachable[v] && (arch.GetCapacity() - arch.GetFlow()) > 0) {
			FindReachableNodes(v, reachable);
		}
	}
}

std::optional<int> Graph::NodeValueForCoordinate(QPoint point)
{
	for (const auto& node : m_nodes) {
		if (std::abs(node.second.GetCoordinates().x() - point.x()) <= Node::kradius
			&& std::abs(node.second.GetCoordinates().y() - point.y()) <= Node::kradius)
			return node.first;
	}
	return std::nullopt;
}

Graph::Graph():
	m_minCut(std::nullopt)
{
}

void Graph::AddNode(QPoint point)
{
	if (NodeValueForCoordinate(point) == std::nullopt)
		m_nodes.emplace(m_nodes.size(), Node(point, m_nodes.size()));
}

void Graph::AddArch(QPoint p1, QPoint p2)
{
	std::optional<int> pointFrom = NodeValueForCoordinate(p1);
	std::optional<int> pointTo = NodeValueForCoordinate(p2);
	if (pointFrom == std::nullopt)
		return;
	if (pointTo == std::nullopt)
		return;
	bool ok;
	int inputValue = QInputDialog::getInt(nullptr, "Input Dialog", "Enter an integer:", 0, -1000, 1000, 1, &ok);

	if (ok) {
		m_arches[pointFrom.value()].emplace_back(Arch(pointFrom.value(), pointTo.value(), inputValue));
	}
}

void Graph::DrawGraph(QPainter& p)
{
	DrawArches(p);

	if(m_minCut != std::nullopt)
		DrawEmphasizedArches(p);

	for (auto& node : m_nodes) {
		node.second.DrawNode(p);
	}
}
