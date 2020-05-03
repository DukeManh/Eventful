#include <vector>
#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
using namespace std;

#define e 2.718281828459045
/****************************************
LIZARD STRUCT
****************************************/

struct Lizard
{
    int pos;    // cell index where lizard is placed
    int row;    // row in which lizard is placed
    int col;    // column in which lizard is placed
    int rowL;   // cell index upto which lizard can attack towards left along the row; includes tree cell
    int rowH;   // cell index upto which lizard can attack towards right along the row; includes tree cell
    int colL;   // cell index upto which lizard can attack towards top along the column; includes tree cell
    int colH;   // cell index upto which lizard can attack towards bottom along the column; includes tree cell
    int bdiagL; // cell index upto which lizard can attack towards left top along \ diagonal; includes tree cell
    int bdiagH; // cell index upto which lizard can attack towards right bottom along \ diagonal; includes tree cell
    int fdiagL; // cell index upto which lizard can attack towards right top along / diagonal; includes tree cell
    int fdiagH; // cell index upto which lizard can attack towards left bottom along / diagonal; includes tree cell
};

/****************************************
SEGMENT STRUCT
****************************************/

struct Segment
{
    int start; // starting cell index of segment; does not include tree cell
    int end;   // ending cell index of segment; does not include tree cell
    int row;   // row of the segment

    Segment()
    {
    }

    Segment(int x1, int x2, int r)
    {
        start = x1;
        end = x2;
        row = r;
    }
};

/****************************************
GARDEN CLASS
****************************************/

class Garden
{

public:
    int N;
    int P;
    long TreeCount;
    int CountOfLizardsAdded;
    vector<int> input;
    vector<Segment> segments;
    vector<Lizard> lizards;

public:
    Garden(int n, int p)
    {
        N = n;
        P = p;
        TreeCount = 0;
        CountOfLizardsAdded = 0;
    }

    bool CanLizardBeAddedHere(int cellIndex)
    {
        if (input[cellIndex] == 2)
            return false; // There's a tree here, so lizard can't be placed here.

        int cellRow = cellIndex / N;
        int cellCol = cellIndex % N;
        Lizard lz;
        for (int i = 0; i < CountOfLizardsAdded; i++)
        {
            lz = lizards[i];

            // If there are no trees, we can simplify checks for attacks by avoiding checking for trees, hence this if else condition.
            if (TreeCount > 0)
            {
                /*
                // We don't need to check if the lizard is being attacked along the row because that's something we are taking care of while traversing the garden in the first place
                if (cellRow == lz.row && (lz.rowL <= cellIndex && cellIndex <= lz.rowH))
                    return false; // cell shares the row with the lizard and is inside its attack zone
                */

                if (cellCol == lz.col && (lz.colL <= cellIndex && cellIndex <= lz.colH))
                    return false; // cell shares the column with the lizard and is inside its attack zone

                if ((cellRow - lz.row == cellCol - lz.col) && (lz.bdiagL <= cellIndex && cellIndex <= lz.bdiagH))
                    return false; // cell shares the \ diagonal with the lizard and is inside its attack zone

                if ((cellRow - lz.row == lz.col - cellCol) && (lz.fdiagL <= cellIndex && cellIndex <= lz.fdiagH))
                    return false; // cell shares the / diagonal with the lizard and is inside its attack zone
            }
            else
            {
                /*
                // We don't need to check if the lizard is being attacked along the row because that's something we are taking care of while traversing the garden in the first place
                if (cellRow == lz.row)
                    return false; // cell shares the row with the lizard
                */

                if (cellCol == lz.col)
                    return false; // cell shares the column with the lizard

                if (cellRow - lz.row == cellCol - lz.col)
                    return false; // cell shares the \ diagonal with the lizard

                if (cellRow - lz.row == lz.col - cellCol)
                    return false; // cell shares the / diagonal with the lizard
            }
        }
        return true;
    }

