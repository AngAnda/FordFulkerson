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

private:
    Ui::FordFulkersonClass ui;
    Graph g;
};
