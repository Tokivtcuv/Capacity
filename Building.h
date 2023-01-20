#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>
#include <map>

#include "Material.h"

class Building
{
    public:
        // Getter & Setter
        double get_base_price();
        std::string get_name();
        void set_name(std::string name);
        void set_label(std::string label);
        void set_base_price(double price);
        
        std::string get_label();
        std::map<Material*, int> get_material_list();
        double sum_material_costs();
        double total_costs();
        void generate_mat_list(int,int,int);
        std::string list_materials();
        double get_power();


    private:
        std::string m_name;
        std::string m_label;
        std::map<Material*, int> m_material_list;
        // std::vector<Material*> m_material_list;
        double m_base_price;
        double m_power;
};

class Hydropowerstation : public Building
{
    public:
        Hydropowerstation();
};

class Solarpanel : public Building
{
    public:
        Solarpanel();
};

class Windpowerstation : public Building
{
    public:
        Windpowerstation();
};

#endif