    void AddLizard(int cellIndex)
    {
        Lizard lz;
        lz.pos = cellIndex;
        lz.row = cellIndex / N;
        lz.col = cellIndex % N;
        if (TreeCount > 0) // No need to calculate attack zone if there are no trees on the board, we can perform simple row, column and diagonal checks to confirm.
            UpdateAttackZone(lz);

        lizards.push_back(lz);
        CountOfLizardsAdded++;
    }

    void UpdateAttackZone(Lizard &lz)
    {
        int i;
        int min;
        int max;
        if (CountOfLizardsAdded < P)
        { // Calculate the attack zone of the just added lizard only if the problem is not solved yet
            // Traverse along the row leftwards from the lizard until a tree is found or the edge of the garden is reached; that's where lizard's attack zone ends to its left.
            i = lz.pos;
            min = N * (i / N);
            while (i >= min)
            {
                if (input[i] == 2 || i == min)
                {
                    lz.rowL = i;
                    break;
                }
                i--;
            }

            // Traverse along the row rightwards from the lizard until a tree is found or the edge of the garden is reached; that's where lizard's attack zone ends to its right.
            i = lz.pos;
            max = N * (i / N) + N - 1;
            while (i <= max)
            {
                if (input[i] == 2 || i == max)
                {
                    lz.rowH = i;
                    break;
                }
                i++;
            }

            // Traverse along the column upwards from the lizard until a tree is found or the edge of the garden is reached; that's where lizard's attack zone ends above it.
            i = lz.pos;
            min = i % N;
            while (i >= min)
            {
                if (input[i] == 2 || i == min)
                {
                    lz.colL = i;
                    break;
                }
                i = i - N;
            }

            // Traverse along the column downwards from the lizard until a tree is found or the edge of the garden is reached; that's where lizard's attack zone ends below it.
            i = lz.pos;
            max = N * (N - 1) + (i % N);
            while (i <= max)
            {
                if (input[i] == 2 || i == max)
                {
                    lz.colH = i;
                    break;
                }
                i = i + N;
            }

            // Traverse along the \ diagonal leftwards/upwards from the lizard until a tree is found or the edge of the garden is reached, that's where lizard's attack zone ends to its left on \ diagonal.
            i = lz.pos;
            while (i / N >= 0 || i % N >= 0)
            {
                if (input[i] == 2 || i / N == 0 || i % N == 0)
                {
                    lz.bdiagL = i;
                    break;
                }
                i = i - N - 1;
            }

            // Traverse along the \ diagonal rightwards/downwards from the lizard until a tree is found or the edge of the garden is reached, that's where lizard's attack zone ends to its right on \ diagonal.
            i = lz.pos;
            while (i / N <= (N - 1) || i % N <= (N - 1))
            {
                if (input[i] == 2 || i / N == (N - 1) || i % N == (N - 1))
                {
                    lz.bdiagH = i;
                    break;
                }
                i = i + N + 1;
            }

            // Traverse along the / diagonal rightwards/upwards from the lizard until a tree is found or the edge of the garden is reached, that's where lizard's attack zone ends to its right on / diagonal.
            i = lz.pos;
            while (i / N >= 0 || i % N <= (N - 1))
            {
                if (input[i] == 2 || i / N == 0 || i % N == (N - 1))
                {
                    lz.fdiagL = i;
                    break;
                }
                i = i - N + 1;
            }

            // Traverse along the / diagonal leftwards/downwards from the lizard until a tree is found or the edge of the garden is reached, that's where lizard's attack zone ends to its left on / diagonal.
            i = lz.pos;
            while (i % N >= 0 || i / N <= (N - 1))
            {
                if (input[i] == 2 || i % N == 0 || i / N == (N - 1))
                {
                    lz.fdiagH = i;
                    break;
                }
                i = i + N - 1;
            }
        }
    }

