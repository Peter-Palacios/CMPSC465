/**

*Academic Integrity Statement: I certify that, while others may have assisted me in brain storming, debugging and validating this program, the program itself is my own work. I understand that submitting code which is the work of other individuals is a violation of the course Academic Integrity Policy and may result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. I also understand that if I knowingly give my original work to another individual that it could also result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. See Academic Integrity Procedural GuidelinesLinks to an external site. at:  https://psbehrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural-guidelinesLinks to an external site.

*Assisted by and Assisted line numbers:


*Your Name: Peter Palacios

*Your PSU user ID:  pfp5237

*Course title: CMPSC465 Semester Summer 2025

*Due Time: 11:59 PM, Sun, Jun-01-2025

*Time of Last Modification: 06:59 PM, Sun, Jun-01-2025

*Description: Program takes test input file, runs program logic that checks whether the permutationed order is able to be output

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <stack>
using namespace std;


//This is the actual algorithm used to verify if the train coaches can be sorted, which takes a vector<int> as input and sorts and uses a stack to verify
bool train_can_be_sorted(const vector<int> &permutationed_received){
    vector<int> arriving_coaches_array = permutationed_received;
    ranges::sort(arriving_coaches_array,  std::less<int>() );

    stack<int> train_station_stack;

    int k=0;

    for (int i = 0; i <arriving_coaches_array.size(); i++) {
        while (!train_station_stack.empty() && train_station_stack.top() == permutationed_received[k]) {
            train_station_stack.pop();
            k++;
        }
        if (arriving_coaches_array[i] == permutationed_received[k]) {
            train_station_stack.push(arriving_coaches_array[i]);
            train_station_stack.pop();
            k++;
        }
        else {
            train_station_stack.push(arriving_coaches_array[i]);
        }
    }

    if (train_station_stack.empty()) {
        return true;
    }
    return false;
}

//method is used to help parse string expected to boolean
bool to_bool(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    string n;
    for (int i = 0; i < 2; i++) {
        n += str[i];
    }
    if (n == "no") {
        return false;
    }

    return true;
}

//method is used to output actual and expected test cases
void output_test_result(bool expected, bool actual) {
    string expected_response_str;
    string actual_response_str;
    if (expected == 0) {
        expected_response_str = "false";
    }
    else {
        expected_response_str = "true";
    }
    if (actual == 0) {
        actual_response_str = "false";
    }
    else {
        actual_response_str = "true";
    }
    cout << "Expected response: " << expected_response_str <<", Actual response: "<< actual_response_str <<endl;
}

int main(){
    ifstream f("lab1in.txt");
    if (!f.is_open())
    {
        cerr << "Error opening input file";
        return 1;
    }
    else {
        cout << "Input file successfully opened"<<endl;
    }

    string current_line;

    int block_size = 0;
    vector<int> received_vec;
    int desired_outf_line_number = 0;
    int number_of_tests_passed = 0;

    //this while loop is used to parse the testfile for an input and then use that input for the algorithm and then parses the output file and verifies
    while (getline (f, current_line)) {
        if(block_size == 0 && current_line != "0\r")
        {
            block_size = stoi(current_line);
            continue;
        }
        if (current_line == "0\r"){
            block_size = 0;
            break;
        }
        string new_int;
        int parsed_value = -1;
        int block_pointer = 0;
        int char_pointer = 0;

        while(block_pointer < block_size)
        {

            if (current_line[char_pointer] == ' '){

                parsed_value = std::stoi(new_int);
                received_vec.push_back(parsed_value);
                new_int = "";
                block_pointer +=1;
            }
            else
            {
                new_int += current_line[char_pointer];
            }

            char_pointer+=1;
        }
        if (received_vec.size() == block_size)
        {

            bool can_be_sorted = train_can_be_sorted(received_vec);

            string current_outf_line;
            ifstream outf("lab1out-1.txt");

            int current_outf_line_number = 0;
            desired_outf_line_number++;
            while (!outf.eof())
            {
                current_outf_line_number++;
                getline(outf, current_outf_line);
                if (current_outf_line_number == desired_outf_line_number)
                {
                    break;
                }

            }
            bool expected_response = to_bool(current_outf_line);
            output_test_result(expected_response, can_be_sorted);

            if (expected_response == can_be_sorted) {
                number_of_tests_passed++;
            }

            received_vec.clear();
        }
    }
    cout << number_of_tests_passed << "/"<<desired_outf_line_number<<" tests passed"<< endl;
    return 0;
}

/*
Program Output:
Input file successfully opened
Expected response: false, Actual response: false
Expected response: true, Actual response: true
Expected response: false, Actual response: false
Expected response: false, Actual response: false
Expected response: false, Actual response: false
Expected response: true, Actual response: true
Expected response: true, Actual response: true
7/7 tests passed
 */