#include "incl.hpp"
#include <stdexcept>
#include <cstdlib>
#include <algorithm>

static std::pair<double, std::string> parse_number( const std::string& expression )
{
    char * next_end {nullptr};
    const double result {std::strtod(expression.c_str(),
                                     &next_end )};

    if (next_end == expression.c_str()) {
        throw std::runtime_error{"bad number"};
    }

    return {result, std::string{next_end}};
}

static std::string remove_white_spaces( std::string expression )
{
    const auto new_end = std::remove_if(
                   std::begin(expression),
                   std::end(expression),
                   std::isspace);

    // "1 2 3" -> "123 3"

    // "123 3" -> "123"
    expression.erase(new_end, std::end(expression));

    return expression;
}


double calc_express_impl( std::string expression )
{
    const auto found (std::find_if(
          std::begin(expression),
          std::end(expression),
          [](const char c) { return c == '+' || c == '-'; }
          ));

    if (found != std::end(expression)) {
        const char op {*found};
        const std::string left {
            std::begin(expression),
            found};
        const std::string right {
            std::next(found, 1),
            std::end(expression)};

        return op == '+'
            ? calc_express_impl(left) + calc_express_impl(right)
            : calc_express_impl(left) - calc_express_impl(right);
    }

    double num;
    std::tie(num, expression) = parse_number(expression);

    if (expression.empty()) {
        return num;
    }

    std::string rest {std::begin(expression) + 1,
                      found};
    const char op {expression[0]};

    switch (op) {
    case '*': return num * calc_express_impl(rest);
    case '/': return num / calc_express_impl(rest);
    default:
        throw std::runtime_error {"invalid op"};
    }
}

double calc_express( const std::string& input )
{
    std::string expression = remove_white_spaces( input );

    if ( expression.empty() )
        throw std::runtime_error( "empty expression" );

    return calc_express_impl( input );
}