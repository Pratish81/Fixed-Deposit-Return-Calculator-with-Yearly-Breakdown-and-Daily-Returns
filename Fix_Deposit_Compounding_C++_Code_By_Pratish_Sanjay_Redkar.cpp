#include <iostream>
#include <iomanip> // For setprecision
#include <sstream> // For number formatting
#include <cmath>   // For pow function
#include <limits>  // For numeric limits
#include <string>  // For string operations
#include <algorithm> // For std::remove
using namespace std;

// Function to format numbers according to Indian numbering system
string formatIndianNumber(double number) {
    stringstream ss;
    ss << fixed << setprecision(2) << number; // Format with 2 decimal places
    string numStr = ss.str();

    // Separate the decimal part (if any)
    size_t dotPosition = numStr.find('.');
    string integerPart = numStr.substr(0, dotPosition);
    string decimalPart = numStr.substr(dotPosition);

    // Reverse the integer part to process grouping
    string reversedInteger = string(integerPart.rbegin(), integerPart.rend());
    string formattedReversed = "";

    // Add commas as per Indian numbering system
    for (size_t i = 0; i < reversedInteger.length(); i++) {
        if (i == 3 || (i > 3 && (i - 3) % 2 == 0)) {
            formattedReversed += ",";
        }
        formattedReversed += reversedInteger[i];
    }

    // Reverse it back to get the final formatted number
    string formattedNumber = string(formattedReversed.rbegin(), formattedReversed.rend());
    return formattedNumber + decimalPart + "/-"; // Append decimal and "/-"
}

// Function to remove commas from a string and convert it to a double
double sanitizeInput(string input) {
    input.erase(remove(input.begin(), input.end(), ','), input.end()); // Remove commas
    return stod(input); // Convert sanitized string to double
}

// Function to validate user input
double getValidatedInput(string prompt) {
    string input;
    double value;

    while (true) {
        cout << prompt;
        cin >> input;

        try {
            value = sanitizeInput(input); // Remove commas and convert
            return value; // Return valid input
        } catch (invalid_argument &) {
            cout << "Error: Please enter a valid numeric value. No invalid characters allowed." << endl;
        } catch (out_of_range &) {
            cout << "Error: The number entered is out of range. Please try again." << endl;
        }
    }
}

int main() {
    double annualReturn, principal, compoundedAmount;
    int years;

    // Input
    annualReturn = getValidatedInput("Enter the annual return percentage (e.g., 7 for 7%): ");
    years = static_cast<int>(getValidatedInput("Enter the number of years for the Fixed Deposit: "));
    principal = getValidatedInput("Enter the principal amount: ");

    // Convert annual return percentage to decimal
    double rate = annualReturn / 100;

    // Initialize compoundedAmount with the principal
    compoundedAmount = principal;

    // Output Header
    cout << endl << "Yearly Compounded Returns:" << endl;
    cout << setw(5) << "Year" << setw(20) << "Annual Return (%)" << setw(25) << "Amount (Rs)" << endl;

    // Loop to calculate compounded return for each year
    for (int year = 1; year <= years; year++) {
        // Calculate the return amount for the current year
        double interestEarned = compoundedAmount * rate;
        compoundedAmount += interestEarned;

        // Output the year, annual return %, and amount
        cout << setw(5) << year
             << setw(20) << fixed << setprecision(2) << annualReturn
             << setw(25) << formatIndianNumber(compoundedAmount) << endl;
    }

    // Calculate average daily return
    int totalDays = years * 365; // Assuming no leap years
    double totalInterest = compoundedAmount - principal;
    double dailyReturn = totalInterest / totalDays;

    // Calculate average daily return percentage
    double averageDailyReturnPercentage = (pow((compoundedAmount / principal), (1.0 / (years * 365))) - 1) * 100;

    // Calculate total percentage return
    double totalPercentageReturn = (totalInterest / principal) * 100;

    // Final Output
    cout << endl << "Total return after " << years << " years: Rs " << formatIndianNumber(compoundedAmount) << endl;
    cout << "Average daily return: Rs " << formatIndianNumber(dailyReturn) << endl;
    cout << "Average daily return percentage: " << fixed << setprecision(6) << averageDailyReturnPercentage << "% per day" << endl;
    cout << "Total percentage return after " << years << " years: " << fixed << setprecision(2) << totalPercentageReturn << "%" << endl;

    // Credit
    cout << "\nCode by Pratish Sanjay Redkar and ChatGPT." << endl;

    return 0;
}
