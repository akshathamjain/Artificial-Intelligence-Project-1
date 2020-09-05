#ifndef BACKWARDCHAINING_H_INCLUDED
#define BACKWARDCHAINING_H_INCLUDED

#include <iostream>
#include <map>
#include <stack>
#include <string>

using namespace std;

struct variable
{
    string varname;
    string varstatus;
    string varvalue;
};

struct conclusionlist
{
    int rulenum;
    string conclusionname;
};

struct conclusionstack
{
    int rulenumber;
    int clausenumber;
};


class BackwardChaining
{
public:
    //variables
    variable variableList[33];
    conclusionlist conlist [27];
    stack <conclusionstack> conclusionStack;
    string clauseVarList[300];
    string KBBC[27];


    //functions
    BackwardChaining(); // Constructor
    string init();
    void knowledgeBaseBC();
    void conclusionStackOperation(int,int); // Conclusion Stack to store Rule number and Clause Number
    int variableIndex(string); // returns the index of the variable
    string variableValue(string); // returns the value YES/NO of the variable
    void instantiation(string); //to instantiate a variable in the variable list
    variable knowledgeBase(int, map<string,string> &);


};

#endif // BACKWARDCHAINING_H_INCLUDED
