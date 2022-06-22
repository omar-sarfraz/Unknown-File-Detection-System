#include <chrono>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::time_point;
using std::chrono::system_clock;

void monitorRunEvent();
void initializeBlacklist();
void initializeScripts();
void initializeBlackLinkedList();
void initializeProcessLinkedList();
void updateBlackLinkedList(string fileName);
void updateBlackList();
void decision();
bool compareProcess();
void blockProcess();
void addToBlackList(string name);
int DisplayConfirmSaveAsMessageBox();
int DisplayDeleteMessageBox();
int DeletedMessageBox();
void DisplayLines(string line);

struct node {
    string name;
    string path;
    struct node *next;
};

struct node *head = NULL, *list1, *temp;
struct node *head2 = NULL, *list2, *temp2;
string blockName, blockPath;

bool insert(string name){
    bool added = false;

    list1 = head;

    if(head == NULL){
        head = new node;
        head -> name = name;
        head -> next = NULL;
        added = true;
    } else {
        while(list1 -> next != NULL && list1 -> name != name){
            list1 = list1 -> next;
        }
        if(list1 -> next == NULL && list1 -> name != name){
            temp = new node;
            temp -> name = name;
            temp -> next = NULL;
            list1 -> next = temp;
            added = true;
        }
    }

    if(!added){
        return 0;
    } else {
        return 1;
    }
}

void print(){
    if(head == NULL){
        cout << "BlackList is empty!" << endl;
        Sleep(1000);
        return;
    }
    cout << endl;
    cout << "BlackList: " << endl;
    list1 = head;
    while(list1 -> next != NULL){
        cout << list1 -> name << endl;
        list1 = list1 -> next;
    }
    if(list1 -> next == NULL){
        cout << list1 -> name << endl;
    }
    Sleep(2000);
}

bool empty1(){
    if(head == NULL){
        return 1;
    } else {
        return 0;
    }
}

bool empty2(){
    if(head2 == NULL){
        return 1;
    } else {
        return 0;
    }
}

void delete1(){
    if(head == NULL){
        cout << "BlackLinkedList is empty!" << endl;
        return;
    }

    temp = new node();

    while( head != NULL){
        temp = head;
        head = head -> next;
        free(temp);
    }
}

void insert2(string name, string path){
    list2 = head2;

    if(head2 == NULL){
        head2 = new node;
        head2 -> name = name;
        head2 -> path = path;
        head2 -> next = NULL;
    } else {
        while(list2 -> next != NULL){
            list2 = list2 -> next;
        }
        if(list2 -> next == NULL){
            temp2 = new node;
            temp2 -> name = name;
            temp2 -> path = path;
            temp2 -> next = NULL;
            list2 -> next = temp2;
        }
    }
}

void print2(){
    if(head2 == NULL){
        cout << "ProcessList is empty!" << endl;
        Sleep(1000);
        return;
    }

    list2 = head2;
    while(list2 -> next != NULL){
        cout << list2 -> name << endl;
        cout << list2 -> path << endl;
        list2 = list2 -> next;
    }
    if(list2 -> next == NULL){
        cout << list2 -> name << endl;
        cout << list2 -> path << endl;
    }
    Sleep(2000);
}

void delete2(){
    if(head == NULL){
        cout << "BlackLinkedList is empty!" << endl;
        return;
    }

    temp2 = new node();

    while( head2 != NULL){
        temp2 = head2;
        head2 = head2 -> next;
        free(temp2);
    }
}

int main(){
    menu:
    system("cls");
    cout << "Press 1 to start monitoring" << endl;
    cout << "Press 2 to remove a program from BlackList" << endl;
    cout << "Press 3 to add a program to BlackList" << endl;
    cout << "Press 4 to view BlackList" << endl;
    cout << "Press 5 to exit" << endl;

    initializeBlackLinkedList();

    string name, name2;
    cout << endl;
    cout << "Enter Choice: ";
    int choice;
    cin >> choice;

    while((choice > 5 && choice < 1) || cin.fail()){
        cin.clear();
        cin.ignore();
        cout << "Wrong Choice! Enter again: " << endl;
        cin >> choice;
    }
string str1,str2,str3,str4;
    switch(choice){
        case 1:
             str1="Monitoring Downloads Folder ...\n";
             str2="Monitoring Processes ...\n" ;
            DisplayLines(str1);
            DisplayLines(str2);
            initializeScripts();
            Sleep(5);

            //initializeBlacklist();
            str3="Real-Time Protection Active...\n";
            DisplayLines(str3);

            cout << endl;
            cout<<"Press Escape Key to stop monitoring."<<endl;

            monitorRunEvent();
            break;
        case 2:
            print();
            cout << endl;
            if(!empty1()){
                cout << "Enter complete name of program that you want to remove: ";
                cin >> name;
                updateBlackLinkedList(name);
            }
            break;
        case 3:
            print();
            cout << endl;

            cout << "Enter complete name of program that you want to add (make sure to add .exe): ";
            cin >> name2;
            addToBlackList(name2);

            break;
        case 4:
            print();
            break;
        case 5:
            system("taskkill /im powershell.exe");
            return 0;
            break;
    }
    goto menu;

    return 0;
}

