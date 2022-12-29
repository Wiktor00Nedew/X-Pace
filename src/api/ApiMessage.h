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
            }
            else if(status == 500){ // internal server error
                data = {
                        {"key", "APPLICATION_ERROR"}
                };
            }
        }
    }
};