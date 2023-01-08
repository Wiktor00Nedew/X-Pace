//
// Created by Wiktor on 26.06.2022.
//

#include "common.h"

std::map<std::string, std::string> APIErrors = {
        {"INVALID_VALIDATION", "Podane dane nie są poprawne."},
        {"INVALID_CREDENTIALS", "Nieprawidłowy email lub hasło."},
        {"NO_USERNAME", "Podaj nazwę użytkownika."},
        {"NO_EMAIL", "Podaj email."},
        {"NO_PASSWORD", "Podaj hasło."},
        {"SERVER_ERROR", "Błąd serwera."},
        {"SERVER_UNREACHABLE", "Serwer niedostępny."},
        {"NO_PERMISSIONS", "Brak uprawnień administratora."},
        {"UNAUTHORIZED", "Odmowa dostępu."},
        {"APPLICATION_ERROR", "Błąd aplikacji."},
        {"USER_NOT_FOUND", "Odmowa dostępu."},
        {"ACCOUNT_DISABLED", "Odmowa dostępu."},
        {"EMAIL_IN_USE", "Email jest zajęty."},
        {"USERNAME_IN_USE", "Nazwa użytkownika jest zajęta."},
        {"TEAM_NOT_FOUND", "Nie znaleziono zespołu."},
        {"USER_ALREADY_REGISTERED", "Użytkownik już należy do zespołu."},
        {"DIRECTORY_NOT_IN_TEAM", "Folder nie należy do tego zespołu."},
        {"PAGE_NOT_FOUND", "Nie znaleziono strony."},
        {"DIRECTORY_NOT_FOUND", "Nie znaleziono folderu."},
        {"PAGE_NOT_IN_TEAM", "Strona nie należy do tego zespołu."},
        {"USER_NOT_IN_TEAM", "Użytkownik nie należy do tego zespołu."},
        {"MODERATOR_ALREADY_REGISTERED", "Użytkownik już jest moderatorem."},
        {"OWNER_ALREADY_REGISTERED", "Użytkownik już jest właścicielem."},
        {"PERMISSION_NOT_FOUND", "Nie znaleziono permisji."},
        {"NO_NAME", "Podaj nazwę."},
        {"NO_TOKEN", "Podaj kod dołączenia."},
        {"NO_ERROR", ""}
};