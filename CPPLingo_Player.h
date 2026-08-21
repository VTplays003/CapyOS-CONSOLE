#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <map>
#include <memory>
enum class Race
{
	Capybara,
	Elf,
	Fairy,
	Demon,
	Angel,
	undefined
};
enum class Gender
{
	Male,
	Female,
	NonBinary,
	Unknown
};
class Player
{
public:
	std::string name;
	std::string input;
	std::string characterComfirmation;
	std::string loadedCharacter;
	std::string action;
	std::string lingoAnswer;
	std::string respawnPos;
	Gender gender = Gender::Unknown;
	Race race = Race::undefined;
	int level = 1;
	int XP = 0;
	bool characterVerifcation = false;
	bool hasGuildCard = false;
	//soon to be optimization stuff
	void CharacterCustomizationRace(int input)
	{
		switch (input)
		{
			case 1:
				race = Race::Capybara;
				break;
			case 2:
				race = Race::Elf;
				break;
			case 3:
				race = Race::Fairy;
				break;
			case 4:
				race = Race::Demon;
				break;
			case 5:
				race = Race::Angel;
				break;
			default:
				race = Race::undefined;
				break;
		}
	}
	void CharacterCustomizationGender(int input)
	{
		switch (input)
		{
		case 1:
			gender = Gender::Male;
			break;
		case 2:
			gender = Gender::Female;
			break;
		case 3:
			gender = Gender::NonBinary;
			break;
		default:
			gender = Gender::Unknown;
			break;
		}
	}
	std::string RaceToString(const Player& player)
	{
		switch (player.race)
		{
			case Race::Capybara:
				return "Capybara";
				break;
			case Race::Elf:
				return "Elf";
				break;
			case Race::Fairy:
				return "Fairy";
				break;
			case Race::Demon:
				return "Demon";
				break;
			case Race::Angel:
				return "Angel";
				break;
			default:
				return "Unknown";
				break;
		}
	}	
	std::string GenderToString(const Player& player)
	{
		switch (player.gender)
		{
			case Gender::Male:
				return "Male";
				break;
			case Gender::Female:
				return "Female";
				break;
			case Gender::NonBinary:
				return "Non-Binary";
				break;
			case Gender::Unknown:
				return "Unknown";
				break;
			default:
				return "Unknown";
				break;
		}
	}
};
struct Item
{
	std::string name;
	std::string description;
	int quantity = 1;
	enum class ItemType
	{
		Consumable,
		Equipment,
		Miscellaneous,
		Unknown
	} type = ItemType::Unknown;
	struct ItemStats
	{
		int healthBonus;
		int attackBonus;
		int defenseBonus;
		bool QuestItem;
	} stats = { 0, 0, 0, false };
}; 
class Inventory
{
	public:
		Inventory()
		{
			itemDatabase["Beginner Uniform"] = { "Guild Academy Uniform", "The standard guild uniform for students", 1, Item::ItemType::Equipment, {0, 0, 0, false} };
			itemDatabase["Beginner Armor"] = {"Guild Academy Armor", "The standard guild armor for students. Created with weak leather.", 1, Item::ItemType::Equipment, {0, 0, 0, false}};
			itemDatabase["Beginner Sword"] = { "Guild Academy Sword", "The standard guild sword for students. Created with steel.", 1, Item::ItemType::Equipment, {0, 0, 0, false} };
		}
		//for this function, you have to put the exact item key (the [string] in the constructor), otherwise it won't work.
		void addItem(const std::string& itemName)
		{
			auto it = itemDatabase.find(itemName);
			if (it != itemDatabase.end())
			{
				inventoryObj.push_back(it->second);
				std::cout << "You have obtained: " << it->second.name << "\n";
			}
			else
			{
				std::cout << "Item not found in database." << "\n";
			}
		}
		void useItem(Item item)
		{
			//also placehold
		}
		const std::vector<Item>& getInventory() const
		{
			return inventoryObj;
		}
		std::vector<Item>& getInventory()
		{
			return inventoryObj;
		}
		std::unordered_map<std::string, Item>& getDatabase()
		{
			return itemDatabase;
		}
	private:
		std::vector<Item> inventoryObj;
		std::unordered_map<std::string, Item> itemDatabase;
};
class LingoManual
{
public:
	void viewPage()
	{
		std::cout << (page1 ? "Page 1: Intro to C++" : "Page 1: ???") << "\n";
		std::cout << (page2 ? "Page 2: Variables and Data Types" : "Page 2: ???") << "\n";
		std::cout << "Select the page you want to read. (Page Number only)" << "\n";
		std::getline(std::cin, selectedPage);
		readPage = std::stoi(selectedPage);
		if (readPage == 1)
		{
			std::cout << "C++ is the type of programming language the lingo system runs on." << "\n";
			std::cout << "As you could see a few lines ago, the box had a hint." << "\n";
			std::cout << "You'll need to guess what the box is refering to based on the hint." << "\n";
			std::cout << "In fact, the answer is the language's name. Try typing it." << "\n";
			return;
		}
		else if (readPage == 2)
		{
			std::cout << "Variables are used to store data in a program." << "\n"; 
			std::cout << "They can hold different types of information, such as numbers or text." << "\n";
			std::cout << "Here are the 6 main data types of C++:" << "\n";
			std::cout << "1. int - for integer values" << "\n";
			std::cout << "2. float - for decimal values" << "\n";
			std::cout << "3. double - for larger decimal values" << "\n";
			std::cout << "4. char - for single characters" << "\n";
			std::cout << "5. string - for a STRING of characters (text)" << "\n";
			std::cout << "6. bool - for true or false values" << "\n";
			return;
		}
		else
		{
			std::cout << "Invalid page number." << "\n";
			return;
		}

	}
	void unlockPage(int markedPage)
	{

		//someone tell me how to optimize this i have no clue
		switch (markedPage)
		{
			//this is useless since page1 is true by default but if save gets corrupted then ill use it
			case 1:
			{
				page1 = true;
				break;
			}
			case 2:
			{
				page2 = true;
				break;
			}
		}
	}
private:
	int totalPages = 2;
	std::string selectedPage;
	int readPage = 0;
	bool page1 = true;
	bool page2 = false;
};
struct PlayerProgression
{
	bool prologue1_1 = false;
	bool prologue1_2_1 = false;
	bool prologue1_2_2 = false;
	bool prologue1_2_3 = false;
	bool prologue1_2 = false;
	bool prologue1_3 = false;
	bool prologue1 = false;
	bool prologueComplete = false;
};
class SaveSystem
{
public:
	std::string loadCharacter;
	void SaveGame(const Player& playerObj, const PlayerProgression& progressionObj, const std::vector<Item>& inventoryObj)
	{
		std::ofstream saveFile("savefile.txt");
		if (!saveFile)
		{
			std::cout << "Error: Unable to open save file for writing." << "\n";
			return;
		}
		saveFile << "Name: " << playerObj.name << "\n";
		saveFile << "Race: " << static_cast<int>(playerObj.race) << "\n";
		saveFile << "Gender: " << static_cast<int>(playerObj.gender) << "\n";
		saveFile << "Prologue - Act 1, Puzzle 1: " << static_cast<int>(progressionObj.prologue1_1) << "\n";
		saveFile << "Has Guild Card: " << static_cast<int>(playerObj.hasGuildCard) << "\n";
		saveFile << "Prologue - Act 1, Puzzle 2: " << static_cast<int>(progressionObj.prologue1_2) << "\n";
		saveFile << "---------------------------------------------" << "\n";
		saveFile << "Inventory:" << "\n";
		for (const auto& item : inventoryObj)
		{
			saveFile << item.name << "\n";
			saveFile << item.description << "\n";
			saveFile << item.quantity << "\n";
		}
		saveFile.close();
	}
	void LoadGame(Player& playerObj, PlayerProgression& progressionObj, std::vector<Item>& inventoryObj, const std::unordered_map<std::string, Item>& itemDatabase)
	{
		std::string saveText;
		std::ifstream loadFile("savefile.txt");
		if (!loadFile)
		{
			std::cout << "File loading unsucessful" << "\n";
			return;
		}
		while (std::getline(loadFile, saveText))
		{
			if (saveText.find("Name:") == 0)
			{
				playerObj.name = saveText.substr(6);
			}
			else if (saveText.find("Race:") == 0)
			{
				playerObj.race = static_cast<Race>(std::stoi(saveText.substr(6)));
			}
			else if (saveText.find("Gender:") == 0)
			{
				playerObj.gender = static_cast<Gender>(std::stoi(saveText.substr(8)));
			}
			else if (saveText.find("Prologue - Act 1, Puzzle 1:") == 0)
			{
				progressionObj.prologue1_1 = static_cast<bool>(std::stoi(saveText.substr(28)));
			}
			else if (saveText.find("Has Guild Card:") == 0)
			{
				playerObj.hasGuildCard = static_cast<bool>(std::stoi(saveText.substr(16)));
			}
			else if (saveText.find("Prologue - Act 1, Puzzle 2:") == 0)
			{
				progressionObj.prologue1_2 = static_cast<bool>(std::stoi(saveText.substr(28)));
			}
			else if (saveText.find("Inventory:") == 0)
			{
				for (int i = 0; i < 3; i++)
				{
					Item importedItem;
					std::getline(loadFile, importedItem.name);
					std::getline(loadFile, importedItem.description);
					std::string quantityStr;
					std::getline(loadFile, quantityStr);
					importedItem.quantity = std::stoi(quantityStr);
					auto it = itemDatabase.find(importedItem.name);
					if (it != itemDatabase.end())
					{
						importedItem.type = it->second.type;
						importedItem.stats = it->second.stats;
					}
					inventoryObj.push_back(importedItem);
				}
			}
		}
		playerObj.characterVerifcation = true;
		loadFile.close();
	}
};
//chapter 1_3 stuff right here guys
class CombatSystem 
{
public:
	struct Enemy
	{
		std::string name;
		int level = 0;
		int health = 100;
		int strength = 1;
		int defense = 1;
	};
	Enemy* currentEnemy = nullptr;

