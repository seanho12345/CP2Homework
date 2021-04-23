#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *readFile(){
    int valid=1,i;
    char filename[128]={0};
    FILE *ptr = NULL;
    fgets(filename,128,stdin);
    filename[strlen(filename)-1] = 0;
    for(i=strlen(filename)-1;i>=0;i--){
        if(filename[i] == '.'){
            break;
        }
    }
    if(i == -1){
        valid = 0;
    }else{
        i++;
        if(strlen(filename) - i != 3){
            valid = 0;
        }else{
            char type[3];
            int k=0;
            for(i; i<strlen(filename);i++){
                type[k] = filename[i];
                k++;
            }
            if(strncmp(type,"csv",3) != 0){
                valid = 0;
            }
        }
    }
    if(valid == 1){
        return fopen(filename,"r");
    }else{
        return NULL;
    }
}

typedef struct{
    char name[20];
    int scores,rcard;
    int homewin,awaywin;
    int win,draw,lose;
    int goal,goala;
    int seasonpoint;
}teamdata;
typedef struct{
    struct _date{
        int yr,mo,date;
    }date;
    char home[20],away[20];
    int homegoal,awaygoal,homered,awayred;
    int result;
}matchdata;

teamdata team_default = {
    .name = {0},
    .scores = 0, .rcard = 0,
    .homewin = 0, .awaywin = 0,
    .win = 0, .lose = 0, .draw = 0,
    .goal = 0, .goala = 0,
    .seasonpoint = 0
};
matchdata match_default = {
    .date.yr = 0, .date.mo = 0, .date.date = 0,
    .home = {0}, .away = {0},
    .homegoal = 0, .awaygoal = 0, .homered = 0, .awayred = 0,
    .result = 0
};
int main(){
    FILE *fptr = NULL;
    printf("Please open a season record: ");
    fptr = readFile();
    
    if(fptr == NULL){
        printf("Unable to read file\n");
    }else{
        teamdata team[20] = {team_default};
        matchdata bestgap = match_default;
        int maxgap = 0,teamnum = -1;
        char tmpstr[128]={0};
        fgets(tmpstr,128,fptr);
        while(fgets(tmpstr,128,fptr) != NULL){
            matchdata match = match_default;
            int lencount = 0,commacount = 0;
            int pos = 0;
            for(pos; tmpstr[pos] != '-'; pos++){
                match.date.yr *= 10;
                match.date.yr += tmpstr[pos] - '0';
            }
            pos++;
            for(pos; tmpstr[pos] != '-'; pos++){
                match.date.mo *= 10;
                match.date.mo += tmpstr[pos] - '0';
            }
            pos++;
            for(pos; tmpstr[pos] != ','; pos++){
                match.date.date *= 10;
                match.date.date += tmpstr[pos] - '0';
            }
            pos++;
            for(pos; tmpstr[pos] != ','; pos++){
                match.home[lencount] = tmpstr[pos];
                lencount++;
            }
            match.home[lencount] = '\0';
            lencount = 0;
            pos++;
            for(pos; tmpstr[pos] != ','; pos++){
                match.away[lencount] = tmpstr[pos];
                lencount++;
            }
            match.away[lencount] = '\0';
            lencount = 0;
            pos++;
            for(pos; tmpstr[pos] != ','; pos++){
                match.homegoal *= 10;
                match.homegoal += tmpstr[pos] - '0';
            }
            pos++;
            for(pos; tmpstr[pos] != ','; pos++){
                match.awaygoal *= 10;
                match.awaygoal += tmpstr[pos] - '0';
            }
            pos++;
            if(tmpstr[pos] == 'H'){
                match.result = 1;
            }else if(tmpstr[pos] == 'D'){
                match.result = 0;
            }else if(tmpstr[pos] == 'A'){
                match.result = -1;
            }
            pos++;
            commacount = 15;
            while(commacount > 0){
                if(tmpstr[pos] == ','){
                    commacount--;
                }
                pos++;
            }
            for(pos; tmpstr[pos] != ','; pos++){
                match.homered *= 10;
                match.homered += tmpstr[pos] - '0';
            }
            pos++;
            for(pos; tmpstr[pos] != 13; pos++){
                match.awayred *= 10;
                match.awayred += tmpstr[pos] - '0';
            }
            if(abs(match.homegoal - match.awaygoal) > maxgap){
                maxgap = abs(match.homegoal - match.awaygoal);
                bestgap = match;
            }
            int found = -1;
            for(int i=0; i<=teamnum; i++){
                if(strcmp(match.home,team[i].name) == 0){
                    found = i;
                }
            }
            if(found == -1){
                teamnum++;
                strcpy(team[teamnum].name,match.home);
                team[teamnum].scores += match.homegoal;
                team[teamnum].goal += match.homegoal;
                team[teamnum].goala += match.awaygoal;
                team[teamnum].rcard += match.homered;
                if(match.result == 1){
                    team[teamnum].homewin++;
                    team[teamnum].seasonpoint += 3;
                    team[teamnum].win++;
                }else if(match.result == 0){
                    team[teamnum].seasonpoint++;
                    team[teamnum].draw++;
                }else{
                    team[teamnum].lose++;
                }
            }else{
                team[found].scores += match.homegoal;
                team[found].rcard += match.homered;
                team[found].goal += match.homegoal;
                team[found].goala += match.awaygoal;
                if(match.result == 1){
                    team[found].homewin++;
                    team[found].seasonpoint += 3;
                    team[found].win++;
                }else if(match.result == 0){
                    team[found].seasonpoint++;
                    team[found].draw++;
                }else{
                    team[found].lose++;
                }
            }
            found = -1;
            for(int i=0; i<=teamnum; i++){
                if(strcmp(match.away,team[i].name) == 0){
                    found = i;
                    break;
                }
            }
            if(found == -1){
                teamnum++;
                strcpy(team[teamnum].name,match.away);
                team[teamnum].scores += match.awaygoal;
                team[teamnum].rcard += match.awayred;
                team[teamnum].goal += match.awaygoal;
                team[teamnum].goala += match.homegoal;
                if(match.result == -1){
                    team[teamnum].awaywin++;
                    team[teamnum].seasonpoint += 3;
                    team[teamnum].win++;
                }else if(match.result == 0){
                    team[teamnum].seasonpoint++;
                    team[teamnum].draw++;
                }else{
                    team[teamnum].lose++;
                }
            }else{
                team[found].scores += match.awaygoal;
                team[found].rcard += match.awayred;
                team[found].goal += match.awaygoal;
                team[found].goala += match.homegoal;
                if(match.result == -1){
                    team[found].awaywin++;
                    team[found].seasonpoint += 3;
                    team[found].win++;
                }else if(match.result == 0){
                    team[found].seasonpoint++;
                    team[found].draw++;
                }else{
                    team[found].lose++;
                }
            }
            for(int i=0;i<128;i++){
                tmpstr[i] = 0;
            }
        }
        while(1){
            int cmd;
            printf("1) Who is the winner in this season?\n");
            printf("2) Which team gets the most scores?\n");
            printf("3) Which team gets the most red cards?\n");
            printf("4) Which team wins the most games at home?\n");
            printf("5) Which team wins the most games away from home?\n");
            printf("6) Which game has the most scoring gap?\n");
            printf("7) Team information.\n");
            printf("8) Exit\n");
            printf("Choice (1-7, 8:exit): ");
            scanf("%d",&cmd);
            char c;
            while((c = getchar()) && c != '\n');
            if(cmd == 8){
                break;
            }else if (cmd == 1){
                int maxpoint = 0, maxteam = 0;
                for(int i=0; i<=teamnum; i++){
                    if(team[i].seasonpoint > maxpoint){
                        maxpoint = team[i].seasonpoint;
                        maxteam = i;
                    }
                }
                printf("The winner is %s\n",team[maxteam].name);
            }else if(cmd == 2){
                int maxscore = 0,maxteam = 0;
                for(int i=0; i<=teamnum; i++){
                    if(team[i].scores > maxscore){
                        maxscore = team[i].scores;
                        maxteam = i;
                    }
                }
                printf("%s, %d\n",team[maxteam].name,maxscore);
            }else if(cmd == 3){
                int maxred = 0,maxteam = 0;
                for(int i=0; i<=teamnum; i++){
                    if(team[i].rcard > maxred){
                        maxred = team[i].rcard;
                        maxteam = i;
                    }
                }
                printf("%s, %d\n",team[maxteam].name,maxred);
            }else if(cmd == 4){
                int maxscore = 0,maxteam = 0;
                for(int i=0; i<=teamnum; i++){
                    if(team[i].homewin > maxscore){
                        maxscore = team[i].homewin;
                        maxteam = i;
                    }
                }
                printf("%s, %d\n",team[maxteam].name,maxscore);
            }else if(cmd == 5){
                int maxscore = 0,maxteam = 0;
                for(int i=0; i<=teamnum; i++){
                    if(team[i].awaywin > maxscore){
                        maxscore = team[i].awaywin;
                        maxteam = i;
                    }
                }
                printf("%s, %d\n",team[maxteam].name,maxscore);
            }else if(cmd == 6){
                printf("%d-%d-%d,%s(%d) vs %s(%d)\n",bestgap.date.yr,bestgap.date.mo,bestgap.date.date,bestgap.home,bestgap.homegoal,bestgap.away,bestgap.awaygoal);
            }else if(cmd == 7){
                char query[20] = {0};
                int found = -1;
                printf("Team: ");
                fgets(query,20,stdin);
                query[strlen(query)-1] = '\0';
                for(int i=0; i<=teamnum; i++){
                    if(strcmp(query,team[i].name) == 0){
                        found = i;
                        break;
                    }
                }
                if(found == -1){
                    printf("Team Not Found\n");
                }else{
                    printf("Points: %d\n",team[found].seasonpoint);
                    printf("Win/Draw/Lose: %d/%d/%d\n",team[found].win,team[found].draw,team[found].lose);
                    printf("Goal Scored/Goals Against: %d/%d\n",team[found].goal,team[found].goala);
                }
            }
        }
        fclose(fptr);
    }
    return 0;
}
///home/vonernue/CP2Homework/40947029S_hw03/season-1617_csv.csv