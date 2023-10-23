#include "FishTank.h"


FishTank::FishTank(int max, int vol, int temp, float ph, bool filt) //constructor with 5 parameters: one int to set the size of the animals dynamic array, 2 ints to set the volume and temperature, a float to set the ph_level, and a bool to set the filtration.
{
    num_animals = 0;
    max_animals = max;
    volume = vol;
    occupied_volume = 0;
    temperature = temp;
    ph_level = ph;
    has_filtration = filt;
    
    animals = new AquaticAnimal*[max_animals];
    for(int i = 0; i < max_animals; i++)
    {
        animals[i] = nullptr;
    }
}
FishTank::~FishTank()
{
    delete[] animals;
}

AquaticAnimal** FishTank::getAnimals() //returns the dynamic array of animals.
{
    return animals;
}
AquaticAnimal* FishTank::getAnimal(int index) //returns a specific animal at th specified index
{
    if(animals[index] != nullptr)
    {
        return animals[index];
    }
    else //this should not ever run.
    {
        cout << "Critical Error: no animal at " << index << endl;
        return animals[0];
    }
}
int FishTank::get_num_animals() //returns the num_animals int.
{
    return num_animals;
}
void FishTank::set_num_animals(int num) //sets num_animals int to a specified value.
{
    num_animals = num;
}
int FishTank::get_max_animals() //returns the max_animals int.
{
    return max_animals;
}
int FishTank::get_volume() //returns the volume int.
{
    return volume;
}
int FishTank::get_occupied() //returns the combined amount of volume that the fish are comfortably occupying.
{
    return occupied_volume;
}
void FishTank::set_occupied(int vol) //sets the amount of space in the tank that is already occupied by an AquaticAnimal.
{
    occupied_volume = vol;
}
int FishTank::get_temperature() //returns the temperature int.
{
    return temperature;
}
void FishTank::set_temperature(int temp) //sets the temperature with temp.
{
    temperature = temp;
}
float FishTank::get_ph_level() //returns the pl_level float.
{
    return ph_level;
}
void FishTank::set_ph_level(float ph) //sets the ph_level with ph.
{
    ph_level = ph;
}
bool FishTank::get_filtration() //returns the filtration boolean.
{
    return has_filtration;
}
void FishTank::set_filtration(bool filt) //sets the filtration with filt.
{
    has_filtration = filt;
}





void FishTank::next_day() //calls next_day() for each AquaticAnimal in animals. Allows the animals to become older, hungrier, sicker, and possibly die.
{
    for(int i = 0; i < num_animals; i++)
    {
        animals[i]->next_day(has_filtration);
        if(animals[i]->is_dead())
        {
            cout << "Your " << animals[i]->get_type() << " has died." << endl;
            remove_animal(i);
            i--;
        }
    }
}
void FishTank::add_animal(AquaticAnimal* animal) //if possible, add a new AquaticAnimal to animals and increase num_animals and occupied_volume.
{
    if(num_animals < max_animals)
    {
        animals[num_animals] = animal;
        occupied_volume += animals[num_animals]->get_volume_requirement();
        num_animals++;
    }
    else
    {
        cout << "ERROR: TOO MANY ANIMALS" << endl;
    }
}

void FishTank::remove_animal(int index) //remove the AquaticAnimal from animals at index. This will decrease num_animals and occupied_volume.
{
    occupied_volume -= animals[index]->get_volume_requirement();
    delete animals[index];
    for(int i = index; i < num_animals-1; i++)
    {
        animals[i] = animals[i+1];
    }
    animals[num_animals-1] = nullptr;
    num_animals--;
}

