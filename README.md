# Incomes-and-Expenses-tracker-in-C

Final project for my uni course.
When the program is ran, the total income, total expense and available balance can be 
seen on the upper right side, it has 5 functionalities:
1.INSERT INCOME
2.INSERT EXPENSE
3.VIEW INCOME RECORD
4.VIEW EXPENSE RECORD
5.EXIT

Any option can be choosen unlimited number of times, until the user chooses to exit. 

## When entering the data, the user should follow these rules:
If one of the first two options is chosen, the user should enter three things, and press 
the enter button when finished:
- The date - (DD MM YY), separate the day, month and year with a space. 
- The amount - no decimal numbers allowed.
- The category - there are no options to choose from, any word can be written.

If the third or forth option is choosen, all of the recorded incomes/expenses will pop up.

All the data will be stored in 3 files, named:
- myexpense
- myincome
- Record
The files will be created in the same directory as the .c file. Every information inserted in 
the program can be seen by opening the files. 
Deleting the current data and starting from zero can be achieved by deleting the files.
  