void monitorRunEvent(){
    bool running = true;
    while(1 && running){
        if(GetAsyncKeyState(VK_RETURN) & 0x8000 != 0){
            //cout << "Return" << endl;
            initializeBlacklist();
            decision();
        }

        if(GetAsyncKeyState(VK_ESCAPE) & 0x8000 !=0){
            running = false;
        }

        if(GetAsyncKeyState(VK_LBUTTON) & 0x8000 !=0){

            int doubleClickTime = GetDoubleClickTime();
            bool doubleClick = false;

            time_point<system_clock> start;
            start = system_clock::now(); /* start timer */
            while(true){
                __int64 secondsElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-start).count();

                if(GetAsyncKeyState(VK_LBUTTON) & 0x8000 != 0){
                    doubleClick = true;
                    break;
                }

                if(secondsElapsed >= doubleClickTime){
                    break;
                }
            }
            if(doubleClick){
                //cout << "Double Click" << endl;
                initializeBlacklist();
                decision();
            } else {
                //cout << "Single Click" << endl;
            }

        }

        if(GetAsyncKeyState(VK_RBUTTON) & 0x8000 != 0){

            bool rightThenLeft = false;

            time_point<system_clock> start;
            start = system_clock::now(); /* start timer */
            while(true){
                __int64 secondsElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-start).count();

                if((GetAsyncKeyState(VK_LBUTTON) & 0x8000 != 0) || (GetAsyncKeyState(VK_RBUTTON) & 0x8000 != 0)){
                    rightThenLeft = true;
                    break;
                }

                if(secondsElapsed >= 5000){
                    break;
                }
            }
            if(rightThenLeft){
                initializeBlacklist();
                decision();
            } else {
                //cout << "Right Click" << endl;
            }
        }

    }

}

void decision(){
    Sleep(2000);
    delete1();
    initializeBlackLinkedList();
    //cout << "BlackList: " << endl;
    //print();
    //cout << endl;
    delete2();
    initializeProcessLinkedList();
    //cout << "ProcessList:" << endl;
    //print2();
    //cout << endl;
    string command, command2;

    if(compareProcess()){
        //Code to bring window to front
        HWND hwnd = GetConsoleWindow();
        DWORD dwCurrentThread = GetCurrentThreadId();
        DWORD dwFGThread      = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
        AttachThreadInput(dwCurrentThread, dwFGThread, TRUE);
        SetForegroundWindow(hwnd);
        SetCapture(hwnd);
        SetFocus(hwnd);
        SetActiveWindow(hwnd);
        EnableWindow(hwnd, TRUE);
        AttachThreadInput(dwCurrentThread, dwFGThread, FALSE);
        //Code to bring window to front

        cout << "Block It" << endl;
        command = "Taskkill /im \"" + blockName + "\"";
        system(command.c_str());

        cout << "New Application " << blockName << " is trying to run..." << endl;
        cout << endl;
        DisplayConfirmSaveAsMessageBox();

        /*switch(choice){
        case 1:
            cout << blockName << " blocked successfully! " << endl;
            //cout << "Do you want to delete " << blockName << " ? (Y/N)"<< endl;
            //cin >> decision;

            switch(decision){
            case 'y':
            case 'Y':
                command2 = "del \"" + blockPath + "\"";
                system(command2.c_str());
                cout << "Removed " << blockPath << endl;
                break;
            case 'n':
            case 'N':
                break;
            }

            break;
        case 2:
            updateBlackLinkedList(blockName);
            string parentPath = blockPath.substr(0, (blockPath.size()-blockName.size()));
            cout << "Parent Path: " << parentPath  << blockName << endl;
            string allowCommand = "cd \"" + parentPath + "\" && start " + blockName;
            system(allowCommand.c_str());
            break;
        }

    } else {
        //cout << "Allow it" << endl;
    }*/
}
}
void updateBlackLinkedList(string fileName){
    //print();
    list1 = head;
    node *p = head;
    bool found = false;

    if(list1 -> name == fileName){
        head = head -> next;
        found = true;
        free(list1);
    } else {
        while(list1 -> name != fileName && list1 -> next != NULL){
            p = list1;
            list1 = list1 -> next;
        }

        if(list1 -> name == fileName){;
            p -> next = list1 -> next;
            found = true;
            free(list1);
        }
    }

    if(!found){
        cout << "Program not found in linked list" << endl;
        Sleep(1000);
        return;
    }
    //cout << endl;
    //cout << "BlackList:" << endl;
    updateBlackList();
    print();
}


