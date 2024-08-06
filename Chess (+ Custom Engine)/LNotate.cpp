//
//  LNotate.cpp
//  Chess (+ Custom Engine)
//
//  Created by Quirix Wastaken on 6/8/24.
//

#include "LNotate.hpp"

#include <iostream>

LNotate::LNotate(int specialAndIntForm, int f, int t)
: spNInf(specialAndIntForm), From(f), To(t) {}

void LNotate::print() {
    std::cout << "special + intform: \"" << spNInf << "\" from: \"" << From << "\" to: \"" << To << "\" \n"; 
}

std::array<int, 3> LNotate::sprint() {
    return std::array<int, 3>{spNInf, From, To};
}

bool LNotate::operator==(const LNotate& cl) {
    return (spNInf == cl.spNInf) && (From == cl.From) && (To == cl.To);
}
