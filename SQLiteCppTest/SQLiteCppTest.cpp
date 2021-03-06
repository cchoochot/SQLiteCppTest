// SQLiteCppTest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <SQLiteCpp\Database.h>
#include <SQLiteCpp\Transaction.h>

int main()
{
	try {

		// create db if necessary
		SQLite::Database db("d:/example.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

		if (!db.tableExists("test")) {
			db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT, size INTEGER)");
		}



		// insert data
		SQLite::Transaction transaction(db);
		db.exec("INSERT INTO test VALUES(1, \"Value\", 8)");
		db.exec("INSERT INTO test VALUES(2, \"Value\", 2)");
		db.exec("INSERT INTO test VALUES(3, \"Value\", 11)");
		db.exec("INSERT INTO test VALUES(4, \"Value\", 15)");
		db.exec("INSERT INTO test VALUES(5, \"Value\", 6)");
		db.exec("INSERT INTO test VALUES(6, \"Value\", 7)");
		transaction.commit();


		// select data
		SQLite::Statement query(db, "SELECT * FROM test WHERE size > ?");

		query.bind(1, 6);

		while (query.executeStep()) {
			auto id = query.getColumn(0);
			auto value = query.getColumn(1);
			auto size = query.getColumn(2);

			std::cout << "Row: " << id << ", " << value << ", " << size << std::endl;
		}
	}
	catch (std::exception& ex) {
		std::cout << "exception " << ex.what() << std::endl;
	}

	return 0;
}

