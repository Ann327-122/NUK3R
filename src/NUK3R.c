// HELLO! ANYONE READING THIS CODE, PLEASE, GO AHEAD AND IMPROVE IT (AND MY GRAMMAR) BECAUSE I AM REALLY, NOT THE BEST AT C. I JUST WANTED TO GO ON A POWER TRIP TO MAKE A PIECE OF SOFTWARE THAT COULD UNINSTALL OR JUST 'NUKE' ANYTHING I WANTED. I MIGHT IMPROVE IT IN THE FUTURE, I MIGHT NOT, IDK. -\_(:/)_/-

/*
* VERSION: 5.2 (Updated with Permission Seizing and Better Path Handling)
*
* NOTES:
* - Codes likely buggy, or non-functional in some places,
* - This is uncommented as shit lmao.
* - Absolutely No fucking safety protocols or standards anywhere because 1. Not treating the user like an idiot. 2. 4am power-trip.
*
* ENJOY! :3
*
* @Author Ann
*
*/



#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <windows.h>    
#include <tlhelp32.h>   
#include <errno.h>      
#include <conio.h>
#include <ctype.h>

// I'm so bad at C why does none of the text look Bold in the app???
// --- ANSI COLOR DEFINITIONS! ---
#define R_B      "\033[1;31m"      // Bold Red
#define ORANGE   "\033[38;5;208m"  // Orange
#define YELLOW   "\033[1;33m"      // Bold Yellow
#define GREEN    "\033[1;32m"      // Bold Green
#define GRAY     "\033[90m"        // Dark Gray
#define BOLD     "\033[1m"         // Bold
#define ITALIC   "\033[3m"         // Italic
#define RESET    "\033[0m"         // Reset

// --- Forward Declarations ---
void display_help();
void kill_process_by_name(const char* process_name);
int delete_file_or_directory(const char* path);
int delete_directory_recursive(const char* path);
void uninstall_app_winget(const char* app_name);
void run_powershell_command(const char* command_str);
void uninstall_ms_edge(); 
int is_edge_alias(const char* name); 
int PathFileExistsA_Custom(const char* path); 
void list_installed_apps();
void list_running_processes();
void list_directory_contents(const char* path);
size_t _strlcpy(char *dst, const char *src, size_t size);
void strip_quotes(char *str);
void trim_whitespace(char *str);

// --- Main NUK3R Program ---
int main() {
    // Enable ANSI support in Windows Console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    char input_line[512];         
    char command_str[64];         
    char sub_command_str[64];     
    char target_arg_str[MAX_PATH * 4]; 

    printf(R_B "NUK3R - The Ultimate Local Obliterator\n" RESET);
    printf(ORANGE "HEY HOW ARE YOU? FEEL FREE TO OBLITERATE ANYTHING YOU WANT! I'M ADDING A WAY TO UNINSTALL EDGE TOO! NO WARNINGS!!!!\n" RESET);
    printf(YELLOW "Oh, and btw for some things " RESET ITALIC YELLOW "*especially with deleting edge* " RESET YELLOW "You " RESET YELLOW ITALIC "might" RESET YELLOW " wanna run this with " RESET R_B BOLD "Administrator Privileges." RESET "\n");
    printf(GREEN "Type HELP for commands\n\n" RESET);
    // Line break in code. Duh, Idk why I left this comment, I should really use my time to comment the actual code rather than blank lines, since this shit is so uncommented, I'll come back to it in a month or a year and not understand anything lmao.
    printf(R_B BOLD "THE ONLY WARNING YOU WILL GET: \n");
    printf(R_B BOLD "NUK3R operates instantly upon command submission.\n");
    printf(R_B BOLD "There are no \"Are you sure?\" prompts. Any input error may result in immediate, unrecoverable data loss. \n");
    printf(R_B BOLD "Type HELP to review available commands before proceeding.\n" RESET);
    printf(YELLOW "This tool requires Administrator Privileges to function fully. \n");
    printf(YELLOW "By running NUK3R elevated, you accept 100%% responsibility for any system instability, \n");
    printf(YELLOW "data loss, or application corruption resulting from its execution.\n\n" RESET);
    
    
    while (1) {
        printf(R_B "NUK3R> " RESET);
        if (fgets(input_line, sizeof(input_line), stdin) == NULL) break;
        input_line[strcspn(input_line, "\n")] = 0; 

        char *token = strtok(input_line, " "); 
        if (token == NULL) continue;
        _strlcpy(command_str, token, sizeof(command_str));

        token = strtok(NULL, " ");
        if (token != NULL) {
            _strlcpy(sub_command_str, token, sizeof(sub_command_str));
            // Grab the rest of the line to allow for spaces in paths
            token = strtok(NULL, ""); 
            if (token != NULL) {
                _strlcpy(target_arg_str, token, sizeof(target_arg_str));
                // Clean up the input path
                trim_whitespace(target_arg_str);
                strip_quotes(target_arg_str);
            }
            else target_arg_str[0] = '\0';
        } else {
            sub_command_str[0] = '\0';
            target_arg_str[0] = '\0';
        }

        if ((_stricmp(command_str, "NUKE") == 0 && is_edge_alias(sub_command_str)) ||
            is_edge_alias(command_str) || 
            (_stricmp(command_str, "KILL") == 0 && is_edge_alias(sub_command_str)) || 
            (_stricmp(command_str, "NUKEDGE") == 0) || 
            (_stricmp(command_str, "NUKEEDGE") == 0) )
        {
            printf(ORANGE "Detected an Edge uninstallation request. Initiating special Edge obliteration sequence!\n" RESET);
            uninstall_ms_edge();
            continue; 
        }

        if (_stricmp(command_str, "HELP") == 0) display_help();
        else if (_stricmp(command_str, "NUKE") == 0) {
            if (_stricmp(sub_command_str, "kill") == 0) kill_process_by_name(target_arg_str);
            else if (_stricmp(sub_command_str, "app") == 0) uninstall_app_winget(target_arg_str);
            else if (_stricmp(sub_command_str, "dir") == 0) delete_file_or_directory(target_arg_str);
            else if (_stricmp(sub_command_str, "ps") == 0) run_powershell_command(target_arg_str);
        } else if (_stricmp(command_str, "NLIST") == 0) {
            if (_stricmp(sub_command_str, "app") == 0) list_installed_apps();
            else if (_stricmp(sub_command_str, "tasks") == 0) list_running_processes();
            else if (_stricmp(sub_command_str, "dir") == 0) list_directory_contents(target_arg_str);
        } else if (_stricmp(command_str, "EXIT") == 0) {
            printf(ORANGE "Exiting NUK3R. Goodbye.\n" RESET);
            break;
        }
    }
    return 0;
}

