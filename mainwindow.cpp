#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
        connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1",5555);
    socket->write("client is connected");
    drawingenemyLife();
}

void MainWindow::sockDisc()
{
    socket->deleteLater();
}

void MainWindow::sockReady()
{
    if(socket->waitForConnected(500))
    {
        socket->waitForReadyRead(500);
        Data = socket->readAll();
        qDebug()<<Data;

        buf_ = Data;
        qDebug()<<buf_;
        if(buf_ == "xxx")
        {
            enemylife--;
            drawingenemyLife();
        }
        if(buf_.length() < 3)
        {
            char x_str = buf_[0].toLatin1();
            char y_str = buf_[1].toLatin1();

            int x = (int)x_str - 48;
            int y = (int)y_str - 48;

            if(matrix_[x][y] == 1)
            {
                mylife--;
                socket->write("xxx");
                drawingYourLife();

            }
            matrix_[x][y] = 2;
            drawing();
            Data.clear();
        }
    }
}

// Заполнение массивы 0
void MainWindow::createMatrix()
{
    //add zero
    for(int i =0; i < 10; i++)
    {
        for(int j =0; j <10; j++)
        {
            matrix_[i][j] = 0;
        }
    }
}
void MainWindow::createFireMatrix()
{
    //add zero
    for(int i =0; i < 10; i++)
    {
        for(int j =0; j <10; j++)
        {
            fire_[i][j] = 0;
        }
    }
}

//создание рандом кораблей
void MainWindow::creatShip()
{
    //time for rand
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    // add 10 random
    for(int i =0; i < 10; i++)
    {
        matrix_[qrand()%10][qrand()%10] = 1;
    }
}

//Отрисовка поля с короблями
void MainWindow::drawing()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // drawing
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);

    int width_ = 25;
    int height_ = 0;

    for(int i = 0; i < 10; i++)
    {
        for(int j =0; j < 10; j++)
        {
            if(matrix_[i][j] == 0)
            {
                rectangle = scene->addRect(width_, height_, 25, 25, blackPen);
            }
            else if(matrix_[i][j] == 1)
            {
                rectangle = scene->addRect(width_, height_, 25, 25, blackPen,blueBrush);
            }
            else if(matrix_[i][j] == 2)
            {
                rectangle = scene->addRect(width_, height_, 25, 25, blackPen,redBrush);
            }
            width_ += 25;
        }
        height_ += 25;
        width_ = 25;
    }
}

// Отрисовка мтрицы огня
void MainWindow::drawingFire()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView_2->setScene(scene);

    // drawing
    QBrush redBrush(Qt::red);
    QBrush greenBrush(Qt::green);
    QPen blackPen(Qt::black);

    int width_ = 25;
    int height_ = 0;

    for(int i = 0; i < 10; i++)
    {
        for(int j =0; j < 10; j++)
        {
            if(fire_[i][j] == 0)
            {
                rectangle = scene->addRect(width_, height_, 25, 25, blackPen);
            }
            else if(fire_[i][j] == 1)
            {
                rectangle = scene->addRect(width_, height_, 25, 25, blackPen);
                ellipse = scene->addEllipse(width_ + 7,height_ + 7,10,10, blackPen, redBrush);
            }
            else if(fire_[i][j] == 2)
            {
                rectangle = scene->addRect(width_, height_, 25, 25, blackPen);
                ellipse = scene->addEllipse(width_ + 7,height_ + 7,10,10, blackPen, greenBrush);
            }
            width_ += 25;
        }
        height_ += 25;
        width_ = 25;
    }
}
//Отрисовка количество жизней
void MainWindow::drawingYourLife()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView_3->setScene(scene);
    QFont seriFont("Times",30,QFont::Bold);
    text_ = scene->addText((QString::number(mylife)),seriFont);
}

void MainWindow::drawingenemyLife()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView_4->setScene(scene);
    QFont seriFont("Times",30,QFont::Bold);
    text_ = scene->addText((QString::number(enemylife)),seriFont);
}

void MainWindow::send(QString x, QString y)
{
    Data += x;
    Data += y;
    socket->write(Data);
    Data.clear();
}
//События при нажати на кнопку
void MainWindow::mousePressEvent(QMouseEvent *ev)
{

    if(ev->button() == Qt::LeftButton)
    {

        int x = ev->x();
        int y = ev->y();

        int matrixElemX = 665 - x;
        int matrixElemY = 408 - y;

        if(x > 415 && matrixElemX > 0 && y > 157 && matrixElemY > 0)
        {
            int buffX = matrixElemX/25;
            int getIndex = 9 - buffX;

            int buffY = matrixElemY/25;
            int getIndexY = 9 - buffY;

//            matrix_[getIndexY][getIndex] = 2;
            fire_[getIndexY][getIndex] = 1;

            QString xx= QString::number(getIndexY);
            QString yy = QString::number(getIndex);

            send(xx,yy);

            drawing();
            drawingFire();

        }
    }
}
