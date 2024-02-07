#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>


class Connection
{
    QSqlDatabase db ;
public:
    Connection();
    bool createconnection();
    bool closeocnnection();
};

#endif // CONNECTION_H



