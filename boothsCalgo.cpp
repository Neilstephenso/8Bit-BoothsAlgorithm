/*
Author Neil Stephenson
Date: 5/7/2025

Program: Booths Algorithm for 8 bit numbers
Class: Computer Architecture
*/

#include <iostream>
#include <bitset>
#include <cstdint>
#include <cstdio>
#include <sys/types.h>

using namespace std;

const int BITS = 8;

// two's complement function
bitset<BITS> twosComplement(bitset<BITS> b) {
    return bitset<BITS>((~b).to_ulong() + 1);
}

// Perform arithmetic right shift on A, Q, and Q-1
void arithmeticRightShift(bitset<BITS>& A, bitset<BITS>& Q, bool& Q_1) {
    bool MSB_A = A[BITS - 1];
    bool LSB_Q = Q[0];

    Q >>= 1;
    Q[BITS - 1] = A[0];

    A >>= 1;
    A[BITS - 1] = MSB_A;

    Q_1 = LSB_Q;
}

void boothsAlgorithm(bitset<BITS> M, bitset<BITS> Q) {
    bitset<BITS> A(0);
    bool Q_1 = 0;
    int count = BITS;

    cout << "Initial values:\n";
    cout << "A = " << A << " Q = " << Q << " Q-1 = " << Q_1 << " M = " << M << "\n\n";
    cout << "It\t" << "Step\t\t" << "A" << "\t\tQ" << "\t\tQ-1"<< "\n";
    while (count > 0) {
        string step = "";
        string offset = "\t";
        if (Q[0] == 1 && Q_1 == 0) {
            A = bitset<BITS>((A.to_ulong() - M.to_ulong()) & 0xFF); 
            step =  "A = A - M";
            offset = "";
        } else if (Q[0] == 0 && Q_1 == 1) {
            A = bitset<BITS>((A.to_ulong() + M.to_ulong()) & 0xFF); 
            step = "A = A + M";
            offset = "";
        }

        arithmeticRightShift(A, Q, Q_1);
        count--;
        
        cout << (8-count) << "\t" << step << offset << "\t" << A << "\t" << Q << "\t" << Q_1 << "\n";
    }

    // Combines A and Q for the results
    bitset<2 * BITS> result((A.to_ulong() << BITS) | Q.to_ulong());
    cout << "Final result (binary): " << result << "\n";

    // Converts to a signed integer
    int signed_result = static_cast<int16_t>(result.to_ulong());
    cout << "Final result (decimal): " << signed_result << "\n";
}

int main() {
    int m, q;

    cout << "Enter multiplicand (127 ~ -127)(M): ";
    cin >> m;
    cout << "Enter multiplier (127 ~ -127)(Q): ";
    cin >> q;

    if (m < -128 || m > 127 || q < -128 || q > 127) {
        cout << "Inputs must be 8-bit ints (-128 to 127).\n";
        return 1;
    }

    bitset<BITS> M(static_cast<uint8_t>(m));
    bitset<BITS> Q(static_cast<uint8_t>(q));

    boothsAlgorithm(M, Q);

    return 0;
}
