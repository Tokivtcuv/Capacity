#include "CapycitySim.h"

// Constructor
CapycitySim::CapycitySim(int rows, int columns)
{
    m_rows = rows;
    m_columns = columns;
    create_field(m_rows, m_columns);
}

// Create Area
void CapycitySim::create_field(int rows, int columns)
{
    m_area = new std::string* [m_columns];

    for(int i = 0; i < columns; i++)
    {
        m_area[i] = new std::string [m_rows];
        for(int j = 0; j < rows; j++)
        {
            this->m_area[i][j] = BLANK;
        }
    }
}

// Show Menu
void CapycitySim::start_menu()
{
    bool flag = true;
    while(flag)
    {
        // Menu Select
        int select;
        std::cout << std::endl;
        std::cout << "(1) Place building" << std::endl;
        std::cout << "(2) Clear Area" << std::endl;
        std::cout << "(3) Show Area" << std::endl;
        std::cout << "(4) Building/Material Costs" << std::endl;
        std::cout << "(5) Exit Programm" << std::endl;
        std::cout << "Enter a option: ";
        std::cin >> select;

        switch(select)
        {
            case 1:
                // Place Building
                int build_select;
                std::cout << "Building: (1) Hydro (2) Wind (3) Solar: " << std::endl;
                std::cout << "Enter a option: ";
                std::cin >> build_select;

                switch(build_select){
                    case 1:
                        set_building(new Hydropowerstation());
                        break;
                    case 2:
                        set_building(new Windpowerstation());
                        break;
                    case 3:
                        set_building(new Solarpanel());
                        break;
                    default:
                        std::cout << "Unknown Building";
                }
                break;
            case 2:
                // Clear Area
                clear_area();
                break;
            case 3:
                // Show Area
                print_area();
                break;
            case 4:
                // Costs
                //print_information();
                print_building_material_cost();
                break;
            case 5:
                // Exit
                flag = false;
                break;
            default:
                // Default
                std::cout << "Unknown input. Enter a valid option." << std::endl;
        }
    }
}

// Print Area
void CapycitySim::print_area()
{

    for(int i = 0; i < m_columns; i++)
    {
        for(int j = 0; j < m_rows; j++)
        {
            std::cout << m_area[i][j] << " ";
        }
        std::cout << "\n";
    }
    // print_information();
    print_costs();
}

void CapycitySim::print_building_material_cost()
{
    Building* hydro = new Hydropowerstation();
    Building* wind = new Windpowerstation();
    Building* solar = new Solarpanel();
    Material* wood = new Wood;
    Material* metal = new Metal();
    Material* plastic = new Plastic();

    std::cout << "\nBasprice Buildings: " << std::endl;
    std::cout << "Hydro " << hydro->get_label() << ": " << hydro->get_base_price() << std::endl;
    std::cout << "Wind " << wind->get_label() << ": " << wind->get_base_price() << std::endl;
    std::cout << "Solar " << solar->get_label() << ": " << solar->get_base_price() << std::endl;

    std::cout << "\nBasprice Materials: " << std::endl;
    std::cout << "Wood " << ": " << wood->get_price() << std::endl;
    std::cout << "Metal " << ": " << metal->get_price() << std::endl;
    std::cout << "Plastic "<< ": " << plastic->get_price() << std::endl;

    delete hydro;
    delete wind;
    delete solar;
    delete wood;
    delete metal;
    delete plastic;
}

// Check, if Building fits in area
bool CapycitySim::in_area(int b_rows, int b_columns, int b_pos_r, int b_pos_c)
{
    return (((b_pos_c + b_columns) > m_columns) || (b_pos_r + b_rows) > m_rows) ? false : true;
}

// Check collission
bool CapycitySim::check_collission(int b_rows, int b_columns, int b_pos_r, int b_pos_c)
{
    for(int i = 0; i < m_columns; i++)
    {
        for(int j = 0; j < m_rows; j++)
        {
            if((i >= b_pos_c && i < (b_pos_c + b_columns)) && (j >= b_pos_r && j < (b_pos_r + b_rows)))
            {
                if(m_area[i][j] != "0")
                {
                    return false;
                    break;
                }
            }

        }
    }
    return true;
}

