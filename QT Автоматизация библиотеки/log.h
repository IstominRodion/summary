#ifndef LOG_H
#define LOG_H

#include <QWidget>
#include <QShowEvent>

namespace Ui {
class Log;
}

class Log : public QWidget
{
    Q_OBJECT

public:
    explicit Log(QWidget *parent = nullptr);
    ~Log();

signals:
    void getLog();
    void clearLog();

public slots:
    void sendLog(QString);


private slots:
    void on_pushButton_clicked();

private:
    Ui::Log *ui;
    void showEvent(QShowEvent *event);
};

#endif // LOG_H
