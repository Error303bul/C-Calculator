#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

char actions[7] = {'+', '-', '*', '/', '^','%',':'};
int totalActions = sizeof(actions);
string task = "";
string minitask = "";
float result;


bool isAction(char ctx) {
  for (int temp = 0; temp < totalActions; temp++) {
    if (actions[temp] == ctx) {
      return true;
    }
  }
  return false;
}

int charId(string ctx, char targetChar) {
  for (int temp = 0; temp < ctx.size(); temp++) {
    if (ctx[temp] == targetChar) {
      return temp;
    }
  }
  return -1;
}

int getFirstBracket(string ctx, int start) {
  int number;
  int check = start--;
  for (check = start; check > -1; check--) {
    if (ctx[check] == '(') {
      number = check;
      break;
    }
  }
  return number;
}

int getSecondBracket(string ctx) {
  int brks;
  int check;
  for (check = 0; check < ctx.size(); check++) {
    if (ctx[check] == ')') {
      brks = check;
      break;
    }
  }
  return brks;
}

float calculate(float a, float b, char action) {
  if (action == '+') {
    return a + b;
  } else if (action == '-') {
    return a - b;
  } else if (action == '*') {
    return a * b;
  } else if (action == '/') {
    return a / b;
  } else if (action == '^') {
    return pow(a, b);
  } else if (action=='%'){
    return ((int)(a))%((int)(b));
  } else if(action==':'){
    return floor(a/b);
  } else {
    return 1;
  }
}

void print(string text) { cout << text << "\n"; }

bool containsBrackets(string ctx) {
  int temp;
  for (temp = 0; temp < ctx.size(); temp++) {
    if (ctx[temp] == '(' || ctx[temp] == ')') {
      return true;
    }
  }
  return false;
}

char getAction(string ctx) {
  int checkNumber = 0;
  for (checkNumber = 0; checkNumber < ctx.size(); checkNumber++) {
    if (isAction(ctx[checkNumber])) {
      return ctx[checkNumber];
    }
  }
  return ' ';
}

string replace(string ctx, int start, int total, string replacement) {
  string result = ctx.replace(start, total, replacement);
  return result;
}

string doTask(string Task) {
  string currentTask = Task;
  int brackets[2];
  brackets[1] = getSecondBracket(currentTask);
  brackets[0] = getFirstBracket(currentTask, brackets[1]);
  int distanceFromBrackets = brackets[1] - brackets[0] + 1;
  minitask = currentTask.substr(brackets[0], distanceFromBrackets);
  char action = getAction(minitask);
  float firstInt = stof(minitask.substr(1, charId(minitask, action) - 1));
  float secondInt =
      stof(minitask.substr(charId(minitask, action) + 1, minitask.size() - 1));
  result = calculate(firstInt, secondInt, action);
  currentTask = replace(currentTask, brackets[0], minitask.size(), to_string(result));
  if (containsBrackets(currentTask)) {
    currentTask = doTask(currentTask);
  }
  return currentTask;
}

int main() {
  while (true) {
    print("Enter task");
    cin >> task;
    cin.get();
    print(doTask(task));
  }
}
