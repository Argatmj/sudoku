#ifndef BACKEND_H
#define BACKEND_H

#include <QQmlEngine>
#include <QtQml>
#include <QList>

class Backend : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QList<QList<int>> sudokuData READ sudokuData NOTIFY sudokuDataChanged)
    Q_PROPERTY(int highlightRow READ highlightRow NOTIFY highlightChanged)
    Q_PROPERTY(int highlightCol READ highlightCol NOTIFY highlightChanged)
private:
    bool isValidCol(int row, int number);
    bool isValidRow(int col, int number);
    bool isValidSubGrid(int row, int col, int number);

public:
    explicit Backend(QObject *parent = nullptr);

    QList<QList<int>> sudokuData ();
    int highlightRow();
    int highlightCol();
    Q_INVOKABLE void setSudokuData(int row, int col, int number);
    Q_INVOKABLE bool solve(int row, int col);
    Q_INVOKABLE void setReset();
    bool isValid(int row, int col, int number);

public slots:
    void onSudokuDataChanged();

signals:
    void sudokuDataChanged();
    void highlightChanged();

private:
    QList<QList<int>> m_sudokuData;
    bool isCancelled = false;
    int currentRow = -1;
    int currentCol = -1;
};

#endif // BACKEND_H
