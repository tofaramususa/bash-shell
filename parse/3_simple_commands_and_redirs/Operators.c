


// Handling the parenthesiss:
// 1. Start at ft_strtok. We need to split on && and ||. Handle the case where we have one &
// 2. Then assign token names AND and OR
// 3. We seperate commands on PIPES, AND, OR
// 4. But as we pass a flag to say this in part of AND, OR OPERATOR. Also that these are in parenthesis
// -- But pipe takes precedence so we go through commands on PIPE then we go and checke 
// 5. Then on execution we give priority to the commands with parenthesis flag we try to execute those;
// 6. Then for each command before we execute we check the is it part of && is so check check the status code,
// Then is its part of OR then execute if not then we do not execute;
// THIS IS no about the execution it self but about the order in which we execute commands
// Then on execution we need to check 