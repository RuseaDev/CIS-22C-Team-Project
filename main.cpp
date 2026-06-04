#include <iostream>
using namespace std;

void searchManager();
void displayManager();
void deleteManager();
int main()
{
  displayManager();
  return 0;
}

void searchManager()
{
  string key;
  cout << "Enter the key to search: ";
  cin >> key;
  cout << "Searching for key " << key << "..." << endl;
}

void displayManager()
{
  int choice;
  cout << "1. List all data sorted by key: " << endl;
  cout << "2. Display the indented tree : " << endl;
  cout << "Enter your choice: ";
  cin >> choice;

  while (cin.fail() || (choice != 1 && choice != 2))
  {
    cout << "Invalid choice, please try again" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter your choice: ";
    cin >> choice;
  }

  switch (choice)
  {
  case 1:
    cout << "Listing all data sorted by key..." << endl;
    break;
  case 2:
    cout << "Displaying the indented tree..." << endl;
    break;
  }
}
void deleteManager()
{
  cout << "Delete Manager\n";
}