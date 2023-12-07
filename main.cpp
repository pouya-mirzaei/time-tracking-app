#include <iostream>
using namespace std;

// Global variables
string userName; // This is a temporary variable.The system might have a feature that can proccess several employees's actions in the future;
bool isInitiated = false;
int START_DAY_TIME, END_DAY_TIME, WORK_TIME, ALLOWED_DELAY;

int date[3] = {0, 0, 0};
int maxDate[3] = {0, 0, 0};
int minDate[3] = {0, 0, 0};

int totalWorkTime = 0, totalDelay = 0, totalAllowedDelay = 0, totalHaste = 0,
    totalAllowedHaste = 0, totalStartTime = 0, totalFinishTime = 0, dayCount = 0,
    totalOverTime = 0, totalFraction = 0, maxWorkTime = 0,
    minWorkTime = 24 * 60; // A full day = 24*60

// ----------------------------------------------

// Function Declarations  :

// App structure
void app();
void initiateApp();
void showMainMenu(string msg);
int displayAndGetMenuResult(string msg);
void start();
void displayExistingData();
void getData();
void showResult(int time, string msg);

// Date calculations
void getFirstDate();
void nextDay();
void printDate(int d[]);

// Calculations
int hourToMinutes(int hour, int minutes);
void printFormattedTime(int minutes);
void analyzeWorkingTime(int start_h, int start_m, int finish_h, int finish_m);

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

  showMainMenu("Please select an option to start: ");
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
  if (dayCount == 0) // ------------------------------------------- this must be changed in the future
  {
    showMainMenu("You have not any data in the app. Please start the app first");
  }
  else
  {
    system("cls");

    showResult(totalWorkTime, "total work time : ");
    showResult(totalDelay, "total delay : ");
    showResult(totalAllowedDelay, "total allowed delay : ");
    showResult(totalHaste, "total haste : ");
    showResult(totalAllowedHaste, "total allowed  haste : ");
    showResult(totalStartTime, "total start time : ");
    showResult(totalFinishTime, "total finish time : ");
    showResult(maxWorkTime, "max worked time : ");
    showResult(minWorkTime, "min worked time : ");
    showResult(totalOverTime, "total overtime : ");
    showResult(totalFraction, "total fraction : ");

    int a;
    cout << "1. back\n";
    cin >> a;
    if (a == 1)
    {
      showMainMenu("welcome back");
    }
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
    cin >> hour;
    cin.ignore(1, ':');
    cin >> minutes;
    if (minutes < 0 || minutes >= 60 || hour >= 24 || hour < 0)
      cout << "Invalid time format. Please enter the time in the correct format (HH:MM): \n";
    else
    {
      START_DAY_TIME = hourToMinutes(hour, minutes);
      break;
    }
  }

  cout << "Now enter your company's ending time in 24-hour format. (HH:MM)\n";
  while (true)
  {
    cin >> hour;
    cin.ignore(1, ':');
    cin >> minutes;

    if (minutes < 0 || minutes >= 60 || hour >= 24 || hour < 0)
      cout << "Invalid time format. Please enter the time in the correct format (HH:MM): \n";
    else
    {
      END_DAY_TIME = hourToMinutes(hour, minutes);
      break;
    }
  }

  WORK_TIME = END_DAY_TIME - START_DAY_TIME;
  if (WORK_TIME < 0)
  {
    showMainMenu("Invalid end time: the ending time cannot be before the starting time. start again");
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
  int startHour, startMinute, finishHour, finishMinute, currentDayWorkTime;

  if (date[0] == 0)
  {
    getFirstDate();
  }

  while (true)
  {
    system("cls");
    cout << "Enter your staring time for : ";
    printDate(date);
    cout << endl;
    cout << "( Enter -1 to return to the main menu. If today is holiday,enter -2 )\n";
    cin >> startHour;
    if (startHour == -1)
      break;
    if (startHour == -2)
    {
      nextDay();
      continue;
    }
    cin.ignore(1, ':');
    cin >> startMinute;
    while (startMinute >= 60 || startMinute < 0 || startHour >= 24 || startHour < 0)
    {
      cout << "Invalid time format :( try again\n";
      cin >> startHour;
      cin.ignore(1, ':');
      cin >> startMinute;
    }

    cout << "Enter your finishing time for : ";
    printDate(date);
    cout << endl;
    cin >> finishHour;
    cin.ignore(1, ':');
    cin >> finishMinute;
    currentDayWorkTime = (finishHour - startHour) * 60 + (finishMinute - startMinute);

    while (finishMinute >= 60 || finishMinute < 0 || finishHour >= 24 || finishHour < 0 || currentDayWorkTime < 0)
    {
      cout << "Invalid time format or wrong finishing hour :( try again\n";
      cin >> finishHour;
      cin.ignore(1, ':');
      cin >> finishMinute;
      currentDayWorkTime = (finishHour - startHour) * 60 + (finishMinute - startMinute);
    }

    //------------------------------ calculations :

    totalWorkTime += currentDayWorkTime;
    totalStartTime += startHour * 60 + startMinute;
    totalFinishTime += finishHour * 60 + finishMinute;
    maxWorkTime = currentDayWorkTime >= maxWorkTime ? currentDayWorkTime : maxWorkTime;
    minWorkTime = currentDayWorkTime <= minWorkTime ? currentDayWorkTime : minWorkTime;
    analyzeWorkingTime(startHour, startMinute, finishHour, finishMinute);

    dayCount++;
    nextDay();
  }
  showMainMenu("returned");
}

// Date calculations :

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
  int m = date[1], d = date[2];

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

void printDate(int d[])
{
  cout << d[0] << "/" << d[1] << "/" << d[2];
}

// Calculations:

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

  cout << ": ";

  if (minute < 10)
    cout << "0" << minute;
  else
    cout << minute;
}

void analyzeWorkingTime(int start_h, int start_m, int finish_h, int finish_m)
{
  int start = start_h * 60 + start_m;
  int finish = finish_h * 60 + finish_m;
  int workTime = finish - start;

  // delay
  int delay = start - START_DAY_TIME;
  if (delay > 0 && delay <= ALLOWED_DELAY && workTime >= WORK_TIME)
    totalAllowedDelay += delay;
  else if (delay > 0)
    totalDelay += delay;

  // haste
  int haste = END_DAY_TIME - finish;
  if (haste > 0 && haste <= ALLOWED_DELAY && workTime >= WORK_TIME)
    totalAllowedHaste += haste;
  else if (haste > 0)
    totalHaste += haste;

  // overtime
  int overtime = workTime - WORK_TIME;
  if (overtime > 0)
    totalOverTime += overtime;

  // fraction
  int fraction = WORK_TIME - workTime;
  if (fraction > 0)
    totalFraction += fraction;
}

void showResult(int time, string msg)
{
  cout << msg;
  printFormattedTime(time);
  cout << "\n";
}
