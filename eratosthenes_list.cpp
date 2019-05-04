#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <string>
#include <chrono>

using namespace std;


/* find all the prime numbers within a range of integers 

** the algorithm is an ancient method proposed by Eratosthenes
** collect all the integers within the range
** starting with the first F, scratch off numbers that are divisible by F
** take the next, and repeat scratching off 
** with each scratch off, the, collection gets reduced
** at the end, the remaining numbers are the prime numbers
** seems to be O(N^2) -> could it be O(N.LogN)?

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

        for (unsigned int i=0; i<pmax; i++){
            if ( (i+2) > pmax)
                break;
            else
                v.push_back(i+2);                           // load up with integers from 0 up to pmax
        }

        auto start = std::chrono::steady_clock::now();


        list<unsigned int>::iterator it=v.begin();
        while (it !=v.end() && *it <= pmax) {                                         // scan through the list

            list<unsigned int>::iterator jt=next(it,1);

            while (jt !=v.end()){                                    // start from back, scratch off #s divisible by v[i]
                if (*jt % *it == 0){
                    list<unsigned int>::iterator temp=next(jt,1);
                    v.erase(jt);
                    jt = temp;
                }
                else
                    jt++;
            }
            it++;
        }

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