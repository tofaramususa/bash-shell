The work to be done:
Have a global variable for exit status and have the messages ready for different codes and messages, initiate the value to zero
Handle the signals
Create the int main and also the interface to bring the execution with the parsing, display the prompt too
Add the history
Bring it all together and have a working shell as soon as possible, thats the most important thing
Implement --> && and || with parenthesis for priorities and also the wildcard

Tests:
Use top to check for memory leaks and usage
Need to understand fork and execve
Make sure to when l return the prompt l free everythin and have the proper error handling;
Handle calling the BUILTINS;
Handle ENVIRONMENT management - env, setenv, unsetenv, also take note of this the path of the executable
PATH Management - 
COMMAND LINE MANAGEMENT - Spaces and tabulations and 
HANDLE THE SIGNALS -

Note we need to check for permission rights before we check for execution okay

BONUS:
Do pattern matching for * and currentworkingdirectory -- have an identifier for words that need pattern matching and then have function to does the pattern matching for each word and then add the words that match the pattern and add them to command list, which l think l will do if as tokens after syntax checks
Do the AND, OR operations which will require me to handle and look for that || and && then for the commands l need to add a flag
that checks if && is before if so then check previous command. Also check if || the set a flag to say this is part of the && command. We likely need flag for both AND_ID is 1 or 2. then OR_ID is 1 or 2

zsh: no matches found: *.c

l like this:
			initwarm();

			if (getline()) 
				if (i = parse())
					execute(i);

THE MOST IMPORTANT THING IS LAUNCH, MVP, HAVING A WORKING PROTOTPYE AND VERSION. THEN BECAUSE YOU HAVE APPLIED THE ENGINEERING METHODS
OF MODULARITY, SEPERATION OF CONCERNS, THEN IT WILL BE EASY TO ADD FEATURE. ALSO THE PRINCIPLE OF TDD, HAVE A WORKING VERSION FIRST