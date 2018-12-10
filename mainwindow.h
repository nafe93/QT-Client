#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTcpSocket* socket;
    QByteArray Data;

    int matrix_[10][10];
    int fire_[10][10];
    int mylife = 10;
    int enemylife = 10;

public slots:
    void sockReady();
    void sockDisc();

private slots:
    void on_pushButton_clicked();

public:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text_;
    QGraphicsTextItem *connection;
    void mousePressEvent(QMouseEvent *ev);
    QString buf_;

public:

    //matrix
    void drawing();
    void createMatrix();
    void creatShip();
    //fire
    void createFireMatrix();
    void drawingFire();
    //life
    void drawingYourLife();
    void drawingenemyLife();
    //conection
    void drawConnection();
    void drawDisConnection();
    //send
    void send(QString x, QString y);
};

#endif // MAINWINDOW_H
