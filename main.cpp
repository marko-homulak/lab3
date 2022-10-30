#include <iostream>
#include <string>
#include <vector>

using namespace std;

class InvalidPriceException
{
    string message;
public:
    InvalidPriceException(string message)
    {
        this->message = message;
    }

    string getMessage() {
        return message;
    }

};

class ElectricityCalculationBook
{

    int kilowattHourPrice;

    class Indicator;

    vector<Indicator> indicators;

public:

    ElectricityCalculationBook(int kilowattHourPrice)
    {
        if (kilowattHourPrice <= 0) {
            throw InvalidPriceException(string("Given invalid kilowatt hour price: ") + to_string(kilowattHourPrice));
        }
        this->kilowattHourPrice = kilowattHourPrice;
        indicators = vector<Indicator>();
    }

    vector<Indicator> findByPaymentDate(string paymentDate) {
        auto searchResulr = vector<Indicator>();
        for (auto& indocator : indicators) {
            if (indocator.getPaymentDate() == paymentDate) {
                searchResulr.push_back(indocator);
            }
        }
        return searchResulr;
    }

    void addIndicator(Indicator& indicator) {
        this->indicators.push_back(indicator);
    }

    int getKilowattHourPrice() {
        return this->kilowattHourPrice;
    }

    class Indicator
    {

        string paymentDate;

        int value;

        int paidAmount;


    public:
        Indicator(string paymentDate, int value, int paidAmount)
        {
            this->paymentDate = paymentDate;
            this->value = value;
            this->paidAmount = paidAmount;
        }

        Indicator& operator ++ () {
            value++;
            return *this;
        }

        Indicator& operator -= (int value) {
            this->value -= value;
            return *this;
        }

        int getValue() {
            return value;
        }

        int getPaidAmount() {
            return paidAmount;
        }

        string getPaymentDate() {
            return paymentDate;
        }

    };

};

int main()
{
    int kilowattHourPrice = 10;
    try {
        ElectricityCalculationBook electricityBook(kilowattHourPrice);
        int indicator1Value = 14;
        ElectricityCalculationBook::Indicator indicator1("2022:00:00", indicator1Value, electricityBook.getKilowattHourPrice() * indicator1Value);
        int indicator2Value = 10;
        ElectricityCalculationBook::Indicator indicator2("2023:00:00", indicator2Value, electricityBook.getKilowattHourPrice() * indicator2Value);
        electricityBook.addIndicator(indicator1);
        electricityBook.addIndicator(indicator2);
        vector<ElectricityCalculationBook::Indicator> indecatorsByDate = electricityBook.findByPaymentDate(string("2023:00:00"));

        cout << "Indicator 1: " << indicator1.getValue() << " " << indicator1.getPaidAmount() << endl;
        cout << "Indicator 2: " << indicator2.getValue() << " " << indicator2.getPaidAmount() << endl;
        for (auto& indicator : indecatorsByDate) {
            cout << "Search result: " << indicator.getValue() << " " << indicator.getPaidAmount() << endl;
        }
        ++indicator1;
        indicator2 -= 2;
        cout << "Indicator 1: " << indicator1.getValue() << " " << indicator1.getPaidAmount() << endl;
        cout << "Indicator 2: " << indicator2.getValue() << " " << indicator2.getPaidAmount() << endl;
    }
    catch (InvalidPriceException e) {
        cout << e.getMessage() << endl;
    }
}