    void RemoveLizard()
    {
        if (CountOfLizardsAdded > 0)
        {
            //cout << "\n Removing lizard at " << lizards[CountOfLizardsAdded - 1];
            lizards.pop_back();
            CountOfLizardsAdded--;
        }
    }

public:
    void CreateOutputFile()
    {
        ofstream outputFile;

        outputFile.open("./output.txt", ios::trunc);
        if (outputFile.is_open())
        {
            if (CountOfLizardsAdded == P)
            {
                outputFile << "OK\n";
                for (int k = 0; k < lizards.size(); k++)
                    input[lizards[k].pos] = 1;

                for (int i = 0; i < N; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        outputFile << input[N * i + j];
                    }
                    outputFile << "\n";
                }
            }
            else
            {
                outputFile << "FAIL";
            }
            outputFile.close();
        }
    }
};

/****************************************
BFS STRATEGY
****************************************/

class BFSStrategy
{

private:
    vector<Garden> states;
    Garden *grdn;

public:
    BFSStrategy(Garden &g)
    {
        grdn = &g;
    }

public:
    Garden Execute()
    {
        int startIndex;
        int depth;
        for (int i = 0; i < grdn->N * grdn->N; i++)
        {
            Garden gNew = *grdn;
            if (gNew.CanLizardBeAddedHere(i))
            {
                gNew.AddLizard(i);
                states.push_back(gNew);
            }

            depth = 0;
            while (!states.empty())
            {
                Garden gResult = states.front();
                states.erase(states.begin());
                if (gResult.CountOfLizardsAdded == gResult.P) // Should we move this before placing a node in the final array? This would reduce some complexity, both for BFS and DFS.
                    return gResult;

                if (gResult.TreeCount > 0)
                    startIndex = (gResult.CountOfLizardsAdded == 0) ? 0 : gResult.lizards[gResult.CountOfLizardsAdded - 1].rowH + 1;
                else
                    startIndex = (gResult.CountOfLizardsAdded == 0) ? 0 : ((gResult.lizards[gResult.CountOfLizardsAdded - 1].pos / gResult.N + 1)) * gResult.N;

                int childCount = 0;
                while (startIndex < gResult.N * gResult.N && ((depth < 5 && childCount < 4) || (depth >= 5 && childCount < 1)))
                {
                    Garden gChild = gResult;
                    if (gChild.CanLizardBeAddedHere(startIndex))
                    {
                        gChild.AddLizard(startIndex);
                        states.push_back(gChild);
                        childCount++;
                    }
                    startIndex++;
                }
                depth++;
            }
        }
        return Garden(1, 1);
    }
};

/****************************************
DFS STRATEGY
****************************************/

class DFSStrategy
{

private:
    Garden *grdn;

public:
    DFSStrategy(Garden &g)
    {
        grdn = &g;
    }

public:
    // Traverse cell by cell, row by row, from top left to bottom right
    bool Execute()
    {
        if (grdn->CountOfLizardsAdded == grdn->P)
            return true;

        // By starting from the appropriate cell along the row, we can avoid row safety check. This appropriate cell would either be after a tree on the same row or will be on the next row if there are no trees on the same row, as we are traversing from left to right & top to bottom.
        int startIndex;
        if (grdn->TreeCount > 0)
            startIndex = (grdn->CountOfLizardsAdded == 0) ? 0 : grdn->lizards[grdn->CountOfLizardsAdded - 1].rowH + 1;
        else
            startIndex = (grdn->CountOfLizardsAdded == 0) ? 0 : ((grdn->lizards[grdn->CountOfLizardsAdded - 1].pos / grdn->N + 1)) * grdn->N;

        long totalCells = grdn->N * grdn->N;
        for (int index = startIndex; index < totalCells; index++)
        {
            if (grdn->TreeCount == 0 && (grdn->N - index / grdn->N) < (grdn->P - grdn->CountOfLizardsAdded))
                return false; // no point going down this branch further because it's not going to yield a solution because number of rows left is less than number of lizards yet to be placed.

            if (grdn->CanLizardBeAddedHere(index))
            {
                grdn->AddLizard(index);
                bool hasChildren = Execute();
                if (hasChildren)
                    return true;
                grdn->RemoveLizard();
            }
        }
        return false;
    }

