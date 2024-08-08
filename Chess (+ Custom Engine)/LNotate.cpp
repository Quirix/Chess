//
//  LNotate.cpp
//  Chess (+ Custom Engine)
//
//  Created by Quirix Wastaken on 6/8/24.
//

#include "LNotate.hpp"

#include <iostream>

LNotate::LNotate(AddNoT sp, int intForm, int f, int t)
: special{sp}, inf(intForm), From(f), To(t) {}

void LNotate::print() {
    std::cout << "special: " << (int) special << " int form: " << inf << " from: " << From << " to: " << To << " \n";
}

std::array<int, 4> LNotate::sprint() {
    return std::array<int, 4>{(int)special, inf, From, To};
}

bool LNotate::operator==(const LNotate& cl) {
    return (special == cl.special) && (inf == cl.inf) && (From == cl.From) && (To == cl.To);
}

void LNotate::onCreate(int i)
{
    To = i;
    From = i;
}
