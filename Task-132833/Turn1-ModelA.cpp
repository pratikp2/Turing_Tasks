#include <iostream>
#include <string>
#include <lmdb.h>

// Step 1: Install LMDB library
// sudo apt-get update
// sudo apt-get install liblmdb-dev

int main() {
	// Step 2: Compile the code
	// g++ -std=c++11 lmdb_example.cpp -llmdb -o lmdb_example

	const char* db_path = "./mydb";
	MDB_env* env;
	MDB_dbi dbi;
	int rc;

	// Create the LMDB environment
	rc = mdb_env_create(&env);
	if (rc) {
		std::cerr << "mdb_env_create: " << mdb_strerror(rc) << std::endl;
		return 1;
	}

	// Set the maximum database size to 1GB
	rc = mdb_env_set_mapsize(env, 1024 * 1024 * 1024);
	if (rc) {
		std::cerr << "mdb_env_set_mapsize: " << mdb_strerror(rc) << std::endl;
		mdb_env_close(env);
		return 1;
	}

	// Open the database environment
	rc = mdb_env_open(env, db_path, 0, 0);
	if (rc) {
		std::cerr << "mdb_env_open: " << mdb_strerror(rc) << std::endl;
		mdb_env_close(env);
		return 1;
	}

	// Create a database handle
	rc = mdb_env_create_db(env, &dbi, 0);
	if (rc) {
		std::cerr << "mdb_env_create_db: " << mdb_strerror(rc) << std::endl;
		mdb_env_close(env);
		return 1;
	}

	MDB_txn* txn;
	rc = mdb_txn_begin(env, NULL, 0, &txn);
	if (rc) {
		std::cerr << "mdb_txn_begin: " << mdb_strerror(rc) << std::endl;
		mdb_env_close(env);
		return 1;
	}

	// Example usage: storing and retrieving strings
	std::string key = "product_id_123";
	std::string value = "Some detailed information about the product";

	MDB_val mdb_key, mdb_value;