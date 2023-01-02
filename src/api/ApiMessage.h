//
// Created by Wiktor on 26.06.2022.
//

#pragma once

#include <QDebug>
#include "../utilities/json.hpp"

struct ApiMessage{
    enum Type{
        NoError = 0,
        Error = 1
    };

    Type type;
    nlohmann::json data;

    ApiMessage(){
        type = Error;
        data = {
                {"key", "APPLICATION_ERROR"}
        };
    }

    // messageData = data / error message [key]
    ApiMessage(nlohmann::json apiResponse, int status){
        qDebug() << QString::fromStdString(apiResponse.dump());
        if(status >= 200 && status <= 299){
            type = NoError;
            //qDebug() << QString::fromStdString(to_string(apiResponse));
            data = apiResponse;
            //qDebug() << "ajdalfjladjfl";
        }
        else{
            type = Error;
            if (status == 400) { // invalid validation
                data = {
                        {"key", "INVALID_VALIDATION"}
                };
            }
            else if(status == 401){ // unauthorized
                data = {
                        {"key", "UNAUTHORIZED"}
                };
            }
            else if(status == 404){ // server unreachable
                data = {
                        {"key", "SERVER_UNREACHABLE"}
                };
            }
            else if(status == 409){ // conflict
                if(apiResponse["secondaryCode"] == 1001){ // email in use
                    data = {
                            {"key", "EMAIL_IN_USE"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1002){ // username in use
                    data = {
                            {"key", "USERNAME_IN_USE"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1003){ // user not found
                    data = {
                            {"key", "USER_NOT_FOUND"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1004){ // account disabled
                    data = {
                            {"key", "ACCOUNT_DISABLED"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1005){ // account disabled
                    data = {
                            {"key", "TEAM_NOT_FOUND"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1006){ // account disabled
                    data = {
                            {"key", "USER_ALREADY_REGISTERED"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1007){ // account disabled
                    data = {
                            {"key", "DIRECTORY_NOT_IN_TEAM"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1008){ // account disabled
                    data = {
                            {"key", "PAGE_NOT_FOUND"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1009){ // account disabled
                    data = {
                            {"key", "DIRECTORY_NOT_FOUND"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1010){ // account disabled
                    data = {
                            {"key", "PAGE_NOT_IN_TEAM"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1011){ // account disabled
                    data = {
                            {"key", "USER_NOT_IN_TEAM"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1012){ // account disabled
                    data = {
                            {"key", "MODERATOR_ALREADY_REGISTERED"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1013){ // account disabled
                    data = {
                            {"key", "OWNER_ALREADY_REGISTERED"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1014){ // account disabled
                    data = {
                            {"key", "PERMISSION_NOT_FOUND"}
                    };
                }
            }
            else if(status == 500){ // internal server error
                data = {
                        {"key", "APPLICATION_ERROR"}
                };
            }
        }
    }
};