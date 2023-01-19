#include "Material.h"

// Getter & Setter
std::string Material::get_name() { return m_name; }

double Material::get_price() { return m_price; }

void Material::set_name(std::string new_name)
{
    m_name = new_name;
}

void Material::set_price(double new_price)
{
    m_price = new_price;
}

// Constructors
Wood::Wood()
{
    this->set_name("Wood");
    this->set_price(5);
}

Metal::Metal()
{
    this->set_name("Metal");
    this->set_price(10);
}

Plastic::Plastic()
{
    this->set_name("Plastic");
    this->set_price(15);
}