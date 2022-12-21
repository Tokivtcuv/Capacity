#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>

#include "Material.h"

class Building
{
    public:
        // Getter & Setter
        std::string get_name();
        void set_name(std::string new_name);
        std::string get_label();
        void set_label(std::string new_label);
        std::vector<Material*> get_material_list();
        double get_base_price();
        void set_base_price(double new_base_price);

        // Methods
        std::string list_materials();
        double total_material_costs();
        double total_costs();
        void add_materials(int, int, int);

    private:
        std::string m_name;
        std::string m_label;
        std::vector<Material*> m_material_list;
        double m_base_price;
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
