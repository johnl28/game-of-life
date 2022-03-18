#ifndef GAME_OF_LIFE_H_
#define GAME_OF_LIFE_H_

#define ALIVE_CHAR 'O'
#define DEAD_CHAR '-'


struct cell {
    int x = 0;
    int y = 0;
    bool alive = false;
};

class GridWorld {
public:
    GridWorld(int width, int height);
    ~GridWorld();
    void GenerateNextGeneration();


    int GetHeight()
    {
        return this->height;
    }

    int GetWidth()
    {
        return this->width;
    }

    int GetCurrentGeneration()
    {
        return this->currentGeneration;
    }

    cell* GetCellXY(int x, int y) const
    {
        return &this->currentCellsArray[y * this->width + x];
    }

    int GetCellsCount()
    {
        return this->width * this->height;
    }

    char* GetOutputRow(int index)
    {
        return this->outputStateBuff[index];
    }

    char GetOutputStateXY(int x, int y)
    {
        return this->outputStateBuff[y][x];
    }

    void SetOutputNewCharXY(int x, int y, char newChar)
    {
        this->outputStateBuff[y][x] = newChar;
    }


private:
    void __freeMemory();
    void __initCellsArray();
    void __computeCellArray();

    void __initOutputState();
    void __generateOutputState();

    bool __isCellAliveInNextGen(cell *currCell);

private:
    int currentGeneration = 0;
    int height = 0;
    int width = 0;
    cell* currentCellsArray = nullptr;
    cell* cellsArray = nullptr;
    char** outputStateBuff = nullptr;
};

#endif
