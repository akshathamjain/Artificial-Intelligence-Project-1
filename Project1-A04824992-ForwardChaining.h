#ifndef FORWARDCHAINING_H
#define FORWARDCHAINING_H
#include <iostream>
#include <map>
#include <queue>
#include <string>

using namespace std;

class ForwardChaining
{
public:
    static const int v_size = 1, r_size = 24, cv_size = 72, var_inc = 10;
    string KB[r_size], Res;
    string CVL[cv_size];

    map<int, string> map_rulenum;
    map<int, string> map_clausenum;
    map<string, string> v_list_Ins = {{"DIAGNOSIS", "NI"}};
    queue <string> cv_queue;
    ForwardChaining();
    void KB_FW();
    void MapRuleNumbertoKB();
    void MapCN_CVL();
    bool Comparetwostr(string str1,string str2);
    void diagnosis_treatment(string str);
};

#endif // FORWARDCHAINING_H
