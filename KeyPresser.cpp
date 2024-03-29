#include <stdio.h>
#include <windows.h>
#include <ctime>
#include <string>

int main(int argc, char* argv[]) {
	// 파라미터 1개 (지연 시간) 입력 받기
	if (argc != 3) {
		printf("사용법: %s <반복 주기 (초)> <키>\n", argv[0]);
		printf(" 키: 알파벳, 숫자, 특수문자, VK_RETURN");
		return 1;
	}

	int delayTime = atoi(argv[1]);
	std::string keystring(argv[2]);
	printf("반복 주기 (%d초)\n출력문자 (%s)\nCtrl + C 를 누르면 종료됩니다.\n", delayTime, keystring.c_str());
	int inputkey;
	if (keystring == "VK_RETURN") {
		inputkey = VK_RETURN;
	}
	else {

		inputkey = argv[2][0];
	}


	while (true) {

		// 지연 시간 동안 잠시 대기
		Sleep(delayTime * 1000); // 1초 단위로 변환
		// 현재 시간 정보를 담을 tm 구조체
		tm curTime;

		// 현재 시간을 가져와 tm 구조체에 저장
		time_t t = time(NULL);
		localtime_s(&curTime, &t);

		// 현재 시간 출력
		printf("%d년 %d월 %d일 %d시 %d분 %d초 %s\n",
			curTime.tm_year + 1900, curTime.tm_mon + 1, curTime.tm_mday,
			curTime.tm_hour, curTime.tm_min, curTime.tm_sec, argv[2]);

		INPUT inputs[4] = {};
		ZeroMemory(inputs, sizeof(inputs));

		inputs[0].type = INPUT_KEYBOARD;
		inputs[0].ki.wVk = VK_RETURN;

		inputs[1].type = INPUT_KEYBOARD;
		inputs[1].ki.wVk = VK_RETURN;
		inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

		UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
	}

	return 0;
}
