/* BankLoanManagement */

#include <stdio.h>
#include <string.h>

#define N 5 /* Define constant N for the number of customers */

/*                      ||>---|--------->   PROGRAM USAGE INSTRUCTIONS   <---------|<---||
    The program records, evaluates, and approves loan applications of bank customers based on specific criteria.
  -Step 1--->Data entry (main): The user enters the target total loan amount to be approved.
             For each customer (5 in total), the details found in the "struct customer" structure are entered.
  -Step 2--->Creditworthiness calculation (main): The creditworthiness of each customer starts at 300 points and
             increases/decreases accordingly (see Main program (main)).
  -Step 3--->Loan approval (approve_loan): Each customer's approval criteria are checked.
             See "void approve_loan()".
  -Step 4--->Display initial results (display): See Function void display().
  -Step 5--->Evaluation and adjustment of credit limit (evaluate_loans):
            See function "void evaluate_loans()".
  -Step 6--->Display final results (display): See Function void display().                      
*/

/* Definition of customer structure with 7 fields - Question 1 (recording new loan applications) */
/* This structure belongs to step 1 of the program usage instructions */
struct customer
{
  int id;               /* Customer ID (integer) */
  float income;         /* Annual income of the customer (float) */
  float loan_amount;    /* Loan amount requested by the customer (float) */
  float dti;            /* Debt-to-Income Ratio (float) */
  int years_employed;   /* Years the customer has been employed (integer) */
  int has_red_loan;     /* Has a red loan? (0 = No, 1 = Yes) (integer) */
  int credit_score;     /* Customer's credit score (integer, e.g., from 300 to 850) */
};

/* Definition of loan structure - Question 1 (recording new loan applications) */
struct loan
{
  int id;               /* Loan ID (integer) */
  int customer_id;      /* Customer ID (integer) */
  float amount;         /* Loan amount (float) */
};

/* Create an array for customers - Question 2 */
struct customer customers_list[N];

/* Declare an array for approved loans - Question 2 */
struct loan loans_list[N];

/* Declare necessary variables for the program */
int total_loans = 0;            /* Total number of approved loans */
float total_loan_amount = 0;    /* Total amount of approved loans */
int loan_target;                /* Target total loan amount */
int credit_score_threshold = 650; /* Initial credit score threshold */

/* Loan approval function - Question 5 */
/* This function belongs to step 3 of the program usage instructions */
void approve_loan()
{
  for (int i = 0; i < N; i++)
  {
    /* Check if the customer meets the loan approval criteria */
    /* Income >= 30,000€ - DTI < 40% - Credit score >= 650 - No red loan */
    /* If they meet the criteria, the loan is approved and recorded in the approved loans list. */
    if (customers_list[i].income >= 30000 && customers_list[i].dti < 40 &&
        customers_list[i].credit_score >= credit_score_threshold &&
        !customers_list[i].has_red_loan)
    {    
        /* Record approved loan in the loan_list array */
        loans_list[total_loans].id = total_loans + 1;
        loans_list[total_loans].customer_id = customers_list[i].id;
        loans_list[total_loans].amount = customers_list[i].loan_amount;
        total_loan_amount += customers_list[i].loan_amount;
        total_loans++;
    }
  }
}

/* Function to display customer details, approved loans,
   total number of approved loans, and their total amount - Question 7 */
/* This function belongs to step 4 of the program usage instructions */
/* Prints the customer array with all their details, approved loans, and the total amount of approved loans. */
void display()
{
  printf("-----------------------------------------\n");
  printf("------> Customer Table:\n");
  printf("|--------------------------------------------------------------------------------------------------------------------------------------------------||\n");
  for (int i = 0; i < N; i++)
  {
      printf("| id=%d, income=%.2f, requested Loan Amount=%.2f, DTI= %.2f, years employed=%d, red loan=%s, credit score=%d      ||\n",
              customers_list[i].id, customers_list[i].income, customers_list[i].loan_amount, customers_list[i].dti,
              customers_list[i].years_employed, customers_list[i].has_red_loan ? "Yes" : "No", customers_list[i].credit_score);
  }
  printf("|--------------------------------------------------------------------------------------------------------------------------------------------------||");
  printf("\n------> Approved Loans Table <------\n");
  
  for (int i = 0; i < total_loans; i++)
  {
    printf("id=%d, customer=%d, loan amount=%.2f\n", loans_list[i].id, loans_list[i].customer_id, loans_list[i].amount);
  }
  printf("------------------------------------------------");

  printf("\nTotal Number of Approved Loans: %d\n", total_loans);
  printf("Total Amount of Approved Loans: %.2f\n", total_loan_amount);
}

/* Function to evaluate the achievement of the loan target and adjust - Question 7 */
/* This function belongs to step 5 of the program usage instructions */
void evaluate_loans()
{
  while (total_loan_amount < loan_target && credit_score_threshold > 550)
  {
    credit_score_threshold -= 10; // Reduce the credit score threshold by 10 points
    total_loans = 0;
    total_loan_amount = 0;
    approve_loan();
  }
}

int main()  /* Main Program */
{
  /* Data Entry by User - Question 3 */
  /* Here we have step 1 of the program usage instructions */
  printf("Enter the target total loan amount (€): ");
  scanf("%d", &loan_target);

  for (int i = 0; i < N; i++)
  {
    customers_list[i].id = i + 1;
    printf("Customer %d:\n", i + 1);
    printf("Enter the customer's income: ");
    scanf("%f", &customers_list[i].income);
    printf("Enter the requested Loan Amount: ");
    scanf("%f", &customers_list[i].loan_amount);
    printf("Enter the DTI percentage (e.g., 35 for 35%%): ");
    scanf("%f", &customers_list[i].dti);
    printf("Enter the years employed: ");
    scanf("%d", &customers_list[i].years_employed);
    printf("Has a red loan (0=No, 1=Yes): ");
    scanf("%d", &customers_list[i].has_red_loan);

    /* Credit Score Calculation - Question 4 */
    /* Here we have step 2 of the program usage instructions */
    customers_list[i].credit_score = 300;
    if (customers_list[i].income > 50000)
    /* Customers with high income +100 points. */
    {
      customers_list[i].credit_score += 100;
    }
    if (customers_list[i].dti < 30)
    /* Customers with low DTI +150 points. */
    {
      customers_list[i].credit_score += 150;
    }
    if (customers_list[i].years_employed > 5)
    /* Customers with more than 5 years of employment +100 points. */
    {
      customers_list[i].credit_score += 100;
    }
    if (customers_list[i].has_red_loan)
    /* Customers with red loans -200 points. */
    {
      customers_list[i].credit_score -= 200;
    }
  }

  approve_loan();   /* Call function to evaluate loan criteria - Question 5 */
  display();        /* Call function to display details on the screen */
  evaluate_loans(); /* Call function to check loan target and readjust */
  printf("\nApproved loans after adjustment\n");
  display();        /* Call function to display details on the screen */

  printf("\nFinal credit score threshold: %d\n", credit_score_threshold);

  return 0;
}
