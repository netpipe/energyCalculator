#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

class EnergyCostCalculator : public QWidget {
    Q_OBJECT

public:
    EnergyCostCalculator(QWidget *parent = nullptr);
~EnergyCostCalculator();
private slots:
    void calculateCost();

private:
    QLineEdit *hoursInput;
    QLineEdit *costInput;
    QLineEdit *wattsInput;
    QLabel *dailyCostLabel;
    QLabel *monthlyCostLabel;
    QLabel *bimonthlyCostLabel;
    QLabel *yearlyCostLabel;  // Added label for yearly cost
};
EnergyCostCalculator::~EnergyCostCalculator() {
    // Cleanup if necessary
}
EnergyCostCalculator::EnergyCostCalculator(QWidget *parent)
    : QWidget(parent) {

    // Create layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *inputLayout = new QHBoxLayout;

    // Create input fields
    hoursInput = new QLineEdit(this);
    costInput = new QLineEdit(this);
    wattsInput = new QLineEdit(this);

    // Create labels for instructions
    QLabel *hoursLabel = new QLabel("Hours per day:", this);
    QLabel *costLabel = new QLabel("Cost per kWh ($):", this);
    QLabel *wattsLabel = new QLabel("Wattage (W):", this);

    // Create result labels
    dailyCostLabel = new QLabel("Daily Cost: $0.00", this);
    monthlyCostLabel = new QLabel("Monthly Cost: $0.00", this);
    bimonthlyCostLabel = new QLabel("Bimonthly Cost: $0.00", this);
    yearlyCostLabel = new QLabel("Yearly Cost: $0.00", this);  // Added label for yearly cost

    // Create calculate button
    QPushButton *calculateButton = new QPushButton("Calculate", this);

    // Layout for inputs
    inputLayout->addWidget(hoursLabel);
    inputLayout->addWidget(hoursInput);
    inputLayout->addWidget(costLabel);
    inputLayout->addWidget(costInput);
    inputLayout->addWidget(wattsLabel);
    inputLayout->addWidget(wattsInput);

    // Add widgets to the main layout
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(calculateButton);
    mainLayout->addWidget(dailyCostLabel);
    mainLayout->addWidget(monthlyCostLabel);
    mainLayout->addWidget(bimonthlyCostLabel);
    mainLayout->addWidget(yearlyCostLabel);  // Added yearly cost label

    setLayout(mainLayout);

    // Connect the calculate button to the calculation function
    connect(calculateButton, &QPushButton::clicked, this, &EnergyCostCalculator::calculateCost);
}

void EnergyCostCalculator::calculateCost() {
    // Get user inputs
    bool ok;
    double hours = hoursInput->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid number for hours.");
        return;
    }

    double costPerKWh = costInput->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid number for cost per kWh.");
        return;
    }

    double watts = wattsInput->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid number for watts.");
        return;
    }

    // Convert watts to kWh (1 kWh = 1000 watts per hour)
    double powerInKWh = watts / 1000.0;

    // Calculate daily, monthly, bimonthly, and yearly costs
    double dailyCost = powerInKWh * costPerKWh * hours;
    double monthlyCost = dailyCost * 30;  // Assuming 30 days in a month
    double bimonthlyCost = dailyCost * 30 /2;  // Assuming 60 days in two months
    double yearlyCost = dailyCost * 365;  // Assuming 365 days in a year

    // Display results
    dailyCostLabel->setText(QString("Daily Cost: $%1").arg(dailyCost, 0, 'f', 2));
    monthlyCostLabel->setText(QString("Monthly Cost: $%1").arg(monthlyCost, 0, 'f', 2));
    bimonthlyCostLabel->setText(QString("Bimonthly Cost: $%1").arg(bimonthlyCost, 0, 'f', 2));
    yearlyCostLabel->setText(QString("Yearly Cost: $%1").arg(yearlyCost, 0, 'f', 2));  // Display yearly cost
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    EnergyCostCalculator calculator;
    calculator.setWindowTitle("Energy Cost Calculator");
    calculator.show();
    return app.exec();
}

#include "main.moc"
