#pragma once

char* fed;
char* lockedRegions;
int regindex;
bool RequiresFeed;

class KernelCore {
private:
    
public:
    
    static void Initialize() {
        regindex = 0;
        lockedRegions = "";
        fed = "";
    }
    static bool Call(int ID, char* CALLARG, char* DAT) {
        RequiresFeed = false;
        switch(ID) {
            case 0: {
                // memlock
                if(CALLARG == "lock") {
                    lockedRegions[regindex++] = DAT[0];
                    lockedRegions[regindex++] = DAT[1];
                    return true;
                } else if(CALLARG == "unlock") {
                    for(int i = 0; lockedRegions[i] != '\0'; i++) {
                        if(lockedRegions[i] == DAT[0] && lockedRegions[i] == DAT[1]) {
                            int rep = 2;
                        doagain:
                            for(int y = i; y < regindex; y++) {
                                if(lockedRegions[y+1] == '\0') break;
                                char temp = lockedRegions[y];
                                lockedRegions[y] = lockedRegions[y+1];
                            }
                            if(rep-- != 0) goto doagain;
                            return true;
                        }
                    }
                    return false;
                }
            } break;
            default: 
                return false;
        }
    }
    static void Feed(char* F) {
        RequiresFeed = false;
    }
};