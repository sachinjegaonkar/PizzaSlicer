#include "PizzaSlicer.h"
#include <iostream>


std::tuple<int, int> PizzaSlicer::FindIngredients(Slice slice) const noexcept
{
    int mushrooms = 0;
    int tomatoes = 0;

    for (int row = slice.rowStart; row <= slice.rowEnd; ++row) {
        for (int col = slice.colStart; col <= slice.colEnd; ++col) {
            if (pizza[row][col] == (Ingredient)'M') {
                ++mushrooms;
            }
            else {
                ++tomatoes;
            }
        }
    }

    return std::tie(mushrooms, tomatoes);
}

Point PizzaSlicer::FindFirstValidSlice(Point startingPoint)
{
    Point tempPoint{ 0, 0 }, endingPoint{ 0, 0 };

    int i = startingPoint.row + 1;
    int j = (totalColumns / maxCells >= 1) ? maxCells : totalColumns;

    for (; i < totalRows && j > 0; )
    {
        while ((i - startingPoint.row) * j != maxCells)
        {
            if ((i - startingPoint.row) * j < maxCells)
                i += 1;
            else
                j -= 1;
        }

        if (!(i <= totalRows && j > 0))
            break;

        if ((i - startingPoint.row) * j == maxCells)
        {
            tempPoint.row = i;
            tempPoint.col = j;

            Slice tempSlice{ startingPoint.row, startingPoint.col, tempPoint.row-1, tempPoint.col-1 };
            auto[mushrooms, tomatoes] = FindIngredients(tempSlice);
            if (IsMinimumIngredients(mushrooms, tomatoes))
            {
                endingPoint = tempPoint;

                if (mushrooms > minIngredients && tomatoes > minIngredients)
                {
                    j -= 1;
                    continue;
                }
                else if (mushrooms == minIngredients || tomatoes == minIngredients)
                {
                    break;
                }
            }
            else i += 1;
        }
    }

    return endingPoint;
}

std::vector<Slice> PizzaSlicer::MakeSlices()
{
    Point startingPoint{ 0, 0 }, endingPoint{ 0, 0 };
    // define sliding window.

    while (startingPoint.row < totalRows && startingPoint.col < totalColumns)
    {
        endingPoint = FindFirstValidSlice(startingPoint);
        if (endingPoint.row == 0 && endingPoint.col == 0)
        {
            startingPoint.col += 1;
            continue;
        }
        else
        {
            Point newStartingPoint = startingPoint;
            Point newEndingPoint = endingPoint;
            // use slidingWindow

            Slice firstSlice{ startingPoint.row, startingPoint.col, endingPoint.row - 1, endingPoint.col - 1 };
            slices.push_back(firstSlice);

            //if (newEndingPoint.row >= totalRows) break;
            while (newEndingPoint.row <= totalRows)
            {
                newStartingPoint.col = newStartingPoint.col + endingPoint.col;
                newEndingPoint.col = newStartingPoint.col + endingPoint.col;

                while (newEndingPoint.col < totalColumns) // continue for rest of the columns in this row.
                {
                    Slice nextSlice{ newStartingPoint.row, newStartingPoint.col, newEndingPoint.row - 1, newEndingPoint.col - 1 };
                    slices.push_back(nextSlice);

                    newStartingPoint.col = newStartingPoint.col + endingPoint.col;
                    newEndingPoint.col = newStartingPoint.col + endingPoint.col;
                }

                // new row comes up
                newStartingPoint.row = newStartingPoint.row + endingPoint.row;
                newEndingPoint.row = newStartingPoint.row + endingPoint.row;

                newStartingPoint.col = startingPoint.col;
                newEndingPoint.col = endingPoint.col;

                if (newEndingPoint.row < totalRows)
                {
                    Slice nextSlice{ newStartingPoint.row, newStartingPoint.col, newEndingPoint.row - 1, newEndingPoint.col - 1 };
                    slices.push_back(nextSlice);
                    // continue for rest of the columns in this row.
                }
                else
                {
                    startingPoint = newStartingPoint;
                    break;
                }
            }

        }
    }

    for (int row = 0; row < pizza.size(); row++)
    {
        for (int col = 0; col < pizza[0].size(); col++)
        {
            //auto slice = create_slice_for(row, col);
            //if (!slice) continue;
            //int next_slice_id = slices.size();
            //mark_slice(slice.value(), next_slice_id);
            //slices.push_back(slice.value());
        }
    }
    return std::move(slices);
}
