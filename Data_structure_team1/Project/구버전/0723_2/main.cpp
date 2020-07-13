#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>

using namespace std;

#include "customer.h"


vector<string> csv_read_row(istream &file, char delimeiter);

int main() {
	ifstream file("info.csv");

	vector<customer> customer_list;
	if (file.fail())
		return (cout << "파일존재x" << endl) && 0;
	vector<string> row = csv_read_row(file, ',');
	while (file.good()) { // file이 끝날때까지 반복

		row = csv_read_row(file, ',');
		if (!row[0].find("#"))
			continue;
		else {
			customer temp;
			temp.set(row);
			customer_list.push_back(temp);			
		}
	}
	//for (int i = 0; i < customer_list.size(); i++) //회원 정보 출력
	//	customer_list[i].print();
	file.close();


	// 회원정보는 customer_list에 vector 형식으로 담겨있습니다! 

	//1. 가장 회원을 많이 확보한 트레이너는? ( 지현)
	//2. 가장 훈련 성과가 좋은 트레이너는?
	//3. 가장 출석률이 좋은 회원은?
	//5. 가장 등록이 많은/적은 달은?
	//6. 가장 오래된 회원은?
	//7. 구매 상품이 가장 가까운 시간 내에 종료하는 회원은?
	//8. 전월 대비 가장 등록률이 떨어지는 달은?
	//11. PT를 받는 회원 중에 라커를 사용하지 않는 회원은? (정연)
	//16. 운동 달성률이 갖아 높은/낮은 회원은?
	//19. PT를 가장 많이/ 적게이용하는 연령대는?(유진)
	
	cout << "\n============================= 1조 ====================================\n" << endl;
	q01(customer_list);

	q02(customer_list);

	q07(customer_list);

	//q13(customer_list);
	
	//q16(customer_list);

	//q19(customer_list);
	return 0;
}


vector<string> csv_read_row(istream &file, char delimiter) {
	stringstream ss;
	bool inquotes = false;
	vector<string> row;

	while (file.good()) {
		char c = file.get();

		if (!inquotes  &&  c == '"')
			inquotes = true;
		else if (inquotes  &&  c == '"') {
			if (file.peek() == '"')
				ss << (char)file.get();
			else
				inquotes = false;
		}
		else if (!inquotes  &&  c == delimiter) {
			row.push_back(ss.str());
			ss.str("");
		}
		else if (!inquotes && (c == '\r' || c == '\n')) {
			if (file.peek() == '\n')
				file.get();
			row.push_back(ss.str());
			return row;
		}
		else
			ss << c;

	}

}