#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <typename T>
class EntityList
{
private:
    int arraySize;
    struct Entity
    {
        int id;
        string name;
    } *entities;

public:
    EntityList(int arraySize)
    {
        this->arraySize = arraySize;
        entities = new Entity[arraySize];
        // Initialize the entities array with default values
        for (int i = 0; i < arraySize; i++)
        {
            entities[i].id = -1; // Using -1 as an indicator of uninitialized ID
            entities[i].name = "";
        }
    }

    ~EntityList()
    {
        delete[] entities;
    }

    bool isDuplicateID(int id)
    {
        for (int i = 0; i < arraySize; i++)
        {
            if (entities[i].id == id)
            {
                return true;
            }
        }
        return false;
    }

    bool addEntity(int id, string name)
    {
        if (isDuplicateID(id))
        {
            return false;
        }
        for (int i = 0; i < arraySize; i++)
        {
            if (entities[i].id == -1)
            { // Find the first available slot
                entities[i].id = id;
                entities[i].name = name;
                return true;
            }
        }
        return false; // No available slot
    }

    bool checkEmptyArray(int index)
    {
        return entities[index].name.empty();
    }

    int searchEntityByID(int searchID)
    {
        for (int i = 0; i < arraySize; i++)
        {
            if (entities[i].id == searchID)
            {
                return i;
            }
        }
        return -1;
    }

    int searchEntityByName(string searchName)
    {
    
        for (int i = 0; i < arraySize; i++)
        {
            if (entities[i].name == searchName)
            {
                return i;
            }
        }
        return -1;
    }

    void updateEntity(int updateID)
    {
        int newID;
        string newName;
        int foundIndex = searchEntityByID(updateID);
        if (foundIndex == -1)
        {
            cout << "Entity not found." << endl;
            return;
        }
        cout << "Enter New ID: ";
        cin >> newID;
        cout << "Enter New Name: ";
        cin.ignore();
        getline(cin, newName);
        entities[foundIndex].id = newID;
        entities[foundIndex].name = newName;
        cout << "------------------------------------------" << endl;
    }

    void updateEntityByName(string updateName)
    {

        int newID;
        string newName;
        int foundIndex = searchEntityByName(updateName);
        if (foundIndex == -1)
        {
            cout << "Entity not found." << endl;
            return;
        }
        cout << "Enter New ID: ";
        cin >> newID;
        cout << "Enter New Name: ";
        cin.ignore();
        getline(cin, newName);
        entities[foundIndex].id = newID;
        entities[foundIndex].name = newName;

    }

    void printEntity(int index)
    {
        if (entities[index].id != -1)
        { // Check if the entity slot is used
            cout << "ID: " << entities[index].id << ": " << entities[index].name << endl;
        }
    }

    void printAllEntities()
    {

        for (int i = 0; i < arraySize; i++)
        {
            if (!checkEmptyArray(i))
            {
                printEntity(i);
            }
        }
    }

    void sortEntitiesByID()
    {
        for (int i = 0; i < arraySize - 1; i++)
        {
            for (int j = 0; j < arraySize - i - 1; j++)
            {
                if (entities[j].id != -1 && entities[j + 1].id != -1 && entities[j].id > entities[j + 1].id)
                {
                    Entity temp = entities[j];
                    entities[j] = entities[j + 1];
                    entities[j + 1] = temp;
                }
            }
        }
    }
    void saveToFile(const string &filename)
    {
        ofstream outFile(filename);
        if (!outFile)
        {
            cerr << "File could not be opened for writing." << endl;
            return;
        }

        for (int i = 0; i < arraySize; i++)
        {
            if (entities[i].id != -1)
            {
                outFile << entities[i].id << "," << entities[i].name << endl;
            }
        }

        outFile.close();
    }
    void loadFromFile(const string &filename)
    {
        ifstream inFile(filename);
        if (!inFile)
        {
            cerr << "File could not be opened for reading." << endl;
            return;
        }
        int id;
        string name;
        while (inFile >> id)
        {
            inFile.ignore(1, ','); // Ignore the comma separator
            getline(inFile, name);
            addEntity(id, name);
        }

        inFile.close();
    }
};

