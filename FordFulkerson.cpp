#include "FordFulkerson.h"
#include <QMouseEvent>
#include <qmessagebox.h>

FordFulkerson::FordFulkerson(QWidget *parent)
    : QMainWindow(parent),
    m_archesManagement({std::nullopt, std::nullopt})
{
    ui.setupUi(this);
    QObject::connect(ui.pushButton, &QPushButton::clicked, this, &FordFulkerson::Algorithm);

}

FordFulkerson::~FordFulkerson()
{
}

void FordFulkerson::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    g.DrawGraph(p);
}

void FordFulkerson::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) 
    {
        g.AddNode(event->pos());
    }
    else 
    {
        auto& [firstPressed, secondPressed] = m_archesManagement;
       
        if (!firstPressed.has_value()) {
            firstPressed = event->pos();
        }
        else if (!secondPressed.has_value()) {
            secondPressed = event->pos();
        }
        else {
            firstPressed = secondPressed.value();
            secondPressed = this->pos();
        }

        if (firstPressed != std::nullopt && secondPressed != std::nullopt) {
            g.AddArch(firstPressed.value(), secondPressed.value());
            firstPressed = secondPressed.value();
            secondPressed = event->pos();
            m_archesManagement = std::make_pair(std::nullopt, std::nullopt);
        }

    }
    update();
}

void FordFulkerson::Algorithm()
{
    int result = g.FordFulkerson(ui.lineEdit->text().toInt(), ui.lineEdit_2->text().toInt());
    g.CalculateMinCut(ui.lineEdit->text().toInt(), ui.lineEdit_2->text().toInt());
   
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Result:");
    msgBox.setInformativeText(QString::number(result));

    // Add an "OK" button to close the message box
    msgBox.addButton(QMessageBox::Ok);

    // Show the message box
    msgBox.exec();
}
