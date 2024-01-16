#pragma once
#include "Node.h"
#include "Arch.h"
#include <map>

class Graph
{
	std::map<int, Node> m_nodes;
	std::map<int, std::vector<Arch>> m_arches;

	int FordFulkerson(int source, int sink);

	std::vector<Arch> CalculateMinCut(int source, int sink);

private:
	void DrawArch(const QPoint& firstNode, const QPoint& secondNode, const QString& data, QPainter& p);

	void DrawArches(QPainter& p);

	bool FindAugmentingPath(int source, int sink, std::vector<int>& parent);

	void FindReachableNodes(int u, std::vector<bool>& reachable);


public:
	Graph() = default;

	void AddNode(QPoint point, int value);

	void DrawGraph(QPainter& p);

};