// Calculate Total Costs
double CapycitySim::calc_total_costs()
{
    double sum = 0;

    Building* hydro = new Hydropowerstation();
    Building* wind = new Windpowerstation();
    Building* solar = new Solarpanel();


    for(int i = 0; i < m_columns; i++)
    {
        for(int j = 0; j < m_rows; j++)
        {
            if(m_area[i][j] == "W")
            {
                sum += wind->total_costs();
            }
            if(m_area[i][j] == "S")
            {
                sum += solar->total_costs();
            }
            if(m_area[i][j] == "H")
            {
                sum += hydro->total_costs();
            }
        }
    }

    delete hydro;
    delete wind;
    delete solar;

    return sum;
}

// Place Building
void CapycitySim::set_building(Building* building)
{
    int b_rows, b_columns, b_pos_r, b_pos_c;
    int cnt = 0;
    //int select;

    std::cout << "Length: ";
    std::cin >> b_rows;
    std::cout << "Width: ";
    std::cin >> b_columns;
    std::cout << "x-Position: ";
    std::cin >> b_pos_r;
    std::cout << "y-Position: ";
    std::cin >> b_pos_c;
    std::cout << "Building: (1) Hydro (2) Water (3) Solar: " << std::endl;

    bool fits_in_area = in_area(b_rows, b_columns, b_pos_r, b_pos_c);
    bool no_collssion = check_collission(b_rows, b_columns, b_pos_r, b_pos_c);

    for(int i = 0; i < m_columns; i++)
    {
        for(int j = 0; j < m_rows; j++)
        {
            if((i >= b_pos_c && i < (b_pos_c + b_columns)) && (j >= b_pos_r && j < (b_pos_r + b_rows)))
            {
                cnt++;
            }
        }
    }

    current_building_costs = building->get_base_price() + (building->sum_material_costs() * cnt);

    current_total_costs += current_building_costs;

    // Building in area and no collission
    if(fits_in_area && no_collssion)
    {
        for(int i = 0; i < m_columns; i++)
        {
            for(int j = 0; j < m_rows; j++)
            {
                if((i >= b_pos_c && i < (b_pos_c + b_columns)) && (j >= b_pos_r && j < (b_pos_r + b_rows)))
                {
                    // m_area[i][j] = building->get_label();
                    m_area[i][j] = building->get_label();
                }
            }
        }
    }
    // Building not in area
    else if(!fits_in_area)
    {
        std::cout << "Building does not fit in area!" << std::endl;
    }
    // Collission detected
    else
    {
        int choose;
        std::cout << "Collission detected!" << std::endl;
        std::cout << "Do you want to clear the needed space? (1) yes (2) no: ";
        std::cin >> choose;
        switch(choose)
        {
            case 1:
                for(int i = 0; i < m_columns; i++)
                {
                    for(int j = 0; j < m_rows; j++)
                    {
                        if((i >= b_pos_c && i < (b_pos_c + b_columns)) && (j >= b_pos_r && j < (b_pos_r + b_rows)))
                        {
                            m_area[i][j] = building->get_label();
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

    if(building->get_label() == "H")
    {
        current_aqua_costs += current_building_costs;
    }
    else if(building->get_label() == "W")
    {
        current_wind_costs += current_building_costs;
    }
    else if(building->get_label() == "S")
    {
        current_solar_costs += current_building_costs;
    }
}

// Clear Area
void CapycitySim::clear_area()
{
    for(int i = 0; i < m_columns; i++)
    {
        for(int j = 0; j < m_rows; j++)
        {
            m_area[i][j] = BLANK;
        }
    }
    current_total_costs = 0, current_building_costs = 0, current_aqua_costs = 0, current_wind_costs = 0, current_solar_costs = 0;

}

// Print Costs
/*
void CapycitySim::print_material_costs()
{
    Building* hydro = new Hydropowerstation();
    Building* wind = new Windpowerstation();
    Building* solar = new Solarpanel();
    Material* wood = new Wood();
    Material* metal = new Metal();
    Material* plastic = new Plastic();

    std::cout << "\nBaseprice Buildings:" << std::endl;
    std::cout << hydro->get_name() << " " << hydro->get_label() << ": " << hydro->get_base_price() << " Euro"  << std::endl;
    std::cout << wind->get_name() << " " << wind->get_label() << ": " << wind->get_base_price() << " Euro"  << std::endl;
    std::cout << solar->get_name() << " " << solar->get_label() << ": " << solar->get_base_price() << " Euro"  << std::endl;

    std::cout << "\nMaterial Costs:" << std::endl;
    std::cout << wood->get_name() << " " << ": " << wood->get_price() << " Euro"  << std::endl;
    std::cout << metal->get_name() << " " << ": " << metal->get_price() << " Euro"  << std::endl;
    std::cout << plastic->get_name() << " " << ": " << plastic->get_price() << " Euro"  << std::endl;

    std::cout << "\nNeeded Resources: " << std::endl;
    std::cout << hydro->get_name() << " " << hydro->get_label() << ": " << hydro->list_materials() << std::endl;
    std::cout << wind->get_name() << " " << wind->get_label() << ": " << wind->list_materials() << std::endl;
    std::cout << solar->get_name() << " " << solar->get_label() << ": " << solar->list_materials() << "\n" << std::endl;

    delete hydro;
    delete wind;
    delete solar;
    delete wood;
    delete metal;
    delete plastic;
}
*/

// Print Information about the costs and needed materials for all buildings
/*
void CapycitySim::print_information()
{
    Building* hydro = new Hydropowerstation();
    Building* wind = new Windpowerstation();
    Building* solar = new Solarpanel();
    Material* wood = new Wood();
    Material* metal = new Metal();
    Material* plastic = new Plastic();

    // Toal Price
    std::cout << "\n\n––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    std::cout << "Total Price: " << calc_total_costs() << " Euro" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    // Number of Buildings
    int w_cnt = 0, h_cnt = 0, s_cnt = 0;
    for(int i = 0; i < m_columns; i++)
    {
        for(int j = 0; j < m_rows; j++)
        {
            if(m_area[i][j] == "W") {w_cnt++;}
            if(m_area[i][j] == "H") {h_cnt++;}
            if(m_area[i][j] == "S") {s_cnt++;}
        }
    }
    int total = w_cnt + s_cnt + h_cnt;
    std::cout << "Total Buildings: " << total << std::endl;
    std::cout << "Windpowerstations: " << w_cnt << std::endl;
    std::cout << "Hydropowerstations: " << h_cnt << std::endl;
    std::cout << "Solarpanels: " << s_cnt << std::endl;
    std::cout << "------------------------------------------------" << std::endl;


    // Price of Buildings and Materials
    std::cout << "Baseprice Buildings:" << std::endl;
    std::cout << hydro->get_name() << " " << hydro->get_label() << ": " << hydro->get_base_price() << " Euro"  << std::endl;
    std::cout << wind->get_name() << " " << wind->get_label() << ": " << wind->get_base_price() << " Euro"  << std::endl;
    std::cout << solar->get_name() << " " << solar->get_label() << ": " << solar->get_base_price() << " Euro"  << std::endl;

    std::cout << "\nMaterial Costs:" << std::endl;
    std::cout << wood->get_name() << " " << ": " << wood->get_price() << " Euro"  << std::endl;
    std::cout << metal->get_name() << " " << ": " << metal->get_price() << " Euro"  << std::endl;
    std::cout << plastic->get_name() << " " << ": " << plastic->get_price() << " Euro"  << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    // List of Materials
    std::cout << "Needed Resources: " << std::endl;
    std::cout << hydro->get_name() << " " << hydro->get_label() << ": " << hydro->list_materials() << std::endl;
    std::cout << wind->get_name() << " " << wind->get_label() << ": " << wind->list_materials() << std::endl;
    std::cout << solar->get_name() << " " << solar->get_label() << ": " << solar->list_materials() << std::endl;

    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n\n" << std::endl;


    delete hydro;
    delete wind;
    delete solar;
    delete wood;
    delete metal;
    delete plastic;
}
*/

void CapycitySim::print_costs()
{
    std::cout << "Aqua: " << current_aqua_costs << std::endl;
    std::cout << "Wind: " << current_wind_costs << std::endl;
    std::cout << "Solar: " << current_solar_costs << std::endl;
    std::cout << "Total: " << current_total_costs << std::endl;
}