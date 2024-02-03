from persistence import *

import sys
import os

def add_branche(splittedline : list):
    # parse splitted line
    id = splittedline[0]
    location = splittedline[1]
    number_of_employees = splittedline[2]
    #insert into branches
    repo.branches.insert(Branche(id, location, number_of_employees))
   

def add_supplier(splittedline : list):
    # parse splitted line
    id = splittedline[0]
    name = splittedline[1]
    contact_information = splittedline[2]
    #insert into suppliers
    repo.suppliers.insert(Supplier(id,name,contact_information))

def add_product(splittedline : list):
    # parse splitted line
    id = splittedline[0]
    description = splittedline[1]
    price = splittedline[2]
    quantity = splittedline[3]
    #insert into products
    repo.products.insert(Product(id,description, price, quantity))

def add_employee(splittedline : list):
    # parse splitted line
    id = splittedline[0]
    name = splittedline[1]
    salary = splittedline[2]
    branche = splittedline[3]
    #insert into employees
    repo.employees.insert(Employee(id,name, salary, branche))

adders = {  "B": add_branche,
            "S": add_supplier,
            "P": add_product,
            "E": add_employee}

def main(args : list):
    inputfilename = args[1]
    # delete the database file if it exists
    repo._close()
    if os.path.isfile("bgumart.db"):
        os.remove("bgumart.db")
    repo.__init__()
    repo.create_tables()
    with open(inputfilename) as inputfile:
        for line in inputfile:
            splittedline : list[str] = line.strip().split(",")
            adders.get(splittedline[0])(splittedline[1:])

if __name__ == '__main__':
    main(sys.argv)