void display_help() {
    printf("\n" ORANGE "--- NUK3R Commands ---" RESET "\n");
    printf(YELLOW "HELP" RESET "                         - Display this help message.\n");
    printf(R_B "NUKE kill <process_name>" RESET "     - Mercilessly terminate all processes with the given name (e.g., taskmgr.exe, msedge.exe). \n");
    printf(GRAY ITALIC "(Yes, You should be able to terminate NUK3R itself using this lol.)" RESET "\n");
    printf(" \n");
    printf(R_B "NUKE app <\"App Name\">" RESET "      - Use winget to uninstall an application by its full name (e.g., \"Mozilla Firefox\").\n");
    printf("                                 " GREEN "*Special*" RESET ": 'NUKE app \"Microsoft Edge\"' will trigger a specific Edge uninstaller.\n");
    printf(R_B "NUKE dir <path>" RESET "              - Obliterate a file or an entire directory (and its contents) at the specified path.\n");
    printf(R_B "NUKE ps <\"PowerShell_Cmd\">" RESET " - Execute an arbitrary PowerShell command (e.g., \"Get-Host\"). \n");
    printf("\n" R_B BOLD "--- Special Edge Obliteration Commands ---" RESET "\n");
    printf(GREEN "NUKE EDGE" RESET "                    - Triggers the special Microsoft Edge uninstaller.\n");
    printf(GREEN "NUKEDGE" RESET "                      - Alias for NUKE EDGE.\n");
    printf(GREEN "NUKEEDGE" RESET "                     - Another alias for NUKE EDGE.\n");
    printf(GREEN "KILL EDGE" RESET "                    - Also triggers the special Microsoft Edge uninstaller.\n");
    printf("                                 " GRAY ITALIC "(Any variant of 'EDGE', 'MSEDGE', 'MICROSOFT EDGE', 'INTERNET EXPLORER' works for these.)" RESET "\n");
    printf(ORANGE "--- NLIST Commands ---" RESET "\n");
    printf(YELLOW "NLIST app" RESET "                    - List all installed applications via winget.\n");
    printf(YELLOW "NLIST tasks" RESET "                  - List all currently running processes (tasks).\n");
    printf(YELLOW "NLIST dir <path>" RESET "             - List all files and directories within the specified path.\n");
    printf(R_B BOLD "EXIT" RESET "                         - Close NUK3R.\n");
    printf(ORANGE "---------------------------" RESET "\n\n");
}

