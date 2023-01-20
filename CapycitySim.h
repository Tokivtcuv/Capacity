#ifndef CAPYCITYSIM_H
#define CAPYCITYSIM_H

#include <iostream>
#include <list>
#include <string>

#include "Building.h"

class CapycitySim
{
    public:
        CapycitySim(int rows, int columns);
        //const char BLANK = 32;
        std::string BLANK = "0";
        void start_menu();
        void create_field(int rows, int columns);
        void print_area();
        void set_building(Building* building);
        void clear_area();
        void print_material_costs();
        void print_information();
        bool in_area(int b_rows, int b_columns, int b_pos_r, int b_pos_c);
        bool check_collission(int b_rows, int b_columns, int b_pos_r, int b_pos_c);
        double calc_total_costs();

        void print_costs();
        void print_building_material_cost();

        double current_total_costs = 0, current_building_costs = 0, current_aqua_costs = 0, current_wind_costs = 0, current_solar_costs = 0;

    private:
        int m_rows;
        int m_columns;
        std::string** m_area;
};

#endif