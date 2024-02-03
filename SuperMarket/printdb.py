from persistence import *

def main():
    cursor = repo._conn.cursor()
    print("Activities")
    cursor.execute("""SELECT * FROM activities ORDER BY date""")
    lineInTable = cursor.fetchone()
    while (lineInTable != None) :
        print(lineInTable)
        lineInTable = cursor.fetchone()
    
    print("Branches")
    cursor.execute("""SELECT * FROM branches ORDER BY id""")
    lineInTable = cursor.fetchone()
    while (lineInTable != None) :
        print(lineInTable)
        lineInTable = cursor.fetchone()

    print("Employees")
    cursor.execute("""SELECT * FROM employees ORDER BY id""")
    lineInTable = cursor.fetchone()
    while (lineInTable != None) :
        print(lineInTable)
        lineInTable = cursor.fetchone()

    print("Products")
    cursor.execute("""SELECT * FROM products ORDER BY id""")
    lineInTable = cursor.fetchone()
    while (lineInTable != None) :
        print(lineInTable)
        lineInTable = cursor.fetchone()

    print("Suppliers")
    cursor.execute("""SELECT * FROM suppliers ORDER BY id""")
    lineInTable = cursor.fetchone()
    while (lineInTable != None) :
        print(lineInTable)
        lineInTable = cursor.fetchone()


    print("")
    print("Employees report")
    report = """SELECT E.name AS name, E.salary AS salary, B.location AS location,
                        IFNULL(SUM((A.quantity * (-1)) * P.price), 0) AS sales
                        FROM employees E
                        LEFT JOIN activities A ON A.activator_id=E.id
                        LEFT JOIN products P ON P.id=A.product_id
                        LEFT JOIN branches B ON B.id=E.branche
                        GROUP BY name
                        ORDER BY name
                        """
    output = repo.execute_command(report)
    for rep in output: print(' '.join([str(x) for x in rep]))

    print("")
    print("Activities report")
    report = """SELECT A.date AS date, P.description AS description, A.quantity AS quantity, E.name AS E_name, S.name AS S_name
                        FROM activities A
                        LEFT JOIN products P ON A.product_id=P.id
                        LEFT JOIN employees E ON A.activator_id=E.id
                        LEFT JOIN suppliers S ON A.activator_id=S.id
                        ORDER BY date
                        """
    output = repo.execute_command(report)
    for rep in output: print(rep)

if __name__ == '__main__':
    main()