#ifndef HOME_H
#define HOME_H

#include <QDeclarativeItem>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class homeData;

class home
{
    Q_OBJECT
public:
    home();
    home(const home &);
    home &operator=(const home &);
    ~home();

private:
    QSharedDataPointer<homeData> data;
};

#endif // HOME_H
