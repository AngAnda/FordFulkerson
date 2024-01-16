#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FordFulkerson.h"
#include "Graph.h"

class FordFulkerson : public QMainWindow
{
    Q_OBJECT

public:
    FordFulkerson(QWidget *parent = nullptr);
    ~FordFulkerson();

    void paintEvent(QPaintEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void Algorithm();

private:
    Ui::FordFulkersonClass ui;
    std::pair<std::optional<QPoint>, std::optional<QPoint>> m_archesManagement;

    Graph g;
};
