#include "GameOfLife.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

GridWorld::GridWorld(int newWidth, int newHeight) : height(newHeight), width(newWidth)
{
    srand(time(0)); // init seed for generating random cells
    this->GenerateNextGeneration();
}

GridWorld::~GridWorld()
{
    this->__freeMemory();
}

void GridWorld::GenerateNextGeneration()
{
    this->__computeCellArray();
    this->__generateOutputState();

    // todo: function? (apply Single Responsibility Principle ?)
    ++this->currentGeneration;
}

void GridWorld::__generateOutputState()
{
    if (!this->outputStateBuff) {
        this->__initOutputState();
    }

    for (int y = 0; y < this->height; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            const cell *tmpCell = this->GetCellXY(x, y);
            char stateOutputChar = tmpCell->alive ? ALIVE_CHAR : DEAD_CHAR;
            this->SetOutputNewCharXY(x, y, stateOutputChar);
        }
    }
}

void GridWorld::__initOutputState()
{
    this->outputStateBuff = new char* [this->height];
    for (int y = 0; y < this->height; ++y)
    {
        this->outputStateBuff[y] = new char[this->width + 1]{ 0 };

        memset(this->outputStateBuff[y], DEAD_CHAR, this->width);
    }
}

void GridWorld::__computeCellArray()
{
    if (!this->cellsArray)
    {
        this->__initCellsArray();
        return;
    }

    auto cellPtr = this->cellsArray;
    for (int i = 0; i < this->GetCellsCount(); ++i)
    {
        cellPtr->alive = this->__isCellAliveInNextGen(&this->currentCellsArray[i]);
        ++cellPtr;
    }

    memcpy(this->currentCellsArray, this->cellsArray, (this->height * this->width) * sizeof(cell));
}


void GridWorld::__initCellsArray()
{
    long long buffSize = this->height * this->width;

    this->cellsArray = new cell[buffSize];
    this->currentCellsArray = new cell[buffSize];

    for (int y = 0; y < this->height; ++y)
    {
        for (int x = 0; x < this->width; ++x)
        {
            bool isAlive = !(rand() % 3);
            this->cellsArray[y * this->width + x] = cell{ x, y, isAlive };
        }
    }

    memcpy(this->currentCellsArray, this->cellsArray, buffSize * sizeof(cell));
}

bool GridWorld::__isCellAliveInNextGen(cell *currCell)
{
    int globalX = currCell->x - 1;
    int globalY = currCell->y - 1;
    int neighboursAlive = 0;

    for (int y = 0; y < 3; ++y)
    {
        int tmpY = globalY + y;
        if (tmpY >= this->GetHeight()) {
            break;
        }

        if (tmpY < 0) continue;

        for (int x = 0; x < 3; ++x)
        {
            int tmpX = globalX + x;

            if (tmpX >= this->GetWidth()) {
                break;
            }

            if (tmpX < 0 || (tmpX == currCell->x && tmpY == currCell->y))
                continue;

            const cell *tmpCell = this->GetCellXY(tmpX, tmpY);
            if (tmpCell->alive) {
                ++neighboursAlive;
            }
        }
    }

    if (!currCell->alive && neighboursAlive == 3)
        return true;

    else if (currCell->alive && (neighboursAlive == 3 || neighboursAlive == 2))
        return true;


    return false;
}


void GridWorld::__freeMemory()
{
    for (int i = 0; i < this->height; ++i)
        delete[] this->outputStateBuff[i];

    delete[] this->outputStateBuff;
    delete[] this->cellsArray;


}
