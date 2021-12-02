//
// Created by nisha on 11/9/2021.
//
#include <iostream>

#ifndef BRANCH_PREDICTOR_SAMP1_H
#define BRANCH_PREDICTOR_SAMP1_H
int counter =0;


class functions {

public:

    string xor_str(string astr, string bstr) {
        unsigned long a = strtoul(astr.c_str(), NULL, 16);  // Convert strings to longs
        unsigned long b = strtoul(bstr.c_str(), NULL, 16);

        stringstream sstream;
        sstream << setfill('0') << setw(16) << hex << (a ^ b);  // XOR numbers and
        string result = sstream.str();  // Save result          // convert to string
        sstream.clear();  // Clear buffer (will this happen anyway?)
        return result;
    }

    void smith(int m, const char *trace) {
        ifstream file(trace);
        string str;
        string actual = "";
        int smith = pow(2, m) / 2;
        int miss = 0;
        //float counter = 0;
        string predict;
        while (getline(file, str)) {
            counter++;
            actual = str.substr(7);

            if (smith < pow(2, m) / 2) {
                predict = "n";
            }
            if (smith >= pow(2, m) / 2) {
                predict = "t";
            }
            char t = actual[0];
            char y = predict[0];
            if (t == 'n' && y == 'n') {
                if (smith > 0) {
                    smith--;

                }
            } else if (t == 'n' && y == 't') {
                if (smith > 0)
                smith--;
                miss++;
            } else if (t == 't' && y == 'n') {
                if (smith < pow(2, m) - 1)
                smith++;
                miss++;
            } else if (t == 't' && y == 't') {
                if (smith < pow(2, m) - 1) {
                    smith++;
                }
            }
        }
        cout<<"COMMAND"<<endl;
        printf("./sim %d %s\n",m,trace);
        cout<<"OUTPUT"<<endl;
        float missrate = floor(((float(miss) / counter) * 100) * 100 + 0.5) / 100;
        cout << "number of predictions:\t\t" << counter << endl;
        cout << "number of mispredictions:\t" << miss << endl;
        cout << "misprediction rate:\t\t" << missrate << "%" << endl;
        cout << "FINAL COUNTER CONTENT:\t\t" << smith << endl;
    }

    //bimodalstart
    void bimodal(int m, const char *trace) {
        ifstream file(trace);
        int v = pow(2, m);
        int content[v];
        for (int i = 0; i < pow(2, m); i++) {
            content[i] = 4;
        }
        FILE *FP1;
        string str;
        string addr1;
        string actual = "";
        FP1 = fopen(trace, "r");
        char str1[2];
        char predict;
        float miss = 0;
        while (getline(file, str)) {
            counter++;
            actual = str.substr(7);
            string address = str.substr(0, 6);
            string bin_address = (hextobin(address));
            string tag = bin_address.substr(bin_address.size() - 2 - m, m);
            int decimal_address = bin_to_decimal(tag);
            if (content[decimal_address] < 4) {
                predict = 'n';
            }
            if (content[decimal_address] >= 4) {
                predict = 't';
            }
            char t = actual[0];
            if (t == 'n') {
                if (content[decimal_address] > 0) {
                    content[decimal_address]--;
                }
            } else {
                if (content[decimal_address] < pow(2, 3)-1) {
                    content[decimal_address]++;
                }
            }
            if (t != predict){
                miss++;
            }
        }
        printf("COMMAND");
        float missrate = floor(((miss / counter) * 100) * 100 + 0.5) / 100;
        printf("./sim %d %s\n",m,trace);
        cout<<"OUTPUT"<<endl;
        cout << "number of predictions:\t\t" << counter << endl;
        cout << "number of mispredictions:\t" << miss << endl;
        cout << "misprediction rate:\t\t" << missrate << "%" << endl;
        cout << "FINAL BIMODAL CONTENTS:\t\t" << endl;
        for (int i = 0; i < pow(2, m); i++) {
            cout << i << "\t" << content[i] << endl;
        }


    }
//bimodal end



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //hextobinstart