// TO DESTROY MICROSOFT EDGE, I'VE BUILT A BUNCH OF COMMANDS SPECIFICALLY FOR EDGE TO RUN THIS FUNCTION! IT SHALL BE SCORCHED FROM THIS EARTH.. Or, at least the computers that have the software.. and that.. ran the .. well, any one of the commands to DESTROY microsoft edge.
void uninstall_ms_edge() {
    printf(R_B "\n--- Initiating " BOLD "AGGRESSIVE" RESET R_B " Edge Obliteration ---\n" RESET);
    printf(YELLOW "[Step 1/3] Hunting background processes...\n" RESET);
    kill_process_by_name("msedge.exe");
    kill_process_by_name("MicrosoftEdgeUpdate.exe");
    kill_process_by_name("identity_helper.exe");
    kill_process_by_name("msedge_proxy.exe");
    kill_process_by_name("msedge_elevation_service.exe");

    printf(YELLOW "\n[Step 2/3] Shredding installation directories...\n" RESET);
    delete_file_or_directory("C:\\Program Files (x86)\\Microsoft\\Edge");
    delete_file_or_directory("C:\\Program Files (x86)\\Microsoft\\EdgeCore");
    delete_file_or_directory("C:\\Program Files\\Microsoft\\Edge");
    delete_file_or_directory("C:\\Program Files\\Microsoft\\EdgeCore");

    printf(YELLOW "\n[Step 3/3] Clearing user data footprints...\n" RESET);
    char path[MAX_PATH];
    char* local = getenv("LOCALAPPDATA");
    if (local) {
        sprintf_s(path, MAX_PATH, "%s\\Microsoft\\Edge", local);
        delete_file_or_directory(path);
    }

    printf(GREEN "\n--- AGGRESSIVE Microsoft Edge obliteration complete! ---\n" RESET);
    printf(ITALIC GRAY "Note: Locked files are scheduled for deletion on next reboot.\n\n" RESET);
}

void kill_process_by_name(const char* process_name) {
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32; pe32.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hSnapShot, &pe32)) {
        do {
            if (_stricmp(pe32.szExeFile, process_name) == 0) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
                if (hProcess) {
                    TerminateProcess(hProcess, 0);
                    printf(ORANGE "  >> Terminated: %s (PID: %lu)\n" RESET, process_name, pe32.th32ProcessID);
                    CloseHandle(hProcess);
                }
            }
        } while (Process32Next(hSnapShot, &pe32));
    }
    CloseHandle(hSnapShot);
}

// DIRECTORY AND FILE DELETION!!1!!!!!!!!!!!!!!!!!!!!!!!!!!1!!!!!!!
int delete_file_or_directory(const char* path) {

    // --- THE AGGRESSIVE EMERGENCY BRAKE BECAUSE I HAVE SOME LEVEL OF SANITY APPARENTLY. ---
    // Detect if user is trying to nuke the root of the drive.
    if (_stricmp(path, "C:\\") == 0 || _stricmp(path, "C:/") == 0 || strlen(path) < 4) {
        printf(R_B "\n[!!!] ROOT LEVEL OBLITERATION DETECTED [!!!]\n" RESET);
        printf(YELLOW "You are about to nuke the base of your drive. This will break everything.\n");
        printf(ORANGE "Look, I know I said No warnings but I apparently have some sanity, \n");
        printf(ORANGE "and I wanted to test what happens when you mess up the spaces in the path without breaking my own OS so a little bit selfish, I know.)");
        printf(R_B "I will proceed in 10 seconds unless you stop me.\n" RESET);

        for (int i = 10; i > 0; i--) {
            printf("\r" R_B ">> INITIATING DRIVE COLLAPSE IN: %d (Press 'S' to ABORT or CTRL + C to kill me.) " RESET, i);
            
            // Check for keypress 10 times per second for a total of 1 second
            for (int j = 0; j < 10; j++) {
                if (_kbhit()) {
                    char ch = _getch();
                    if (ch == 's' || ch == 'S') {
                        printf("\n" GREEN ">> OBLITERATION ABORTED. Coward." RESET "\n\n");
                        return 0;
                    }
                }
                Sleep(100); // Wait 100ms
            }
        }
        printf("\n" R_B ">> NO ABORT RECEIVED. GOOD LUCK.\n" RESET);
    }

    DWORD attr = GetFileAttributesA(path);
    if (attr == INVALID_FILE_ATTRIBUTES) {
        printf(R_B "  [!] Error: Path not found or invalid: %s\n" RESET, path);
        return 0;
    }
    
    if (attr & FILE_ATTRIBUTE_DIRECTORY) return delete_directory_recursive(path);

    SetFileAttributesA(path, FILE_ATTRIBUTE_NORMAL);
    
    // First attempt at deletion
    if (DeleteFileA(path)) {
        printf(GREEN "  [X] Nuked File: %s\n" RESET, path);
        return 1;
    } 
    else {
        // PERMISSIONS THING: If access denied, force take ownership and grant permissions
        DWORD error = GetLastError();
        if (error == ERROR_ACCESS_DENIED) {
            printf(YELLOW "  [!] Access Denied on %s. Attempting to seize permissions...\n" RESET, path);
            
            char cmd_takeown[MAX_PATH * 2 + 32];
            char cmd_icacls[MAX_PATH * 2 + 64];
            
            // Command to take ownership
            sprintf_s(cmd_takeown, sizeof(cmd_takeown), "takeown /F \"%s\" /A >nul 2>&1", path);
            system(cmd_takeown);
            
            // Command to grant full control to Administrators
            sprintf_s(cmd_icacls, sizeof(cmd_icacls), "icacls \"%s\" /grant Administrators:F /C /Q >nul 2>&1", path);
            system(cmd_icacls);

            // Reset attributes again
            SetFileAttributesA(path, FILE_ATTRIBUTE_NORMAL);

            // Retry deletion
            if (DeleteFileA(path)) {
                printf(GREEN "  [X] Nuked File (Forced): %s\n" RESET, path);
                return 1;
            }
        }

        if (MoveFileExA(path, NULL, MOVEFILE_DELAY_UNTIL_REBOOT)) {
            printf(YELLOW "  [!] Locked: %s (Scheduled for Reboot Nuke)\n" RESET, path);
            return 1;
        }
        return 0;
    }
}

