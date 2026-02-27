#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QInputDialog>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    int radius = 15;

    for (auto edge : m_graph.getEdges())
    {
        Node* first = edge->getFirst();
        Node* second = edge->getSecond();

        double dx = second->getX() - first->getX();
        double dy = second->getY() - first->getY();
        double angle = atan2(dy, dx);

        QPointF p1(first->getX() + radius * cos(angle), first->getY() + radius * sin(angle));
        QPointF p2(second->getX() - radius * cos(angle), second->getY() - radius * sin(angle));

        if (edge->getIsMinCut())
            p.setPen(QPen(Qt::red, 3));
        else
            p.setPen(QPen(Qt::white, 2));


        p.drawLine(p1, p2);

        int arrowSize = 10;
        QPointF arrow1 = p2 - QPointF(arrowSize * cos(angle - M_PI / 6), arrowSize * sin(angle - M_PI / 6));
        QPointF arrow2 = p2 - QPointF(arrowSize * cos(angle + M_PI / 6), arrowSize * sin(angle + M_PI / 6));
        p.drawLine(p2, arrow1);
        p.drawLine(p2, arrow2);

        QPointF mid = (p1 + p2) / 2;
        QString label = QString("R:%1 | F:%2").arg(edge->getResidualCapacity()).arg(edge->getFlow());
        p.setPen(Qt::blue);
        p.drawText(mid + QPointF(10, -10), label);
    }

    for (auto node : m_graph.getNodes())
    {
        p.setPen(QPen(Qt::black, 2));
        p.setBrush(node == m_firstNode ? Qt::yellow : Qt::white);

        if (!m_graph.getNodes().empty())
        {
            if (node == m_graph.getNodes().front()) p.setBrush(Qt::green);
            if (node == m_graph.getNodes().back()) p.setBrush(Qt::cyan);
        }

        QRect r(node->getX() - radius, node->getY() - radius, 2*radius, 2*radius);
        p.drawEllipse(r);
        p.drawText(r, Qt::AlignCenter, QString::number(node->getIndex()));
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::RightButton)
    {
        if (m_dragged)
        {
            m_dragged = false;
            m_draggedNode = nullptr;
        }
        else
        {
            m_graph.addNode(new Node(m_graph.getNodes().size()+1, ev->pos()));
            m_firstNode = nullptr;
            update();
        }
        return;
    }

    if (ev->button() == Qt::LeftButton)
    {
        if (m_dragged)
        {
            m_dragged = false;
            m_draggedNode = nullptr;
            return;
        }

        std::vector<Node*> nodes = m_graph.getNodes();
        Node* selected = nullptr;

        for (auto node : nodes)
        {
            if (abs(ev->pos().x() - node->getX()) < 10 && abs(ev->pos().y() - node->getY()) < 10)
            {
                selected = node;
                break;
            }
        }

        if (!selected)
            return;

        if (!m_firstNode)
        {
            m_firstNode = selected;
        }
        else
        {
            if (m_firstNode != selected)
            {
                bool ok;
                double cost = QInputDialog::getDouble(this, "Cost muchie:", "Introduceti costul muchiei:",1,1,1000000,0, &ok);
                if(ok)
                {
                    m_graph.addEdge(m_firstNode, selected, cost);
                    for(auto edge : m_graph.getEdges())
                        edge->setIsMinCut(false);
                }
            }
            m_firstNode = nullptr;
            update();
        }
        return;
    }

    m_firstNode = nullptr;
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::RightButton)
    {
        for (auto node : m_graph.getNodes())
        {
            if (abs(ev->pos().x() - node->getX()) < 30 && abs(ev->pos().y() - node->getY()) < 30)
            {
                m_dragged = true;
                m_draggedNode = node;
                return;
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    if (m_dragged && m_draggedNode)
    {
        QPoint newPos = ev->pos();
        bool ok = true;

        for (auto node : m_graph.getNodes())
        {
            if (node == m_draggedNode)
                continue;
            int dx = newPos.x() - node->getX();
            int dy = newPos.y() - node->getY();
            if (std::sqrt(dx*dx + dy*dy) < 20)
            {
                ok = false;
                break;
            }
        }

        if (ok)
        {
            m_draggedNode->setCoord(newPos);
            update();
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if (m_graph.getNodes().size() < 2) return;

    Node* source = m_graph.getNodes().front();
    Node* sink = m_graph.getNodes().back();

    if (ev->key() == Qt::Key_Space)
    {
        double addedFlow = m_graph.updateMaxFlow(source, sink);
        if (addedFlow <= 0)
            m_graph.calculateMinCut(source);
        else
            m_totalMaxFlow += addedFlow;
        setWindowTitle(QString("Flux Maxim Total: %1").arg(m_totalMaxFlow));
        update();
    }

    if (ev->key() == Qt::Key_R)
    {
        m_graph.resetFlow();
        update();
    }
}
