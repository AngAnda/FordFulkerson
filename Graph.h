#pragma once
#include "Node.h"
#include "Arch.h"
#include <map>

class Graph
{
	std::map<int, Node> m_nodes;

	std::map<int, std::vector<Arch>> m_arches;

	std::optional<std::vector<Arch>> m_minCut;

private:
	void DrawArch(const QPoint& firstNode, const QPoint& secondNode, const QString& data, QPainter& p, bool emphasized);

	void DrawArches(QPainter& p);

	void DrawEmphasizedArches(QPainter& p);

	void ClearFlow();

	bool FindAugmentingPath(int source, int sink, std::vector<int>& parent);

	void FindReachableNodes(int u, std::vector<bool>& reachable);

	std::optional<int> NodeValueForCoordinate(QPoint point);

public:

	int FordFulkerson(int source, int sink);

	void CalculateMinCut(int source, int sink);

	int m_sinkIndex;
	int m_startIndex;

	Graph();

	void AddNode(QPoint point);

	void AddArch(QPoint p1, QPoint p2);

	void DrawGraph(QPainter& p);

};


