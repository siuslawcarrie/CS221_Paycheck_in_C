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
char filler();
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
    float fed_tax_rate;
//taxes & retirement - totals
    float fed_tax, state_tax, medicare_tax, soc_sec_tax, retire_ded;
//flat amount deductions
    float life_ins_amt, health_ins_amt;
//totals
    float sum_deductions, net_pay;

//END VARIABLES

//PROGRAM

    emp_id = emp_id_func();
    emp_name_func(emp_name);
    gross_pay = gross_pay_func(emp_name);


    //tax rates
    fed_tax_rate = 0.175;
    state_tax_rate = 0.091;
    medicare_tax_rate = 0.0145;
    soc_sec_tax_rate = 0.062;
//deductions
    retire_ded_perc = 0.0929;
//flat rate deductions
    life_ins_amt = 3.71;
    health_ins_amt = 51.48;

//tax totals
    fed_tax = fed_tax_rate * gross_pay;
    state_tax = state_tax_rate * gross_pay;
    medicare_tax = medicare_tax_rate * gross_pay;
    soc_sec_tax = soc_sec_tax_rate * gross_pay;

//% deductions
    retire_ded = retire_ded_perc * gross_pay;

//calculations
    sum_deductions = fed_tax + state_tax + medicare_tax + soc_sec_tax + retire_ded + life_ins_amt + health_ins_amt;
    net_pay = gross_pay - sum_deductions;



    //DISPLAY

    printf("Paycheck for %s, employeeID %d\n", emp_name, emp_id);

    label("Gross Amount: ");
    filler();
    paycheck_entry(gross_pay);
    printf("\nDeductions\n");

    label("Federal Tax: ");
    paycheck_entry(fed_tax);
    label("State Tax: ");
    paycheck_entry(state_tax);
    label("Social Security Tax: ");
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

//FUNCTION DEFINITIONS


void emp_name_func(char emp_name[]) {
    printf("Enter employee's full name: ");
    getchar();
    fgets(emp_name, 100, stdin);
    emp_name[strcspn(emp_name, "\n")] = 0;
    float gross_pay_func(char emp_name[]);
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

  int emp_id_func() {
      printf("Enter employee's ID: ");
      int min = 1, max = 9999;
      return validation_integer(min, max);
  }

  void label(const char* label)
  {
printf("%-*s", LWIDTH, label);
}

void paycheck_entry(float entry){
    printf(" $%*.2f\n", RWIDTH, entry);
}

double paycheck_entry_perc(double net_pay, double gross_pay){
    double take_home_percent = net_pay / gross_pay;
    printf(" %%%7.2f\n" , take_home_percent);
}
char filler(){
int filler = '.'; /* setfill('#') */
int width = 10;   /* setw(10)     */
int target = 5;   /* 5            */

/* ******** */
int s = snprintf(NULL, 0, "%d", target);
for (int i = 0; i < width - s; i++) {
putchar(filler);
}
printf("%d\n", target);
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

float validation_float(float min, float max)
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


