/*!
 * \file    calculator.c
 * \author  Remi BERTHO
 * \date    18/02/15
 * \version 4.2.0
 */

/*
 * calculator.c
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

#include "calculator.h"

/*!
 * \fn calculatorNodeList *newCalculatorNodeList(bool is_number, double number, char operator, calculatorNodeList *previous_node, calculatorNodeList *next_node)
 *  Allocate memory for the data element and initialize the structure members.
 * \param[in] is_number the new is_number element
 * \param[in] number the new number element
 * \param[in] operator the new operator element
 * \param[in] previous_node the new previous_node element
 * \param[in] next_node the new next_node element
 * \return calculatorNodeList* the address of the new data element
 */
calculatorNodeList *newCalculatorNodeList(bool is_number, double number, char operator, calculatorNodeList *previous_node, calculatorNodeList *next_node)
{
	calculatorNodeList *new=(calculatorNodeList*)malloc(sizeof(calculatorNodeList));

	if(new == NULL)
		return NULL;

	new->is_number = is_number;
	new->number = number;
	new->operator = operator;
	new->next=next_node;
	new->previous = previous_node;

	return new;
}


/*!
 * \fn void deleteCalculatorNodeList(calculatorNodeList *node)
 *  Free a node
 * \param[out] node, the node to be freed
 */
void deleteCalculatorNodeList(calculatorNodeList *node)
{
	free(node);
}

/*!
 * \fn void calculatorListInit(calculatorList *list)
 *  Initialize the list structure members to be consistent with an empty list.
 * \param[out] list the list to be initialized
 */
void calculatorListInit(calculatorList *list)
{
	list->first = list->last = list->current = NULL;
}

/*!
 * \fn bool calculatorListEmpty(calculatorList *list)
 * Tests if it is an empty list.
 * \param[in] list the list to be tested
 * \return true if empty, false otherwise
 */
bool calculatorListEmpty(calculatorList *list)
{
	return list->first == NULL;
}

/*!
 * \fn bool calculatorListFirst(calculatorList *list)
 *  Tests if the current node is the first one.
 * \param[in] list the list to be tested
 * \return true if the current node is the first one, false otherwise
 */
bool calculatorListFirst(calculatorList *list)
{
	return list->first == list->current;
}

/*!
 * \fn bool calculatorListLast(calculatorList *list)
 *  Tests if the current node is the last one.
 * \param[in] list the list to be tested
 * \return true if the current node is the last one, false otherwise
 */
bool calculatorListLast(calculatorList *list)
{
	return list->last == list->current;
}


/*!
 * \fn bool calculatorListOne(calculatorList *list)
 *  Tests if there is only one element in the list
 * \param[in] list the list to be tested
 * \return true if there is only one element in the list, false otherwise
 */
bool calculatorListOne(calculatorList *list)
{
    return list->last == list->first;
}

/*!
 * \fn calculatorListOutOfList(calculatorList *list)
 * Tests if the current node is not valid (ie NULL).
 * \param[in] list the list to be tested
 * \return true if the current node is not valid, false otherwise
 */
bool calculatorListOutOfList(calculatorList *list)
{
	return list->current == NULL;
}

/*!
 * \fn void calculatorListSetOnFirst(calculatorList *list)
 *  Set the current node on the first one.
 * \param[in] list the list to be modified
 */
void calculatorListSetOnFirst(calculatorList *list)
{
	list->current = list->first;
}

/*!
 * \fn void calculatorListSetOnLast(calculatorList *list)
 *  Set the current node on the last one.
 * \param[in] list the list to be modified
 */
void calculatorListSetOnLast(calculatorList *list)
{
	list->current = list->last;
}

/*!
 * \fn void calculatorListNext(calculatorList *list)
 *  Set the current node on the next one.
 * \param[in] list the list to be modified
 */
void calculatorListNext(calculatorList *list)
{
	list->current = list->current->next;
}


/*!
 * \fn void calculatorListPrevious(calculatorList *list)
 *  Set the current node on the previous one.
 * \param[in] list the list to be modified
 */
void calculatorListPrevious(calculatorList *list)
{
	list->current = list->current->previous;
}

/*!
 * \fn double calculatorListGetCurrentNumber(calculatorList *list)
 *  Return the number value stored in the current element.
 * \param[in] list the list
 * \return the number of the current element
 */
double calculatorListGetCurrentNumber(calculatorList *list)
{
	return list->current->number;
}


/*!
 * \fn char calculatorListGetCurrentOperator(calculatorList *list)
 *  Return the operator value stored in the current element.
 * \param[in] list the list
 * \return the operator of the current element
 */
char calculatorListGetCurrentOperator(calculatorList *list)
{
	return list->current->operator;
}


/*!
 * \fn bool calculatorListIsCurrentNumber(calculatorList *list)
 *  Return the ir_number value stored in the current element.
 * \param[in] list the list
 * \return the is_number of the current element
 */
