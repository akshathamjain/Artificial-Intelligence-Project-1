#include "Project1-A04824992-BackwardChaining.h"
#include <iostream>
#include <fstream>

/******************************************************************************
BackwardChaining(): is a special/ member function which initializes objects
                    of the class. It will read the Variable_list.txt, Conclusion_list.txt
                    and clauseVariablelist list files if present and stores them
                    in respective array of structures like variable, conclusionlist
                    and string clauseVarList.
parameters used: no
returns : constructor does not have a return type.
*******************************************************************************/

BackwardChaining::BackwardChaining()
{
    //Initializing variable list
    ifstream fin;
    string name, status, value;
    fin.open("D://Artificial Intelligence/AKSHATHA/Project1-A04824992-Variable_List.txt");
    if(!fin){
        cout << "error ! could not open the file";   }
    for(int i=0; i<33;i++)
    {
        fin >> name;
        fin >> status;
        variableList[i].varname = name;
        variableList[i].varstatus = status;
        variableList[i].varvalue = "";
    }

    //Initializing conclusion list
    ifstream fin1;
    int rulenum;
    string conclusionname;
    fin1.open("D://Artificial Intelligence/AKSHATHA/Project1-A04824992-Conclusion_list.txt");
    if(!fin){
        cout << "error ! could not open the file";   }

    for(int i = 0; i < 27; i++){

        fin1 >> rulenum >> conclusionname;

        conlist[i].rulenum = rulenum;
        conlist[i].conclusionname = conclusionname;
    }

    //Initializing Clause variable list
    ifstream fin2;
    string clausevalue;
    fin2.open("D://Artificial Intelligence/AKSHATHA/Project1-A04824992-Clausevarlist.txt");
    if(!fin2){
        cout << "error ! could not open the file";   }
    for(int i=1; i<299;i++)
    {
        fin2 >> clausevalue;
        clauseVarList[i] = clausevalue;
    }
}

/*******************************************************************************
init(): IF the rule number is satisfied, function will calculate clause number by using rule number and updates
        conclusion stack by calling function conclusionStackOperation, it will
        store the index of the variable by calling variableIndex() function, and
        instantiates the variable using instantiation() function.
        Then function gets user response by calling variableValue(), then it
        identifies the disease by calling knowledgebase().
Parameters used : no
return type: returns disease name if identified by knowledge base else it will
             return null;
*******************************************************************************/

string BackwardChaining::init(){

    for(int i = 0; i<27; i++){
        if(conlist[i].conclusionname == "DIAGNOSIS")
        {
            int ruleNum = conlist[i].rulenum;
            int clauseNum = 11*(ruleNum/10 -1) + 1;//computing clause number

            conclusionStackOperation(ruleNum, clauseNum);
            string symptom = clauseVarList[clauseNum];

            while(symptom != "b"){
                int varIndex = variableIndex(symptom);
                    instantiation(clauseVarList[varIndex]);
                    clauseNum++;
                    symptom = clauseVarList[clauseNum];
                }
            }
            while(conclusionStack.size() != 0){ //until the stack has rule numbers available
                conclusionstack top = conclusionStack.top();
                conclusionStack.pop();
                int rule = top.rulenumber;
                int clause = top.clausenumber;

                map<string,string> clausePair;
                for(int i=clause; i<clause+11; i++){
                        string symp = clauseVarList[i];
                    if(symp != "b"){
                        string sympval = variableValue(symp);
                        clausePair.insert(pair<string,string>(symp, sympval));
                    }

                    else{
                        break;
                    }
                }

                variable ruleResult = knowledgeBase(rule, clausePair);
                if(ruleResult.varstatus == "true"){
                    if(ruleResult.varname == "DIAGNOSIS"){
                        cout<<"You are diagnosed with : "<< ruleResult.varvalue << endl;
                        conclusionStack.pop();
                        return ruleResult.varvalue;
                        break;
                    }
                }
                else//rule is not satisfied
                    break;
            }
        }

    }