void getInput(int &inputID, string &inputName)
{
    cout << "Enter ID: ";
    cin >> inputID;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, inputName);
}

void EmployeeChoose()
{
    const int arraySize = 10;
    EntityList<string> employee(arraySize);
    int inputID;
    string inputName;
    string filename = "employees.txt";
    int choice = 0;
    while(true){
    	cout << "------------------------------------------" << endl;
	    cout << "1.Add Employee" << endl;
	    cout << "2.Show Employee" << endl;
	    cout << "3.Search Employee" << endl;
	    cout << "4.Update Employee" << endl;
	    cout << "5.Sort Employee" << endl;
	    cout << "6.Save File" << endl;
	    cout << "7.Load File" << endl;
	    cout << "8.Clear Screen" << endl;
	    cout << "9. Exit" << endl;
	    cout << "------------------------------------------" << endl;
	    cout << "choose: ";
	    cin >> choice;
	    cout << "------------------------------------------" << endl;
	
	    switch (choice)
	    {
		    case 1:
		    {
		    	cout << "------------------------------------------" << endl;
		        int amount;
		        cout << "Enter Amount to Add: ";
		        cin >> amount;
		        cout << "------------------------------------------" << endl;
		        for (int i = 0; i < amount; i++)
		        {
		            getInput(inputID, inputName);
		            if (!employee.addEntity(inputID, inputName))
		            {
		                cout << "Duplicate ID or no available slot. Employee not added." << endl;
		            }
		        }
		        employee.printAllEntities();
		        cout << "------------------------------------------" << endl;
		        break;
		    }
		    case 2:
		    {
		    	cout << "------------------------------------------" << endl;
		        employee.printAllEntities();
		        cout << "------------------------------------------" << endl;
		        break;
		    }
		    case 3:
		    {
		    	cout << "------------------------------------------" << endl;
		        int option;
		        cout << "1. Search By ID: " << endl;
		        cout << "2. Search By Name: " << endl;
		        cout << "------------------------------------------" << endl;
		        cout << "Choose: ";
		        cin >> option;
		        cout << "------------------------------------------" << endl;
		        switch (option)
		        {
		        case 1:
		        {
					cout << "------------------------------------------" << endl;
		            int searchID;
		            cout << "Enter ID to search: ";
		            cin >> searchID;
		            int foundIndex = employee.searchEntityByID(searchID);
		            if (foundIndex != -1)
		            {
		                employee.printEntity(foundIndex);
		            }
		            else
		            {
		                cout << "employee not found." << endl;
		            }
		            cout << "------------------------------------------" << endl;
		            break;
		        }
		        case 2:
		        {
		        	cout << "------------------------------------------" << endl;
		            string searchName;
		            cout << "Enter Name to search: ";
		            cin >> searchName;
		            int foundIndexName = employee.searchEntityByName(searchName);
		            if (foundIndexName != -1)
		            {
		                employee.printEntity(foundIndexName);
		            }
		            else
		            {
		                cout << "employee not found." << endl;
		            }
		            cout << "------------------------------------------" << endl;
		            break;
		        }
		        }
		        break;
		    }
		    case 4:
		    {
		    	cout << "------------------------------------------" << endl;
		        int updateChoose;
		        cout << "1.Update By ID" << endl;
		        cout << "2.Update By Name" << endl;
		        cout << "------------------------------------------" << endl;
		        cout << "Choose: ";
		        cin >> updateChoose;
		        cout << "------------------------------------------" << endl;
		        switch (updateChoose)
		        {
			        case 1:
			        {	
						cout << "------------------------------------------" << endl;
			            int updateID;
			            cout << "Enter ID to Update: ";
			            cin >> updateID;
			            employee.updateEntity(updateID);
			            cout << "------------------------------------------" << endl;
			            break;
			        }
			        case 2:
			        {
			        	cout << "------------------------------------------" << endl;
			            string updateName;
			            cout << "Enter ID to Update: ";
			            cin >> updateName;
			            employee.updateEntityByName(updateName);
			            cout << "------------------------------------------" << endl;
			            break;
			        }
		        }
		        break;
		    }
		    case 5:
		    {
		    	cout << "------------------------------------------" << endl;
		        employee.sortEntitiesByID();
		        employee.printAllEntities();
		        cout << "------------------------------------------" << endl;
		        break;
		    }
		    case 6:
		    {
		        employee.saveToFile(filename);
		        break;
		    }
		    case 7:
		    {
		        employee.loadFromFile(filename);
		        break;
		    }
		    case 8:
		    {
		        system("cls");
		        break;
		    }
		    case 9:{
		    	return;
				break;
			}
		    default:
		    {
		        cout << "Invalid option. Please try again." << endl;
		        break;
		    }
	    }
	}
}

