//Timer header file
//See gitHub for changes
//Created by: Odin Adema

bool   Timer(long start, int interval){
    long currentMillis = millis();
    if(currentMillis - start >= interval){
        return true;
    }else{
        return false;
    }
}