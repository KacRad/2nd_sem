#ifndef CLASS_SERIALIZATION_H
#define CLASS_SERIALIZATION_H
#include <iostream>
#include <type_traits>
#include <string>
enum class FuelType             {Petrol, Diesel, Hybrid, Electric, Hydrogen};
enum class Colour               {White, Black, Red, Green, Blue};
enum class EmissionsStandards   {Euro_1, Euro_2, Euro_3, Euro_4, Euro_5, Euro_6, Euro_7};
enum class Tires                {Summer, Winter, AllSeason};

const char* a_fuel_types[] = {"Petrol", "Diesel", "Hybrid", "Electric", "Hydrogen"};
const char* a_colours[] = {"White", "Black", "Red", "Green", "Blue"};
const char* a_emission_standards[] = {"Euro_1", "Euro_2", "Euro_3", "Euro_4", "Euro_5", "Euro_6", "Euro_7"};
const char* a_tires[] = {"Summer", "Winter", "AllSeason"};

std::ostream& operator<<(std::ostream& os, FuelType en){
    switch(en){
        case FuelType::Petrol:   return os << "Petrol";
        case FuelType::Diesel:   return os << "Diesel";
        case FuelType::Hybrid:   return os << "Hybrid";
        case FuelType::Electric: return os << "Electric";
        case FuelType::Hydrogen: return os << "Hydrogen";
        default:
        return os << static_cast<uint32_t>(en);
    }
}
std::ostream& operator<<(std::ostream& os, Colour en){
    switch(en){
        case Colour::White: return os << "White";
        case Colour::Black: return os << "Black";
        case Colour::Red:   return os << "Red";
        case Colour::Green: return os << "Green";
        case Colour::Blue:  return os << "Blue";
        default:
        return os << static_cast<uint32_t>(en);
    }
}
std::ostream& operator<<(std::ostream& os, EmissionsStandards en){
    switch(en){
        case EmissionsStandards::Euro_1:    return os << "Euro_1";
        case EmissionsStandards::Euro_2:    return os << "Euro_2";
        case EmissionsStandards::Euro_3:    return os << "Euro_3";
        case EmissionsStandards::Euro_4:    return os << "Euro_4";
        case EmissionsStandards::Euro_5:    return os << "Euro_5";
        case EmissionsStandards::Euro_6:    return os << "Euro_6";
        case EmissionsStandards::Euro_7:    return os << "Euro_7";
        default:
        return os << static_cast<uint32_t>(en);
    }
}
std::ostream& operator<<(std::ostream& os, Tires en){
    switch(en){
        case Tires::Summer:     return os << "Summer";
        case Tires::Winter:     return os << "Winter";
        case Tires::AllSeason:  return os << "AllSeason";
        default:
        return os << static_cast<uint32_t>(en);
    }
}




#endif /*CLASS_SERIALIZATION_H*/