#include "calculator.h"
#include <fstream>
#include <string>

const std::unordered_set<char> Calculator::symbols = {'/', '*', '-', '+', '^', '(', ')', '.'};
const std::unordered_set<char> Calculator::operations = {'/', '*', '-', '+', '^'};
const std::unordered_set<char> Calculator::parentheses = {'(', ')'};

Calculator::Calculator() {
    std::ifstream file(HISTORY_FILE);
    if (!file.is_open())
        return;
    std::string line;
    while (std::getline(file, line))
        if (!line.empty())
            history.push_back(line);
}

void Calculator::save_history() {
    std::ofstream file(HISTORY_FILE, std::ios::trunc);
    for (const auto& line : history)
        file << line << "\n";
}

std::string Calculator::parse_symbols(const std::string& input) {
    std::string result;
    result.reserve(input.size());
    for (auto& ch : input) {
        if (std::isspace(ch))
            continue;
        if (this->symbols.contains(ch) || isdigit(ch))
            result.push_back(ch);
        else
            throw std::runtime_error("Unexpected symbol: '" + std::string(1, ch) + "'");
    }
    return result;
}

void Calculator::check_order(const std::string& input) {
    int i = 0;
    int parenthes_count = 0;
    while (i < input.size()) {
        char symbol = input[i];
        if (operations.contains(symbol)) {
            if ((i == 0 || i == input.size() - 1) && !(symbol == '+' || symbol == '-'))
                throw std::runtime_error("Operation symbol at the beginning or end: '" + std::string(1, symbol));
            if (i != 0 && (isdigit(input[i - 1]) <= 0 &&
                           (!parentheses.contains(input[i - 1]) && !(symbol == '+' || symbol == '-'))))
                throw std::runtime_error("Non digit symbol before operation: '" + std::string(1, input[i - 1]) +
                                         std::string(1, symbol) + "'");
            if (i != 0 && operations.contains(input[i - 1]))
                throw std::runtime_error("Two operation symbols in a row: '" + std::string(1, input[i - 1]) +
                                         std::string(1, symbol) + "'");
        }
        if (symbol == '(' || symbol == ')') {
            if (symbol == '(')
                parenthes_count++;
            else {
                if (parenthes_count == 0)
                    throw std::runtime_error("Opening parenthesis is missing");
                parenthes_count--;
            }
        }
        if (symbol == '.') {
            if (i == 0)
                throw std::runtime_error("Dot at the beginning");
            if (i != 0 && isdigit(input[i - 1]) <= 0)
                throw std::runtime_error("No digit before dot: '" + std::string(1, input[i - 1]) + std::to_string(i));
            i++;
            while (i < input.size() && isdigit(input[i]) > 0)
                i++;
            if (i < input.size() && input[i] == '.')
                throw std::runtime_error("Two dots in the number at position " + std::to_string(i));
            if (input[i - 1] == '.')
                throw std::runtime_error("No digit after dot at position " + std::to_string(i));
            continue;
        }
        i++;
    }
    if (parenthes_count != 0)
        throw std::runtime_error("There are no closing parenthesis");
}

double Calculator::get_number_from_str(const std::string& input, int& index) {
    std::string result;
    while (index < input.size() && (isdigit(input[index]) || input[index] == '.')) {
        result.push_back(input[index]);
        index++;
    }
    return std::stod(result);
}

double Calculator::get_expression_result(const std::string& input, int& pos) {
    if (pos < input.size() && input[pos] == '(') {
        pos++;
        double val = get_add_sub_result(input, pos);
        pos++;
        return val;
    } else if (pos < input.size() && isdigit(input[pos])) {
        return get_number_from_str(input, pos);
    } else if (pos < input.size() && (input[pos] == '+' || input[pos] == '-')) {
        char sign = input[pos];
        pos++;
        double val = get_expression_result(input, pos);
        return sign == '-' ? -val : val;
    }
}

double Calculator::get_factor_result(const std::string& input, int& pos) {
    double left = get_expression_result(input, pos);
    while (pos < input.size() && input[pos] == '^') {
        pos++;
        double right = get_factor_result(input, pos);
        left = std::pow(left, right);
    }
    return left;
}

double Calculator::get_multi_div_result(const std::string& input, int& pos) {
    double left = get_factor_result(input, pos);
    while (pos < input.size() && (input[pos] == '*' || input[pos] == '/')) {
        char op = input[pos];
        pos++;
        double right = get_factor_result(input, pos);
        if (op == '*')
            left *= right;
        else {
            if (right == 0.0)
                throw std::runtime_error("Division by zero");
            left /= right;
        }
    }
    return left;
}

double Calculator::get_add_sub_result(const std::string& input, int& pos) {
    double left = get_multi_div_result(input, pos);
    while (pos < input.size() && (input[pos] == '+' || input[pos] == '-')) {
        char op = input[pos];
        pos++;
        double right = get_multi_div_result(input, pos);
        if (op == '+')
            left += right;
        else
            left -= right;
    }
    return left;
}

double Calculator::calculate(const std::string& input) {
    std::string parsed = parse_symbols(input);
    check_order(parsed);
    int pos = 0;
    double result = get_add_sub_result(parsed, pos);
    history.push_back(parsed + " = " + std::to_string(result));
    save_history();
    return result;
}