void BackwardChaining::knowledgeBaseBC()
{
        //knowledge base
       ifstream fin;
       string knowledgebase;
       fin.open("D://Artificial Intelligence/AKSHATHA/Project1-A04824992-KnowledgeBaseBC.txt");
       if(!fin){
        cout << "error ! could not open the file";   }
        for(int i=0; i<27;i++)
        {
        getline(fin, knowledgebase, '\n');
        KBBC[i] = knowledgebase;
        cout << KBBC[i] << endl << endl;
        }

}

/*******************************************************************************
conclusionStackOperation(): This function will push the rule numbers and clause
                            numbers and stores them in stack.
parameters used :  ruleNumber, clauseNumber.
returns : nothing, as it is a void function.
*******************************************************************************/

void BackwardChaining::conclusionStackOperation(int ruleNumber, int clauseNumber){
    conclusionstack stacktemp = { ruleNumber, clauseNumber};
    conclusionStack.push(stacktemp);
}

/******************************************************************************
variableIndex() : Function will ask user whether he/she suffering from any of the
                  and the data( string value YES/NO) will be stored in the index
                  of variable list.
                  if user enters other than YES/ NO it will ask the user to enter
                  correct value again.
                  Function will check whether Symptom or variable is present in
                  variableList or not, it will instantiate the variable status.

Parameters used : symptom
returns : (i)index of the variable is returned if the variable/symptom is present
           else it will write -1.
*******************************************************************************/

int BackwardChaining::variableIndex(string symptom){

    for(int i=0; i< 33; i++){
        if(variableList[i].varname == symptom){
            if(variableList[i].varstatus == "NI"){
                cout << "Are you suffering from "<< variableList[i].varname<< " :   ";
                string data;
                cin >> data;
                while((data != "YES")&& (data != "NO"))
                   {
                       cout << "WRONG ENTRY: Please enter YES or NO (uppercase)" << endl << endl;
                       cout << "Are you suffering from "<< variableList[i].varname<< " :   ";
                       cin >> data;
                   }
                variableList[i].varvalue = data;
                variableList[i].varstatus = "I";
            }
            return i;
        }
    }
    return -1;
}

/******************************************************************************
instantiation(): if a valid symptom(variable) is found from function variableIndex(),it
                will instantiate the respective variable status in the conclusion
                list.
Parameters used : var
returns : nothing
*******************************************************************************/

void BackwardChaining::instantiation(string var){
    for(int i=0; i<33; i++){ //--------->>>>>> update here as well
        if(variableList[i].varname == var){
            if(variableList[i].varstatus == "NI"){
                cout << "Are you suffering from  "<< variableList[i].varname << " :   ";
                string data;
                cin >> data;
                variableList[i].varvalue = data;
                variableList[i].varstatus = "I";
            }
            break;
        }
    }
}

/******************************************************************************
variableValue(): This function will update variable list depending on the user
                 input and instantiate the respective variable status.
Parameters used : symptom
returns : YES/NO, depending on the user input
******************************************************************************/

string BackwardChaining::variableValue(string symptom){

    string res = "";
    for(int i=0; i<33; i++){ //----------->>>>>>>> update here as well
        if(variableList[i].varname == symptom){
            if(variableList[i].varstatus == "NI"){
                cout << "Are you suffering from "<< variableList[i].varname << " :   ";
                string data;
                cin >> data;
                variableList[i].varvalue = data;
                variableList[i].varstatus = "I";
                return data;
            }
            else{
                return variableList[i].varvalue;
            }
        }
    }
}

/******************************************************************************
knowledgeBase(): depending on the rule number function will check the clause variable
                 list, if all the clause variables are matching with the user entered
                 data then the function will diagnose the disease and updates variable
                 name, variable status and variable value.
Parameters used :ruleNumber, clausePair( is a reference variable)
returns : returns diagnosis of type structure variable.
*******************************************************************************/