bool calculatorListIsCurrentNumber(calculatorList *list)
{
    return list->current->is_number;
}

/*!
 * \fn void calculatorListDelete(calculatorList *list)
 *  Delete all the nodes of the list
 * \param[in] list the list
 */
void calculatorListDelete(calculatorList *list)
{
	calculatorListSetOnFirst(list);
	while(!calculatorListOutOfList(list))
	{
		calculatorListDeleteCurrent(list);
	}
	calculatorListSetOnFirst(list);
}

/*!
 * \fn void calculatorListPrint(calculatorList *list)
 *  Print the content of the list.
 * \param[in] list the list to be displayed
 */
void calculatorListPrint(calculatorList *list)
{
	printf("Calculator list :\n");
	calculatorListSetOnFirst(list);
	while(!calculatorListOutOfList(list))
	{
	    if (list->current->is_number)
            printf("%f",list->current->number);
        else
            printf("%c",list->current->operator);
		calculatorListNext(list);
	}
	printf("\n");
	calculatorListSetOnFirst(list);
}


/*!
 * \fn bool calculatorListInsertAfterCurrent(calculatorList *list, bool is_number, double number, char operator)
 *  Insert a node after the current one
 * \param[in] is_number the new is_number element
 * \param[in] number the new number element
 * \param[in] operator the new operator element
 * \param[in] list the list
 * \return true if everything is OK, false otherwise
 */
bool calculatorListInsertAfterCurrent(calculatorList *list, bool is_number, double number, char operator)
{
    if (calculatorListEmpty(list))
    {
        list->last = list->current = list->first=newCalculatorNodeList(is_number,number,operator,NULL,NULL);
        return true;
    }

    if (calculatorListOutOfList(list))
    {
        printf(_("\nCannot insert a node after a NULL node.\n"));
        return false;
    }

    calculatorNodeList *new = newCalculatorNodeList(is_number,number,operator,list->current,list->current->next);
    if (!calculatorListLast(list))
        list->current->next->previous = new;
    list->current->next = new;

    if (calculatorListLast(list))
        list->last = new;

    return true;
}


/*!
 * \fn bool calculatorListInsertBeforeCurrent(calculatorList *list, bool is_number, double number, char operator)
 *  Insert a node before the current one
 * \param[in] is_number the new is_number element
 * \param[in] number the new number element
 * \param[in] operator the new operator element
 * \param[in] list the list
 * \return true if everything is OK, false otherwise
 */
bool calculatorListInsertBeforeCurrent(calculatorList *list, bool is_number, double number, char operator)
{
    if (calculatorListEmpty(list))
    {
        list->last = list->current = list->first=newCalculatorNodeList(is_number,number,operator,NULL,NULL);
        return true;
    }

    if (calculatorListOutOfList(list))
    {
        printf(_("\nCannot insert a node after a NULL node.\n"));
        return false;
    }

    calculatorNodeList *new = newCalculatorNodeList(is_number,number,operator,list->current->previous,list->current);
    if (!calculatorListFirst(list))
        list->current->previous->next = new;
    list->current->previous = new;

    if (calculatorListFirst(list))
        list->first = new;

    return true;
}


/*!
 * \fn bool calculatorListInsertLast(calculatorList *list, bool is_number, double number, char operator)
 *  Insert a node in the last position of the list
 * \param[in] is_number the new is_number element
 * \param[in] number the new number element
 * \param[in] operator the new operator element
 * \param[in] list the list
 * \return true if everything is OK, false otherwise
 */
bool calculatorListInsertLast(calculatorList *list, bool is_number, double number, char operator)
{
    if (calculatorListEmpty(list))
    {
        list->last = list->current = list->first=newCalculatorNodeList(is_number,number,operator,NULL,NULL);
        return true;
    }

    if (calculatorListOutOfList(list))
    {
        printf(_("\nCannot insert a node after a NULL node.\n"));
        return false;
    }

    calculatorNodeList *new = newCalculatorNodeList(is_number,number,operator,list->last,NULL);
    list->last->next = new;
    list->last = new;

    return true;
}


/*!
 * \fn bool calculatorListDeleteCurrent(calculatorList *list)
 *  Delete the current node to the list a set the current to the next or to the previous if the current was the last
 * \param[in] list the list
 * \return true if everything is OK, false otherwise
 */
bool calculatorListDeleteCurrent(calculatorList *list)
{
    if (calculatorListEmpty(list))
    {
        printf(_("\nCannot delete the current node : the node is NULL.\n"));
        return false;
    }

    if (calculatorListOne(list))
    {
        deleteCalculatorNodeList(list->current);
        calculatorListInit(list);
        return true;
    }

    if (calculatorListFirst(list))
    {
        list->first = list->first->next;
        deleteCalculatorNodeList(list->first->previous);
        list->first->previous = NULL;
        list->current = list->first;
        return true;
    }

    if (calculatorListLast(list))
    {
        list->last = list->last->previous;
        deleteCalculatorNodeList(list->last->next);
        list->last->next = NULL;
        list->current = list->last;
        return true;
    }

    calculatorNodeList *tmp = list->current;
    list->current->previous->next = list->current->next;
    list->current->next->previous = list->current->previous;
    list->current = list->current->next;
    deleteCalculatorNodeList(tmp);

    return true;
}


