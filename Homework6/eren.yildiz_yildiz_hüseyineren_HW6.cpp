// Huseyin Eren YILDIZ, 31047
// Homework 6

/******************************************************************************
Purpose: In this homework, I wrote a multithreaded C++ program that simulates the game, guess the number
Author: HUSEYIN EREN YILDIZ - 31047
Date: 27/05/2024
******************************************************************************/


#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <ctime>
#include <random>
#include <iomanip>

using namespace std;

// global variables and mutexes
// https://en.cppreference.com/w/cpp/thread/get_id

int min_bound, max_bound;
mutex mutex1;
thread::id winner;   // variable that includes threat id
vector<thread::id> thread_id;
bool finish;
bool round_S;
int h_num;
vector <int> scores;

/* Start: I took these code part from thread_codes -> threads16.cpp */
int random_range(const int & min, const int & max) {  // function to generate a random number in a range

    // static Mersenne Twister random number generator initialized with current time
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}
/* End: I took these code part from thread_codes -> threads16.cpp */


tm * getCurrentLocalTime() {

    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());  // get current time as time_t object

    tm * current_time = new tm;   // dynamically allocate a tm structure on the heap.

    localtime_s(current_time, &tt);   // convert time_t to tm as local time

    return current_time;   // return the local time as tm structure
}


void p_thread(tm * current_time, int id) {
// This function takes a pointer and int as parameters

    thread_id[id] = this_thread::get_id();    // store the thread id for the current thread
    this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(current_time)));   // sleep until the specified time

    while(!finish) {      // keep running until the finish variable is true

        int make_guess = random_range(min_bound, max_bound);   // produce a random number within the defined bounds

        tm * temp = getCurrentLocalTime();   // get the current local time
        mutex1.lock();    // lock the mutex

        if (round_S) {    // verify if the round is still active

            if (h_num == make_guess) {    // check if the guessed number is correct

                cout << "Player with id " << id << " guessed "<< make_guess;
                cout << " correctly at: " << put_time (temp, "%X") << endl;
                round_S = false;    // end the round
                winner = this_thread::get_id();   // set the winner
            }

            else {   // if the guess is incorrect

                cout << "Player with id " << id << " guessed "<< make_guess;
                cout << " incorrectly at: " << put_time(temp, "%X") << endl;

            }
        }

        mutex1.unlock();    // unlock the mutex
        this_thread::sleep_for(chrono::seconds(1));  // sleep for 1 second before the next guess

    }
}


void host_thread (int player_num, int round_num) {    // host thread function

    for (int i = 0; i < player_num; ++i) {   // initialize all player to 0
        scores[i]=0;
    }

    tm * ptm = getCurrentLocalTime();   // get the current local time

    for (int i = 0; i < round_num; ++i) {

        h_num = random_range(min_bound, max_bound);   // generate the target number for this round

        cout << endl << "---------------------------------------------------" << endl;

        ptm = getCurrentLocalTime();  // update the current local time

        if (i == 0) {

            // print the game start time and wait 3 seconds for the first round
            cout << "Game started at: " << put_time(ptm, "%X") << endl;
            cout << "Round 1 will start 3 seconds later" << endl;
            ptm -> tm_sec += 3;
        }

        else {
            // display the start time for next rounds
            cout << "Round " << i + 1 << " started at: " << put_time(ptm, "%X") << endl;
        }

        cout << "Target is " << h_num << endl << endl;

        round_S = true;   // set the round start flag

        // Start: I took these code part from CS204Lab12 and I updated it
        while (round_S) {   // wait for the round to finish

            this_thread::sleep_for(chrono::milliseconds (1));
        }
        // End: I took these code part from CS204Lab12 and I updated it

        for (int j = 0; j < player_num; j++) {    // update the scores based on the winner
            if (thread_id[j] == winner){
                scores[j]+=1;
            }
        }

        if ( i == (round_num-1) ) {    // If this is the last round, set the finish flag
            finish = true;
        }
    }
}


int main() {

    int player_num, round_num;

    cout << "Please enter number of players" << endl;   // take the player_num from the user
    cin >> player_num;
    while (player_num < 1) {
        cout << "Number of players must be at least 1. Please enter number of players again" << endl;
        cin >> player_num;
    }

    cout << "Please enter number of rounds" << endl;    // take the round_num from the user
    cin >> round_num;
    while (round_num < 1) {
        cout << "Number of rounds must be at least 1. Please enter number of rounds again" << endl;
        cin >> round_num;
    }

    cout << "Please enter the randomization range" << endl;   // take the randomization range
    cin >> min_bound >> max_bound;
    while (min_bound > max_bound) {
        cout << "Minimum bound must be less than or equal to maximum bound. Please enter the randomization range again" << endl;
        cin >> min_bound >> max_bound;
    }

    scores.resize(player_num);   // resize the scores vector to fit player_num

    thread_id.resize(player_num);   // resize the thread_id vector to fit player_num

    // take the current local time and set it to start 3 seconds later
    tm * local_time = getCurrentLocalTime();
    local_time -> tm_sec += 3;

    // create threads for each player
    thread player_thread[player_num];
    for (int i = 0; i < player_num; i++) {

        player_thread[i] = thread (&p_thread, local_time, i);
    }

    // initialize the finish boolean
    finish = false;

    // create the host thread
    thread host = thread (& host_thread, player_num, round_num);

    // join player threads
    for (int i = 0; i < player_num; i++) {

        if (player_thread[i].joinable()) {

            player_thread[i].join();
        }
    }

    // join the host thread
    if (host.joinable()) {

        host.join();
    }

    // print final leaderboard from 0 to player_num
    cout << endl << "Game is over!" << endl;
    cout << "Leaderboard:" << endl;

    for (int j = 0; j < player_num; ++j) {

        cout << "Player " << j << " has won " << scores[j] << " times" << endl;
    }

    return 0;
}
