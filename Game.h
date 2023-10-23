#include "FishTank.h"

#include <fstream>
#include <sstream>
#include <iomanip>

#ifndef Game_h
#define Game_h

class Game {
private:
    string filename; //used when loading and saving a game. Important for accessing files.
    FishTank* tank; //stores a pointer to the Fish Tank that will be used in the game.
    double money; //stores how much money the player owns. Determines what can be bought, and is used in won_game() and lost_game().

public:
    Game(string fn, bool is_new); //constructor for a game that has 2 parameters. The first parameter is for filename, so that it knows what file to open and/or save to. The second parameter is for a boolean is_new, which determines if the constructor should either make a new Game or load a pre-existing game.
    
    void start_game(); //starts a new game instead of loading a pre-existing game.
    void load_game(); //resumes a game from a pre-existing file from filename.
    void save_game(); //writes to a file based on filename to save progress.
    
    bool won_game(); //checks if tank has enough money to win.
    bool lost_game(); //checks if there is no AquaticAnimal in tank, and if there is not enough money to purchase an AquaticAnimal. Causes the user to lose the game.
    
    void next_day(); //handles the game loop. First, it calls next_day() for tank so that every AquaticAnimal can have their next_day() functions called. From there, it allows for user interaction via menus, and checks wonGame() and lostGame(). wonGame() or lostGame() returning true will cause the game to end. If the game did not end, then it will reiterate.
    void first_day(); //nearly identical to next_day. However, it will not call next_day for tank. This is so that no AquaticAnimal in tank will call their next_day() function more than necessary.
    
    void sell_fish(int index); //accesses the AquaticAnimal at location index in AquaticAnimal* tank, increases the amount of money earned based on the AquaticAnimal’s sell_price, and removes the AquaticAnimal
    bool buy_fish(int type); //if possible, adds a new AquaticAnimal to the tank, and increments the tank’s num_animals and occupied_volume. It will also decrease the amount of money based on the buy_price. The AquaticAnimal added will be based on the value of type, with a switch-case. If the AquaticAnimal cannot be bought, the game will explain why and return false without buying the AquaticAnimal. On success, it will return true.
    
    bool feed_fish(int index); //has the user feed an AquaticAnimal so that it is no longer hungry. If the AquaticAnimal is not actually hungry, the game will say that it is not hungry and return false. Otherwise, it will return true.
    bool treat_fish(int index); //spends money in order to reduce the sickness of an AquaticAnimal. If the AquaticAnimal is not sick, or if there is not enough money to provide treatment to the AquaticAnimal, the function will return false. Otherwise, it will return true.
    void display_fish_list(); //iterates through the dynamic array of AquaticAnimals in tank and displays their basic information, along with their index in the array.
    
    //This function will get an integer between an accepted range of values.
    //If the process fails, or if it is not within the accepted range,
    //it will continue to get the value for the user's response until it works.
    int getIntResponse(int min, int max);
    
    //this deletes the FishTank when the game is over.
    //Deleting the FishTank should delete all of its animals.
    void deleteTank();
};

#endif /* Game_h */
