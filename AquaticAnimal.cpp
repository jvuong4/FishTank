#include "AquaticAnimal.h"

AquaticAnimal::AquaticAnimal(string t, int hp, int hun_r, int sick_r, double buy, float max_p, float min_p, int max_t, int min_t, int vol)
//an overloaded constructor with 10 parameters: a string for the type of AquaticAnimal; an int for the starting health of the animal; two more ints for the rates at which the AquaticAnimal gets hungry and sick; one double for the buy price of the AquaticAnimal, two floats for the maximum and minimum ph_levels the AquaticAnimal can handle, two ints for the maximum and minimum temperatures the AquaticAnimal can handle, and an int for the amount of space the AquaticAnimal needs. All other variables do not require any new parameters to set.
{
    type = t;
    health = hp;
    hunger = 0;
    hunger_rate = hun_r;
    sickness = 0;
    sickness_rate = sick_r;
    age = 1;
    
    buy_price = buy;
    sell_price = 0.0;
    
    max_ph = max_p;
    min_ph = min_p;
    max_temp = max_t;
    min_temp = min_t;
    volume_requirement = vol;
}

std::string AquaticAnimal::get_type()
//returns what type of animal the AquaticAnimal is. Has no setter function because it should not be changed once its value is set in the constructor.
{
    return type;
}
int AquaticAnimal::get_health() //returns the health of the AquaticAnimal.
{
    return health;
}
void AquaticAnimal::set_health(int hp) //sets the health of the AquaticAnimal.
{
    health = hp;
}
bool AquaticAnimal::is_dead() //checks if the AquaticAnimal has a health value of 0. If it is 0, then it is dead (true), otherwise it is alive (false).
{
    return health <= 0;
}
int AquaticAnimal::get_hunger() //returns the hunger level of the AquaticAnimal
{
    return hunger;
}
void AquaticAnimal::set_hunger(int hun) //sets the hunger level of the AquaticAnimal.
{
    hunger = hun;
    if(hunger < 0)
    {
        hunger = 0;
    }
}
int AquaticAnimal::get_hunger_rate() // Has no setter function because it should not be changed once its value is set in the constructor.
{
    return hunger_rate;
}
int AquaticAnimal::get_sickness() //returns the sickness level of the AquaticAnimal
{
    return sickness;
}
void AquaticAnimal::set_sickness(int sick) //sets the sickness level of the AquaticAnimal
{
    sickness = sick;
    if(sickness < 0)
    {
        sickness = 0;
    }
}
int AquaticAnimal::get_sickness_rate() // returns the rate at which the animal becomes sick. Has no setter function because it should not be changed once its value is set in the constructor.
{
    return sickness_rate;
}
int AquaticAnimal::get_age() //returns the age of the AquaticAnimal
{
    return age;
}
void AquaticAnimal::set_age(int a) //sets the age of the AquaticAnimal
{
    age = a;
}
double AquaticAnimal::get_buy_price() // Has no setter function because it should not be changed once its value is set in the constructor.
{
    return buy_price;
}
double AquaticAnimal::get_sell_price() //returns the amount of money that would be earned from selling the AquaticAnimal.
{
    return sell_price;
}
float AquaticAnimal::get_max_ph() // returns the maximum ph_level that the animal can handle. Has no setter function because it should not be changed once its value is set in the constructor.
{
    return max_ph;
}
float AquaticAnimal::get_min_ph() // returns the minimum ph_level that the animal can handle. Has no setter function because it should not be changed once its value is set in the constructor.
{
    return min_ph;
}
int AquaticAnimal::get_max_temp() // returns the maximum temperature that the animal can handle.  Has no setter function because it should not be changed once its value is set in the constructor.
{
    return max_temp;
}
int AquaticAnimal::get_min_temp() // returns the minimum temperature that the animal can handle.  Has no setter function because it should not be changed once its value is set in the constructor.
{
    return min_temp;
}
int AquaticAnimal::get_volume_requirement() // returns the amount of space that the animal needs in the tank. Has no setter function because it should not be changed once its value is set in the constructor.
{
    return volume_requirement;
}
void AquaticAnimal::next_day(bool filtration) // causes the AquaticAnimal to become older by one day, increases hunger by the hunger_rate, increases sickness by the sickness_rate (and increases sickness more if filtration is false), and decreases health if hunger and sickness is too high.
{
    age++;
    hunger += hunger_rate;
    sickness += sickness_rate;
    if(!filtration) //a lack of a filter further intensifies sickness. Get one as soon as possible!
    {
        sickness = sickness * 3 / 2;
    }
    else
    {
        sickness = sickness * 6 / 5;
    }
    
    if(hunger > 20)
    {
        health -= hunger - 20;
    }
    if(sickness > 20)
    {
        health -= sickness - 20;
    }
}
void AquaticAnimal::display() //displays the basic information of an AquaticAnimal. Will be used in
{
    cout << endl << type << ": Age " << age << "\nHealth: " << health << "\tHunger: ";
    if(hunger <= 0)
    {
        cout << "Full";
    }
    else if(hunger <= 10)
    {
        cout << "Normal";
    }
    else if(hunger <= 20)
    {
        cout << "Hungry";
    }
    else
    {
        cout << "Starving";
    }
    cout << "\tSickness: ";
    if(sickness <= 0)
    {
        cout << "Medicated";
    }
    else if(sickness <= 10)
    {
        cout << "Fair";
    }
    else if(sickness <= 20)
    {
        cout << "Unwell";
    }
    else
    {
        cout << "Sick";
    }
    cout << endl << endl;
}
