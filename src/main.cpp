#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "Picture.h"
#include "SmartPaint.h"
#include "Network.h"

using namespace std;

/////////////////////////

const string sost = "DRAW"; // "LEARN" "DRAW" "TEST" "DAWN" "SUPER TEST" "BIG WORK"

/////////////////////////

string path_to_network = "../networks/network_16_16";

vector<int> sloi{ 28 * 28,20, 10 };




// Network diana(path_to_network + "weights_to_network.txt");
// Network diana(sloi);
Network diana("../networks/magic.txt");


int main()
{


	cout << "HI" << endl;

	srand(time(NULL));

	Picture picture;

	

	ofstream testf(path_to_network + "result/final_result.csv", ofstream::out | ofstream::app);
	ofstream trainingf(path_to_network + "result/training_result.csv", ofstream::out | ofstream::app);
	ofstream errorf(path_to_network + "result/global_error.csv", ofstream::out | ofstream::app);

	cout.setf(ios::fixed);
	cout.precision(8);

	testf.setf(ios::fixed);
	testf.precision(8);

	trainingf.setf(ios::fixed);
	trainingf.precision(8);

	errorf.setf(ios::fixed);
	errorf.precision(8);

	if (sost == "BIG WORK")
	{
		diana.learn_rate = 0.0002;
		picture.read_test_data_set();
		diana.examples = picture.data_set;
		picture.read_data_set();

		int st = 0;

		while (true)
		{
			if (st % 10 == 0)
			{
				diana.save_network_as(path_to_network + "weights_to_network.txt");

				cout << "I SAVE IT!!\n";

				////

				int correct_answer = 0;

				for (int i = 0; i < picture.data_set.size(); ++i)
				{
					diana.value[0] = picture.data_set[i].first;
					diana.calculate_network();
					int network_ans = 0;
					for (int j = 1; j < 10; ++j)
					{
						if (diana.value.back()[j] > diana.value.back()[network_ans])
						{
							network_ans = j;
						}
					}

					int picture_ans = 0;
					for (int j = 1; j < 10; ++j)
					{
						if (picture.data_set[i].second[j] > picture.data_set[i].second[picture_ans])
						{
							picture_ans = j;
						}
					}

					if (network_ans == picture_ans)
					{
						++correct_answer;
					}

				}

				double testing_result = 100 * (correct_answer + 0.0) / (picture.data_set.size() + 0.0);

				testf << st << "; " << testing_result << endl;

				////

				int learn_correct_answer = 0;

				for (int i = 0; i < diana.examples.size(); ++i)
				{
					diana.value[0] = diana.examples[i].first;
					diana.calculate_network();
					int network_ans = 0;
					for (int j = 1; j < 10; ++j)
					{
						if (diana.value.back()[j] > diana.value.back()[network_ans])
						{
							network_ans = j;
						}
					}

					int picture_ans = 0;
					for (int j = 1; j < 10; ++j)
					{
						if (diana.examples[i].second[j] > diana.examples[i].second[picture_ans])
						{
							picture_ans = j;
						}
					}

					if (network_ans == picture_ans)
					{
						++learn_correct_answer;
					}

				}

				double learn_testing_result = 100 * (learn_correct_answer + 0.0) / (diana.examples.size() + 0.0);

				trainingf << st << "; " << learn_testing_result << endl;

				////

			}

			

			errorf << st << "; " << diana.global_error << endl;
			cout << st << "; " << diana.global_error << endl;
			
			++st;

			diana.backPropagate();
		}


	}

	if (sost == "SUPER TEST")
	{
		picture.read_data_set();
		Picture test_picture;
		test_picture.read_test_data_set();
		long long st = 81;

		diana.learn_rate = 0.00001;

		ofstream testf("../networks/3_gen/test.txt", ofstream::out | ofstream::app);
		ofstream trainingf("../networks/3_gen/training.txt", ofstream::out | ofstream::app);

		diana.examples = picture.data_set;

		while (true)
		{
			cout << "+";
			if (st % 10 == 0)
			{	
				int correct_answer = 0;


				for (int i = 0; i < picture.data_set.size(); ++i)
				{
					diana.value[0] = picture.data_set[i].first;
					diana.calculate_network();
					int network_ans = 0;
					for (int j = 1; j < 10; ++j)
					{
						if (diana.value.back()[j] > diana.value.back()[network_ans])
						{
							network_ans = j;
						}
					}

					int picture_ans = 0;
					for (int j = 1; j < 10; ++j)
					{
						if (picture.data_set[i].second[j] > picture.data_set[i].second[picture_ans])
						{
							picture_ans = j;
						}
					}


					if (network_ans == picture_ans)
					{
						++correct_answer;
					}

					

					

				}

				double ians = (correct_answer + 0.0) / (picture.data_set.size() + 0.0) * 100;
				trainingf << st << " " << ians << endl;
			}

			if (st % 10 == 0)
			{
				int correct_answer = 0;


				for (int i = 0; i < test_picture.data_set.size(); ++i)
				{
					diana.value[0] = test_picture.data_set[i].first;
					diana.calculate_network();
					int network_ans = 0;
					for (int j = 1; j < 10; ++j)
					{
						if (diana.value.back()[j] > diana.value.back()[network_ans])
						{
							network_ans = j;
						}
					}

					int picture_ans = 0;
					for (int j = 1; j < 10; ++j)
					{
						if (test_picture.data_set[i].second[j] > test_picture.data_set[i].second[picture_ans])
						{
							picture_ans = j;
						}
					}


					if (network_ans == picture_ans)
					{
						++correct_answer;
					}



				}
				double ians = (correct_answer + 0.0) / (test_picture.data_set.size() + 0.0) * 100;
				testf << st << " " << ians << endl;
			}

			if (st % 10 == 0)
			{
				diana.save_network_as("../networks/3_gen/1.txt");
				cout << "I SAVE IT!!\n";
			}

			++st;
			cout << diana.global_error << endl;

			diana.backPropagate();
		}

	}

	if (sost == "DAWN")
	{
		picture.read_data_set();
		SmartPaint paint;
		int st = 0;
		int i = 0;

		while (true)
		{
			if (st >= 600)
			{
				st = 0;
				i = (i + 1) % picture.data_set.size();
			}

			++st;

			for (int j = 0; j < 28; ++j)
			{
				for (int l = 0; l < 28; ++l)
				{
					paint.mat[j][l] = picture.data_set[i].first[j * 28 + l];
				}
			}
			paint.next_tick();
			diana.value[0] = paint.get_mat();
			diana.calculate_network();
			paint.set_chances(diana.value.back());
		}
		
	}

	if (sost == "DRAW") {
		SmartPaint paint;

		while (true)
		{
			paint.next_tick();
			diana.value[0] = paint.get_mat();
			diana.calculate_network();
			paint.set_chances(diana.value.back());
		}
	}

	if (sost == "LEARN")
	{

		diana.learn_rate = 0.00002;

		picture.read_data_set();

		cout << "I READ DATA SET\n";
		cout << "VSEGO STOKA : " << picture.data_set.size();

		diana.examples = picture.data_set;

		//for (int i = 0; i < 4000; ++i)
		//{
		//	diana.examples.push_back(picture.data_set[i]);
		//}

		int st = 0;

		while (true)
		{
			if (st >= 10)
			{
				diana.save_network_as("../networks/2_gen_13.txt");
				st = 0;
				cout << "I SAVE IT!!\n";
			}
			++st;
			cout << diana.global_error << endl;

			diana.backPropagate();
		}

		return 0;

	}

	if (sost == "TEST")
	{
		picture.read_test_data_set();

		int correct_answer = 0;

		vector<pair<int, int>> ch (10, { 0, 0 });

		for (int i = 0; i < picture.data_set.size(); ++i)
		{
			diana.value[0] = picture.data_set[i].first;
			diana.calculate_network();
			int network_ans = 0;
			for (int j = 1; j < 10; ++j)
			{
				if (diana.value.back()[j] > diana.value.back()[network_ans])
				{
					network_ans = j;
				}
			}

			int picture_ans = 0;
			for (int j = 1; j < 10; ++j)
			{
				if (picture.data_set[i].second[j] > picture.data_set[i].second[picture_ans])
				{
					picture_ans = j;
				}
			}

			++ch[picture_ans].second;

			if (network_ans == picture_ans)
			{
				++correct_answer;
				++ch[picture_ans].first;
			}

		}

		cout << "RESULT : " << correct_answer << " / " << picture.data_set.size() << endl << endl;

		for (int i = 0; i < 10; ++i)
		{
			cout << i << " : " << ch[i].first << " / " << ch[i].second << endl;
		}

		return 0;
	}

}