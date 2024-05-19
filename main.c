/* Carrie Bailey
 * CS 221 Spring 2024
 Paycheck Program in C
 * Description: Prints a paycheck for named user based on gross income and tax and benefit
 * deductions.*/
 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//functions
int validation_integer(int min, int max);//validate integer ee ID
float validation_float(float min, float max);//validate gross pay
float gross_pay_func(char emp_name[]);//deductions from gross pay
int emp_id_func();//get employee's ID
void emp_name_func(char emp_name[]);//get employee's name
void label(const char*label);//label the paycheck entry
void paycheck_entry(float entry);//dollars and cents for paycheck entry
double paycheck_entry_perc(double net_pay, double gross_pay);//percentage for take home percentage
char filler(); // for period/ellipses on paycheck between "gross pay" and amount for example
//CONSTANTS
//left width
const int LWIDTH = 32;
//right width
const int RWIDTH = 7;

void main() {

    //VARIABLES
    char emp_name[100]; //employee name
    int emp_id;//user's employee ID
    //monthly pay
    float gross_pay; //user's gross pay
//taxes & retirement - rates
    float state_tax_rate, medicare_tax_rate, soc_sec_tax_rate, retire_ded_perc;
    double take_home_percent;
    float fed_tax_rate; //federal taxes
//taxes & retirement - totals
    float fed_tax, state_tax, medicare_tax, soc_sec_tax, retire_ded;
//flat amount deductions
    float life_ins_amt, health_ins_amt;
//totals
    float sum_deductions, net_pay; //total all deductions, gross - deductions = net pay

//END VARIABLES

//PROGRAM

    emp_id = emp_id_func(); //put employee ID into a variable
    emp_name_func(emp_name); //put employee name into a variable
    gross_pay = gross_pay_func(emp_name);//put gross pay into a variable

    //tax rates
    fed_tax_rate = 0.175;
    state_tax_rate = 0.091;
    medicare_tax_rate = 0.0145;
    soc_sec_tax_rate = 0.062;
//deductions
    retire_ded_perc = 0.0929;
//flat rate deductions
    life_ins_amt = 3.71; //life insurance cost per paycheck
    health_ins_amt = 51.48; //health insurance deduction per paycheck

//tax totals
    fed_tax = fed_tax_rate * gross_pay; //federal tax calculation
    state_tax = state_tax_rate * gross_pay; //state tax calculation
    medicare_tax = medicare_tax_rate * gross_pay; //medicare tax calculation
    soc_sec_tax = soc_sec_tax_rate * gross_pay; //social security tax calculations

//% deductions
    retire_ded = retire_ded_perc * gross_pay; //retirement deduction calculation

//calculations
    sum_deductions = fed_tax + state_tax + medicare_tax + soc_sec_tax + retire_ded + life_ins_amt + health_ins_amt;
    net_pay = gross_pay - sum_deductions;
    //DISPLAY

    printf("Paycheck for %s, employeeID %d\n", emp_name, emp_id); //employee name's paycheck

    /*THIS SECTION NOTES
     * label lines are the category of the paycheck, both credits and debits
     * filler is the dots between labels and amount
     * paycheck entry is the amount, either credit or debit
     * */
    label("Gross Amount: ");
    filler();
    paycheck_entry(gross_pay);
    printf("\nDeductions\n");
    label("Federal Tax: ");
    paycheck_entry(fed_tax);
    label("State Tax: ");
    filler();
    paycheck_entry(state_tax);
    filler();
    paycheck_entry(soc_sec_tax);
    label("Medicare Tax: ");
    paycheck_entry(medicare_tax);
    label("Retirement Plan: ");
    paycheck_entry(retire_ded);
    label("Health Insurance: ");
    paycheck_entry(health_ins_amt);
    label("Life Insurance: ");
    paycheck_entry(life_ins_amt);
    printf("\n");
    label("Net Pay: ");
    paycheck_entry(net_pay);
    label("Percent take home: ");;
    paycheck_entry_perc(net_pay, gross_pay);
}
//END PAYCHECK DISPLAY

//FUNCTION DEFINITIONS


void emp_name_func(char emp_name[]) {//collect and validate employee name user entry
    printf("Enter employee's full name: ");
    getchar();
    fgets(emp_name, 100, stdin);
    emp_name[strcspn(emp_name, "\n")] = 0;

    float gross_pay_func(char emp_name[]);//collect and validate gross pay user entry
    {
        printf("Enter gross salary for %s:\n", emp_name);
    }
}
    float gross_pay_func(char emp_name[]){
    float min = 1;
    float max = 9999999;
    float pay = validation_float(min, max);
    printf("\n");
    return pay;
    }

  int emp_id_func() {//collect from user employee ID# and validate
      printf("Enter employee's ID: ");
      int min = 1, max = 9999;
      return validation_integer(min, max);
  }

  void label(const char* label) //print out for label, left justified
  {
printf("%-*s", LWIDTH, label);
}

void paycheck_entry(float entry){ //paycheck print for paycheck amounts, right justified
    printf(" $%*.2f\n", RWIDTH, entry);
}

double paycheck_entry_perc(double net_pay, double gross_pay){//function to calculate and format % take home pay
    double take_home_percent = net_pay / gross_pay;
    printf(" %%%7.2f\n" , take_home_percent);
}
char filler(){//function to print dots/ellipses between labels and amounts
int filler = '.'; // in C++ setfill('*')
int width = 20;   // in C++ setw(10)
int target = 0;   // ****TEST VALUE****
/* ******** */
int s = snprintf(NULL, 0, "%d", target); //returns number of characters if no error
for (int i = 0; i < width - s; i++) {//put char to width
putchar(filler);
}
printf("%d\n", target);//print value at end of dots/periods
/* ******** */
return 0;
}

int validation_integer(int min, int max) // function to validate integers
{
    int number;
    int return_code;
    do {
        return_code = scanf("%d", &number);
        if (return_code <= 0 || number < min || number > max) {
            // Explain error not entering an integer or out of range
            printf("I'm sorry that's not a valid entry. Please enter a number between %d and %d: ", min, max);
            // Clear input stream
            while (getchar() != '\n'); // Discard previous input
        }
    } while (return_code <= 0 || number < min || number > max);
    return number;
}

float validation_float(float min, float max)//validate floating point numbers
{
    bool valid = false;
    float number;
    int return_code;
    do {
        return_code = scanf("%f", &number);
        if (return_code <= 0) {
            // Explain error not entering a float
            printf("I'm sorry that's not a valid entry. Please retry: ");
            printf("\n");
            // Clear input stream
            while (getchar() != '\n'); // Discard previous input
        } else if (number < min || number > max) {
            // Explain error not entering out of range
            printf("I'm sorry that's not a valid entry. Please enter a number between %f and %f: ", min, max);
            printf("\n");
        } else {
            valid = true;
        }
    } while (!valid);
    return number;
}


