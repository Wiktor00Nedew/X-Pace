//
// Created by Wiktor on 26.06.2022.
//

#include "common.h"

std::map<std::string, std::string> APIErrors = {
        {"INVALID_VALIDATION", "Podane dane nie są poprawne."},
        {"INVALID_CREDENTIALS", "Nieprawidłowy email lub hasło."},
        {"NO_EMAIL", "Podaj email."},
        {"NO_PASSWORD", "Podaj hasło."},
        {"SERVER_ERROR", "Błąd serwera."},
        {"SERVER_UNREACHABLE", "Serwer niedostępny."},
        {"NO_PERMISSIONS", "Brak uprawnień administratora."},
        {"UNAUTHORIZED", "Odmowa dostępu."},
        {"APPLICATION_ERROR", "Błąd aplikacji."},
        {"USER_NOT_FOUND", "Odmowa dostępu."},
        {"ACCOUNT_DISABLED", "Odmowa dostępu."},
        {"NO_ERROR", ""}
};