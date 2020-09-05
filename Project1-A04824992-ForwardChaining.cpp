
#include "Project1-A04824992-ForwardChaining.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>



using namespace std;

/******************************************************************************
ForwardChaining(): is a special/ member function which initializes objects
                    of the class. It initializes the clause variable list.
                    It will update the knowledge base by calling KB_FW(),
                    maps the rules number to Knowledge Base by calling
                    MapRuleNumbertoKB(), maps clause number to conclusion
                    variable list by calling MapCN_CVL() function.
parameters used: no
returns : constructor does not have a return type.
*******************************************************************************/

ForwardChaining::ForwardChaining()
{
       //initializing clause variable list
       ifstream fin;
       string cVL;
       fin.open("D://Artificial Intelligence/AKSHATHA/Project1-A04824992-ClausevarlistFC.txt");
       if(!fin){
        cout << "error ! could not open the file";   }
        for(int i=0; i<cv_size;i++)
        {
        fin >> cVL;
        CVL[i] = cVL;
        }

        KB_FW();
        MapRuleNumbertoKB();
        MapCN_CVL();
}

/******************************************************************************
KB_FW(): This function will store the knowledge base for forward chaining using
         string array for all the rule numbers.

Parameters Used : no
return type : nothing, as it is a void function.
*******************************************************************************/

void ForwardChaining::KB_FW()
{
       //knowledge base
       ifstream fin;
       string knowledgebase;
       fin.open("D://Artificial Intelligence/AKSHATHA/Project1-A04824992-KnowledgeBaseFC.txt");
       if(!fin){
        cout << "error ! could not open the file";   }
        for(int i=0; i<r_size;i++)
        {
        getline(fin, knowledgebase, '\n');
        KB[i] = knowledgebase;
        }
}

/*******************************************************************************
MapRuleNumbertoKB() : This function maps the rule number to knowledge base.
Parameters used : no
return type: no, as it is a void function.
*******************************************************************************/

void ForwardChaining::MapRuleNumbertoKB()
{
    map_rulenum.insert(pair<int, string>(10, KB[0]));
    map_rulenum.insert(pair<int, string>(20, KB[1]));
    map_rulenum.insert(pair<int, string>(30, KB[2]));
    map_rulenum.insert(pair<int, string>(40, KB[3]));
    map_rulenum.insert(pair<int, string>(50, KB[4]));
    map_rulenum.insert(pair<int, string>(60, KB[5]));
    map_rulenum.insert(pair<int, string>(70, KB[6]));
    map_rulenum.insert(pair<int, string>(80, KB[7]));
    map_rulenum.insert(pair<int, string>(90, KB[8]));
    map_rulenum.insert(pair<int, string>(100, KB[9]));
    map_rulenum.insert(pair<int, string>(110, KB[10]));
    map_rulenum.insert(pair<int, string>(120, KB[11]));
    map_rulenum.insert(pair<int, string>(130, KB[12]));
    map_rulenum.insert(pair<int, string>(140, KB[13]));
    map_rulenum.insert(pair<int, string>(150, KB[14]));
    map_rulenum.insert(pair<int, string>(160, KB[15]));
    map_rulenum.insert(pair<int, string>(170, KB[16]));
    map_rulenum.insert(pair<int, string>(180, KB[17]));
    map_rulenum.insert(pair<int, string>(190, KB[18]));
    map_rulenum.insert(pair<int, string>(200, KB[19]));
    map_rulenum.insert(pair<int, string>(210, KB[20]));
    map_rulenum.insert(pair<int, string>(220, KB[21]));
    map_rulenum.insert(pair<int, string>(230, KB[22]));
    map_rulenum.insert(pair<int, string>(240, KB[23]));
}

/*******************************************************************************
MapCN_CVL(): maps clause number to conclusion variable list.
Parameters used : no
return type : no, as it is a void function.
*******************************************************************************/

