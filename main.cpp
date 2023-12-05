#include <iostream>
#include <stdalign.h>
using namespace std;

// Global variables
string userName; // This is a temporary variable.The system might have a feature that can proccess several employees's actions in the future;
bool isInitiated = false;
int CLOCK_IN_HOUR, CLOCK_IN_MINUTES, CLOCK_OUT_HOUR, CLOCK_OUT_MINUTES;
int START_DAY_TIME, END_DAY_TIME, WORK_TIME, ALLOWED_DELAY;

int date[3] = {0, 0, 0};

int totalWorkTime = 0, totalDelay = 0, totalAllowedDelay = 0, totalHaste = 0,
    totalAllowedHaste = 0, totalStartTime = 0, totalEndTime = 0;

// ----------------------------------------------

// Function Declarations  :
void app();
void initiateApp();
void showMainMenu(string msg);
int displayAndGetMenuResult(string msg);
void start();
void displayExistingData();
void getData();
void printCurrentDate();

void getFirstDate();
void nextDay();

int hourToMinutes(int hour, int minutes);
void printFormattedTime(int minutes);

//------------ main code

int main()
{
  app();
  return 0;
}

void app()
{
  system("cls");
  cout << "Welcome to ABC Software Development Time Tracking app :)";
  cout << "\nTo get started, please tell us your name:\n";
  cin >> userName;

  showMainMenu("Please select an option to start:");
}

void start()
{
  if (!isInitiated)
  {
    initiateApp();
    if (isInitiated)
      showMainMenu("Well done! now enter your data to continue");
    else
      showMainMenu("There was an error while initiating the app. Please try again");
    return;
  }

  // start getting data from the user
  getData();
}

void displayExistingData()
{
  if (!isInitiated) // ------------------------------------------- this must be changed in the future
  {
    showMainMenu("You have not any data in the app. Please start the app first");
  }
  else
  {
    system("cls");
    cout << date[0] << "/" << date[1] << "/" << date[2] << endl;
    cout << START_DAY_TIME << " " << END_DAY_TIME << " " << WORK_TIME << " " << ALLOWED_DELAY;
  }
}

void showMainMenu(string msg)
{
  int menu = displayAndGetMenuResult(msg);

  switch (menu)
  {
  case 1:
    start();
    break;
  case 2:
    displayExistingData();
    break;
  case 3:
    system("cls");
    break;

  default:
    cout << "\nAn unknown error :(";
    break;
  }
}

int displayAndGetMenuResult(string msg)
{
  int selectedIndex;
  system("cls");

  // displaying the menu based on the initialization status
  !isInitiated &&cout << "Hi " << userName << "! ";
  do
  {
    cout << msg;
    isInitiated ? cout << "\n  1. Enter new Data" : cout << "\n  1. Start";
    cout << "\n  2. Display the result";
    cout << "\n  3. Exit the program\n";

    cin >> selectedIndex;

    if (selectedIndex < 1 || selectedIndex > 3)
    {
      system("cls");
      cout << "Invalid option selected. Please enter a valid option (1-3).\n";
    }
  } while (selectedIndex < 1 || selectedIndex > 3);

  return selectedIndex;
}

void initiateApp()
{
  int hour, minutes;

  system("cls");

  cout << "Please enter your company's starting time in 24-hour format. (HH:MM)\n";
  while (true)
  {
    int hour, minutes;
    cin >> hour;
    cin.ignore(1, ':');
    cin >> minutes;
    if (minutes < 0 || minutes >= 60 || hour >= 24 || hour < 0)
      cout << "Invalid time format. Please enter the time in the correct format (HH:MM): \n";
    else
    {
      CLOCK_IN_HOUR = hour;
      CLOCK_IN_MINUTES = minutes;
      START_DAY_TIME = hourToMinutes(hour, minutes);
      break;
    }
  }

  cout << "Now enter your company's ending time in 24-hour format. (HH:MM)\n";
  while (true)
  {
    int hour, minutes;
    cin >> hour;
    cin.ignore(1, ':');
    cin >> minutes;

    if (minutes < 0 || minutes >= 60 || hour >= 24 || hour < 0)
      cout << "Invalid time format. Please enter the time in the correct format (HH:MM): \n";
    else
    {
      CLOCK_OUT_HOUR = hour;
      CLOCK_OUT_MINUTES = minutes;
      END_DAY_TIME = hourToMinutes(hour, minutes);
      break;
    }
  }

  WORK_TIME = END_DAY_TIME - START_DAY_TIME;
  if (WORK_TIME < 0)
  {
    cout << "Invalid end time. the ending time cannot be before the starting time";
    return;
  }

  int delay;
  cout << "Specify an allowed delay time in minutes \n";
  cin >> delay;

  while (delay < 0 || delay > 60)
  {
    cout << "The allowed time most be between 0 and 60 minutes . Reenter the allowed delay \n";
    cin >> delay;
  }

  ALLOWED_DELAY = delay;

  system("cls");
  isInitiated = true;
}

// The main logic for the app
void getData()
{
  system("cls");
  int startHour, startMinute, finishHour, finishMinute;

  getFirstDate();

  showMainMenu("hello");
}

int hourToMinutes(int hour, int minutes)
{
  return hour * 60 + minutes;
}

void printFormattedTime(int minutes)
{
  int hour = minutes / 60;
  int minute = minutes % 60;
  if (hour < 10)
    cout << "0" << hour;
  else
    cout << hour;

  cout << ":";

  if (minute < 10)
    cout << "0" << minute;
  else
    cout << minute;
}

void getFirstDate()
{
  cout << "Enter the date of your first working day :(yyyy/mm/dd)\n";
  cin >> date[0];
  cin.ignore(1, '/');
  cin >> date[1];
  cin.ignore(1, '/');
  cin >> date[2];
  while (date[0] < 1000 || date[0] > 9999 || date[1] < 0 || date[1] > 12 || date[2] < 0 || date[2] > 30)
  {
    cout << "Invalid date :( try again\n";
    cin >> date[0];
    cin.ignore(1, '/');
    cin >> date[1];
    cin.ignore(1, '/');
    cin >> date[2];
  }
}

void nextDay()
{
  int y = date[0], m = date[1], d = date[2];

  if (d + 1 <= 30)
  {
    date[2]++;
  }
  else if (d + 1 > 30 && m + 1 <= 12)
  {
    date[2] = 1;
    date[1]++;
  }
  else if (d + 1 > 30 && m + 1 > 12)
  {
    date[2] = 1;
    date[1] = 1;
    date[0]++;
  }
}
void printCurrentDate()
{
  cout << date[0] << "/" << date[1] << "/" << date[2];
}