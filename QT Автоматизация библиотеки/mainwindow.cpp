#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Система учёта книг");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    Addition* form = new Addition();
    connect(form, SIGNAL(setLog(QString)), this, SIGNAL(setLog(QString)));
    connect(form, SIGNAL(getDeps(int)), this, SIGNAL(getDeps(int)));
    connect(this, SIGNAL(setDeps(QList<Periodical>, QList<EducLit>, QList<ImagLit>)), form, SLOT(setDeps(QList<Periodical>, QList<EducLit>, QList<ImagLit>)));
    connect(form, SIGNAL(listReady(QList<Periodical>, QList<EducLit>, QList<ImagLit>)), this, SIGNAL(listReady(QList<Periodical>, QList<EducLit>, QList<ImagLit>)));
    connect(form, SIGNAL(listReady(QList<Periodical>, QList<EducLit>, QList<ImagLit>, int)), this, SIGNAL(listReady(QList<Periodical>, QList<EducLit>, QList<ImagLit>, int)));
    connect(form, SIGNAL(getCount()), this, SIGNAL(getCount()));
    connect(this, SIGNAL(setCount(int)), form, SLOT(setCount(int)));
    setCentralWidget(form);
}

void MainWindow::on_action_4_triggered()
{
    View* form = new View();
    connect(form, SIGNAL(getDeps(int)), this, SIGNAL(getDeps(int)));
    connect(this, SIGNAL(setDeps(QList<Periodical>, QList<EducLit>, QList<ImagLit>)), form, SLOT(setDeps(QList<Periodical>, QList<EducLit>, QList<ImagLit>)));
    connect(form, SIGNAL(getCount()), this, SIGNAL(getCount()));
    connect(this, SIGNAL(setCount(int)), form, SLOT(setCount(int)));
    setCentralWidget(form);
    emit renewView();
}

void MainWindow::error(QString str)
{
    ui->statusbar->showMessage(str, 3000);
}

void MainWindow::on_action_3_triggered()
{
    Log* form = new Log();
    connect(this, SIGNAL(sendLog(QString)), form, SLOT(sendLog(QString)));
    connect(form, SIGNAL(getLog()), this, SIGNAL(getLog()));
    connect(form, SIGNAL(clearLog()), this, SIGNAL(clearLog()));
    setCentralWidget(form);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    emit save();
}