/*!
 * \fn bool calculatorListInsertLastFromString(char *string,calculatorList *list)
 *  Convert the string into the list
 * \param[in] list the list
 * \param[in] string the string which contain all the element of the list (a mathematical expression)
 * \return true if everything is OK, false otherwise
 */
bool calculatorListInsertLastFromString(char *string,calculatorList *list)
{
    double tmp_nb;
    char tmp_char;
    int next;
    char *tmp_string=string;

    if (sscanf(string,"%lf",&tmp_nb) <= 0)
        return false;
    calculatorListInsertLast(list,true,tmp_nb,0);


    while ((next = calculatorSearchNextOperatorString(tmp_string)) > 0)
    {
        tmp_string += next;
        sscanf(tmp_string,"%c",&tmp_char);
        calculatorListInsertLast(list,false,0,tmp_char);
        tmp_string += 1;
        if (sscanf(tmp_string,"%lf",&tmp_nb) <= 0)
            return false;
        calculatorListInsertLast(list,true,tmp_nb,0);
    }

    if (next == 0)
        return true;
    else
        return false;
}


/*!
 * \fn unsigned int calculatorSearchNextOperatorString(char *string)
 *  Search the next occurrence of an operator in a string
 * \param[in] string the string which contain all the element of the list (a mathematical expression)
 * \return the position of the next operator, 0 if there is no
 */
int calculatorSearchNextOperatorString(char *string)
{
    unsigned int i;
    for (i=1 ; i<strlen(string) ; i++)
    {
        if((string[i] == '+' ||
            string[i] == '-' ||
            string[i] == '*' ||
            string[i] == '^' ||
            string[i] == '/') && string[i-1] !='e')
            return i;
        else
        {
            if (string[i] != '0' &&
                string[i] != '1' &&
                string[i] != '2' &&
                string[i] != '3' &&
                string[i] != '4' &&
                string[i] != '5' &&
                string[i] != '6' &&
                string[i] != '7' &&
                string[i] != '8' &&
                string[i] != '9' &&
                string[i] != '.' &&
                string[i] != ',' &&
                string[i] != 'e')
                return -1;
        }

    }
    return 0;
}

/*!
 * \fn bool calculatorListDeleteCurrent(calculatorList *list)
 *  Calculate an expression with one of the two operator
 *  Scann all the list and if an operator is detected calculate the result and replace the expression to the result
 * \param[in] list the list
 * \return true if everything is OK, false if there is no expression to evaluate
 */
bool calculatorListCalculate(calculatorList *list, char operator1, char operator2)
{
    double res;
    double op1;
    double op2;
    char operator;

    calculatorListSetOnFirst(list);
    while (!calculatorListOutOfList(list))
    {
        if (operator1 == list->current->operator || operator2 == list->current->operator)
        {
            op1 = list->current->previous->number;
            op2 = list->current->next->number;
            if (operator1 == list->current->operator)
                operator = operator1;
            else
                operator = operator2;
            switch (operator)
            {
            case '+':
                res = op1 + op2;
                break;
            case '-':
                res = op1 - op2;
                break;
            case '*':
                res = op1 * op2;
                break;
            case '/':
                res = op1 / op2;
                break;
            case '^':
                res = pow(op1,op2);
                break;
            default:
                res = 0;
            }
            calculatorListPrevious(list);
            calculatorListDeleteCurrent(list);
            calculatorListDeleteCurrent(list);
            calculatorListDeleteCurrent(list);
            if (calculatorListLast(list))
                calculatorListInsertAfterCurrent(list,true,res,0);
            else
                calculatorListInsertBeforeCurrent(list,true,res,0);
            return true;
        }
        else
            calculatorListNext(list);
    }
    return false;
}

/*!
 * \fn double calculateFromString(char *string)
 *  Calculate the result of an expression passed in parameter
 * \param[in] string the string which contain all the element of the list (a mathematical expression)
 * \return the result, Nan if the expression is incorrect
 */
double calculateFromString(char *string)
{
    double res;
    calculatorList list;
    calculatorList *ptr_list = &list;
    calculatorListInit(ptr_list);

    if(!calculatorListInsertLastFromString(string,ptr_list))
    {
        printf(_("\nErreur when converting the string into the list.\n"));
        calculatorListDelete(ptr_list);
        return nan("");
    }

    while (calculatorListCalculate(ptr_list,'^',-1));
    while (calculatorListCalculate(ptr_list,'*','/'));
    while (calculatorListCalculate(ptr_list,'+','-'));

    res = ptr_list->first->number;
    calculatorListDelete(ptr_list);
    return res;
}
