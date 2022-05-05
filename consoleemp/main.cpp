#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <string>
using namespace std;

//for demonstration only. never save your password in the code!
const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "1234";
int emp_id, basic, hra, bonus;
string name, location;
void addemployee()
{
	system("cls");
	cout << "\n\n\t\t\t insert record";
	cout << "\n\n\n Employee Id :";
	cin >> emp_id;
	cout << "\n\n Employee Name : ";
	cin >> name;
	cout << "\n\n Employee Location : ";
	cin >> location;
	cout << "\n\n Employee Basic : ";
	cin >> basic;
	cout << "\n\n Employee HRA: ";
	cin >> hra;
	cout << "\n\n Employee Bonus : ";
	cin >> bonus;
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;
	sql::PreparedStatement* pstmt;
	try 
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
		con->setSchema("employee");
		std::string usr;
		string qry = "Insert into emp_d values("+to_string(emp_id)+" , '"+name+" ' , '" + location + "' , " + to_string(basic)+" , "+to_string(hra)+" , "+to_string(bonus)+");";
		cout << qry<<endl;
		pstmt = con->prepareStatement(qry);
			pstmt->executeUpdate();
	}
	catch (sql::SQLException e)
	{
		cout << "Invalid Username: " << e.what() << endl;
		system("pause");
		exit(1);
	}
}
void modifyemployee()
{
	system("cls");
	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;
		sql::PreparedStatement* pstmt;
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
		con->setSchema("employee");
		std::string usr;
		cout << "Enter emp_id :";
		cin >> usr;
		cout << "Enter \".\" (dot) if you dont want to make changes to data ..";
		cout << "\nEnter employee name : " << endl;
		cin >> name;
		if (name != ".")
		{
			string qry = "update emp_d set Name ='" + name + "' where Id =" + usr + ";";
			cout << qry << endl;
			pstmt = con->prepareStatement(qry);
			pstmt->executeUpdate();
		}

		cout << "\nEnter employee location : " << endl;
		cin >> location;
		if (location != ".")
		{
			string qry = "update emp_d set location ='" + location + "' where Id =" + usr + ";";
			cout << qry << endl;
			pstmt = con->prepareStatement(qry);
			pstmt->executeUpdate();
		}

		cout << "\nEnter employee basic : " << endl;
		cin >> basic;
		if (to_string(basic) != ".")
		{
			string qry = "update emp_d set Basic ='" + to_string(basic) + "' where Id =" + usr + ";";
			cout << qry << endl;
			pstmt = con->prepareStatement(qry);
			pstmt->executeUpdate();
		}

		cout << "\nEnter employee hra : " << endl;
		cin >> hra;
		if (to_string(hra) != ".")
		{
			string qry = "update emp_d set HRA ='" + to_string(hra) + "' where Id =" + usr + ";";
			cout << qry << endl;
			pstmt = con->prepareStatement(qry);
			pstmt->executeUpdate();
		}

		cout << "\nEnter employee bonus : " << endl;
		cin >> bonus;
		if (to_string(bonus) != ".")
		{
			string qry = "update emp_d set hra ='" + to_string(bonus) + "' where Id =" + usr + ";";
			cout << qry << endl;
			pstmt = con->prepareStatement(qry);
			pstmt->executeUpdate();
		}
	}
	catch (sql::SQLException e)
	{
		cout << "Invalid Username: " << e.what() << endl;
		system("pause");
		exit(1);
	}

}
void delemployee()
{
	system("cls");
	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;
		sql::PreparedStatement* pstmt;
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
		con->setSchema("employee");
		std::string usr;
		cout << "Enter emp_id :";
		cin >> usr;
		cout << "Enter \".\" (dot) if you dont want to make changes to data ..";
		if (usr != ".")
		{
			string qry = "delete from emp_d where Id =" + usr + ";";
			cout << qry << endl;
			pstmt = con->prepareStatement(qry);
			pstmt->executeUpdate();
		}
	}
	catch (sql::SQLException e)
	{
		cout << "Invalid empid: " << e.what() << endl;
		system("pause");
		exit(1);
	}
}
int main()
{
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;
	sql::PreparedStatement* pstmt;

	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
		con->setSchema("employee");
		std::string usr;
		int pwd;
		cout << "\t" << "Enter Login Details" << "\n" << endl;
		cout << "UserName:";
		cin >> usr;
		cout << "\nPassword:";
		cin >> pwd;
		string qry = "Select * from login where" + std::string(" username = '" )+ usr+"';";
		cout << qry;
		pstmt = con->prepareStatement(qry);
		res = pstmt->executeQuery();
		res->first();
		int menu;
		int pa = res->getInt(2);
		string my_str = to_string(pa);
		if (pa == pwd)
		{
			cout << "\nLogin Successful\n\n";
			while (1)
			{
				cout << "**************************Menu*************************************";
				cout << "\n1.Add Employee\n2.Modify Employee\n3.Delete From Employee\n4.Exit: " << endl;
				cout << "*******************************************************************";
				cout << "\n\nEnter Option: ";
				cin >> menu;
				switch (menu)
				{
				case 1:addemployee(); break;
				case 2:modifyemployee(); break;
				case 3:delemployee(); break;
				case 4:return 0;
				}
			}
		}
		else
		{
			cout << "Invalid Credentials";
		}
		//String^ str2 = gcnew String(my_str.c_str());
		//label3->Text = "Login Successful";
		//this->Hide();
		//MyForm1^ obj = gcnew MyForm1();
		//obj->ShowDialog();
	}
	catch (sql::SQLException e)
	{
		cout << "Invalid Username: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	//please create database "quickstartdb" ahead of time
	//stmt = con->createStatement();
	//stmt->execute("DROP TABLE IF EXISTS inventory");
	//cout << "Finished dropping table (if existed)" << endl;
	//stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
	//cout << "Finished creating table" << endl;
	//delete stmt;

	//pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)");
	///pstmt->setString(1, "banana");
	//pstmt->setInt(2, 150);
	//pstmt->execute();
	//cout << "One row inserted." << endl;

	//pstmt->setString(1, "orange");
	//pstmt->setInt(2, 154);
	//pstmt->execute();
	//cout << "One row inserted." << endl;

	//pstmt->setString(1, "apple");
	//pstmt->setInt(2, 100);
	//pstmt->execute();
	//cout << "One row inserted." << endl;

	//delete pstmt;
	//delete con;
	//system("pause");
	return 0;
}
