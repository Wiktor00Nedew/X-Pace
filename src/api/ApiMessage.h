//
// Created by Wiktor on 26.06.2022.
//

#pragma once
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
            data = apiResponse;
        }
        else{
            type = Error;
            if (apiResponse["status"] == 400) { // invalid validation
                data = {
                        {"key", "INVALID_VALIDATION"}
                };
            }
            else if(apiResponse["status"] == 401){
                data = {
                        {"key", "UNAUTHORIZED"}
                };
            }
            else if(apiResponse["status"] == 404){
                data = {
                        {"key", "SERVER_UNREACHABLE"}
                };
            }
            else if(apiResponse["status"] == 409){ // internal server error
                if(apiResponse["secondaryCode"] == 1003){ // route not found
                    data = {
                            {"key", "USER_NOT_FOUND"}
                    };
                }
                else if(apiResponse["secondaryCode"] == 1004){ // route not found
                    data = {
                            {"key", "ACCOUNT_DISABLED"}
                    };
                }
            }
        }
    }
};