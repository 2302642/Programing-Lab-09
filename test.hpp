/*!***********************************************************************************************************************************************************************************************************************************************
\file       test.hpp
\par        Author:          Najih
\par        Email:           n.hajasheikallaudin
\par        Course:          RSE1202
\par        Section:         RSE
\par        Tutorial:        Lab 9
\par        File created on: 22/03/2024
\brief      class with template functions for spell checking

\par        File information:
            This file contains 
            - 3 classes
                - division_by_zero
                - invalid_input
                - stream_wrapper
            - 5 test functions
*************************************************************************************************************************************************************************************************************************************************/

#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <sstream>
#include <string>

namespace hlp2 {
//################################################################################################################################################################################################################################################
//================================================================================================================================================================================================================================================
//|                                                                                     CLASSES                                                                                                                                                  |
//================================================================================================================================================================================================================================================
    class division_by_zero : public std::exception {                                                                                                // Exception class for division by zero
        public:
            division_by_zero(int numerator) {                                                                                                       // constructer for throwing exception
                std::stringstream ss;
                ss << "Division by zero: " << numerator << " / 0!" << std::endl;                                                                    // preparing the error message
                error_message = ss.str();                                                                                                           // storing the error message
            }
            const char *what() const noexcept override { return error_message.c_str(); }                                                            // overriding what() method to provide error message

        private: std::string error_message;                                                                                                         // storing the error message  
    };
//************************************************************************************************************************************************************************************************************************************************   
    class invalid_input : public std::exception { public: const char* what() const noexcept override { return "Invalid input!"; }  };               // overriding what() method to provide error message
//************************************************************************************************************************************************************************************************************************************************
    class stream_wrapper {                                                                                                                          // Wrapper class for std::cin
        private: std::istream& stream;                                                                                                              // reference to std::cin                                          
        public:
            explicit stream_wrapper(std::istream& s) : stream(s) {}                                                                                 // constructor for inputdata
            template<typename T> stream_wrapper& operator>>(T& value) {                                                                             // overloading operator >> for reading integer values                     
                if (!(stream >> value)) { throw invalid_input{}; }                                                                                  // throwing exception for invalid input
                return *this;
            }
    };
//================================================================================================================================================================================================================================================
//|                                                                                     TEST FUNCTIONS                                                                                                                                           |
//================================================================================================================================================================================================================================================
    template<typename DivideFunc> void test1(int numerator, int denominator, DivideFunc divide_func) {                                                      // Function template to test divide1
        int value = 0;                                                                                                                                      // Initializing value to store the result of the division
        bool div_val = divide_func(numerator, denominator, value);                                                                                          // calling the divide function with the specified numerator, denominator, and value 
        if (div_val) { std::cout << "Calling function #1; result: " << value << "." << std::endl; }                                                         // checking if the division was successful and printing the result
        else { std::cout << "Calling function #1.\n"; throw division_by_zero(numerator); }                                                                  // else printing a message and throw a division_by_zero exception
    }
    template<typename DivideFunc> void test2(int numerator, int denominator, DivideFunc divide_func) {                                                      // Function template to test divide2
        std::pair<bool, int> result = divide_func(numerator, denominator);                                                                                  // calling the divide function with the specified numerator and denominator
        if (result.first) { std::cout << "Calling function #2; result: " << result.second << "." << std::endl; }                                            // checking if the division was successful and printing the result
        else { std::cout << "Calling function #2.\n"; throw division_by_zero(numerator); }                                                                  // else printing a message and throw a division_by_zero exception
    }
    template<typename DivideFunc> void test3(int numerator, int denominator, DivideFunc divide_func) {                                                      // Function template to test divide3
        int result = divide_func(numerator, denominator);                                                                                                   // calling the divide function with the specified numerator and denominator
        if (result != 0 || denominator != 0) { std::cout << "Calling function #3; result: " << result << "." << std::endl; }                                // checking if the division was successful and printing the result 
        else { std::cout << "Calling function #3.\n"; throw division_by_zero(numerator); }                                                                  // else printing a message and throw a division_by_zero exception
    }
    template<typename DivideFunc> void test4(int numerator, int denominator, DivideFunc divide_func) {                                                      // Function template to test divide4
        int result = divide_func(numerator, denominator);                                                                                                   // calling the divide function with the specified numerator and denominator
        if (result != std::numeric_limits<int>::min() || denominator != 0) {std::cout << "Calling function #4; result: " << result << "." << std::endl; }   // checking if the division was successful and printing the result 
        else { std::cout << "Calling function #4.\n"; throw division_by_zero(numerator); }                                                                  // else printing a message and throw a division_by_zero exception
    }
    template<typename DivideFunc> void test5(int numerator, int denominator, DivideFunc divide_func) {                                                      // Function template to test divide5
        try {
            int result = divide_func(numerator, denominator);                                                                                               // calling the divide function with the specified numerator and denominator
            std::cout << "Calling function #5; result: " << result << "." << std::endl;                                                                     // printing the result if the division was successfull
        } 
        catch (const division_by_zero& error) { std::cout << "Calling function #5." << std::endl; throw error; }                                            // printing a message and re-throwing the exception
    }
//############################################################################################################################################################################################################################################
} // namespace hlp2

#endif // TEST_HPP
