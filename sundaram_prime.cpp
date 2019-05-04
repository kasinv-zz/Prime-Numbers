#include <iostream>
#include <iomanip>
#include <set>
#include <algorithm>
#include <string>
#include <chrono>

using namespace std;


/* find all the prime numbers within a range of integers 

** the algorithm was proposed by sundaram
** collect all the integers within the range (N)
** remove all integers that are (i+j+2ij), where 1<j<i and i+j+2ij < N
** the remaining numbers are the odd primes (2 is the even prime)

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

    unsigned int pl = stoi(p);							// get the upper limit
    const unsigned int len = p.length()+2;

    p = argv[2];										// get step size
    unsigned int step =stoi(p);

    string pr = "";										// p = print, d = duration (optional)
    if (argc >= 4){
        pr = argv[3];
    }


    // set up headers for printing
    if ((pr == "d" || pr == "D") || (pr == "p" || pr == "P")) {
        cout << "N\tElapsed Dur (ms)" << endl;
    }

    for (unsigned int t=step; t <= pl; t=t+step ) {
        unsigned int pmax = t;							// pmax is the max for each iteration
        set<unsigned int> v;

        for (unsigned int i=0; i<pmax; i++){
            if ( (i+1) > pmax)
                break;
            else
                v.insert( (i+1) );						    // load up with integers from 0 up to pmax
        }

        auto start = std::chrono::steady_clock::now();

        for (unsigned int i=1; i<=pmax; i++){
            for (unsigned int j=1; j<=i; j++){
                unsigned int x = i + j + (2*i*j);
                if (x > pmax)
                    break;
                if (v.count(x)>0 && x <= pmax)
                    v.erase(x);
                else{

                }
            }
        }

        auto finish= std::chrono::steady_clock::now();

        set<unsigned int> v2;
        if (pmax >= 2)
            v2.insert(2);
        for (const unsigned int &s: v){
            if (s*2 + 1 > pmax )
                break;
            else
                v2.insert(s*2 + 1);
        }

        if (pr == "t" || pr == "T")
    		cout << "# of Primes between: 0 and " << pmax << " = " << v2.size() << endl;

        // print out run time duration
        if (pr == "d" || pr == "D"){
            cout << pmax << "\t" << chrono::duration_cast<chrono::milliseconds> (finish - start).count() << endl;
        }

        // print out prime numbers
        if (pr == "p" || pr == "P"){
	        cout << pmax << "\t" << chrono::duration_cast<chrono::milliseconds> (finish - start).count() << endl;

            int c = 0;
            for (set<unsigned int>::iterator it=v2.begin(); it!=v2.end(); it++){
                cout << setw(len) << *it << " ";
                if ((c+1)%10 == 0)
                    cout << endl;
                c++;
            }
            cout << endl;
        }

    }

    return 0;
}