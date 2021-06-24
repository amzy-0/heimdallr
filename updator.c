/*
 *  HE
 IMDALLR: 
 *  Copyright [2021] [M.Amin Azimi .K (amzy-0)]
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *  
 *  @author(s) : amzy-0 (Mohammad Amin Azimi .K) 
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/unistd.h>
#include<string.h>

int main(void){
    
    //  home address 
    char *home_addr = getenv("HOME");
    char *heimdallr_addr = "/.heimdallr/makefile";
    
    // finally length of the path (/home/username/.heimdallr)
    // **************************************dinamic opration
    int home_addr_len = strlen(home_addr);
    int heimdallr_addr_len = strlen(heimdallr_addr);
    int finally_len = home_addr_len + heimdallr_addr_len+1;

    // hidden directory path
    char *path = (char*)malloc(finally_len*sizeof(char));
    strcpy(path, home_addr);
    strcat(path, heimdallr_addr); 

    // change path to hidden directory (~/.heimdallr) 
    chdir(path);
    printf("%s\n", path);
    
    // fetch & update & compile & copy (force)
    system(" git pull ; make; sudo cp -rf heimdallr /usr/bin/heimdallr");
    return 0;
}