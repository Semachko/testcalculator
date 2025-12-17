#pragma once

#include <iostream>
#include <unordered_set>
#include <vector>

class Calculator {
    public:
        Calculator();
        double calculate(const std::string& input);
        std::vector<std::string> get_history() const { return history; }

    private:
        std::string parse_symbols(const std::string& input);
        void check_order(const std::string& input);
        double get_number_from_str(const std::string& input, int& index);
        double get_expression_result(const std::string& input, int& pos);
        double get_factor_result(const std::string& input, int& pos);
        double get_multi_div_result(const std::string& input, int& pos);
        double get_add_sub_result(const std::string& input, int& pos);
        void save_history();

    private:
        std::vector<std::string> history;
        const std::string HISTORY_FILE = "calculator_history.txt";
        static const std::unordered_set<char> symbols;
        static const std::unordered_set<char> operations;
        static const std::unordered_set<char> parentheses;
};