void updateBlackList(){
    if(head == NULL){
        ofstream openFile ("blacklist.txt",ofstream::trunc);
        openFile.close();
        return;
    }
    list1 = head;
    ofstream blackListStream ("blacklist.txt");
    if(blackListStream.is_open()){
        while(list1 -> next != NULL){
            blackListStream << list1 -> name << endl;
            list1 = list1 -> next;
        }
        if(list1 -> next == NULL){
            blackListStream << list1 -> name << endl;
        }
    } else {
        cout << "Error opening file!";
    }

    blackListStream.close();
}

void addToBlackList(string name){
    if(!insert(name)){
        cout << "Program already exists!" << endl;
        Sleep(1000);
        return;
    };
    updateBlackList();
    cout << "Program added to BlackList" << endl;
    print();
    return;
}

void initializeBlacklist(){

    system("powerShell.exe -command \".\\InitBlacklistScript.ps1\"");

}

void initializeScripts(){

    system("powershell.exe -command \".\\startScripts.ps1");

}

void initializeProcessLinkedList(){
    again:
    ifstream processStream ("C:\\Program Files\\process.txt");
    string process, name, path;

    if(processStream.is_open()){
        while(getline(processStream,process)){
            int space = process.find(',');
            name = process.substr(0, space);
            path = process.substr(space+1, process.size());
            name += ".exe";
            insert2(name, path);
        }
    } else {
        goto again;
    }

    processStream.close();
    return;
}

void initializeBlackLinkedList(){
    ifstream blackListStream ("blacklist.txt");
    string blackList;

    while(getline(blackListStream,blackList)){
        insert(blackList);
    }

    blackListStream.close();
    return;
}

bool compareProcess(){
    if(head == NULL){
        return 0;
    }

    bool result = false;
    list1 = head;
    list2 = head2;

    while(list1 -> next != NULL) {
        while(list2 -> next != NULL) {

            if(list1 -> name == list2 -> name){
                result = true;
                blockName = list2 -> name;
                blockPath = list2 -> path;
                cout << endl;
                cout << list2 -> name << " should be blocked! It's path is " << list2 ->path << endl;
                cout << endl;
                return result;
            }
            else{
                list2 = list2 -> next;
            }
        }
        if(list2 -> next == NULL){
            if(list1 -> name == list2 -> name){
                result = true;
                blockName = list2 -> name;
                blockPath = list2 -> path;
                cout << endl;
                cout << list2 -> name << " should be blocked! It's path is " << list2 ->path << endl;
                cout << endl;
                return result;
            }
        }
        list2 = head2;
        list1 = list1 -> next;
    }

    if(list1 -> next == NULL){
        while(list2 -> next != NULL) {

            if(list1 -> name == list2 -> name){
                result = true;
                blockName = list2 -> name;
                blockPath = list2 -> path;
                cout << endl;
                cout << list2 -> name << " should be blocked! It's path is " << list2 ->path << endl;
                cout << endl;
                return result;
            }
            else{
                list2 = list2 -> next;
            }
        }
        if(list2 -> next == NULL){
            if(list1 -> name == list2 -> name){
                result = true;
                blockName = list2 -> name;
                blockPath = list2 -> path;
                cout << endl;
                cout << list2 -> name << " should be blocked! It's path is " << list2 ->path << endl;
                cout << endl;
                return result;
            }
        }
        list2 = head2;
        list1 = list1 -> next;
    }
    return result;
}
int DisplayConfirmSaveAsMessageBox()
{
    string newF = "New Application " + blockName +" is trying to run...\nPress YES to Block or NO to Allow?";
    int msgboxID = MessageBox(
        NULL,
        newF.c_str(),
        "Confirmation",
        MB_ICONEXCLAMATION | MB_YESNO
    );

    if (msgboxID == IDYES)
    {
        cout << blockName << " blocked successfully! " << endl;
        DisplayDeleteMessageBox();
    }
    if(msgboxID==IDNO){
        updateBlackLinkedList(blockName);
        string parentPath = blockPath.substr(0, (blockPath.size()-blockName.size()));
        cout << "Parent Path: " << parentPath  << blockName << endl;
        string allowCommand = "cd \"" + parentPath + "\" && start " + blockName;
        system(allowCommand.c_str());
    }

    return msgboxID;
}

int DisplayDeleteMessageBox()
{
    string command2;
    int msgboxID = MessageBox(
        NULL,
        "Do you want to Delete the file?",
        "Delete File",
        MB_ICONEXCLAMATION | MB_YESNO
    );

    if (msgboxID == IDYES)
    {
         command2 = "del \"" + blockPath + "\"";
         system(command2.c_str());

         DeletedMessageBox();
    }


    return msgboxID;
}
int DeletedMessageBox()
{
    string command2;
    string removed = "Removed " + blockPath;
    int msgboxID = MessageBox(
        NULL,
        removed.c_str() ,
        "File Deleted",
        MB_ICONEXCLAMATION | MB_OK
    );

    return msgboxID;
}
void DisplayLines(string line){
    for(int i=0;i<line.size();i++){
        cout<<line[i];
        Sleep(1);
    }

}
