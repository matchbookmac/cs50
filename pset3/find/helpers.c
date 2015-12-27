/*
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"
#include <stdio.h>

bool binary(int value, int values[], int min, int max);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Searches values[] array for a value using binary search 
    int min = 0;
    int max = n;
    if (binary(value, values, min, max))
    {
        return true;
    }
    return false;
}

// Implements a recursive binary search to find the value
bool binary(int value, int values[], int min, int max)
{
    // Is the search over, or is there still more to go?
    while (max > 0 && min <= max)
    {
        int midp = min + ((max - min) / 2);
        int mid = values[midp];
        if (value == mid)
        {
            return true;
        }
        else
        {
            // Recursively calls the binary search function
            if (value > mid)
            {
                if (binary(value, values, midp + 1, max))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if (binary(value, values, min, midp - 1))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return false;
}
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Uses bubble sort to sort the array

    bool swaped; 
    do
    {
        swaped = false;

        for (int i = 0; i < n; i++)
        {
            int elmt = values[i];
            if (elmt > values[i + 1])
            {
                values[i] = values[i + 1];
                values[i + 1] = elmt;
                swaped = true;
            }
        }
    } while(swaped == true);
    return;
}
