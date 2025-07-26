#pragma once
#include "Headers.h"
class SignUpAndSignIn
{
public:

	void MakeNewAccount();
	void SaveAccountToFile(string& username, string& hashedPassword);
	int SignInToAccount();
};

