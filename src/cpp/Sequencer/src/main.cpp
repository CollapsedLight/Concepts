#include <iostream>

#include "ControlDummy.h"

int main()
{
	unsigned char       InByte[10];
	unsigned char       OutByte[10];


	ControlDummy* ctrl = new ControlDummy((unsigned char*)& InByte[0], (unsigned char*)& OutByte[0]);

	for (int i = 0; i < 10; i++)
	{
		ctrl->Sequence[0]->Invoke();
		std::cout << "Press key to execute the next step" << std::endl;
		std::cin.get();
	};

	 return 1;
}
