#ifndef DEFINES_H
#define DEFINES_H
#include <QtCore/QDebug>

#define LOG_DEBUG(...) qDebug() << "[DEBUG]" << __TIME__ << __FUNCTION__ << ##__VA_ARGS__

#endif // DEFINES_H
