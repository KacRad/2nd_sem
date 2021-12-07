#include <iostream>
#include <array>
#include <string.h>
#include <string>
#include <type_traits>
#include <fstream>
#include <stdexcept>
#include "class_serialization.h"

struct Wheels{
    Wheels()
        : size(16), tires(Tires::Summer)
    {
    }
    Wheels(uint32_t c_size, Tires c_tires)
        : size(c_size), tires(c_tires)
    {
    }
    uint32_t size;
    Tires tires;
};

class Car{
public: 
//constructors=================================================================
    Car()
        : fuel_type(FuelType::Petrol), max_speed(180), colour(Colour::White), wheels()
    {
    }
    Car(FuelType c_fuel_type, uint32_t c_max_speed, Colour c_colour, std::array<Wheels, 4> c_wheels)
        : fuel_type(c_fuel_type), max_speed(c_max_speed), colour(c_colour), wheels(c_wheels)
    {
    }
    Car(FuelType c_fuel_type, uint32_t c_max_speed, Colour c_colour)
        : fuel_type(c_fuel_type), max_speed(c_max_speed), colour(c_colour)
    {
    }
    Car(const Car& other)
        : fuel_type(other.fuel_type), max_speed(other.max_speed), colour(other.colour), wheels(other.wheels)
    {
    }
    ~Car()
    {
    }
//setters======================================================================
    void set_fuel_type(FuelType ft){
        fuel_type = ft;
    }
    void set_max_speed(uint32_t ms){
        max_speed = ms;
    }
    void set_colour(Colour c){
        colour = c;
    }
    void set_wheels(uint32_t w_size, Tires season){
        Wheels wheel(w_size, season);
        for(int i = 0; i < 4; i++){
            wheels[i] = wheel;
        }
    }
    void set_wheels(std::array<Wheels, 4> wh){
        wheels = wh;
    }
//getters======================================================================
    FuelType get_fuel_type(){
        return fuel_type;
    }
    uint32_t get_max_speed(){
        return max_speed;
    }
    Colour get_colour(){
        return colour;
    }
    std::array<Wheels, 4> get_wheels(){
        return wheels;
    }
//=====================================
protected:
    FuelType fuel_type;
    uint32_t max_speed;
    Colour colour;
    std::array<Wheels, 4> wheels;
};

class PersonalCar : public Car{
public:
//constructors=================================================================
    PersonalCar()
        : Car(), number_of_seats(4), emission(EmissionsStandards::Euro_1)
    {
    }
    PersonalCar(FuelType c_fuel_type, uint32_t c_max_speed, Colour c_colour, std::array<Wheels, 4> c_wheels, uint8_t seats, EmissionsStandards standard)
        : Car(c_fuel_type, c_max_speed, c_colour, c_wheels), number_of_seats(seats), emission(standard)
    {
    }
    PersonalCar(const PersonalCar& other)
        :  number_of_seats(other.number_of_seats), emission(other.emission)
    {
        fuel_type = other.fuel_type;
        max_speed = other.max_speed; 
        colour = other.colour;
        wheels = other.wheels;
    }
    ~PersonalCar()
    {
    }
//setters======================================================================
    void set_number_of_seats(uint8_t seats){
        number_of_seats = seats;
    }
    void set_emission_standards(EmissionsStandards standard){
        emission = standard;
    }
//getters======================================================================
    uint8_t get_number_of_seats(){
        return number_of_seats;
    }
    EmissionsStandards get_emission_standards(){
        return emission;
    }

//=====================================
protected:
    uint8_t number_of_seats;
    EmissionsStandards emission;
};

const char* establish_ext(const char* name){
    const char* ext = &name[strlen(name) - 4];
    return ext;
}
//SERIALIZE TO BINARY AND TXT FORMATS BASED ON FILE EXTENSION =================
template<typename T>
void serialize(T s_object, const char* file_name){
    if(strcmp(".bin", establish_ext(file_name)) == 0){
        std::ofstream f(file_name, std::ios::out | std::ios::app | std::ios::binary);
        if(f.is_open()){    
            f.write(reinterpret_cast<char*>(&s_object), sizeof(s_object));
            f.close();
        } else throw std::runtime_error("Unable to open file");
    } else if (strcmp(".txt", establish_ext(file_name)) == 0) {
        std::ofstream f(file_name, std::ios::out | std::ios::app);
        if(f.is_open()){  
            std::array<Wheels, 4> w_wheels = s_object.get_wheels();
            Wheels w_wheel = w_wheels[0];
            f << a_fuel_types[static_cast<int>(s_object.get_fuel_type())] << "\n";
            f << s_object.get_max_speed() << "\n";
            f << a_colours[static_cast<int>(s_object.get_colour())] << "\n";
            f << w_wheel.size << "\n";
            f << a_tires[static_cast<int>(w_wheel.tires)] << "\n";
            f << static_cast<int>(s_object.get_number_of_seats()) << "\n";
            f << a_emission_standards[static_cast<int>(s_object.get_emission_standards())];
            f.close();
        } else throw std::runtime_error("Unable to open file");
    } else {
        throw std::invalid_argument("Wrong file extension");
    }
}


//UNSERIALIZE FROM BINARY FILE =====================================================
void unserialize(PersonalCar& obj, const char* file_name){
    if(strcmp(".bin", establish_ext(file_name))){
        FuelType re_fuel;
        uint32_t re_speed;
        Colour re_colour;
        std::array<Wheels, 4> re_wheels;
        uint8_t re_number_of_seats;
        EmissionsStandards re_emission;
        std::ifstream rd(file_name, std::ios::in | std::ios::binary);
        if(rd.is_open()){
            while(rd.is_open()){
                rd.read((char*)& re_fuel, sizeof(re_fuel));
                rd.read((char*)& re_speed, sizeof(re_speed));
                rd.read((char*)& re_colour, sizeof(re_colour));
                rd.read((char*)& re_wheels, sizeof(re_wheels));
                rd.read((char*)& re_number_of_seats, sizeof(re_number_of_seats));
                rd.read((char*)& re_emission, sizeof(re_emission));
                if(rd.eof()){
                    rd.close();
                }
            }
            obj.set_fuel_type(re_fuel);
            obj.set_max_speed(re_speed);
            obj.set_colour(re_colour);
            obj.set_wheels(re_wheels);
            obj.set_number_of_seats(re_number_of_seats);
            obj.set_emission_standards(re_emission);
        } else throw std::runtime_error("Unable to open file");
    }else throw std::invalid_argument("Wrong File Extension");
}

int main(int argc, char* argv[]){
    Wheels my_wheels(19, Tires::AllSeason);
    std::array<Wheels, 4> all_wheels;
    for(auto i : all_wheels){
        i = my_wheels;
    }
    PersonalCar car(FuelType::Hybrid, 320, Colour::Black, all_wheels, 5, EmissionsStandards::Euro_5);
    PersonalCar car2;
    PersonalCar car3;

    try{
        if ((argc == 2) && (strcmp("txt", argv[1]) == 0)){
            serialize(car, "serialized_car.txt");
        } 
        else if ((argc == 2) && (strcmp("bin", argv[1]) == 0) ){
            serialize(car2, "serialized_car2.bin");
        } 
        else if(argc != 2 || strcmp("--help", argv[1]) == 0){
            std::string message;
            std::ifstream help("help.txt", std::ios::in);
            while(getline(help, message)){
                std::cout << message << std::endl;
            }
            help.close();
        }
    }
    catch(std::runtime_error file_error){
        std::cout << file_error.what();
    }
    catch(std::invalid_argument wrong_ext){
        std::cout << wrong_ext.what();
    }

    return 0;
}