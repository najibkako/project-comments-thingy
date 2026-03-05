#pragma once
// makes sure this header file is only included once

#include <string>
// allows us to use std::string


std::string drunkify(const std::string& text);
// takes normal text and replaces letters with symbols based on drunkenness

void drunkPrint(const std::string& text);
// prints the drunkified version of the text

void updateLuckFromDrunkenness();
// updates luck based on drunkenness level