    // Traverse segment by segment, cell by cell, from top left to bottom right
    bool Execute(long startingSmgntIndex)
    {
        if (grdn->CountOfLizardsAdded == grdn->P)
            return true;

        long totalSgmntCount = grdn->segments.size();

        for (long sIndex = startingSmgntIndex; sIndex < totalSgmntCount; sIndex++)
        {
            if (totalSgmntCount - sIndex < grdn->P - grdn->CountOfLizardsAdded)
                return false; // No point going down this branch further; it's not going to yield a solution because number of segments left is less than number of lizards yet to be placed.

            for (int cIndex = grdn->segments[sIndex].start; cIndex <= grdn->segments[sIndex].end; cIndex++)
            {
                if (grdn->CanLizardBeAddedHere(cIndex))
                {
                    grdn->AddLizard(cIndex);
                    bool hasChildren = Execute(sIndex + 1);
                    if (hasChildren)
                        return true;
                    grdn->RemoveLizard();
                }
            }
        }
        return false;
    }
};

/****************************************
SA STRATEGY
****************************************/
class SAStrategy
{

private:
    Garden *grdn;

public:
    SAStrategy(Garden &g)
    {
        grdn = &g;
    }

public:
    void Execute()
    {
        double temp = 1000;
        vector<Lizard> currentState;
        vector<Lizard> nextState;
        int cellIndex;
        Segment sgmnt;

        for (int i = 0; i < grdn->P; i++)
        {
            sgmnt = grdn->segments[i];
            cellIndex = random() % (sgmnt.end - sgmnt.start + 1) + sgmnt.start;
            currentState.push_back(GetLizard(cellIndex));
            grdn->input[cellIndex] = 1;
        }

        long totalSgmntCount = grdn->segments.size();
        long sIndex;
        int i;
        double d = 0.0001;
        time_t end = time(NULL) + 60 * 4.5;
        while (time(NULL) <= end)
        {
            temp = 1 / ((double)grdn->P * log(d));
            d = d + 0.001;

            nextState = currentState;

            i = random() % grdn->P;
            while (true)
            {
                sIndex = random() % totalSgmntCount;
                sgmnt = grdn->segments[sIndex];
                cellIndex = random() % (sgmnt.end - sgmnt.start + 1) + sgmnt.start;
                if (grdn->input[cellIndex] == 0)
                    break;
            }

            nextState[i] = GetLizard(cellIndex);

            double diff = GetNumConflicts(nextState) - GetNumConflicts(currentState);

            if (diff < 0 || (diff > 0 && pow(e, -diff / temp) > (random() % 1000) / (double)1000))
            {
                grdn->input[currentState[i].pos] = 0;
                grdn->input[cellIndex] = 1;
                currentState = nextState;
            }

            if (IsCurrentStateGood(currentState))
            {
                grdn->CountOfLizardsAdded = currentState.size();
                grdn->lizards = currentState;
                return;
            }
        }
        return;
    }

    Lizard GetLizard(int cellIndex)
    {
        Lizard lz;
        lz.pos = cellIndex;
        lz.row = cellIndex / grdn->N;
        lz.col = cellIndex % grdn->N;
        if (grdn->TreeCount > 0)
            UpdateAttackZone(lz);
        return lz;
    }

    bool IsCurrentStateGood(vector<Lizard> &state)
    {
        return GetNumConflicts(state) == 0;
    }