void ForwardChaining::MapCN_CVL()
{
    map_clausenum.insert(pair<int, string>(1, CVL[0]));
    map_clausenum.insert(pair<int, string>(4, CVL[3]));
    map_clausenum.insert(pair<int, string>(7, CVL[6]));
    map_clausenum.insert(pair<int, string>(10, CVL[9]));
    map_clausenum.insert(pair<int, string>(13, CVL[12]));
    map_clausenum.insert(pair<int, string>(16, CVL[15]));
    map_clausenum.insert(pair<int, string>(19, CVL[18]));
    map_clausenum.insert(pair<int, string>(22, CVL[21]));
    map_clausenum.insert(pair<int, string>(25, CVL[24]));
    map_clausenum.insert(pair<int, string>(28, CVL[27]));
    map_clausenum.insert(pair<int, string>(31, CVL[30]));
    map_clausenum.insert(pair<int, string>(34, CVL[33]));
    map_clausenum.insert(pair<int, string>(37, CVL[36]));
    map_clausenum.insert(pair<int, string>(40, CVL[39]));
    map_clausenum.insert(pair<int, string>(43, CVL[42]));
    map_clausenum.insert(pair<int, string>(46, CVL[45]));
    map_clausenum.insert(pair<int, string>(49, CVL[48]));
    map_clausenum.insert(pair<int, string>(52, CVL[51]));
    map_clausenum.insert(pair<int, string>(55, CVL[54]));
    map_clausenum.insert(pair<int, string>(58, CVL[57]));
    map_clausenum.insert(pair<int, string>(61, CVL[60]));
    map_clausenum.insert(pair<int, string>(64, CVL[63]));
    map_clausenum.insert(pair<int, string>(67, CVL[66]));
}

/******************************************************************************
Comparetwostr() : function will cpmapare 2 strings.
Parameters Used : s1, s2.
return type : returns true if 2 strings matchelse it will return false.
*******************************************************************************/

bool ForwardChaining::Comparetwostr(string s1, string s2)
{
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    transform(s2.begin(), s2.end(), s2.begin(), ::toupper);

    if (s1 == s2)
    {
        return true;
    }

    else
    {
        return false;
    }
}

/******************************************************************************
diagnosis_treatment() : when the expert system detects the disease, this function
                        will calculate rule number by using clause variable and
                        clauses in the IF matches with Diagnosis of the expert
                        system it will print the treatment for the corresponding
                        disease.
Parameters Used: diagnosis.
return type: no, as it is a void function.
******************************************************************************/

void ForwardChaining::diagnosis_treatment(string diagnosis)
{


    cv_queue.push("DIAGNOSIS");
    v_list_Ins["DIAGNOSIS"] = diagnosis;
    int clausenum = 1, rulenum;

    if (diagnosis != "")
    {
        while (!cv_queue.empty())
        {

            map<int, string>::iterator i;
            for (i = map_clausenum.begin(); i != map_clausenum.end(); i++)
            {
                if (i->second != "b")
                {
                    // Conversion of Clause number to Rule number
                    rulenum = (((clausenum / 3) + 1) * 10);
                }
            }
            // Finding the DISORDER and comparing it with knowledge base
            int pos = map_rulenum[rulenum].find("=");
            int pos1 = map_rulenum[rulenum].find(" THEN");
            string compare = map_rulenum[rulenum].substr(pos + 1, pos1 - (pos + 1));
            if (Comparetwostr(compare, diagnosis))
            {
                int treatment = map_rulenum[rulenum].rfind("=");
                Res = map_rulenum[rulenum].substr(treatment, map_rulenum[rulenum].length());
                Res.erase(0,1);
                cout << "Treatment for the disorder " << diagnosis << " is : " << Res << endl;
                break;
            }
            else
            {
                clausenum = clausenum + 2;

            }
        }
    }

    else
        cout << "Please consult a Psychologist! No treatment can be detected." << endl;

}



