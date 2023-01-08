#include <iostream>
#include <fstream>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "Picture.h"
#include "SmartPaint.h"
#include "Network.h"

using namespace std;

/////////////////////////

const string sost = "DRAW"; // "LEARN" "DRAW" "TEST"

/////////////////////////

vector<int> sloi{ 28 * 28, 32, 16, 16, 10 };

Network diana("networks\\2_gen_12.txt");

int main()
{

	cout.setf(ios::fixed);
	cout.precision(2);
	srand(time(NULL));

	Picture picture;

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
				diana.save_network_as("networks\\2_gen_13.txt");
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