    int GetNumConflicts(vector<Lizard> &state)
    {
        int conflicts = 0;
        Lizard lz;

        for (int li = 0; li < state.size() - 1; li++)
        {
            int cellIndex = state[li].pos;
            int cellRow = state[li].row;
            int cellCol = state[li].col;

            for (int j = li + 1; j < state.size(); j++)
            {
                lz = state[j];

                // If there are no trees, we can simplify checks for attacks by avoiding checking for trees, hence this if else condition.
                if (grdn->TreeCount > 0)
                {
                    if (cellRow == lz.row && (lz.rowL <= cellIndex && cellIndex <= lz.rowH))
                    {
                        conflicts++; // cell shares the row with the lizard and is inside its attack zone
                        continue;
                    }

                    if (cellCol == lz.col && (lz.colL <= cellIndex && cellIndex <= lz.colH))
                    {
                        conflicts++; // cell shares the column with the lizard and is inside its attack zone
                        continue;
                    }

                    if ((cellRow - lz.row == cellCol - lz.col) && (lz.bdiagL <= cellIndex && cellIndex <= lz.bdiagH))
                    {
                        conflicts++; // cell shares the \ diagonal with the lizard and is inside its attack zone
                        continue;
                    }

                    if ((cellRow - lz.row == lz.col - cellCol) && (lz.fdiagL <= cellIndex && cellIndex <= lz.fdiagH))
                    {
                        conflicts++; // cell shares the / diagonal with the lizard and is inside its attack zone
                        continue;
                    }
                }
                else
                {
                    if (cellRow == lz.row)
                    {
                        conflicts++; // cell shares the row with the lizard
                        continue;
                    }

                    if (cellCol == lz.col)
                    {
                        conflicts++; // cell shares the column with the lizard
                        continue;
                    }

                    if (cellRow - lz.row == cellCol - lz.col)
                    {
                        conflicts++; // cell shares the \ diagonal with the lizard
                        continue;
                    }

                    if (cellRow - lz.row == lz.col - cellCol)
                    {
                        conflicts++; // cell shares the / diagonal with the lizard
                        continue;
                    }
                }
            }
        }
        return conflicts;
    }

    void UpdateAttackZone(Lizard &lz)
    {
        int i;
        int min;
        int max;

        // Traverse along the row leftwards from the lizard until a tree is found or the edge of the garden is reached; that's where lizard's attack zone ends to its left.
        i = lz.pos;
        min = grdn->N * (i / grdn->N);
        while (i >= min)
        {
            if (grdn->input[i] == 2 || i == min)
            {
                lz.rowL = i;
                break;
            }
            i--;
        }

        // Traverse along the row rightwards from the lizard until a tree is found or the edge of the garden is reached; that's where lizard's attack zone ends to its right.
        i = lz.pos;
        max = grdn->N * (i / grdn->N) + grdn->N - 1;
        while (i <= max)
        {
            if (grdn->input[i] == 2 || i == max)
            {
                lz.rowH = i;
                break;
            }
            i++;
        }

        // Traverse along the column upwards from the lizard until a tree is found or the edge of the garden is reached; that's where lizard's attack zone ends above it.
        i = lz.pos;
        min = i % grdn->N;
        while (i >= min)
        {
            if (grdn->input[i] == 2 || i == min)
            {
                lz.colL = i;
                break;
            }
            i = i - grdn->N;
        }

        // Traverse along the column downwards from the lizard until a tree is found or the edge of the garden is reached; that's where lizard's attack zone ends below it.
        i = lz.pos;
        max = grdn->N * (grdn->N - 1) + (i % grdn->N);
        while (i <= max)
        {
            if (grdn->input[i] == 2 || i == max)
            {
                lz.colH = i;
                break;
            }
            i = i + grdn->N;
        }

        // Traverse along the \ diagonal leftwards/upwards from the lizard until a tree is found or the edge of the garden is reached, that's where lizard's attack zone ends to its left on \ diagonal.
        i = lz.pos;
        while (i / grdn->N >= 0 || i % grdn->N >= 0)
        {
            if (grdn->input[i] == 2 || i / grdn->N == 0 || i % grdn->N == 0)
            {
                lz.bdiagL = i;
                break;
            }
            i = i - grdn->N - 1;
        }

        // Traverse along the \ diagonal rightwards/downwards from the lizard until a tree is found or the edge of the garden is reached, that's where lizard's attack zone ends to its right on \ diagonal.
        i = lz.pos;
        while (i / grdn->N <= (grdn->N - 1) || i % grdn->N <= (grdn->N - 1))
        {
            if (grdn->input[i] == 2 || i / grdn->N == (grdn->N - 1) || i % grdn->N == (grdn->N - 1))
            {
                lz.bdiagH = i;
                break;
            }
            i = i + grdn->N + 1;
        }

        // Traverse along the / diagonal rightwards/upwards from the lizard until a tree is found or the edge of the garden is reached, that's where lizard's attack zone ends to its right on / diagonal.
        i = lz.pos;
        while (i / grdn->N >= 0 || i % grdn->N <= (grdn->N - 1))
        {
            if (grdn->input[i] == 2 || i / grdn->N == 0 || i % grdn->N == (grdn->N - 1))
            {
                lz.fdiagL = i;
                break;
            }
            i = i - grdn->N + 1;
        }

        // Traverse along the / diagonal leftwards/downwards from the lizard until a tree is found or the edge of the garden is reached, that's where lizard's attack zone ends to its left on / diagonal.
        i = lz.pos;
        while (i % grdn->N >= 0 || i / grdn->N <= (grdn->N - 1))
        {
            if (grdn->input[i] == 2 || i % grdn->N == 0 || i / grdn->N == (grdn->N - 1))
            {
                lz.fdiagH = i;
                break;
            }
            i = i + grdn->N - 1;
        }
    }
};

