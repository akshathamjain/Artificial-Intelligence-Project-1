#include <iostream>
#include "Project1-A04824992-BackwardChaining.h"
#include "Project1-A04824992-ForwardChaining.h"
#include <iomanip>

using namespace std;

int main()
{

    BackwardChaining disorder;
    ForwardChaining treatment;

    cout << endl << endl;
    cout << "**********************************************************************************************" << endl;
    cout << "                   YOU ARE NOW IN THE MENTAL DISORDER DIAGNOSIS PORTAL!" << endl ;
    cout << "**********************************************************************************************" << endl;
    cout << endl;
    cout << "Here you can diagnose the Disorder and also see what medicines can be prescribed for it!" << endl;
    cout << endl;
    cout << "Please select from the options below: " << endl;
    cout << "1. Identify the disease and get the treatment!" << endl << "2. Print the Knowledge Base, Variable List, Clause Variable List and Conclusion List for Backward Chaining" << endl
         << "3. Print the Knowledge Base and Clause Variable List for Forward Chaining" << endl;

    int choice;
    cin >> choice;

    switch(choice)
    {
        case 1:
        {
            cout << "Please enter YES/NO for the following symptoms" << endl << endl;
            string disease = disorder.init();
            cout << endl;
            treatment.diagnosis_treatment(disease);
            break;
        }
        case 2:
        {

            cout << "**********************************************************************************************" << endl;
            cout << "The Knowledge Base for Backward Chaining is as below:" << endl;
            cout << "**********************************************************************************************" << endl << endl;
            disorder.knowledgeBaseBC();
            cout << endl;

            cout << "**********************************************************************************************" << endl;
            cout << "The Variable List for Backward Chaining is as below:" << endl;
            cout << "**********************************************************************************************" << endl << endl;
            cout << left;
            cout << setw(25) << "NAME" << setw(20) << "STATUS" << setw(10) << "VALUE" << endl << endl;
            for(int i=0; i<33;i++)
            {
                cout << left;
                cout << setw(25) << disorder.variableList[i].varname << setw(20) << disorder.variableList[i].varstatus << setw(10) << disorder.variableList[i].varvalue << endl;

            }
            cout << endl;

            cout << "**********************************************************************************************" << endl;
            cout << "The Clause variable list for Backward Chaining is as below:" << endl;
            cout << "**********************************************************************************************" << endl << endl;
            cout << left;
            for(int i = 1; i < 299; i++){
            cout << disorder.clauseVarList[i] << endl;
            }
            cout << endl;

            cout << "**********************************************************************************************" << endl;
            cout << "The Conclusion list for Backward Chaining is as below:" << endl;
            cout << "**********************************************************************************************" << endl << endl;
            cout << left;
            cout << "RULE NUMBER" << setw(10) << "\t" << "CONCLUSION" << endl << endl;

            for(int i = 0; i < 27; i++){
                cout << left;
                cout << setw(10) << disorder.conlist[i].rulenum << setw(10) << "\t" << disorder.conlist[i].conclusionname << endl;
            }
            cout << endl;
            break;

        }
        case 3:
        {
            cout << "**********************************************************************************************" << endl;
            cout << "The Knowledge Base for Backward Chaining is as below:" << endl;
            cout << "**********************************************************************************************" << endl << endl;
            for(int i = 0; i<24; i++)
            {
                cout << treatment.KB[i] << endl << endl;
            }
            cout << endl;

            cout << "**********************************************************************************************" << endl;
            cout << "The Clause Variable List for Backward Chaining is as below:" << endl;
            cout << "**********************************************************************************************" << endl << endl;
            for(int i=0; i<72;i++){
                cout << treatment.CVL[i] << endl;
            }
            break;
        }

    }
    return 0;
}

