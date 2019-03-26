#ifndef GOOGLE_HASHCODE_2019_PIZZA_SLICER_H
#define GOOGLE_HASHCODE_2019_PIZZA_SLICER_H

#include <ostream>
#include <vector>

typedef char                            Ingredient;
typedef std::vector<Ingredient>         PizzaRow;
typedef std::vector<PizzaRow>           Pizza;
typedef struct
{
    int rowStart, colStart;             // (r1, c1)
    int rowEnd, colEnd;                 // (r2, c2)
}                                       Slice;
typedef struct { int row; int col; }    Point;

class PizzaSlicer
{
public:
    PizzaSlicer(const Pizza& pizza, int minIngredients, int maxCells)
        : pizza(pizza), minIngredients(minIngredients), maxCells(maxCells)
    {
        totalRows = (int)pizza.size();
        totalColumns = (int)pizza[0].size();
    }

    std::vector<Slice> MakeSlices();

private:
    int                 minIngredients; // min number of each ingredient per slice
    int                 maxCells;       // max number of cells per slice
    Pizza               pizza;
    int                 totalRows;
    int                 totalColumns;
    std::vector<Slice>  slices;

    PizzaSlicer() { }                                       // default constructor
    PizzaSlicer(const PizzaSlicer&) = delete;               // no copy constructure
    PizzaSlicer& operator=(PizzaSlicer const&) = delete;    // no assignment operator


    std::tuple<int, int> FindIngredients(Slice slice) const noexcept;
    bool IsMinimumIngredients(int i1, int i2) const noexcept
    {
        return i1 >= minIngredients && i2 >= minIngredients;
    }
    Point FindFirstValidSlice(Point startingPoint);
};

#endif // GOOGLE_HASHCODE_2019_PIZZA_SLICER_H
