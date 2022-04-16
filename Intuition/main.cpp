#include <ctime>
#include <thread>

#include "hacks.h"


bool toggleGlow = false;
bool toggleBhop = false;


void Init()
{
    mem.Setup();
    mem.GetModules();
    offsets.OffsetUpdate();
}

void poly()
{
	std::srand(std::time(0));

	int count = 0;
	for (count; count < 10; count++)
	{
		int index = rand() % (6 - 0 + 1) + 0;

		switch (index)
		{
		case 0:

			__asm __volatile
			{
				sub eax, 3
				add eax, 1
				add eax, 2
			}

		case 1:

			__asm __volatile
			{
				push eax
				pop eax
			}

		case 2:

			__asm __volatile
			{
				inc eax
				dec eax
			}

		case 3:

			__asm __volatile
			{
				dec eax
				add eax, 1
			}

		case 4:

			__asm __volatile
			{
				pop eax
				push eax
			}

		case 5:

			__asm __volatile
			{
				mov eax, eax
				sub eax, 1
				add eax, 1
			}

		case 6:

			__asm __volatile
			{
				xor eax, eax
				mov eax, eax
			}


		}
	}
}

void ToggleHacks()
{
	if (GetAsyncKeyState(VK_F3) & 1)
	{
		toggleGlow = !toggleGlow;
		if (toggleGlow)
			std::cout << "Glow enabled" << std::endl;
		else
			std::cout << "Glow disabled" << std::endl;
		Sleep(100);
	}
	if (GetAsyncKeyState(VK_F4) & 1)
	{
		toggleBhop = !toggleBhop;
		if (toggleBhop)
			std::cout << "Bhop enabled" << std::endl;
		else
			std::cout << "Bhop disabled" << std::endl;
		Sleep(100);
	}
}

void DelayedHacks()
{
	while (true) {
		if (toggleGlow) {
			GlowHack();
		}
		if (toggleBhop) {
			BhopHack();
		}
		Sleep(1);
	}
}

int main()
{
	
	SetConsoleTitle("!!INTUITION!!");

	std::cout << std::endl;
	std::cout << "\t\t\t\t\t\t\tINTUITION" << std::endl << std::endl;
	std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl << std::endl;

	Init();
	Sleep(50);

	std::cout << "\nEverything is disabled by default" << std::endl;
	std::cout << "[F3] Glow" << std::endl;
	std::cout << "[F4] Bhop" << std::endl;

	std::thread delayedThread(DelayedHacks);

	while (true)
	{
		ToggleHacks();
		Sleep(50);
	}
}