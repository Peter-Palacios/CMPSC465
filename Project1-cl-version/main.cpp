#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <stack>
using namespace std;



//used for testing, taken from
//https://stackoverflow.com/questions/3613284/c-stdstring-to-boolean
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

    while(!train_station_stack.empty())
    {
        int check_value = train_station_stack.top();
        train_station_stack.pop();
        if (check_value == permutationed_received[k])
        {
            k++;
        }
        else
        {
            return false;
        }
    }
    return true;
}


int main(){

    //read file and then according sort
    ifstream f("lab1in.txt");
    if (!f.is_open())
    {
        cerr << "Error opening input file";
        return 1;
    }
    else {
        cout << "File successfully opened"<<endl;
    }

    string current_line;

    int line_count = 1;
    int block_size = 0;
    vector<int> received_vec;

    int desired_outf_line_number = 0;
    int number_of_tests_passed = 0;
    while (getline (f, current_line)) {
        if(block_size == 0 && current_line != "0\r")
        {
            block_size = stoi(current_line);
            line_count +=1;
            continue;
        }
        else if (current_line == "0\r"){
            block_size = 0;
            continue;
        }
        else
        {

            string new_int;
            int parsed_value = -1;
            int block_pointer = 0;
            int char_pointer = 0;

            while(block_pointer < block_size)
            {

                if (current_line[char_pointer] == ' '){

                    parsed_value = std::stoi(new_int);
                    // cout<< "parsed value is: " << parsed_value << endl;
                    received_vec.push_back(parsed_value);
                    // received_vec[block_pointer] = parsed_value;
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
                string expected_response_str;
                string actual_response_str;
                if (expected_response == 0) {
                    expected_response_str = "false";
                }
                else {
                    expected_response_str = "true";
                }
                if (can_be_sorted == 0) {
                    actual_response_str = "false";
                }
                else {
                    actual_response_str = "true";
                }
                cout << "Expected response: " << expected_response_str <<", Actual response: "<< actual_response_str <<endl;

                if (expected_response == can_be_sorted) {
                    number_of_tests_passed++;
                }


                received_vec.clear();
                //todo remove pointer memory here

            }

        }

        line_count +=1;
    }
    cout << number_of_tests_passed << "/"<<desired_outf_line_number<<" tests passed"<< endl;

    return 0;
}