void FishTank::arowana_event() //if there is both an Arowana and a Goldfish in the tank, kills a random Goldfish in animals with remove_animal() and improves the health and reduces the hunger of a random Arowana in animals.
{
    int ArowanaIndex = -1; //stores the FIRST instance of Arowana (the oldest Arowana)
    int GoldfishIndex = -1; //stores the LAST instance of Goldfish (the youngets Goldfish)
    
    for(int i = 0; i < num_animals; i++)
    {
        if(ArowanaIndex == -1 && animals[i]->get_type() == "Arowana")
        {
            ArowanaIndex = i;
        }
        else if(animals[i]->get_type() == "Goldfish")
        {
            GoldfishIndex = i;
        }
    }
    
    if(ArowanaIndex != -1 && GoldfishIndex != -1) //if there is both an Arowana and a Goldfish
    {
        //The Arowana has a chance to eat of Goldfish if it is hungry. More likely to happen the hungrier it is, and guaranteed at >= 16 hunger.
        //Probability = [(Arowana's hunger) * 5 + 20]% chance
        if(rand() % 100 < animals[ArowanaIndex]->get_hunger() * 5 + 20)
        {
            cout << "Your Arowana ate a Goldfish!" << endl << endl;
            
            //increases the Arowana's health equal to the Goldfish's health plus its age, minus 11.
            //this means an age 1, health 20 Goldfish will improve the Arowana's sell price by more than $10 and result in a large profit.
            animals[ArowanaIndex]->set_health(animals[ArowanaIndex]->get_health() + animals[GoldfishIndex]->get_health() + animals[GoldfishIndex]->get_age() - 11);
            
            //feeds the Arowana
            animals[ArowanaIndex]->set_hunger(0);
            
            //kills the Goldfish
            remove_animal(GoldfishIndex);
            
            cout << "\nPress 'enter' to continue." << endl;
            string nul;
            getline(cin, nul); //gets the user's 'response' and saves it to nothing.
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
        }
    }
    
}
void FishTank::shrimp_event() //for each Shrimp in the tank, there is a chance that every Goldfish and Turtle in the tank will have its sickness reduced. Shrimps and Arowanas will never receive this benefit.
{
    int ShrimpCount = 0; //counts how many Shrimp are in the tank
    int SuccessCount = 0; //the amount of Shrimp that succeed in cleaning the tank
    
    for(int i = 0; i < num_animals; i++)
    {
        if(animals[i]->get_type() == "Shrimp")
        {
            ShrimpCount++;
            
            //This shrimp has a small chance to improve the quality of the tank and another separate chance to improve its own health.
            //This chance is equal to [(Shrimp's health) * 3 + (Shrimp's Age)]%
            //This means that as long as the shrimp is healthy, its cleaning abilities will steadily improve.
            if(rand() % 100 < animals[i]->get_health() * 3 + animals[i]->get_age())
            {
                SuccessCount++;
                //improves the Shrimp's health by 1, 2, or not at all.
                animals[i]->set_health(animals[i]->get_health() + rand() % 3);
            }
        }
    }
    
    if(SuccessCount > 0)
    {
        if(SuccessCount == 1 && ShrimpCount == 1)
        {
            cout << "Wow! Your Shrimp really cleaned up the tank!" << endl << endl;
        }
        else if (SuccessCount == ShrimpCount)
        {
            cout << "Wow! All of your Shrimp really cleaned up the tank!" << endl << endl;
        }
        else
        {
            cout << "Wow! " << SuccessCount << " of your " << ShrimpCount << " Shrimps really cleaned up the tank!" << endl << endl;
        }
        
        //A cleaner tank helps Goldfish and Turtles and reduces sickness.
        //There is also a small chance to increase the Goldfish or Turtle's Health.
        for(int i = 0; i < num_animals; i++)
        {
            if(animals[i]->get_type() == "Goldfish" || animals[i]->get_type() == "Turtle")
            {
                
                //reduces the animal's sickness equal to the value of SuccessCount * 2 + 1.
                //an animal has a minimum sickness value of 0. (this is part of set_sickness())
                animals[i]->set_sickness(animals[i]->get_sickness() - (SuccessCount * 2 + 1));
                
                //The chance to increase the animal's health by a random number from 1 to 5 is based on how many successes there were.
                //This chance is equal to [(# of Successes) * 10]%
                if(rand() % 100 < SuccessCount * 10)
                {
                    animals[i]->set_health(animals[i]->get_health() + 1 + rand() % 5);
                    cout << "Woah! Your " << animals[i]->get_type() << " is looking great after the cleaning! Their health definitely improved!" << endl;
                }
                else
                {
                    cout << "Your " << animals[i]->get_type() << " appreciates the cleaning." << endl;
                }
            }
        }
        
        cout << "\nPress 'enter' to continue." << endl;
        string nul;
        getline(cin, nul); //gets the user's 'response' and saves it to nothing.
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    }
    
}
