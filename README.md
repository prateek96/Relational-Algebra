# Relational-Algebra
A functional system for performing a wide range of relational algebra queries.The system supports creation of tables,nested select,rename,project,set difference,union,intersection,division,cartesian product,natural join and aggregate functions(min,max,average,count) .All queries can be nested up to infinite level.

How to run the File:

1.Run file version7.cpp or use the version7.exe 

2.Type H for help with syntax

3.To create more tables create table along with info file .Use 0 for integer and 1 for string in the info file.

# Some sample queries 

1. Union of students from 2 tables:

U(studentsb:P(studentsa:[name,age,class]))

2. Selecting students specifying some condition and are also a part of the union described above

S(U(studentsb:P(studentsa:[name,age,class])):[((age>8|name="Liam")^class>7)])

3.Projecting names only out of the above mentioned query

P(S(U(studentsb:P(studentsa:[name,age,class])):[((age>8|name="Liam")^class>7)]):[name])

4.Union of above mentioned query with name from studentsc table

U(P(S(U(studentsb:P(studentsa:[name,age,class])):[((age>8|name="Liam")^class>7)]):[name]):P(studentsc:[name]))

5.Cartesian product

C(age:instructors)

6.Name of instuctor teaching all  subjects

%(P(instructors:[name,subject]):subject) // Erraneous command

%(P(instructors:[name,subject]):P(subject:[subject]))

7.Name of instuctor teaching all science subjects

%(P(instructors:[name,subject]):ssubjects)

8.Students common in a and b sections

I(P(studentsa:[name]):P(studentsb:[name]))

I(I(P(studentsa:[name,age,class]):studentsb):studentsc)

9.Maximum marks

A(studentsa:[marks,max])

10.Average marks

A(studentsa:[marks,avg])

11.Section A analysis

R(A(studentsa:[marks,max,min,avg]):[highest,lowest,average])
