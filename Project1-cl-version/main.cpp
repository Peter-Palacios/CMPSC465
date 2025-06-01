#include <iostream>
#include <fstream>
#include <string>W
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
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}


bool train_can_be_sorted(const vector<int> &permutationed_received){
    vector<int> arriving_coaches_array = permutationed_received;
    ranges::sort(arriving_coaches_array,  std::less<int>() );

    stack<int> train_station_stack;

    int k=0;

    for (int i = 0; i <arriving_coaches_array.size(); i++) {
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

    // Read from the text file
    string current_line;

    int line_count = 1;
    int block_size = 0;
    vector<int> received_vec;

    int desired_outf_line_number = 1;
    int number_of_tests_passed = 0;
    while (getline (f, current_line)) {
        if(block_size == 0 || current_line.length() == 1)
        {
            block_size = stoi(current_line);
            line_count +=1;
            continue;
        }
        else
        {

            string new_int;
            int parsed_value = -1;
            int block_pointer = 0;
            int char_pointer = 0;


            // int number_of_tests = 0;
            while(block_pointer < block_size)
            {

                if (current_line[char_pointer] == '0')
                {
                    return -1;
                }

                if (current_line[char_pointer] == ' '){

                    parsed_value = std::stoi(current_line);
                    received_vec[block_pointer] = parsed_value;
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

                cout << "Expected response: " << expected_response <<"Actual response: "<< can_be_sorted <<endl;

                if (expected_response == can_be_sorted) {
                    number_of_tests_passed++;
                }
                desired_outf_line_number++;

            }

        }

        line_count +=1;
    }
    cout << number_of_tests_passed << "/"<<desired_outf_line_number<<" tests passed"<< endl;

    return 0;
}


    // sort ascending
    // std::sort( start_iterator, end_iterator, bool compare() );

    // So for an array of int --
    // //sort ascending
    // std::sort( A.begin() , A.end(),  std::less<int>() );

    // // sort descending
    // std::sort( A.begin() , A.end(),  std::greater<int>() );

    // // sort with lambda function
    // std::sort( A.begin() , A.end(),
    //            [](int a, int b) { return a < b;  }


            //this part should be recursive until the end of the file

            // for (int i = 0; i < current_line.length(); i++) {
            //     //search each char
            //     if (current_line[i] == '0')
            //     {
            //         return -1;
            //     }

            //     if (current_line[i] == ' '){

            //         parsed_value = std::stoi(new_int);
            //         // received_array.Add(parsed_value);
            //         received_vec[i] = parsed_value;
            //         // received_array[i]->Add(parsed_value);
            //         new_int = "";

            //     }
            //     else
            //     {
            //         new_int += current_line[i];
            //     }

            // }