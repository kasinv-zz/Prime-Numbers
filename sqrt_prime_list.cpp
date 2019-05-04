#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <string>
#include <cmath>
#include <chrono>

using namespace std;


/* find all the prime numbers within a range of integers 

** the algorithm is a different approach than the typical 
** Eratosthenes or Austin sieve
** looks like this is faster, approaching O(N)... maybe O(N.Sqrt(N) )

** below is the list of the first 100 prime numbers (for qa/testing)
** For more information on primes see http://primes.utm.edu/

      2      3      5      7     11     13     17     19     23     29
     31     37     41     43     47     53     59     61     67     71
     73     79     83     89     97    101    103    107    109    113
    127    131    137    139    149    151    157    163    167    173
    179    181    191    193    197    199    211    223    227    229
    233    239    241    251    257    263    269    271    277    281
    283    293    307    311    313    317    331    337    347    349
    353    359    367    373    379    383    389    397    401    409
    419    421    431    433    439    443    449    457    461    463
    467    479    487    491    499    503    509    521    523    541
*/


bool IsPrime(const unsigned int &num){
    if (num == 2)
        return true;

    if(num % 2 == 0 || num == 1)
        return false;

    unsigned int square_root = sqrt(num);
    for(unsigned long int i = 3;i <= square_root;i += 2){
        if(num % i == 0)
            return false;
    }
    return true;
}

int main(int argc, char* argv[])
{

    // argument handling
    if(argc < 3) {
        std::cerr << "Not enough arguments." << std::endl;
        std::cerr << "Usage: " << argv[0] << " N Step <optional Print> " << std::endl;
    return 1;
    }
    string p = argv[1];

    unsigned int pl = stoi(p);                          // get the upper limit
    const unsigned int len = p.length()+2;

    p = argv[2];                                        // get step size
    unsigned int step =stoi(p);

    string pr = "";                                     // p = print, d = duration (optional)
    if (argc >= 4){
        pr = argv[3];
    }


    // set up headers for printing
    if ((pr == "d" || pr == "D") || (pr == "p" || pr == "P")) {
        cout << "N\tElapsed Dur (ms)" << endl;
    }

    for (unsigned int t=step; t <= pl; t=t+step ) {
        unsigned int pmax = t;                          // pmax is the max for each iteration
        list<unsigned int> v;

        auto start= std::chrono::steady_clock::now();

        for (unsigned int i=2; i<pmax; i++)             // Check function IsPrime for logic
            if (IsPrime(i)) v.push_back(i);               // that i is a prime number

        auto finish= std::chrono::steady_clock::now();

        if (pr == "t" || pr == "T")
            cout << "# of Primes between: 0 and " << pmax << " = " << v.size() << endl;

        // print out run time duration
        if (pr == "d" || pr == "D"){
            cout << pmax << "\t" << chrono::duration_cast<chrono::milliseconds> (finish - start).count() << endl;
        }

        // print out prime numbers
        if (pr == "p" || pr == "P"){
            v.sort();
            cout << pmax << "\t" << chrono::duration_cast<chrono::milliseconds> (finish - start).count() << endl;
            list<unsigned int>::iterator it=v.begin();
            unsigned int i = 0;
            for (; it!=v.end(); it++){
                cout << setw(len) << *it << " ";
                if ((i+1)%10 == 0)
                    cout << endl;
                i++;
            }
            cout << endl;
        }

    }

    return 0;
}