void StudentChoose()
{
    const int arraySize = 10;
    EntityList<string> Student(arraySize);
    int inputID;
    string inputName;
    string filename = "Student.txt";
    int choice = 0;
    while(true){
    	cout << "------------------------------------------" << endl;
	    cout << "1.Add Student" << endl;
	    cout << "2.Show Student" << endl;
	    cout << "3.Search Student" << endl;
	    cout << "4.Update Student" << endl;
	    cout << "5.Sort Student" << endl;
	    cout << "6.Save File" << endl;
	    cout << "7.Load File" << endl;
	    cout << "8.Clear Screen" << endl;
	    cout << "9.Exit" << endl;
	    cout << "------------------------------------------" << endl;
	    cout << "choose: ";
	    cin >> choice;
	    cout << "------------------------------------------" << endl;
	
	    switch (choice)
	    {
		    case 1:
		    {
		    	cout << "------------------------------------------" << endl;
		        int amount;
		        cout << "Enter Amount to Add: ";
		        cin >> amount;
		        for (int i = 0; i < amount; i++)
		        {
		            getInput(inputID, inputName);
		            if (!Student.addEntity(inputID, inputName))
		            {
		                cout << "Duplicate ID or no available slot. Student not added." << endl;
		            }
		        }
		        Student.printAllEntities();
		        cout << "------------------------------------------" << endl;
		        break;
		    }
		    case 2:
		    {
		    	cout << "------------------------------------------" << endl;
		        Student.printAllEntities();
		        cout << "------------------------------------------" << endl;
		        break;
		    }
		    case 3:
		    {
		    	cout << "------------------------------------------" << endl;
		        int option;
		        cout << "1. Search By ID: " << endl;
		        cout << "2. Search By Name: " << endl;
		        cout << "------------------------------------------" << endl;
		        cout << "Choose: ";
		        cin >> option;
		        cout << "------------------------------------------" << endl;
		        switch (option)
		        {
		        case 1:
		        {
					cout << "------------------------------------------" << endl;
		            int searchID;
		            cout << "Enter ID to search: ";
		            cin >> searchID;
		            int foundIndex = Student.searchEntityByID(searchID);
		            if (foundIndex != -1)
		            {
		                Student.printEntity(foundIndex);
		            }
		            else
		            {
		                cout << "User not found." << endl;
		            }
		            cout << "------------------------------------------" << endl;
		            break;
		        }
		        case 2:
		        {
		        	cout << "------------------------------------------" << endl;
		            string searchName;
		            cout << "Enter Name to search: ";
		            cin >> searchName;
		            int foundIndexName = Student.searchEntityByName(searchName);
		            if (foundIndexName != -1)
		            {
		                Student.printEntity(foundIndexName);
		            }
		            else
		            {
		                cout << "Student not found." << endl;
		            }
		            cout << "------------------------------------------" << endl;
		            break;
		        }
		        }
		        break;
		    }
		    case 4:
		    {
		    	cout << "------------------------------------------" << endl;
		        int updateChoose;
		        cout << "1.Update By ID" << endl;
		        cout << "2.Update By Name" << endl;
		        cout << "------------------------------------------" << endl;
		        cout << "Choose: ";
		        cin >> updateChoose;
		        cout << "------------------------------------------" << endl;
		        switch (updateChoose)
		        {
		        case 1:
		        {
		        	cout << "------------------------------------------" << endl;
		            int updateID;
		            cout << "Enter ID to Update: ";
		            cin >> updateID;
		            Student.updateEntity(updateID);
		            cout << "------------------------------------------" << endl;
		            break;
		        }
		        case 2:
		        {
		        	cout << "------------------------------------------" << endl;
		            string updateName;
		            cout << "Enter ID to Update: ";
		            cin >> updateName;
		            cout << "------------------------------------------" << endl;
		            Student.updateEntityByName(updateName);
		            break;
		        }
		        }
		        break;
		    }
		    case 5:
		    {
		    	cout << "------------------------------------------" << endl;
		        Student.sortEntitiesByID();
		        Student.printAllEntities();
		        cout << "------------------------------------------" << endl;
		        break;
		    }
		    case 6:
		    {
		        Student.saveToFile(filename);
		        break;
		    }
		    case 7:
		    {
		        Student.loadFromFile(filename);
		        break;
		    }
		    case 8:
		    {
		        system("cls");
		        break;
		    }
		    case 9:{
		    	return;
				break;
			} 	
		    default:
		    {
		        cout << "Invalid option. Please try again." << endl;
		        break;
		    }
		}
	}
}
	
