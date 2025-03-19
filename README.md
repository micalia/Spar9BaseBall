# Spar9BaseBall

https://youtu.be/bOyeW-HWNtU

필수 기능 구현 사항
- 판정 로직(S/B/OUT 계산), 승리, 무승부, 게임 리셋<br>
void AMyGameMode::ProcessPlayerInput(const FString& PlayerInput) 함수에 작성
![image](https://github.com/user-attachments/assets/7585117b-4cbe-4383-9e99-f0feebe464b5)
- 난수 생성 로직 구현<br>
TArray<int32> UMyTestCppLib::GetRandom() 함수에 작성
![image](https://github.com/user-attachments/assets/0089b989-b7f1-40c8-a28b-5e76dff8120c)
- 시도 횟수 및 상태 관리<br>
시도횟수와 스트라이크, 볼 횟수는 GameMode에서 관리 <br>
AMyGameMode.h에서 확인 가능<br>
![image](https://github.com/user-attachments/assets/4c1b6e0e-8cb5-4836-8e62-9069e838cde9)
- C++ 라이브러리 작성<br>
MyTestCppLib.cpp 클래스에서 확인 가능<br>
![image](https://github.com/user-attachments/assets/67d341a1-0bea-4d7d-a4d8-0bb71bce92ff)