	CombatSystem()
	{
		enemyDatabase["TestDummy"] = { "Test Dummy", 0, 100, 0, 0 };
	}

	void startCombat()
	{
		if (!(currentEnemy == nullptr))
		{
			inCombat = true;
		}
		else
		{
			inCombat = false;
		}
	}
	void playerTurn()
	{

	}
	void enemyTurn()
	{

	}
	const std::unordered_map<std::string, Enemy> GetEnemies()
	{
		return enemyDatabase;
	}
private:
	bool inCombat = false;
	std::unordered_map<std::string, Enemy> enemyDatabase;
};
class AcademySystem
{
public:
	std::string addedClass;
	struct AcademyClass
	{
		std::string name;
		std::string description;
		int levelRequirement = 0;
		int ID = 0;
	};
	AcademySystem()
	{
		classesAvailible[1] = { "Beginner Combat Class", "A class for beginners to learn basic combat skills.", 1, 1001};
		classesAvailible[2] = { "Beginner C++ Class", "A class for beginners to learn basic C++ programming. Teaches you all the way until page 10 of the manual.", 1, 2001};
	}

	std::map<int, AcademyClass> AccessClasses()
	{
		return classesAvailible;
	}

	void addClass(const std::map<int, AcademyClass>& classList)
	{
		std::cout << "Available Classes:" << "\n";
		for (const auto& pair : classList)
		{
			std::cout << " - " << pair.second.name << ": " << pair.second.description << " (Level " << pair.second.levelRequirement << pair.second.ID << ")" << "\n";
		}
		std::cout << "Select a class to enroll in by typing the class ID." << "\n"; 
		std::getline(std::cin, addedClass);
		int classID = std::stoi(addedClass);
		auto finder = classesAvailible.find(classID);
		if (finder != classesAvailible.end())
		{
			classesEnrolled.push_back(finder->second);
		}
		else
		{
			throw std::runtime_error("Item not found in database.");
		}
		
	}
	void attendClass(const std::vector<AcademyClass>& enrolledClasses, CombatSystem& combatSys)
	{
		for (const auto& classes : enrolledClasses)
		{
			if (classes.ID == 1001)
			{
				std::cout << "Today you will learn how to fight enemies." << "\n";
				auto enemies = combatSys.GetEnemies();
				combatSys.currentEnemy = &enemies["TestDummy"];
			}
		}
	}
private:
	std::map<int, AcademyClass> classesAvailible;
	std::vector<AcademyClass> classesEnrolled;
};
