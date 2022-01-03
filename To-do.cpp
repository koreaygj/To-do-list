#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;
void print_menu();
class Format
{
public:
  string list_task;
  string list_due_date;
  int list_priority;
  bool operator<(Format s) const
  {
    if (this->list_priority == s.list_priority)
    {
      return this->list_due_date < s.list_due_date;
    }
    else
    {
      return this->list_priority < s.list_priority;
    }
  }
};
class Todo
{
private:
  string task;
  string due_date;
  int priority;
  string list_format;
  int reset();
  void regist_list();
  void sort_list();

public:
  void input();
  void show_list();
  void modify_list();
  void delete_list();
};
void Todo::input()
{
  cout << "\tTask name: ";
  cin >> task;
  while (1)
  {
    cout << "\tDue day: ";
    cin >> due_date;
    int month = stoi(due_date.substr(5, 2));
    int day = stoi(due_date.substr(8));
    if (due_date.size() != 10)
    {
      cout << "\tWrong format...(longer than format)\n";
      cout << "\tFormat ex)2022-01-01\n";
    }
    else
    {
      if (01 <= month && month <= 12 && 01 <= day && day <= 31)
        break;
      else
      {
        cout << "\tWrong format...(check month&day)\n";
        cout << "\tFormat ex)2022-01-01\n";
      }
    }
  }
  while (1)
  {
    cout << "\tPriority of the task (1~50): ";
    cout << "\n\t---Lower it is, the higer the priority---\n\t";
    cin >> priority;
    if (1 <= priority && priority <= 50)
      break;
  }
  regist_list();
}
void Todo::regist_list()
{
  list_format = task + " " + due_date + " " + to_string(priority);
  ofstream regist_list;
  regist_list.open("Task.txt", ios::in | ios::app);
  if (regist_list.is_open())
  {
    regist_list << list_format;
  }
  regist_list.close();
  sort_list();
}
void Todo::sort_list()
{
  vector<Format> list;
  ifstream getlist;
  getlist.open("Task.txt");
  if (getlist.is_open())
  {
    int count = 0;
    while (!getlist.eof())
    {
      string str;
      vector<string> format;
      string s;
      getline(getlist, str);
      if (str == list_format)
      {
        count++;
        if (count == 2)
        {
          cout << "\tThis task already exist...\n";
          input();
          return;
        }
      }
      if (str == "\n")
        continue;
      for (int i = 0; i < str.size(); i++)
      {
        if (str[i] == ' ')
        {
          format.push_back(s);
          s = "";
          continue;
        }
        if (str[i] == '-')
          continue;
        s += str[i];
      }
      format.push_back(s);
      list.push_back({format[0], format[1], stoi(format[2])});
    }
  }
  getlist.close();
  sort(list.begin(), list.end());
  ofstream comp_sort;
  comp_sort.open("Task.txt", ios::out);
  for (int i = 0; i < list.size(); i++)
    comp_sort << list[i].list_task + " " + list[i].list_due_date.substr(0, 4) + "-" + list[i].list_due_date.substr(4, 2) + "-" + list[i].list_due_date.substr(6) + " " + to_string(list[i].list_priority) + "\n";
  comp_sort.close();
  cout << "\tSuccessfully regist new task\n";
  if (reset() == 1)
    input();
  else
    return;
}
void Todo::show_list()
{
  int count = 1;
  ifstream readFile;
  readFile.open("Task.txt");
  if (readFile.is_open())
  {
    while (!readFile.eof())
    {
      string str;
      getline(readFile, str);
      cout << count << ": " << str << endl;
      count++;
    }
  }
  readFile.close();
  return;
}
void Todo::modify_list()
{
  int num;
  vector<string> modify_list;
  show_list();
  cout << "\tChoice modify line you want\n";
  cin >> num;
  ifstream find_task;
  find_task.open("Task.txt", ios::in);
  if (find_task.is_open())
  {
    while (!find_task.eof())
    {
      string str;
      getline(find_task, str);
      num--;
      if (num == 0)
        continue;
      modify_list.push_back(str);
    }
  }
  find_task.close();
  ofstream delete_task;
  delete_task.open("Task.txt", ios::out);
  for (int i = 0; i < modify_list.size() - 1; i++)
    delete_task << modify_list[i] + "\n";
  delete_task.close();
  input();
}
void Todo::delete_list()
{
  short int n;
  cout << "\tChoice delete mode\n";
  cout << "\t1. Delete all\n";
  cout << "\t2. Delete one Task\n";
  cin >> n;
  if (n == 1)
  {
    ofstream delete_task;
    delete_task.open("Task.txt", ios::out);
    delete_task.close();
  }
  else if (n == 2)
  {
    int num;
    vector<string> delete_list;
    show_list();
    cout << "\tChoice delete line you want\n";
    cin >> num;
    ifstream find_task;
    find_task.open("Task.txt", ios::in);
    if (find_task.is_open())
    {
      while (!find_task.eof())
      {
        string str;
        getline(find_task, str);
        num--;
        if (num == 0)
          continue;
        delete_list.push_back(str);
      }
    }
    find_task.close();
    ofstream delete_task;
    delete_task.open("Task.txt", ios::out);
    for (int i = 0; i < delete_list.size() - 1; i++)
      delete_task << delete_list[i] + "\n";
    delete_task.close();
    cout << "\tDelete task successfully\n";
  }
  else
  {
    delete_list();
  }
  return;
}
int Todo::reset()
{
  string resetButton = " ";
  cout << "\n\nPress '0' to repeat the process...(Go to menu press any button)\n";
  cin >> resetButton;
  if (resetButton != "0")
    return 0;
  else
    return 1;
}
int main()
{
  Todo td;
  while (1)
  {
    int n = 0;
    print_menu();
    cin >> n;
    system("cls");
    switch (n)
    {
    case 1:
    {
      td.show_list();
      break;
    }
    case 2:
    {
      td.input();
      break;
    }
    case 3:
    {
      td.modify_list();
      break;
    }
    case 4:
    {
      td.delete_list();
      break;
    }
    case 5:
    {
      cout << "\tProgram exit...\n";
      return 1;
    }
    default:
      cout << "Please look at the menu again\n";
    }
  }
  return 0;
}
void print_menu()
{
  cout << "\tSIMPLE TO-DO-LIST\n";
  cout << "\t\tMENU\n\n";
  cout << "\t1. See all list\n";
  cout << "\t2. Regist new task\n";
  cout << "\t3. Modify the task\n";
  cout << "\t4. Delete the task\n";
  cout << "\t5. Program exit\n";
  cout << "\n\tChoice what you need(1, 2, 3, 4, 5)";
  return;
}