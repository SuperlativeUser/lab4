#include "console.h"
#include "set"
#include <iostream>

//ƒавайте предположим, что нам не важно количество пам€ти,
//выдел€емое под программу, но мы ратуем за быстродействие (покрайней мере хоть какое-то)
int main()
{
	Console console;
	console.onConsoleCall();

    return 0;
}