int delete_directory_recursive(const char* path) {
    WIN32_FIND_DATAA fd;
    char search[MAX_PATH];
    sprintf_s(search, MAX_PATH, "%s\\*", path);
    HANDLE hFind = FindFirstFileA(search, &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (strcmp(fd.cFileName, ".") != 0 && strcmp(fd.cFileName, "..") != 0) {
                char sub[MAX_PATH];
                sprintf_s(sub, MAX_PATH, "%s\\%s", path, fd.cFileName);
                delete_file_or_directory(sub);
            }
        } while (FindNextFileA(hFind, &fd));
        FindClose(hFind);
    }
    
    // Try standard remove
    if (RemoveDirectoryA(path)) {
        return 1;
    } else {
        // Force Permission logic for directories
        DWORD error = GetLastError();
        if (error == ERROR_ACCESS_DENIED) {
            char cmd_takeown[MAX_PATH * 2 + 32];
            char cmd_icacls[MAX_PATH * 2 + 64];
            sprintf_s(cmd_takeown, sizeof(cmd_takeown), "takeown /F \"%s\" /R /A >nul 2>&1", path);
            system(cmd_takeown);
            sprintf_s(cmd_icacls, sizeof(cmd_icacls), "icacls \"%s\" /grant Administrators:F /T /C /Q >nul 2>&1", path);
            system(cmd_icacls);
            
            if (RemoveDirectoryA(path)) return 1;
        }
        // Fallback to reboot delete
        MoveFileExA(path, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
        return 0;
    }
}

int is_edge_alias(const char* name) {
    if (!name || name[0] == '\0') return 0;
    return (_stricmp(name, "edge") == 0 || _stricmp(name, "msedge") == 0 || _stricmp(name, "microsoft edge") == 0 || _stricmp(name, "internet explorer") == 0);
}

size_t _strlcpy(char *dst, const char *src, size_t size) {
    size_t len = strlen(src);
    if (size > 0) {
        size_t cp = (len < size - 1) ? len : size - 1;
        memcpy(dst, src, cp);
        dst[cp] = '\0';
    }
    return len;
}

void strip_quotes(char *str) {
    size_t len = strlen(str);
    if (len > 1 && str[0] == '"' && str[len - 1] == '"') {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}

void trim_whitespace(char *str) {
    if (!str) return;
    // Trim trailing
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
    // Trim leading
    char *start = str;
    while (*start && isspace((unsigned char)*start)) start++;
    memmove(str, start, strlen(start) + 1);
}

void list_installed_apps() { system("winget list"); }
void list_running_processes() {
    HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 p; p.dwSize = sizeof(p);
    if (Process32First(h, &p)) {
        do { printf("%-6lu | %s\n", p.th32ProcessID, p.szExeFile); } while (Process32Next(h, &p));
    }
    CloseHandle(h);
}
void list_directory_contents(const char* path) {
    WIN32_FIND_DATAA fd;
    char s[MAX_PATH]; sprintf_s(s, MAX_PATH, "%s\\*", path);
    HANDLE h = FindFirstFileA(s, &fd);
    if (h != INVALID_HANDLE_VALUE) {
        do { printf("[%s] %s\n", (fd.dwFileAttributes & 16) ? "DIR" : "FILE", fd.cFileName); } while (FindNextFileA(h, &fd));
        FindClose(h);
    }
}
void uninstall_app_winget(const char* n) {
    char b[512]; sprintf_s(b, 512, "powershell -Command \"Start-Process winget -ArgumentList 'uninstall \\\"%s\\\"' -Verb RunAs -Wait\"", n);
    system(b);
}
void run_powershell_command(const char* c) {
    char b[1024]; sprintf_s(b, 1024, "powershell.exe -NoProfile -Command \"%s\"", c);
    system(b);
}