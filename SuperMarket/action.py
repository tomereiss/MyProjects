from persistence import *

import sys

def main(args : list):
    inputfilename : str = args[1]
    with open(inputfilename) as inputfile:
        for line in inputfile:
            splittedline : list[str] = line.strip().split(", ")

            #find product_id in Product table and check the quantity
            new_p_id = splittedline[0]
            new_p_quantity = int(splittedline[1])

            #get the relevant product with new product id from db
            relevant_product :Product = repo.products.find(id=new_p_id)[0]

            if new_p_quantity + relevant_product.quantity >= 0:
                updated_quantity = relevant_product.quantity + new_p_quantity
                repo.products.delete(id=new_p_id)
                repo.products.insert(Product(relevant_product.id, relevant_product.description, relevant_product.price, updated_quantity)) #update the new quantity of the product in db
                repo.activities.insert(Activitie(new_p_id,new_p_quantity, splittedline[2], splittedline[3])) #insert new activity

if __name__ == '__main__':
    main(sys.argv)