/****************************************
MAIN METHOD
****************************************/

int main()
{
    //    clock_t start = clock();
    string algorithmInstruction;
    ifstream inputFile;
    ofstream outputFile;
    int N;
    int P;

    Garden g(0, 0);

    inputFile.open("./input.txt");
    if (inputFile.is_open())
    {
        inputFile >> algorithmInstruction;
        inputFile >> N;
        inputFile >> P;

        g = Garden(N, P);
        char num = inputFile.get();
        while (inputFile.good())
        {
            if (num == '2')
            {
                g.input.push_back(2);
                g.TreeCount++;
            }

            if (num == '0')
                g.input.push_back(0);

            num = inputFile.get();
        }
        inputFile.close();
    }

    // Create segments
    int previousTreeIndex;
    for (int i = 0; i < g.N * g.N; i++)
    {
        if (i % N == 0) // We are at the beginning of the row. For the ease of visualization and calculation, let's assume there is a tree to the left of it, outside the edge of the board.
            previousTreeIndex = i - 1;

        if (g.input[i] == 2)
        { // We have encountered a tree. If there is no tree to its immediate left, create a new segment. This will also take care of left edge because of the way we are setting previousTreeIndex above. In any case, reset previousTreeIndex to current index.
            if (i - previousTreeIndex > 1)
                g.segments.push_back(Segment(previousTreeIndex + 1, i - 1, i / N));
            previousTreeIndex = i;
        }

        if (i % N == N - 1 && i - previousTreeIndex > 0) // We are at the end of the row. If there is no tree to its immediate left, create a new sgement.
            g.segments.push_back(Segment(previousTreeIndex + 1, i, i / N));
    }

    //    for (int i = 0; i < g.segments.size(); i++)
    //        cout << "\n Segment " << i << ": " << g.segments[i].start << ", " << g.segments[i].end << ", " << g.segments[i].row;

    //        cout << algorithmInstruction;
    // Call the right strategy based on algorithm instruction
    if (algorithmInstruction == "BFS")
    {
        BFSStrategy strategy = BFSStrategy(g);
        Garden grdn = strategy.Execute();
        grdn.CreateOutputFile();
    }
    else if (algorithmInstruction == "DFS")
    {
        DFSStrategy strategy = DFSStrategy(g);
        strategy.Execute(0);
        g.CreateOutputFile();
    }
    else if (algorithmInstruction == "SA")
    {
        SAStrategy strategy = SAStrategy(g);
        //srandom((unsigned int)time(NULL));
        strategy.Execute();
        g.CreateOutputFile();
    }

    //    clock_t stop = clock();
    //    cout << "\n Time elapsed in ms: " << (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC << "\n";

    return 0;
}