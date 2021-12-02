#include <iostream>
#include<math.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <sstream>
#include <bitset>
#include <string>
#define _OPEN_SYS_ITOA_EXT
using namespace std;
#include "samp1.h"
functions c;
int main (int argc, char* argv[]) {

   string branch_type=argv[1];
    if(argc==4)
    {
        if(branch_type=="smith")
        {
            c.smith(stoi(argv[2]),argv[3]);
        }
        else if(branch_type=="bimodal")
        {
            c.bimodal(stoi(argv[2]),argv[3]);
        }
        else
        {
            cout<<"invalid data"<<endl;
        }


    }
    if(branch_type=="gshare" && argc==5)
    {
        c.gshare(stoi(argv[2]),stoi(argv[3]),argv[4]);
    }

    else{
        cout<<"invalid arguments passed"<<endl;
    }



    return 0;
}