void BookChoose()
{
    const int arraySize = 10;
    EntityList<string> Book(arraySize);
    int inputID;
    string inputName;
    string filename = "Book.txt";
    int choice = 0;
    while(true){
    	cout << "------------------------------------------" << endl;
	    cout << "1.Add Book" << endl;
	    cout << "2.Show Book" << endl;
	    cout << "3.Search Book" << endl;
	    cout << "4.Update Book" << endl;
	    cout << "5.Sort Book" << endl;
	    cout << "6.Save File" << endl;
	    cout << "7.Load File" << endl;
	    cout << "8.Clear Screen" << endl;
	    cout << "9.Exit" << endl;
	    cout << "------------------------------------------" << endl;
	    cout << "choose: ";
	    cin >> choice;
	    cout << "------------------------------------------" << endl;
	
	    switch (choice)
	    {
		    case 1:
		    {
		    	cout << "------------------------------------------" << endl;
		        int amount;
		        cout << "Enter Amount to Add: ";
		        cin >> amount;
		        for (int i = 0; i < amount; i++)
		        {
		            getInput(inputID, inputName);
		            if (!Book.addEntity(inputID, inputName))
		            {
		                cout << "Duplicate ID or no available slot. Book not added." << endl;
		            }
		        }
		        Book.printAllEntities();
		        cout << "------------------------------------------" << endl;
		        break;
		    }
		    case 2:
		    {
		    	cout << "------------------------------------------" << endl;
		        Book.printAllEntities();
		        cout << "------------------------------------------" << endl;
		        break;
		    }
		    case 3:
		    {
		    	cout << "------------------------------------------" << endl;
		        int option;
		        cout << "1. Search By ID: " << endl;
		        cout << "2. Search By Name: " << endl;
		        cout << "------------------------------------------" << endl;
		        cout << "Choose: ";
		        cin >> option;
		        cout << "------------------------------------------" << endl;
		        switch (option)
		        {
		        case 1:
		        {
					cout << "------------------------------------------" << endl;
		            int searchID;
		            cout << "Enter ID to search: ";
		            cin >> searchID;
		            int foundIndex = Book.searchEntityByID(searchID);
		            if (foundIndex != -1)
		            {
		                Book.printEntity(foundIndex);
		            }
		            else
		            {
		                cout << "User not found." << endl;
		            }
		            cout << "------------------------------------------" << endl;
		            break;
		        }
		        case 2:
		        {
		        	cout << "------------------------------------------" << endl;
		            string searchName;
		            cout << "Enter Name to search: ";
		            cin >> searchName;
		            int foundIndexName = Book.searchEntityByName(searchName);
		            if (foundIndexName != -1)
		            {
		                Book.printEntity(foundIndexName);
		            }
		            else
		            {
		                cout << "Book not found." << endl;
		            }
		            cout << "------------------------------------------" << endl;
		            break;
		        }
		        }
		        break;
		    }
		    case 4:
		    {
		    	cout << "------------------------------------------" << endl;
		        int updateChoose;
		        cout << "1.Update By ID" << endl;
		        cout << "2.Update By Name" << endl;
		        cout << "------------------------------------------" << endl;
		        cout << "Choose: ";
		        cin >> updateChoose;
		        cout << "------------------------------------------" << endl;
		        switch (updateChoose)
		        {
		        case 1:
		        {
		        	cout << "------------------------------------------" << endl;
		            int updateID;
		            cout << "Enter ID to Update: ";
		            cin >> updateID;
		            Book.updateEntity(updateID);
		            cout << "------------------------------------------" << endl;
		            break;
		        }
		        case 2:
		        {
		        	cout << "------------------------------------------" << endl;
		            string updateName;
		            cout << "Enter ID to Update: ";
		            cin >> updateName;
		            cout << "------------------------------------------" << endl;
		            Book.updateEntityByName(updateName);
		            break;
		        }
		        }
		        break;
		    }
		    case 5:
		    {
		    	cout << "------------------------------------------" << endl;
		        Book.sortEntitiesByID();
		        Book.printAllEntities();
		        cout << "------------------------------------------" << endl;
		        break;
		    }
		    case 6:
		    {
		        Book.saveToFile(filename);
		        break;
		    }
		    case 7:
		    {
		        Book.loadFromFile(filename);
		        break;
		    }
		    case 8:
		    {
		        system("cls");
		        break;
		    }
		    case 9:{
		    	return;
				break;
			} 	
		    default:
		    {
		        cout << "Invalid option. Please try again." << endl;
		        break;
		    }
		}
	}
}
void MovieChoose()
{
    const int arraySize = 10;
    EntityList<string> Movie(arraySize);
    int inputID;
    string inputName;
    string filename = "Movie.txt";
    int choice = 0;
    while(true){
    	cout << "------------------------------------------" << endl;
	    cout << "1.Add Movie" << endl;
	    cout << "2.Show Movie" << endl;
	    cout << "3.Search Movie" << endl;
	    cout << "4.Update Movie" << endl;
	    cout << "5.Sort Movie" << endl;
	    cout << "6.Save File" << endl;
	    cout << "7.Load File" << endl;
	    cout << "8.Clear Screen" << endl;
	    cout << "9.Exit" << endl;
	    cout << "------------------------------------------" << endl;
	    cout << "choose: ";
	    cin >> choice;
	    cout << "------------------------------------------" << endl;
	
	    switch (choice)
	    {
		    case 1:
		    {
		    	cout << "------------------------------------------" << endl;
		        int amount;
		        cout << "Enter Amount to Add: ";
		        cin >> amount;
		        for (int i = 0; i < amount; i++)
		        {
		            getInput(inputID, inputName);
		            if (!Movie.addEntity(inputID, inputName))
		            {
		                cout << "Duplicate ID or no available slot. Movie not added." << endl;
		            }
		        }
		        Movie.printAllEntities();
		        cout << "------------------------------------------" << endl;
		        break;
		    }
		    case 2:
		    {
		    	cout << "------------------------------------------" << endl;
		        Movie.printAllEntities();
		        cout << "------------------------------------------" << endl;
		        break;
		    }
		    case 3:
		    {
		    	cout << "------------------------------------------" << endl;
		        int option;
		        cout << "1. Search By ID: " << endl;
		        cout << "2. Search By Name: " << endl;
		        cout << "------------------------------------------" << endl;
		        cout << "Choose: ";
		        cin >> option;
		        cout << "------------------------------------------" << endl;
		        switch (option)
		        {
		        case 1:
		        {
					cout << "------------------------------------------" << endl;
		            int searchID;
		            cout << "Enter ID to search: ";
		            cin >> searchID;
		            int foundIndex = Movie.searchEntityByID(searchID);
		            if (foundIndex != -1)
		            {
		                Movie.printEntity(foundIndex);
		            }
		            else
		            {
		                cout << "User not found." << endl;
		            }
		            cout << "------------------------------------------" << endl;
		            break;
		        }
		        case 2:
		        {
		        	cout << "------------------------------------------" << endl;
		            string searchName;
		            cout << "Enter Name to search: ";
		            cin >> searchName;
		            int foundIndexName = Movie.searchEntityByName(searchName);
		            if (foundIndexName != -1)
		            {
		                Movie.printEntity(foundIndexName);
		            }
		            else
		            {
		                cout << "Movie not found." << endl;
		            }
		            cout << "------------------------------------------" << endl;
		            break;
		        }
		        }
		        break;
		    }
		    case 4:
		    {
		    	cout << "------------------------------------------" << endl;
		        int updateChoose;
		        cout << "1.Update By ID" << endl;
		        cout << "2.Update By Name" << endl;
		        cout << "------------------------------------------" << endl;
		        cout << "Choose: ";
		        cin >> updateChoose;
		        cout << "------------------------------------------" << endl;
		        switch (updateChoose)
		        {
		        case 1:
		        {
		        	cout << "------------------------------------------" << endl;
		            int updateID;
		            cout << "Enter ID to Update: ";
		            cin >> updateID;
		            Movie.updateEntity(updateID);
		            cout << "------------------------------------------" << endl;
		            break;
		        }
		        case 2:
		        {
		        	cout << "------------------------------------------" << endl;
		            string updateName;
		            cout << "Enter ID to Update: ";
		            cin >> updateName;
		            cout << "------------------------------------------" << endl;
		            Movie.updateEntityByName(updateName);
		            break;
		        }
		        }
		        break;
		    }
		    case 5:
		    {
		    	cout << "------------------------------------------" << endl;
		        Movie.sortEntitiesByID();
		        Movie.printAllEntities();
		        cout << "------------------------------------------" << endl;
		        break;
		    }
		    case 6:
		    {
		        Movie.saveToFile(filename);
		        break;
		    }
		    case 7:
		    {
		        Movie.loadFromFile(filename);
		        break;
		    }
		    case 8:
		    {
		        system("cls");
		        break;
		    }
		    case 9:{
		    	return;
				break;
			} 	
		    default:
		    {
		        cout << "Invalid option. Please try again." << endl;
		        break;
		    }
		}
	}
}
int main()
{
	int chooseMenuOption;
	while(true){
		cout << "------------------------------------------" << endl;
		cout << "1. Employee" << endl;
		cout << "2. Student" << endl;
		cout << "3. Book" << endl;
		cout << "4. Movie" << endl;
		cout << "5. Clear Screen" << endl;
		cout << "6. Exit" << endl;
		cout << "------------------------------------------" << endl;
		cout << "Choose: ";
		cin >>chooseMenuOption;
		cout << "------------------------------------------" << endl;
		switch(chooseMenuOption){
			case 1:{
				EmployeeChoose();
				break;
			}
			case 2:{
				StudentChoose();
				break;
			}
			case 3:{
				BookChoose();
				break;
			}
			case 4:{
				MovieChoose();
				break;
			}
			case 5:{
				system("cls");
				break;
			}
			case 6:{
				return 0;
				break;
			}
			default:{
				cout << "Invalid" << endl;
				break;
			}	
		}
	}
	return 0;
}
