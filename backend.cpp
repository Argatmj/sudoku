#include "backend.h"
#include <QCoreApplication>
#include <QThread>

Backend::Backend(QObject *parent)
    : QObject{parent},
    m_sudokuData(
          {
              {0, 0, 0, 4, 2, 0, 1, 7, 0},
              {0, 3, 0, 0, 0, 0, 0, 0, 6},
              {1, 0, 9, 8, 6, 3, 5, 2, 0},
              {0, 0, 0, 0, 9, 0, 0, 6, 0},
              {7, 8, 6, 1, 0, 2, 4, 3, 9},
              {0, 9, 0, 0, 4, 0, 0, 0, 0},
              {0, 1, 2, 5, 8, 6, 9, 0, 7},
              {9, 0, 0, 0, 0, 0, 0, 8, 0},
              {0, 4, 8, 0, 7, 1, 0, 0, 0}
          })
{
    QObject::connect(this, &Backend::sudokuDataChanged, this, &Backend::onSudokuDataChanged);
}
 QList<QList<int>> Backend::sudokuData()
{
    return m_sudokuData;
}

bool Backend::isValidCol(int row, int number)
{
    for(int c = 0; c < 9; c++){
        if(m_sudokuData[row][c] == number) return false;
    }
    return true;
}

bool Backend::isValidRow(int col, int number)
{
    for(int r = 0; r < 9; r++){
        if(m_sudokuData[r][col] == number) return false;
    }
    return true;
}

bool Backend::isValidSubGrid(int startRow, int startCol, int number)
{
    for (int r = startRow; r < startRow + 3; r++) {
        for (int c = startCol; c < startCol + 3; c++) {
            if (m_sudokuData[r][c] == number) return false;
        }
    }
    return true;
}

int Backend::highlightRow(){
    return currentRow;
}

int Backend::highlightCol(){
    return currentCol;
}

void Backend::setSudokuData(int row, int col, int number)
{
    m_sudokuData[row][col] = number;
    emit sudokuDataChanged();
    isCancelled = false;
}

bool Backend::solve(int row, int col)
{
    if (isCancelled) return false;
    QEventLoop loop;
    currentRow = row;
    currentCol = col;
    emit highlightChanged();

    if (row == 9) {
        return true;
    }

    if (col == 9) {
        return solve(row + 1, 0);
    }

    if (m_sudokuData[row][col] != 0) {
        return solve(row, col + 1);
    }

    for (int num = 1; num <= 9; ++num) {
        if (isValid(row, col, num)) {
            m_sudokuData[row][col] = num;
            emit sudokuDataChanged();
            QTimer::singleShot(200, &loop, &QEventLoop::quit);
            loop.exec();
            if (solve(row, col + 1)) {
                return true;
            }
            currentRow = row;
            currentCol = col;
            m_sudokuData[row][col] = 0;
            emit highlightChanged();
            emit sudokuDataChanged();
        }
    }
    return false;
}

void Backend::setReset()
{
    isCancelled = true;
    currentRow = -1;
    currentCol = -1;

    for(int i = 0; i < m_sudokuData.size(); i++){
        for(int j = 0; j < m_sudokuData[i].size(); j++){
            m_sudokuData[i][j] = 0;
        }
    }

    emit sudokuDataChanged();
    emit highlightChanged();
}


bool Backend::isValid(int row, int col, int number)
{
    int startRow = row - (row % 3);
    int startCol = col - (col % 3);

    return isValidRow(col,number) && isValidCol(row,number) && isValidSubGrid(startRow,startCol,number);
}


void Backend::onSudokuDataChanged()
{
    qInfo() << "Sudoku data was changed!";
}



