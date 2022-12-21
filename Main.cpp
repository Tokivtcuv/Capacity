#include <iostream>

// Ausgangspunkt ist obere linke Ecke

enum class Building {EMPTY, HYRDOPOWERSTATION, WINDPOWERPLANT, SOLARPANEL};

// Create Area
int **create_area(int rows, int columns)
{
    int **area = new int*[columns];
    for(int i = 0; i < columns; i++)
    {
        area[i] = new int[rows];
        for(int j = 0; j < 0; j++)
        {
            area[i][j] = (int) Building::EMPTY;
        }
    }
    return area;
}

// Show Area
void show_area(int **area, int rows, int columns)
{
    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            std::cout << area[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// Clear Area (set to default)
void clear_area(int **area, int rows, int columns)
{
    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            area[i][j] = (int) Building::EMPTY;
        }
    }
}

// Check, if Building fits in area
bool in_area(int rows, int columns, int b_rows, int b_columns, int b_pos_r, int b_pos_c)
{
    return (((b_pos_c + b_columns) > columns) || (b_pos_r + b_rows) > rows) ? false : true;
}

// check, if enough space
bool free_area(int** area, int rows, int columns, int b_rows, int b_columns, int b_pos_r, int b_pos_c)
{
    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            if((i >= b_pos_c && i < (b_pos_c + b_columns)) && (j >= b_pos_r && j < (b_pos_r + b_rows)))
            {
                if(area[i][j] != (int) Building::EMPTY)
                {
                    return false;
                    break;
                }
            }
        }
    }
    return true;
}

// Place Building
void set_building(int **area, int rows, int columns, Building b)
{
    // size and position of building
    int b_rows, b_columns, b_pos_r, b_pos_c;

    std::cout << "Length: ";
    std::cin >> b_rows;
    std::cout << "Width: ";
    std::cin >> b_columns;
    std::cout << "x-Position: ";
    std::cin >> b_pos_r;
    std::cout << "y-Position: ";
    std::cin >> b_pos_c;

    bool fits_in_area = in_area(rows, columns, b_rows, b_columns, b_pos_r, b_pos_c);
    bool enough_space = free_area(area, rows, columns, b_rows, b_columns, b_pos_r, b_pos_c);

    // if building fits in area and no collision detected
    if(fits_in_area && enough_space)
    {
        for(int i = 0; i < columns; i++)
        {
            for(int j = 0; j < rows; j++)
            {
                if((i >= b_pos_c && i < (b_pos_c + b_columns)) && (j >= b_pos_r && j < (b_pos_r + b_rows)))
                {
                    area[i][j] = (int) b;
                }
            }
        }
    }
    // if building does not fit in area
    else if(!fits_in_area)
    {
        std::cout << "Building does not fit in the area!" << std::endl;
    }
    // Collssion detected
    else
    {
        int select;
        std::cout << "Collission detected!" << std::endl;
        std::cout << "Do you want to clear the needed space? (1) yes (2) no: ";
        std::cin >> select;

        switch(select)
        {
            case 1:
                for(int i = 0; i < columns; i++)
                {
                    for(int j = 0; j < rows; j++)
                    {
                        if((i >= b_pos_c && i < (b_pos_c + b_columns)) && (j >= b_pos_r && j < (b_pos_r + b_rows)))
                        {
                            area[i][j] = (int) b;
                        }
                    }
                }
                break;
            case 2:
                break;
            default:
                std::cout << "No changes made." << std::endl;
        }
    }
}

/*          MAIN        */
int main()
{
    // rows = length
    int total_rows;
    // columns = width
    int total_columns;

    std::cout << "Enter the length of the area: ";
    std::cin >> total_rows;

    std::cout << "Enter the width of the area: ";
    std::cin >> total_columns;

    int **area = create_area(total_rows, total_columns);

    bool flag = true;
    while(flag)
    {
        // Menu Select
        int select;
        std::cout << "(1) Place building" << std::endl;
        std::cout << "(2) Clear Area" << std::endl;
        std::cout << "(3) Show Area" << std::endl;
        std::cout << "(4) Exit Programm" << std::endl;
        std::cout << "Enter a option: ";
        std::cin >> select;

        switch(select)
        {
            case 1:
                // Place building
                int build_select;
                std::cout << "(1) Water, (2) Wind, (3) Solar" << std::endl;
                std::cout << "Which building: ";
                std::cin >> build_select;

                switch(build_select)
                {
                    case 1:
                        set_building(area, total_rows, total_columns, Building::HYRDOPOWERSTATION);
                        break;
                    case 2:
                        set_building(area, total_rows, total_columns, Building::WINDPOWERPLANT);
                        break;
                    case 3:
                        set_building(area, total_rows, total_columns, Building::SOLARPANEL);
                        break;
                    default:
                        std::cout << "Unknwon building";
                }
                break;
            case 2:
                // Clear Area
                clear_area(area, total_rows, total_columns);
                break;
            case 3:
                // Show Area
                show_area(area, total_rows, total_columns);
                break;
            case 4:
                // Exit
                flag = false;
                delete[] area;
                break;
            default:
                // Default
                std::cout << "Unknown input. Enter a valid option." << std::endl;
        }
    }

    return 0;
}
