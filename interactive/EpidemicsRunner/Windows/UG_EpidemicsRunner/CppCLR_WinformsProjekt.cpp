#define _ITERATOR_DEBUG_LEVEL 0

#include "pch.h"
#include<msclr\marshal_cppstd.h> //if it is placed elsewhere errors occur, see https://stackoverflow.com/questions/4000663/issue-in-compiling-with-marshal-h-error-c2872-iserviceprovider-ambiguous
using namespace System;

//Also, Unicode support was disabled due to errors in Constrained Optimization https://stackoverflow.com/questions/1319461/how-do-i-turn-off-unicode-in-a-vc-project

//int main(array<System::String ^> ^args)
//{
//    return 0;
//}

#include "Form1.h"

using namespace System::Windows::Forms;

[STAThread]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CppCLRWinformsProjekt::Form1()); 
	return 0;
}