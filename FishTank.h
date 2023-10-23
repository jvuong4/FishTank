//#include <iostream>

//#include "AquaticAnimal.h"
//#include "DerivedAnimal.h"


#include "Goldfish.h"
#include "Turtle.h"
#include "Shrimp.h"
#include "Arowana.h"

#ifndef FishTank_h
#define FishTank_h
class FishTank {
private:
    AquaticAnimal** animals;
    //stores all of the abstract animals that the user will raise.
    //You can't just have a dynamic array of abstract classes, since they can't be instantiated/initalized as a non-concrete class
    //A dynamic array of pointers of abstract classes will work, though.
    int num_animals; //stores the amount of living animals in the tank. Intentionally has no setter function, since it should only be incremented or decremented from add_animal() and clear_dead_animals().
    int max_animals; //stores the maximum amount of animals in the tank. Intentionally has no setter function, since it will not be changed.
    int volume; //stores the maximum amount of animals in the tank. Intentionally has no setter function, since it will not be changed once determined.
    int occupied_volume; //The amount of space that the living fish in the tank are occupying. To add a new AquaticAnimal to the tank, there needs to be enough space in the tank to hold the AquaticAnimal.
    int temperature; //stores the water temperature of the tank. An AquaticAnimal will not be available to purchase if they should not live at that temperature.
    float ph_level; //stores the ph_level of the tank. An AquaticAnimal will not be available to purchase if they should not live at that ph_level.
    bool has_filtration; //stores whether or not the tank has proper filtration. If it has no filtration, the animals may become sick faster.
    
public:
    FishTank(int max, int vol, int temp, float ph, bool filt); //constructor with 5 parameters: one int to set the size of the animals dynamic array, 2 ints to set the volume and temperature, a float to set the ph_level, and a bool to set the filtration.
    ~FishTank();
    
    AquaticAnimal** getAnimals(); //returns the dynamic array of animal pointers.
    AquaticAnimal* getAnimal(int index); //returns a specific animal at th specified index
    
    int get_num_animals(); //returns the num_animals int.
    void set_num_animals(int num); //sets num_animals int to a specified value.
    int get_max_animals(); //returns the max_animals int.
    int get_volume(); //returns the volume int.
    int get_occupied(); //returns the combined amount of volume that the fish are comfortably occupying.
    void set_occupied(int vol); //sets the amount of space in the tank that is already occupied by an AquaticAnimal.
    int get_temperature(); //returns the temperature int.
    void set_temperature(int temp); //sets the temperature with temp.
    float get_ph_level(); //returns the pl_level float.
    void set_ph_level(float ph); //sets the ph_level with ph.
    bool get_filtration(); //returns the filtration boolean.
    void set_filtration(bool filt); //sets the filtration with filt.
    
    void next_day(); //calls next_day() for each AquaticAnimal in animals. Allows the animals to become older, hungrier, sicker, and possibly die.
    void add_animal(AquaticAnimal* animal); //if possible, add a new AquaticAnimal to animals and increase num_animals and occupied_volume.
    void remove_animal(int index); //remove the AquaticAnimal from animals at index. This will decrease num_animals and occupied_volume.
    
    void arowana_event(); //if there is both an Arowana and a Goldfish in the tank, kills a random Goldfish in animals with remove_animal() and improves the health and reduces the hunger of a random Arowana in animals.
    void shrimp_event(); //for each Shrimp in the tank, there is a chance that every Goldfish and Turtle in the tank will have its sickness reduced. Shrimps and Arowanas will never receive this benefit.

};

#endif /* FishTank_h */
