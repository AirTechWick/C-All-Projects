//
// Created by erikr on 4/17/2021.
//
#include "binary_search_function.h"

double binary_search_function(
        const std::function<double(double)>& f,  // function to binary search
        double value,  // value we are searching for
        double max_err,  // maximum allowed error of value being passed to f
        double lower_bound,
        double upper_bound)
        {
            double actual_error = max_err;
            double approx_num = value;

            while (actual_error >= max_err)
            {

                if (lower_bound == upper_bound)    // Item not found
                {
                    return upper_bound;
                }

                const double middle = lower_bound + ((upper_bound-lower_bound) / 2); // or the number that if squared is the square root of value
                double squared_value = f(middle);

                if(squared_value == value)
                {
                    return middle; // Item found
                }
                else if (value < squared_value)
                {
                    upper_bound = middle;
                    actual_error = distance(value, squared_value);
                    approx_num = upper_bound;
                }
                else if (value > squared_value)
                {
                    lower_bound = middle;
                    actual_error = distance(value, squared_value);
                    approx_num = lower_bound;
                }
            }
            return approx_num;
        }

double distance(double first, double second)
{
    double distance = 0;
    first > second ? distance = first - second : distance = second - first;
    return distance;
}
