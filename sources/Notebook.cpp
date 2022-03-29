#include <iostream>
#include <string>

#include "Notebook.hpp"

using namespace std;

ariel::Notebook::Notebook() {}

void arg_check(int page, int row, int column, int length, ariel::Direction dir){
    if (dir == ariel::Direction::Horizontal) {
        if ((length + column - 1) >= ariel::MAX_ROW_LEN || column < ariel::MIN_ROW_LEN || page < ariel::MIN_ROW_LEN ||
            row < ariel::MIN_ROW_LEN || length < ariel::MIN_ROW_LEN) {
            throw invalid_argument(
                    "page, row, column and length can't be negative numbers also column+strlen cant be above 100");
        }
    }
    else{
        if (column + 1 > ariel::MAX_ROW_LEN || column < ariel::MIN_ROW_LEN || page < ariel::MIN_ROW_LEN ||
            row < ariel::MIN_ROW_LEN || length < ariel::MIN_ROW_LEN) {
            throw invalid_argument(
                    "page, row, column and length can't be negative numbers also column cant be above 100");
        }
    }
}

void ariel::Notebook::write(int page, int row, int column, Direction dir, const string &str) {
    arg_check(page, row, column, str.length(), dir);
    const char *temp = str.c_str();
    if (dir == Direction::Horizontal) {
        for (int  i = column, j = 0; j < str.length(); ++i, ++j) {// horizontal
            if ((nb[page][row].count(i) == 0 || nb[page][row][i] == '_') && isprint(temp[j]) != 0 && temp[j] != '~' ) {
                nb[page][row][i] = temp[j];
            }
            else {
                throw invalid_argument("can't write on erased places, not printable chars and cant override other chars");
            }
        }
    } else {
        for (int  i = row, j = 0; j < str.length(); ++i, ++j) { // vertical
            if ((nb[page][i].count(column) == 0 || nb[page][i][column] == '_') && isprint(temp[j]) != 0&& temp[j] != '~') {
                nb[page][i][column] = temp[j];
            }
            else {
                throw invalid_argument("can't write on erased places, not printable chars and cant override other chars");
            }
        }
    }
}


string ariel::Notebook::read(int page, int row, int column, Direction dir, int length) {
    arg_check(page, row, column, length, dir);
    string ans;
    if (dir == Direction::Horizontal) {
        for (int i = column; i < column + length; ++i) {// horizontal
            if (nb[page][row].count(i) == 0) {
                ans += '_';
            }
            else {
                ans += nb[page][row][i];
            }
        }
    } else {
        for (int i = row; i < row + length; ++i) {
            if ((nb[page][i]).count(column) == 0) {
                ans += '_';
            }
            else {
                ans += nb[page][i][column];
            }
        }
    }
    return ans;
}

void ariel::Notebook::erase(int page, int row, int column, Direction dir, int length) {
    arg_check(page, row, column, length, dir);
    if (dir == Direction::Horizontal) {
        for (int i = column; i < column + length; ++i) {
            nb[page][row][i] = '~';
        }
    } else {
        for(int i = row; i < row + length; ++i) {
            nb[page][i][column] = '~';
        }
    }
}

void ariel::Notebook::show(int page) {
    if (page < 0){
        throw invalid_argument("page cant be negative");
    }
    int last_row = -1;
    for (const auto &row : nb[page]){
        if (last_row + 1!= row.first){
            for (int i = last_row + 1; i < row.first; ++i){
                cout << row.first << ") " << read(page, i, 0, Direction::Horizontal, MAX_ROW_LEN - 1);
            }
        }
        cout << row.first << ") " << read(page, row.first, 0, Direction::Horizontal, MAX_ROW_LEN - 1);
        last_row = row.first;
    }
}