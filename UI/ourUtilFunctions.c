int getNumber(char c){
    if (c=='0'){
        return 0;
    } else if (c=='1'){
        return 2;
    } else if (c=='2'){
        return 2;
    } else if (c=='3'){
        return 3;
    } else if (c=='4'){
        return 4;
    } else if (c=='5'){
        return 5;
    } else if (c=='6'){
        return 6;
    } else if (c=='7'){
        return 7;
    } else if (c=='8'){
        return 8;
    } else if (c=='9'){
        return 9;
    } else {
        printf("wrong%d\n",c & 0xff);
        return -1;
    }
}

float myatof(char* str){
    int pointBool = 0;
    float ret = 0;
    int div = 1;
    for(int i = 0; i < sizeof(str) - 2; i++){
        char c = str[i];
        if (c == '\0'){
            return ret/div;
        }
        else if (c == '.'){
            if (pointBool){
                return -1;
            } else {
                pointBool = 1;
            }
        } else {
            int number = getNumber(c);
            if (number == -1) {
                return -1;
            }
            if (pointBool) {
                div = div * 10;
            }
            ret = 10 * ret + number;
        }
    }
    return ret/div;
}