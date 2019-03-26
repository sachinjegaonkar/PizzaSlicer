#include "PizzaSlicer.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct FileData
{
    int R, C, L, H;
    Pizza pizza;
};

PizzaSlicer ReadFromInputFile(const string &inputFile)
{
    FileData fileData;

    std::ifstream iFile(inputFile);

    if (!iFile.is_open()) {
        throw std::ios_base::failure("Cannot open the input file.");
    }

    iFile >> fileData.R >> fileData.C >> fileData.L >> fileData.H;
    iFile.get();

    if (!((1 <= fileData.R && fileData.R <= 1000) &&
          (1 <= fileData.C && fileData.C <= 1000) &&
          (1 <= fileData.L && fileData.L <= 1000) &&
          (1 <= fileData.H && fileData.H <= 1000) &&
          (fileData.L < fileData.H)               )) // L < H
    {
        throw std::exception("The input parameters are not in a valid range.");
    }

    for (int i = 0; i < fileData.R; ++i)
    {
        PizzaRow pizzaRow;
        pizzaRow.reserve(fileData.C);

        for (int j = 0; j < fileData.C; ++j)
        {
            Ingredient ingredient = iFile.get();
            pizzaRow.push_back(ingredient);
        }

        fileData.pizza.push_back(std::move(pizzaRow));
        iFile.get();
    }

    if (!((int)fileData.pizza.size() == fileData.R &&
        (int)fileData.pizza[0].size() == fileData.C))
    {
        throw std::exception("The pizza data is not in a valid range.");
    }

    return PizzaSlicer(std::move(fileData.pizza), fileData.L, fileData.H);
}

void WriteToOutputFile(const std::vector<Slice>& slieces, const string &outputFile)
{
    std::ofstream oFile(outputFile);

    if (!oFile.is_open())
    {
        throw std::ios_base::failure("Cannot open the output file.");
    }

    oFile << slieces.size() << std::endl;

    for (const Slice& slice : slieces)
        oFile << slice.rowStart << ' ' << slice.colStart << ' ' << slice.rowEnd << ' ' << slice.colEnd << std::endl;
}

int main(int argc, char *argv[])
{
    // ToDo: for debugging - remove following line of code after debugging.
    char x; cin >> x;

    if (argc != 3)
    {
        std::cout << "Usage: PizzaSlicer <input_file_path> <output_file_path>\n";
        return 1;
    }

    try
    {
        PizzaSlicer slicer = ReadFromInputFile(argv[1]);
        auto slices = slicer.MakeSlices();
        WriteToOutputFile(slices, argv[2]);
    }
    catch (const std::ios_base::failure& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