variable BackwardChaining::knowledgeBase(int ruleNumber, map<string,string> &clausePair)
{
    variable diagnosis;
    diagnosis.varname = "";
    diagnosis.varstatus = "false";
    diagnosis.varvalue = "";

    if(ruleNumber == 10){

        if(clausePair.find("HEAD_INJURY")->second == "YES" && clausePair.find("ANXIETY")->second == "YES"
           && clausePair.find("INSOMNIA")->second == "YES" && clausePair.find("AGGRESSION")->second == "YES" && clausePair.find("DISORIENTATION")->second == "YES"
           && clausePair.find("HALLUCINATIONS")->second == "YES" && clausePair.find("DELUSIONS")->second == "YES" && clausePair.find("UNABLE_TO_MOVE")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Schizophrenia";
            return diagnosis;
        }
    }

        if(ruleNumber == 20){

        if(clausePair.find("HEAD_INJURY")->second == "YES" && clausePair.find("ANXIETY")->second == "YES"
           && clausePair.find("INSOMNIA")->second == "YES" && clausePair.find("AGGRESSION")->second == "YES" && clausePair.find("DISORIENTATION")->second == "YES"
           && clausePair.find("HALLUCINATIONS")->second == "NO" && clausePair.find("SWEATING")->second =="YES" ){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "General_Anxiety_Disorder";
            return diagnosis;
        }
    }

    if(ruleNumber == 30){

        if( clausePair.find("HEAD_INJURY")->second == "YES" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("INSOMNIA")->second ==  "YES"
           &&  clausePair.find("AGGRESSION")->second == "YES" && clausePair.find("DISORIENTATION")->second == "NO" && clausePair.find("HALLUCINATIONS")->second == "YES"
           && clausePair.find("MOOD_SWINGS")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Bipolar_I";
            return diagnosis;
        }
    }

    if(ruleNumber == 40){

        if( clausePair.find("HEAD_INJURY")->second == "YES" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("INSOMNIA")->second ==  "YES"
           &&  clausePair.find("AGGRESSION")->second == "YES" && clausePair.find("DISORIENTATION")->second == "NO" && clausePair.find("HALLUCINATIONS")->second == "NO"
           && clausePair.find("FLASHBACKS")->second == "YES") {
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Post_Traumatic_Stress_Disorder";
            return diagnosis;
        }
    }

    if(ruleNumber == 50){

        if( clausePair.find("HEAD_INJURY")->second == "YES" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("INSOMNIA")->second ==  "YES"
           &&  clausePair.find("AGGRESSION")->second == "NO" && clausePair.find("DEPRESSION")->second == "YES" && clausePair.find("MOOD_SWINGS")->second == "YES"
           && clausePair.find("FATIGUE")->second == "YES" ){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Major_Depressive_Disorder";
            return diagnosis;
        }
    }

    if(ruleNumber == 60){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("DEPRESSION")->second ==  "YES"
           &&  clausePair.find("DISORIENTATION")->second == "YES" && clausePair.find("INSOMNIA")->second == "YES" && clausePair.find("MEMORY_LOSS")->second == "YES"
           && clausePair.find("UNABLE_TO_MOVE")->second == "YES" && clausePair.find("PARANOID")->second == "YES" ) {
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Alzheimers";
            return diagnosis;
        }
    }

    if(ruleNumber == 70){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("DEPRESSION")->second ==  "YES"
           &&  clausePair.find("DISORIENTATION")->second == "YES" && clausePair.find("INSOMNIA")->second == "YES" && clausePair.find("MEMORY_LOSS")->second == "YES"
           && clausePair.find("UNABLE_TO_MOVE")->second == "NO" && clausePair.find("HALLUCINATIONS")->second == "YES" && clausePair.find("DIFFICULTY_PLANNING")->second == "YES" ){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Dementia";
            return diagnosis;
        }
    }

    if(ruleNumber == 80){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("DEPRESSION")->second ==  "YES"
           &&  clausePair.find("DISORIENTATION")->second == "YES" && clausePair.find("INSOMNIA")->second == "YES" && clausePair.find("MEMORY_LOSS")->second == "NO"
           && clausePair.find("SOCIAL_ISOLATION")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Major_Depressive_Disorder";
            return diagnosis;
        }
    }

    if(ruleNumber == 90){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("DEPRESSION")->second ==  "YES"
           &&  clausePair.find("DISORIENTATION")->second == "YES" && clausePair.find("INSOMNIA")->second == "NO" && clausePair.find("SOCIAL_ISOLATION")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Schizo_Affective_Disorder";
            return diagnosis;
        }
    }

    if(ruleNumber == 100){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("DEPRESSION")->second ==  "YES"
           &&  clausePair.find("DISORIENTATION")->second == "NO" && clausePair.find("AMNESIA")->second == "YES" && clausePair.find("TREMOR")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Parkinsons_Disorder";
            return diagnosis;
        }
    }

    if(ruleNumber == 110){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("DEPRESSION")->second ==  "YES"
           &&  clausePair.find("DISORIENTATION")->second == "NO" && clausePair.find("AMNESIA")->second == "NO" && clausePair.find("HALLUCINATIONS")->second == "YES"
           && clausePair.find("AGGRESSION")->second == "YES" ){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Bipolar_I";
            return diagnosis;
        }
    }

    if(ruleNumber == 120){

        if(clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("DEPRESSION")->second ==  "YES"
           &&  clausePair.find("DISORIENTATION")->second == "NO" && clausePair.find("AMNESIA")->second == "YES" && clausePair.find("TREMOR")->second == "NO"
           && clausePair.find("IMPULSIVE")->second == "YES" ){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Mild_Cognitive_Impairment";
            return diagnosis;
        }
    }

    if(ruleNumber == 130){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("DEPRESSION")->second ==  "NO"
           &&  clausePair.find("AGGRESSION")->second == "YES" && clausePair.find("INSOMNIA")->second == "YES" && clausePair.find("DISORIENTATION")->second == "YES"
           && clausePair.find("TREMOR")->second == "YES" && clausePair.find("HALLUCINATIONS")->second == "YES" && clausePair.find("UNABLE_TO_MOVE")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Schizophrenia";
            return diagnosis;
        }
    }

    if(ruleNumber == 140){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("DEPRESSION")->second ==  "NO"
           &&  clausePair.find("AGGRESSION")->second == "YES" && clausePair.find("INSOMNIA")->second == "YES" && clausePair.find("DISORIENTATION")->second == "YES"
           && clausePair.find("TREMOR")->second == "YES" && clausePair.find("HALLUCINATIONS")->second == "NO" && clausePair.find("SWEATING")->second == "YES" ){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "General_Anxiety_Disorder";
            return diagnosis;
        }
    }

    if(ruleNumber == 150){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("DEPRESSION")->second ==  "NO"
           &&  clausePair.find("AGGRESSION")->second == "YES" && clausePair.find("INSOMNIA")->second == "NO" && clausePair.find("COUNTING_IN_PATTERN")->second == "YES" ){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Obsessive_Compulsive_Disorder";
            return diagnosis;
        }
    }

    if(ruleNumber == 160){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("DEPRESSION")->second ==  "NO"
           &&  clausePair.find("AGGRESSION")->second == "NO" && clausePair.find("PARESTHESIAS")->second == "YES" && clausePair.find("PALPITATIONS")->second == "YES" ){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Panic_Attack";
            return diagnosis;
        }
    }

    if(ruleNumber == 170){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("DEPRESSION")->second ==  "NO"
           &&  clausePair.find("AGGRESSION")->second == "NO" && clausePair.find("PARESTHESIAS")->second == "NO" && clausePair.find("URGE_TO_STEAL")->second == "YES"
           && clausePair.find("RELIEF_STEALING")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Kleptomania";
            return diagnosis;
        }
    }

    if(ruleNumber == 180){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "YES" && clausePair.find("DEPRESSION")->second ==  "NO"
           &&  clausePair.find("AGGRESSION")->second == "NO" && clausePair.find("PARESTHESIAS ")->second == "NO" && clausePair.find("URGE_TO_STEAL")->second == "NO"
           && clausePair.find("HALLUCINATIONS")->second == "YES" && clausePair.find("MEMORY_LOSS")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Hypersomnolence";
            return diagnosis;
        }
    }

    if(ruleNumber == 190){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "NO" && clausePair.find("AGGRESSION")->second ==  "YES"
           &&  clausePair.find("MISBEHAVE")->second == "YES" && clausePair.find("RESENTMENT")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Oppositional_Defiant_Disorder";
            return diagnosis;
        }
    }

    if(ruleNumber == 200){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "NO" && clausePair.find("AGGRESSION")->second ==  "YES"
           &&  clausePair.find("MISBEHAVE")->second == "YES" && clausePair.find("RESENTMENT")->second == "NO" && clausePair.find("DISTRESSED")->second == "YES" ){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Intermittent_Explosive_Disorder";
            return diagnosis;
        }
    }

    if(ruleNumber == 210){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "NO" && clausePair.find("AGGRESSION")->second ==  "YES"
           &&  clausePair.find("MISBEHAVE")->second == "NO" && clausePair.find("INSOMNIA")->second == "YES" && clausePair.find("DISORIENTATION")->second == "YES"
           && clausePair.find("TALKATIVE")->second == "YES" && clausePair.find("DEPRESSION")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Cyclothymia";
            return diagnosis;
        }
    }

    if(ruleNumber == 220){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "NO" && clausePair.find("AGGRESSION")->second ==  "YES"
           &&  clausePair.find("MISBEHAVE")->second == "NO" && clausePair.find("INSOMNIA")->second == "YES" && clausePair.find("DISORIENTATION")->second == "YES"
           && clausePair.find("TALKATIVE")->second == "YES" && clausePair.find("DEPRESSION")->second == "NO" && clausePair.find("EUPHORIA")->second == "YES" ){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Hypomania";
            return diagnosis;
        }
    }

    if(ruleNumber == 230){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "NO" && clausePair.find("AGGRESSION")->second ==  "YES"
           &&  clausePair.find("MISBEHAVE")->second == "NO" && clausePair.find("INSOMNIA")->second == "YES" && clausePair.find("DISORIENTATION")->second == "YES"
           && clausePair.find("TALKATIVE")->second == "NO" && clausePair.find("ANNOYED")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Dysthymia";
            return diagnosis;
        }
    }

    if(ruleNumber == 240){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "NO" && clausePair.find("AGGRESSION")->second ==  "YES"
           &&  clausePair.find("MISBEHAVE")->second == "NO" && clausePair.find("INSOMNIA")->second == "NO" && clausePair.find("TREMOR")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Delirium_Tremens";
            return diagnosis;
        }
    }

    if(ruleNumber == 250){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "NO" && clausePair.find("AGGRESSION")->second ==  "NO"
           &&  clausePair.find("SOCIAL_ISOLATION")->second == "YES" && clausePair.find("INFERIORITY")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Social_Anxiety_Disorder";
            return diagnosis;
        }
    }


    if(ruleNumber == 260){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "NO" && clausePair.find("AGGRESSION")->second ==  "NO"
           &&  clausePair.find("SOCIAL_ISOLATION")->second == "YES" && clausePair.find("INFERIORITY")->second == "NO" && clausePair.find("DELUSIONS")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Agrophobia";
            return diagnosis;
        }
    }

    if(ruleNumber == 270){

        if( clausePair.find("HEAD_INJURY")->second == "NO" &&  clausePair.find("ANXIETY")->second ==  "NO" && clausePair.find("AGGRESSION")->second ==  "NO"
           &&  clausePair.find("SOCIAL_ISOLATION")->second == "NO" && clausePair.find("FAST_HEART_RATE")->second == "YES" && clausePair.find("SWEATING")->second == "YES"){
            diagnosis.varstatus = "true";
            diagnosis.varname = "DIAGNOSIS";
            diagnosis.varvalue = "Panic_Disorder_with_Agrophobia";
            return diagnosis;
        }
    }
    return diagnosis;
}
