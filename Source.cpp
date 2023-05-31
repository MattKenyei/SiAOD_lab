#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int const max_students = 1000;
int N = 0;
string names[max_students];
int friends[max_students][max_students];

void initialize_array(int(&arr)[max_students][max_students], int max_num) {
    for (int i = 0; i < max_num; ++i) {
        for (int j = 0; j < max_num; ++j) {
            arr[i][j] = 0;
        }
    }
}

int string_to_int(string s) {
    int num = 0;
    for (int i = 0; i < s.length(); ++i) {
        num *= 10;
        num += s[i] - '0';
    }
    return num;
}

bool find_in_array(int finding, int arr[max_students]) {
    int size = sizeof(arr) / sizeof(int);
    size -= 1;
    for (int i = 0; i < max_students; ++i) {
        if (arr[i] == finding) return true;
    }
    return false;
}

int find_new_friends(int first, int second, int& depth, int path[max_students]) {
    if (find_in_array(first, path)) return -1;
    else {
        for (int i = 0; i < N; ++i) {
            if (friends[first][i] != 0) {
                if (i == second) return depth + 1;
                else {
                    path[depth] = first;
                    int fr = find_new_friends(i, second, depth=(depth + 1), path);
                    if (fr == -1) continue;
                    else return fr;
                }
            }
        }
    }
    return -1;
}

int find_number_of_student(string st) {
    for (int i = 0; i < N; ++i) 
    {
        if (names[i] == st) return i;
    }
    return -1;
}

int main(int argc, char* argv[]) {
    ifstream f_names("students.txt");
    string student;
    while (!f_names.eof()) {
        int number;
        f_names >> number;
        f_names.get();
        f_names >> student;

        if (student == "") continue;

        names[number] = student;
        N++;
    }

    ifstream f_friends("friends.txt");
    while (!f_friends.eof()) {
        int number;
        f_friends >> number;


        f_friends.get();
        string s;
        getline(f_friends, s);
        int space = 0;
        int num = 0;
        while ((space = s.find(" ")) != -1) {
            num = string_to_int(s.substr(0, space));
            friends[number][num] = 1;
            s = s.substr(space + 1);
        }
        num = string_to_int(s.substr(0, space));

       // cout << "number " << friends[number] << "\n";

        friends[number][num] = 1;
    }

   /* for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            printf("%d ", friends[i][j]);
        }
        printf("\n");
    }*/

    string st1, st2;
    int st1_num, st2_num;
    int path[max_students];
    int depth = 0;
    cout << "Input name of first student: ";
    cin >> st1;
    cout << "Input name of second student: ";
    cin >> st2;
    st1_num = find_number_of_student(st1);
    st2_num = find_number_of_student(st2);
    depth = find_new_friends(st1_num, st2_num, depth, path);
    if (depth < 0)
        cout << "Already introdused" << endl;
    else
        cout << "Students " << st1 << " and " << st2 << " are introdused through " << depth << " weeks" << endl;

    return 0;
}