#include <Spore.hpp>

using namespace Spore;

int main(int argc, char** argv)
{
	_Spore spore;
	spore.Init();
	spore.PreProcessing();
	spore.Runtime();
	spore.Terminate();
}