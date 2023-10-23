#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;


#ifndef AquaticAnimal_h
#define AquaticAnimal_h
class AquaticAnimal {
protected:
    string type; //stores what type of animal the AquaticAnimal is.
    int health; //stores the value of the animal’s health. If it reaches 0, the animal will die. Also, a healthier animal is worth more money.
    int hunger; //stores how hungry the animal is. If hunger is too high, the animal will have its health reduced.
    int hunger_rate; //stores the rate at which hunger increases when next_day() is called.
    int sickness; //stores how sick the animal is. If the sickness is too high, the animal will have its health reduced.
    int sickness_rate; //stores the rate at which the animal becomes sick.
    int age; //stores the age of the animal in terms of days. An older animal is worth more.
    double buy_price; //stores how much the animal cost when it was purchased.
    double sell_price; //stores how much money would be gained from selling the fish. Increases with high health and old age. It will be recalculated whenever either of these two variables are changed. Calculations also depend on the type of AquaticAnimal.
    float max_ph; //stores the maximum ph_level that the animal can handle.
    float min_ph; //stores the minimum ph_level that the animal can handle.
    int max_temp; //stores the maximum temperature that the animal can handle.
    int min_temp; //stores the minimum temperature that the animal can handle.
    int volume_requirement; //stores how much space the animal needs.

public:
    AquaticAnimal(string t, int hp, int hun_r, int sick_r, double buy, float max_p, float min_p, int max_t, int min_t, int vol); //an overloaded constructor with 10 parameters: a string for the type of AquaticAnimal; an int for the starting health of the animal; two more ints for the rates at which the AquaticAnimal gets hungry and sick; one double for the buy price of the AquaticAnimal, two floats for the maximum and minimum ph_levels the AquaticAnimal can handle, two ints for the maximum and minimum temperatures the AquaticAnimal can handle, and an int for the amount of space the AquaticAnimal needs. All other variables do not require any new parameters to set.
    virtual ~AquaticAnimal() {cout << ": Animal deleted" << endl;};
    string get_type(); //returns what type of animal the AquaticAnimal is. Has no setter fu*nction because it should not be changed once its value is set in the constructor.
    int get_health(); //returns the health of the AquaticAnimal.
    void set_health(int hp); //sets the health of the AquaticAnimal.
    bool is_dead(); //checks if the AquaticAnimal has a health value of 0. If it is 0, then it is dead (true), otherwise it is alive (false).
    int get_hunger(); //returns the hunger level of the AquaticAnimal
    void set_hunger(int hun); //sets the hunger level of the AquaticAnimal.
    int get_hunger_rate(); // Has no setter function because it should not be changed once its value is set in the constructor.
    int get_sickness(); //returns the sickness level of the AquaticAnimal
    void set_sickness(int sick); //sets the sickness level of the AquaticAnimal
    int get_sickness_rate(); // returns the rate at which the animal becomes sick. Has no setter function because it should not be changed once its value is set in the constructor.
    int get_age(); //returns the age of the AquaticAnimal
    void set_age(int a); //sets the age of the AquaticAnimal
    double get_buy_price(); // Has no setter function because it should not be changed once its value is set in the constructor.
    double get_sell_price(); //returns the amount of money that would be earned from selling the AquaticAnimal.
    virtual void calculate_sell_price() = 0; //sets the sell_price based on how the subclass calculates it.
    float get_max_ph(); // returns the maximum ph_level that the animal can handle. Has no setter function because it should not be changed once its value is set in the constructor.
    float get_min_ph(); // returns the minimum ph_level that the animal can handle. Has no setter function because it should not be changed once its value is set in the constructor.
    int get_max_temp(); // returns the maximum temperature that the animal can handle.  Has no setter function because it should not be changed once its value is set in the constructor.
    int get_min_temp(); // returns the minimum temperature that the animal can handle.  Has no setter function because it should not be changed once its value is set in the constructor.
    int get_volume_requirement(); // returns the amount of space that the animal needs in the tank. Has no setter function because it should not be changed once its value is set in the constructor.
    void next_day(bool filtration); // causes the AquaticAnimal to become older by one day, increases hunger by the hunger_rate, increases sickness by the sickness_rate (and increases sickness more if filtration is false), and decreases health if hunger and sickness is too high.
    virtual void display(); //displays the basic information of an AquaticAnimal. 
    virtual void act() = 0; //allows the AquaticAnimal to do unique actions based on its type.

};

#endif /* AquaticAnimal_h */