    string hextobin(string z) {
        int i = 0;
        string binary = "";
        while (z[i]) {
            switch (z[i]) {
                case '0' :
                    binary += "0000";
                    break;
                case '1' :
                    binary += "0001";
                    break;
                case '2' :
                    binary += "0010";
                    break;
                case '3' :
                    binary += "0011";
                    break;
                case '4' :
                    binary += "0100";
                    break;
                case '5' :
                    binary += "0101";
                    break;
                case '6' :
                    binary += "0110";
                    break;
                case '7' :
                    binary += "0111";
                    break;
                case '8' :
                    binary += "1000";
                    break;
                case '9' :
                    binary += "1001";
                    break;
                case 'a' :
                    binary += "1010";
                    break;
                case 'b' :
                    binary += "1011";
                    break;
                case 'c' :
                    binary += "1100";
                    break;
                case 'd' :
                    binary += "1101";
                    break;
                case 'e' :
                    binary += "1110";
                    break;
                case 'f' :
                    binary += "1111";
                    break;
                default :
                    binary += "\n Invalid Hexadecimal Digit... ";
            }
            i++;
        }
        return binary;
    }

    int bin_to_decimal(string tag) {
        int i = tag.length() - 1;
        int j = 0;
        int dec = 0;
        while (i >= 0) {
            if (tag[i] == '1') {
                dec += pow(2, j);
            }
            j++;
            i--;
        }
        return dec;
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////
    //gsharestart

    void gshare(int m, int n, const char *trace) {
        ifstream file(trace);
        FILE *FP1;
        int v = pow(2, m);
        int content[v];
        for (int i = 0; i < v; i++) {
            content[i] = 4;
        }
        string shift_reg = "";
        for (int i = 0; i < n; i++) {
            shift_reg += "0";
        }

        string str;
        string addr1;
        string actual = "";
        FP1 = fopen(trace, "r");
        char str1[2];
        char predict;
        float miss = 0;
        while (getline(file, str)) {
            counter++;
            actual = str.substr(7);
            string address = str.substr(0, 6);
            string bin_address = (hextobin(address));
           // cout << bin_address << endl;
            string tag = bin_address.substr(bin_address.size() - 2 - m, m);// lowermost m bits of given bin
            //cout << tag << endl;
            string updated_tag = tag.substr(0, m - n);//m-n bits
            //cout << updated_tag << endl;
            string car = tag.substr(tag.size() - n, n);//3
            //cout << car << endl;
            string xor_intermediate = xor_str(shift_reg, car);
            string xor_final = xor_intermediate.substr(xor_intermediate.size() - n, n);
           // cout << xor_final << endl;
            string m_index = updated_tag + xor_final;
            //cout << m_index << endl;


            int decimal_address = bin_to_decimal(m_index);

            if (content[decimal_address] < 4) {
                predict = 'n';
            }
            if (content[decimal_address] >= 4) {
                predict = 't';
            }

            char t = actual[0];
            if (t == 'n') {
                if (content[decimal_address] > 0) {
                    content[decimal_address]--;
                }
            } else {
                if (content[decimal_address] < pow(2, 3) - 1) {
                    content[decimal_address]++;
                }
            }
            if (t != predict) {
                miss++;
            }
            shift_reg = update(t, shift_reg);
        }

        float missrate = floor(((miss / counter) * 100) * 100 + 0.5) / 100;
        cout<<"COMMAND"<<endl;
        printf("./sim %d %d %s\n",m,n,trace);
        cout<<"OUTPUT"<<endl;
        cout << "number of predictions:\t\t" << counter << endl;
        cout << "number of mispredictions:\t" << miss << endl;
        cout << "misprediction rate:\t\t" << missrate << "%" << endl;
        cout << "FINAL GSHARE CONTENTS:\t\t" << endl;
        for (int i = 0; i < pow(2, m); i++) {
            cout << i << "\t" << content[i] << endl;
        }
    }

    string update(char t, string shift_reg) {
        if (t == 't') {
            shift_reg = "1" + shift_reg;
            shift_reg = shift_reg.substr(0, shift_reg.size() - 1);
        } else {
            shift_reg = "0" + shift_reg;
            shift_reg = shift_reg.substr(0, shift_reg.size() - 1);
        }
        return shift_reg;

    }
};
#endif //BRANCH_PREDICTOR_SAMP1_H
