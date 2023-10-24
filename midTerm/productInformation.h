//
// Created by riverisrain on 10/18/22.
//

#ifndef MIDDLETEST_PRODUCTINFORMATION_H
#define MIDDLETEST_PRODUCTINFORMATION_H

#endif //MIDDLETEST_PRODUCTINFORMATION_H
#define START_ID 1


typedef struct information{
    int id;
    char name[50];
    char productType[50];
    int expirationDate;
    int stock;
};

enum name{SpecialTea,Espresso,CafeLatte,IcedAmericano,IceTea,JavaTea};
enum productType{tea,coffee};