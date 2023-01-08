#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

class Picture
{

public:

	vector<pair<vector<double>, vector<double>>> data_set;

	void read_data_set();

	void read_test_data_set();

private:

	int reverseInt(int i);

	void read_data_set_pictures();
	void read_data_set_labels();

	void read_test_data_set_pictures();
	void read_test_data_set_labels();

};
