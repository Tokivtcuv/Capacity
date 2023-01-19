#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

class Material
{
    public:
        std::string get_name();
        double get_price();
        void set_name(std::string new_name);
        void set_price(double new_price);
    private:
        std::string m_name;
        double m_price;
};

class Wood : public Material
{
    public:
        Wood();
};

class Metal : public Material
{
    public:
        Metal();
};

class Plastic : public Material
{
    public:
        Plastic();
};

#endif