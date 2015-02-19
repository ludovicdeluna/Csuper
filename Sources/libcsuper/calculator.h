/*!
 * \file    calculator.h
 * \author  Remi BERTHO
 * \date    18/02/15
 * \version 4.2.0
 */

/*
 * calculator.h
 *
 * Copyright 2014-2015 dalan <remi.bertho@gmail.com>
 *
 * Csuper is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Csuper is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
*/

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "share.h"


/*! \struct calculatorNodeList
* \brief Data element of a calculatorList, a number or an operator
*/
typedef struct calculatorNodeList{
    bool is_number;                     /*!< Defined if this is a number or not*/
    double number;                      /*!< The number value*/
    char operator;                      /*!< The operator*/
    struct calculatorNodeList *next;    /*!< A pointer to the next element in the calculatorList*/
    struct calculatorNodeList *previous;/*!< A pointer to the previous element in the calculatorList*/
}calculatorNodeList;



/*! \struct calculatorList
* \brief calculatorList of tree nodes
*/
typedef struct{
	 calculatorNodeList *first;     /*!< A pointer to the first calculatorList element*/
	 calculatorNodeList *current;   /*!< A pointer to the current calculatorList element*/
	 calculatorNodeList *last;      /*!< A pointer to the last calculatorList element*/
}calculatorList;

calculatorNodeList * newCalculatorNodeList(bool is_number, double number, char operator, calculatorNodeList *previous_node, calculatorNodeList *next_node);
void deleteCalculatorNodeList(calculatorNodeList *node);

void calculatorListInit(calculatorList *list);
void calculatorListDelete(calculatorList *list);

bool calculatorListEmpty(calculatorList *list);
bool calculatorListOne(calculatorList *list);
bool calculatorListLirst(calculatorList *list);
bool calculatorListLast(calculatorList *list);
bool calculatorListOutOfList(calculatorList *list);

void calculatorListSetOnFirst(calculatorList *list);
void calculatorListSetOnLast(calculatorList *list);
void calculatorListNext(calculatorList *list);
void calculatorListPrevious(calculatorList *list);
double calculatorListGetCurrentNumber(calculatorList *list);
char calculatorListGetCurrentOperator(calculatorList *list);
bool calculatorListIsCurrentNumber(calculatorList *list);

void calculatorListPrint(calculatorList *list);

bool calculatorListInsertAfterCurrent(calculatorList *list, bool is_number, double number, char operator);
bool calculatorListInsertBeforeCurrent(calculatorList *list, bool is_number, double number, char operator);
bool calculatorListInsertLast(calculatorList *list, bool is_number, double number, char operator);
bool calculatorListInsertLastFromString(char *string,calculatorList *list);

bool calculatorListDeleteCurrent(calculatorList *list);

bool calculatorListCalculate(calculatorList *list, char operator1, char operator2);

int calculatorSearchNextOperatorString(char *string);
double calculateFromString(char *string);

#endif // CALCULATOR
