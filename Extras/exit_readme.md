// g_error_status depands of multiple things,
// If the commande work, 0
// If a commande exist and fail cause of the arg, 1
// If a commande exist and you dont have the permission 126
// If a commande doesn't exist 127
// If a signal Kill or interrupte the commande 127 + signal
// If error parsing 2
// Exit status come with Error message in your terminal, don't forget that the error fd is 2
// (putstr_fd)
