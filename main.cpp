#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;

/* ================= TEAM MEMBER ================= */

class TeamMember {
    int teamid;
    char fullname[20];
    char mobile[20];
    char skillset[20];
    char role[20];

public:
    int get() { return teamid; }

    void getData() {
        cout << "Enter Team ID: ";
        cin >> teamid;
        cin.ignore();

        cout << "Enter Full Name: ";
        cin.getline(fullname, 20);

        cout << "Enter Mobile: ";
        cin.getline(mobile, 20);

        cout << "Enter Skill Set: ";
        cin.getline(skillset, 20);

        cout << "Enter Role: ";
        cin.getline(role, 20);
    }

    void heading() {
        cout << left << setw(7) << "ID"
             << setw(15) << "Name"
             << setw(15) << "Mobile"
             << setw(15) << "Skill"
             << setw(15) << "Role" << endl;
    }

    void showData() {
        cout << left << setw(7) << teamid
             << setw(15) << fullname
             << setw(15) << mobile
             << setw(15) << skillset
             << setw(15) << role << endl;
    }

    void addTeamMember() {
        ofstream file("TeamMember.dat", ios::binary | ios::app);
        getData();
        file.write((char*)this, sizeof(*this));
        file.close();
        cout << "Team Member Added Successfully\n";
    }

    void displayTeamMember() {
        ifstream file("TeamMember.dat", ios::binary);
        heading();
        while (file.read((char*)this, sizeof(*this))) {
            showData();
        }
        file.close();
    }

    void editTeamMember() {
        fstream file("TeamMember.dat", ios::binary | ios::in | ios::out);
        int id, found = 0;
        cout << "Enter Team ID to edit: ";
        cin >> id;

        while (file.read((char*)this, sizeof(*this))) {
            if (teamid == id) {
                found = 1;
                file.seekp(-sizeof(*this), ios::cur);
                getData();
                file.write((char*)this, sizeof(*this));
                break;
            }
        }
        file.close();

        if (!found) cout << "Record Not Found\n";
    }

    void deleteTeamMember() {
        ifstream in("TeamMember.dat", ios::binary);
        ofstream out("Temp.dat", ios::binary);

        int id, found = 0;
        cout << "Enter Team ID to delete: ";
        cin >> id;

        while (in.read((char*)this, sizeof(*this))) {
            if (teamid != id)
                out.write((char*)this, sizeof(*this));
            else
                found = 1;
        }

        in.close();
        out.close();

        remove("TeamMember.dat");
        rename("Temp.dat", "TeamMember.dat");

        if (found) cout << "Record Deleted\n";
        else cout << "Record Not Found\n";
    }
};

/* ================= PROJECT ================= */

class Project {
    int pcode;
    char customer[20];
    char pname[20];
    char start[15];
    char end[15];

public:
    int get() { return pcode; }

    void getData() {
        cout << "Enter Project Code: ";
        cin >> pcode;
        cin.ignore();

        cout << "Customer Name: ";
        cin.getline(customer, 20);

        cout << "Project Name: ";
        cin.getline(pname, 20);

        cout << "Start Date: ";
        cin.getline(start, 15);

        cout << "End Date: ";
        cin.getline(end, 15);
    }

    void heading() {
        cout << left << setw(7) << "Code"
             << setw(15) << "Customer"
             << setw(15) << "Project"
             << setw(15) << "Start"
             << setw(15) << "End" << endl;
    }

    void showData() {
        cout << left << setw(7) << pcode
             << setw(15) << customer
             << setw(15) << pname
             << setw(15) << start
             << setw(15) << end << endl;
    }

    void addProject() {
        ofstream file("Project.dat", ios::binary | ios::app);
        getData();
        file.write((char*)this, sizeof(*this));
        file.close();
        cout << "Project Added\n";
    }

    void displayProject() {
        ifstream file("Project.dat", ios::binary);
        heading();
        while (file.read((char*)this, sizeof(*this))) {
            showData();
        }
        file.close();
    }

    void editProject() {
        fstream file("Project.dat", ios::binary | ios::in | ios::out);
        int id, found = 0;
        cout << "Enter Project Code to edit: ";
        cin >> id;

        while (file.read((char*)this, sizeof(*this))) {
            if (pcode == id) {
                found = 1;
                file.seekp(-sizeof(*this), ios::cur);
                getData();
                file.write((char*)this, sizeof(*this));
                break;
            }
        }
        file.close();

        if (!found) cout << "Project Not Found\n";
    }

    void deleteProject() {
        ifstream in("Project.dat", ios::binary);
        ofstream out("Temp.dat", ios::binary);

        int id, found = 0;
        cout << "Enter Project Code to delete: ";
        cin >> id;

        while (in.read((char*)this, sizeof(*this))) {
            if (pcode != id)
                out.write((char*)this, sizeof(*this));
            else
                found = 1;
        }

        in.close();
        out.close();

        remove("Project.dat");
        rename("Temp.dat", "Project.dat");

        if (found) cout << "Project Deleted\n";
        else cout << "Project Not Found\n";
    }
};

/* ================= MENUS ================= */

void teamMenu() {
    TeamMember t;
    int ch;
    do {
        system("cls");
        cout << "\n1.Add  2.Display  3.Edit  4.Delete  0.Back\nChoice: ";
        cin >> ch;
        system("cls");
        switch (ch) {
        case 1: t.addTeamMember(); break;
        case 2: t.displayTeamMember(); break;
        case 3: t.editTeamMember(); break;
        case 4: t.deleteTeamMember(); break;
        }
        system("pause");
    } while (ch != 0);
}

void projectMenu() {
    Project p;
    int ch;
    do {
        system("cls");
        cout << "\n1.Add  2.Display  3.Edit  4.Delete  0.Back\nChoice: ";
        cin >> ch;
        system("cls");
        switch (ch) {
        case 1: p.addProject(); break;
        case 2: p.displayProject(); break;
        case 3: p.editProject(); break;
        case 4: p.deleteProject(); break;
        }
        system("pause");
    } while (ch != 0);
}

int main() {
    int ch;
    do {
        system("cls");
        cout << "\n1.Team Management\n2.Project Management\n0.Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
        case 1: teamMenu(); break;
        case 2: projectMenu(); break;
        }
    } while (ch != 0);
    return 0;
}
