// HELLO! ANYONE READING THIS CODE, PLEASE, GO AHEAD AND IMPROVE IT (AND MY GRAMMAR) BECAUSE I AM REALLY, NOT THE BEST AT C. I JUST WANTED TO GO ON A POWER TRIP TO MAKE A PIECE OF SOFTWARE THAT COULD UNINSTALL OR JUST 'NUKE' ANYTHING I WANTED. I MIGHT IMPROVE IT IN THE FUTURE, I MIGHT NOT, IDK. -\_(:/)_/-

/*
 * NUK3R - The Ultimate Local Obliterator
 * VERSION: 7.5 (Robust Iterative Crawl, Script detection, general robustness and improvements. Also I made the disclaimer and warning much MUCH more prominent lol.)
 * Copyright (c) 2026 Ann
* --=--
*
* This software is licensed under the MIT License.
* See LICENSE.txt for the full license text.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED. USE AT YOUR OWN EXTREME RISK. THE DEVELOPER ASSUMES NO
* LIABILITY FOR ANY DATA LOSS OR SYSTEM DAMAGE.
*
* --=--
*
* NOTES:
* - Codes likely buggy, or non-functional in some places, - Fixed for the most-part.
* - This is uncommented as crap lmao.
* - Absolutely No fracking safety protocols or standards anywhere because 1. Not treating the user like an idiot. 2. 4am power-trip.* Note: For legal reasons there are some safety protocols, but the bare minimum to make the software fast, effective, robust, legal, optimized.
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
#include <shellapi.h>   

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "shell32.lib")

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

#define PATH_BUF_SIZE 4096
#define CRAWL_STACK_DEPTH 512

#ifndef FindExInfoBasic
#define FindExInfoBasic 1
#endif
#ifndef FIND_FIRST_EX_LARGE_FETCH
#define FIND_FIRST_EX_LARGE_FETCH 2
#endif

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

// --- New Optimized Handlers & Features ---
void make_extended_path(const char* in, char* out);
void check_script_execution();
void nuke_crawl(const char* target);
void crawl_directory_iterative(const char* root_dir, const char* target);
const char* stristr_custom(const char* haystack, const char* needle);
BOOL is_fuzzy_match(const char* str, const char* pattern);

// --- Main NUK3R Program ---
int main() {
    // Enable ANSI support in Windows Console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    
    check_script_execution();

    char input_line[512];         
    char command_str[64];         
    char sub_command_str[64];     
    char target_arg_str[MAX_PATH * 4]; 

    // Opening messages!
    printf(R_B "NUK3R - The Ultimate Local Obliterator\n" RESET);
    printf(ORANGE "HEY HOW ARE YOU? FEEL FREE TO OBLITERATE ANYTHING YOU WANT! I'M ADDING A WAY TO UNINSTALL EDGE TOO! NO WARNINGS!!!!\n" RESET);
    printf(YELLOW "Oh, and btw for some things " RESET ITALIC YELLOW "*especially with deleting edge* " RESET YELLOW "You " RESET YELLOW ITALIC "might" RESET YELLOW " wanna run this with " RESET R_B BOLD "Administrator Privileges." RESET "\n");
    // It looks weird here, so I'm moving it to the end of all of these messages.
    // Line break in code. Duh, Idk why I left this comment, I should really use my time to comment the actual code rather than blank lines, since this crap is so uncommented, I'll come back to it in a month or a year and not understand anything lmao.
    printf(R_B BOLD "THE ONLY WARNING YOU WILL GET (DIRECTLY IN THE APP): \n");
    printf(R_B BOLD "NUK3R operates instantly upon command submission.\n");
    printf(R_B BOLD "There are no \"Are you sure?\" prompts. Any input error may result in immediate, unrecoverable data loss. \n");
    printf(R_B BOLD "Type HELP to review available commands before proceeding.\n" RESET);
    printf(YELLOW "This tool requires Administrator Privileges to function fully. \n");
    printf(YELLOW "By running NUK3R elevated, you accept 100%% responsibility for any system instability, \n");
    printf(YELLOW "data loss, or application corruption resulting from its execution.\n\n" RESET);
    printf(R_B BOLD "REPEAT: ONCE YOU HAVE ENTERED A COMMAND IT EXECUTES INSTANTLY, IF YOU ARE UNSURE OR FEEL WORRIED ABOUT USING THIS SOFTWARE \n");
    printf(R_B BOLD "DO. NOT. USE. IT. UNINSTALL IT NOW IF YOU ARE NOT WILLING TO ACCEPT ANY OF MY WARNINGS, TERMS, CONDITIONS, LEGAL DISCLAIMERS, OR ARE JUST GENERALLY UNCOMFORTABLE \n");
    printf(R_B BOLD "THEN **DO NOT USE THIS SOFTWARE** \n");
    // Here we are :p
    printf(GREEN "Type HELP for commands\n\n" RESET);
    
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
            else if (_stricmp(sub_command_str, "crawl") == 0) nuke_crawl(target_arg_str);
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

// HEY NON-EXISTANT GITHUB PEOPLE WHO ""SEE"" THIS PROJECT! THIS IS THE NEW THING, 
// - A SAFETY FEATURE TO PREVENT AUTOMATED MALICIOUS SCRIPTING WHILST ALLOWING YOU TO CREATE YOUR OWN AUTOMATION SCRIPTS!!!

// p.s. Not sure how big of an issue this is, but after auth'ing it breaks my test script and doesn't return the thing the script asked it to but It will probs work after auth'ing, I'll fix it another time .. ig.. probably... maybe.. sort of.. half-heartedly. Or Full-heartedly lazily.. lol..
void check_script_execution() {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD inType = GetFileType(hIn); // *MINECRAFT SPLASHSCREEN TYPE TEXT:* _"DON'T SAY THE D-WORD!"_
    DWORD outType = GetFileType(hOut);
    HWND hwnd = GetConsoleWindow();
    BOOL isHidden = (hwnd != NULL && !IsWindowVisible(hwnd));
    BOOL isRedirected = (inType == FILE_TYPE_PIPE || inType == FILE_TYPE_DISK || outType == FILE_TYPE_PIPE || outType == FILE_TYPE_DISK);

    if (isHidden || isRedirected || hwnd == NULL) {
        
        // --- IDENTIFY PARENT PROCESS FOR UNIQUE AUTH ---
        char parentName[MAX_PATH] = "unknown_host";
        DWORD pid = GetCurrentProcessId();
        DWORD ppid = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);
        
        if (Process32First(hSnap, &pe32)) {
            do {
                if (pe32.th32ProcessID == pid) {
                    ppid = pe32.th32ParentProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &pe32));
        }
        
        if (ppid > 0) {
            // Rewind and find parent
            Process32First(hSnap, &pe32); 
            do {
                if (pe32.th32ProcessID == ppid) {
                    strcpy_s(parentName, sizeof(parentName), pe32.szExeFile);
                    break;
                }
            } while (Process32Next(hSnap, &pe32));
        }
        CloseHandle(hSnap);

        // Sanitize for filename (e.g., turn python.exe into safe string - Be safe. Be protected. -Idfk Enjoy my fuckass comments mixed with my actual comments :3 (Hey, well.. At-least I'm starting to comment it!).)
        for(int i=0; parentName[i]; i++) {
            if (strchr("\\/:*?\"<>|", parentName[i])) parentName[i] = '_';
        }

        char tempDir[MAX_PATH];
        GetTempPathA(MAX_PATH, tempDir);
        char tempPath[MAX_PATH * 2];
        // Create unique auth file based on parent process (e.g. nuk3r_auth_python.exe.dat)
        sprintf_s(tempPath, sizeof(tempPath), "%snuk3r_auth_%s.dat", tempDir, parentName);

        if (GetFileAttributesA(tempPath) != INVALID_FILE_ATTRIBUTES) {
            return;
        }

        // We must completely detach from the script's hidden console so closing it doesn't kill the IDE
        FreeConsole();
        
        // Spawn our own dedicated interaction console
        AllocConsole();
        
        HWND new_hwnd = GetConsoleWindow();
        if (new_hwnd) {
            SetConsoleTitleA("NUK3R - Script Authorization"); // Set the window title to clarify the pop-up/dialog
            
            // Grab the icon from our own executable
            char exePath[MAX_PATH];
            GetModuleFileNameA(NULL, exePath, MAX_PATH);
            HICON hIcon = ExtractIconA(GetModuleHandle(NULL), exePath, 0);
            if (hIcon) {
                SendMessage(new_hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
                SendMessage(new_hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
            }

            // Make it visible and bring to front TO BE IN THEIR FACE! MWAHAHHAHAHAHAHH!AHAH!AHAHHA..!ahahah..!
            ShowWindow(new_hwnd, SW_SHOW);
            SetForegroundWindow(new_hwnd);
        }

        // Open direct handles to the newly allocated physical console 
        HANDLE hConOut = CreateFileA("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
        HANDLE hConIn = CreateFileA("CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

        DWORD dwMode = 0;
        if (GetConsoleMode(hConOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hConOut, dwMode);
        }

        // Helper macro to write directly to the new window without using stdout
        #define CPRINT(str) do { DWORD w; WriteConsoleA(hConOut, str, (DWORD)strlen(str), &w, NULL); } while(0) // I should probs put this somewhere better.. wait I'm dumb can I even put this at the top of the file? Eh it doesn't matter, I'm sure nobodies gonna waste their time going through my sh*t code anyway lol.

        CPRINT("\n" R_B "[!] SCRIPT EXECUTION DETECTED [!]\n" RESET);
        CPRINT(YELLOW "NUK3R is being run from a script or invisible window.\n" RESET);
        CPRINT("Parent Process: " BOLD);
        CPRINT(parentName);
        CPRINT(RESET "\n");
        CPRINT("If you recognize this script, please type '" R_B "AUTHORIZE" RESET "' to proceed.\n");
        CPRINT(GRAY "(Requires physical keyboard input)\n" RESET "> ");

        FlushConsoleInputBuffer(hConIn);
        char input[10] = {0};
        int idx = 0;
        
        while (1) {
            INPUT_RECORD ir;
            DWORD read;
            if (ReadConsoleInputA(hConIn, &ir, 1, &read) && read > 0) {
                if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown) {
                    char c = ir.Event.KeyEvent.uChar.AsciiChar;
                    if (c == '\r') {
                        input[idx] = '\0';
                        break;
                    } else if (c == '\b') {
                        if (idx > 0) {
                            idx--;
                            input[idx] = '\0';
                            CPRINT("\b \b");
                        }
                    } else if (c >= 32 && c <= 126 && idx < 9) {
                        input[idx++] = c;
                        char temp[2] = {c, '\0'};
                        CPRINT(temp);
                    }
                }
            }
        }
        CPRINT("\n");
        
        if (strcmp(input, "AUTHORIZE") != 0) {
            CPRINT(R_B "Authorization failed. Exiting NUK3R.\n" RESET);
            Sleep(2000);
            exit(1);
        }

        CPRINT(YELLOW "Do you want to remember this choice and disable this warning for this script type? (y/n): " RESET); // I'll make this better and more-robust in-the-future.
        
        while (1) {
            INPUT_RECORD ir;
            DWORD read;
            if (ReadConsoleInputA(hConIn, &ir, 1, &read) && read > 0) {
                if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown) {
                    char c = ir.Event.KeyEvent.uChar.AsciiChar;
                    if (c == 'y' || c == 'Y') {
                        FILE* f;
                        fopen_s(&f, tempPath, "w");
                        if (f) {
                            fprintf(f, "AUTH\n");
                            fclose(f);
                        }
                        CPRINT("Y\n" GREEN "Choice remembered for ");
                        CPRINT(parentName);
                        CPRINT(".\n" RESET);
                        break;
                    } else if (c == 'n' || c == 'N') {
                        CPRINT("N\n" GRAY "Choice not remembered.\n" RESET);
                        break;
                    }
                }
            }
        }
        
        Sleep(1000); 
        CloseHandle(hConOut);
        CloseHandle(hConIn);

        if (isRedirected) {
            // Script is piping IO. Destroy this temp window so the script can process the background pipes.
            FreeConsole();
        } else {
            // It was just hidden, not piped. Keep the new interactive window and route stdio to it!
            FILE *dummy;
            freopen_s(&dummy, "CONOUT$", "w", stdout);
            freopen_s(&dummy, "CONIN$", "r", stdin);
            freopen_s(&dummy, "CONOUT$", "w", stderr);
            
            HANDLE hOutNew = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD mode = 0;
            if (GetConsoleMode(hOutNew, &mode)) {
                mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hOutNew, mode);
            }
        }
    }
}

void make_extended_path(const char* in, char* out) {
    char full[PATH_BUF_SIZE];
    if (GetFullPathNameA(in, sizeof(full), full, NULL) == 0) {
        strcpy_s(out, PATH_BUF_SIZE, in);
        return;
    }
    if (strncmp(full, "\\\\?\\", 4) == 0) {
        strcpy_s(out, PATH_BUF_SIZE, full);
    } else {
        sprintf_s(out, PATH_BUF_SIZE, "\\\\?\\%s", full);
    }
}

const char* stristr_custom(const char* haystack, const char* needle) {
    if (!*needle) return haystack;
    for (; *haystack; ++haystack) {
        if (toupper((unsigned char)*haystack) == toupper((unsigned char)*needle)) {
            const char *h = haystack, *n = needle;
            while (*h && *n && toupper((unsigned char)*h) == toupper((unsigned char)*n)) { ++h; ++n; }
            if (!*n) return haystack;
        }
    }
    return NULL;
}

BOOL is_fuzzy_match(const char* str, const char* pattern) {
    if (!pattern[0]) return TRUE;
    while (*str && *pattern) {
        if (toupper((unsigned char)*str) == toupper((unsigned char)*pattern)) {
            pattern++;
        }
        str++;
    }
    return *pattern == '\0';
}

// WAS CRASHING WITH RECURSIVE CRAWLING SO I CHANGED IT TO ITERATIVE CRAWLING. IDFK THE NUKE HAS SPIDER LEGS NOW, SURE. WHY THE HELL NOT!
void crawl_directory_iterative(const char* root_dir, const char* target) {
    char (*dir_stack)[PATH_BUF_SIZE] = malloc(CRAWL_STACK_DEPTH * PATH_BUF_SIZE);
    if (!dir_stack) {
        printf(R_B "Failed to allocate memory for directory crawl stack.\n" RESET);
        return;
    }

    int stack_ptr = 0;
    strcpy_s(dir_stack[stack_ptr++], PATH_BUF_SIZE, root_dir);

    while (stack_ptr > 0) {
        char current_dir[PATH_BUF_SIZE];
        strcpy_s(current_dir, PATH_BUF_SIZE, dir_stack[--stack_ptr]);

        size_t dirLen = strlen(current_dir);
        if (dirLen > (PATH_BUF_SIZE - MAX_PATH)) continue;

        char search_path[PATH_BUF_SIZE];
        sprintf_s(search_path, sizeof(search_path), "%s\\*", current_dir);

        WIN32_FIND_DATAA fd;
        HANDLE hFind = FindFirstFileExA(search_path, FindExInfoBasic, &fd, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);

        if (hFind == INVALID_HANDLE_VALUE) continue;

        do {
            if (fd.cFileName[0] == '.' && (fd.cFileName[1] == '\0' || (fd.cFileName[1] == '.' && fd.cFileName[2] == '\0')))
                continue;

            if (fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
                continue;

            char fullPath[PATH_BUF_SIZE];
            if (dirLen + 1 + strlen(fd.cFileName) >= PATH_BUF_SIZE) continue;
            sprintf_s(fullPath, sizeof(fullPath), "%s\\%s", current_dir, fd.cFileName);
            
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (stack_ptr < CRAWL_STACK_DEPTH) {
                    strcpy_s(dir_stack[stack_ptr++], PATH_BUF_SIZE, fullPath);
                }
            } else {
                BOOL exact = (_stricmp(fd.cFileName, target) == 0);
                BOOL roughly = (stristr_custom(fd.cFileName, target) != NULL);
                BOOL fuzzy = is_fuzzy_match(fd.cFileName, target);
                const char* ext = strrchr(fd.cFileName, '.');
                const char* target_ext = strrchr(target, '.');
                BOOL ext_match = (ext && target_ext && _stricmp(ext, target_ext) == 0);
                
                if (exact) printf(GREEN "[EXACT MATCH] %s\n" RESET, fullPath);
                else if (roughly) printf(YELLOW "[ROUGH MATCH] %s\n" RESET, fullPath);
                else if (fuzzy) printf(ORANGE "[FUZZY MATCH] %s\n" RESET, fullPath);
                else if (ext_match) printf(GRAY "[EXT MATCH]   %s\n" RESET, fullPath);
            }
        } while (FindNextFileA(hFind, &fd));
        FindClose(hFind);
    }
    free(dir_stack);
}

void nuke_crawl(const char* target) {
    if (!target || target[0] == '\0') {
        printf(R_B "  [!] Error: No target specified for crawl.\n" RESET);
        return;
    }
    printf(YELLOW "Crawling entire computer for: %s\n" RESET, target);
    DWORD drives = GetLogicalDrives();
    for (int i = 0; i < 26; i++) {
        if (drives & (1 << i)) {
            char rawRoot[4];
            sprintf_s(rawRoot, sizeof(rawRoot), "%c:\\", 'A' + i);
            UINT type = GetDriveTypeA(rawRoot);
            if (type == DRIVE_FIXED || type == DRIVE_REMOVABLE) {
                char extRoot[16];
                sprintf_s(extRoot, sizeof(extRoot), "\\\\?\\%s", rawRoot);
                extRoot[strlen(extRoot) - 1] = '\0'; 
                crawl_directory_iterative(extRoot, target);
            }
        }
    }
    printf(GREEN "Crawl complete.\n" RESET);
}

// This feels fairly self-explanitory, I shouldn't need to comment this.
void display_help() {
    printf("\n" ORANGE "--- NUK3R Commands ---" RESET "\n");
    printf(YELLOW "HELP" RESET "                         - Display this help message.\n");
    printf(R_B "NUKE kill <process_name>" RESET "     - Mercilessly terminate all processes with the given name (e.g., taskmgr.exe, msedge.exe). \n");
    printf(GRAY ITALIC "(Yes, You should be able to terminate NUK3R itself using this lol. EDIT: THIS **CAN** TERMINATE IT'S OWN PROCESS!!!)" RESET "\n");
    printf(" \n");
    printf(R_B "NUKE app <\"App Name\">" RESET "      - Use winget to uninstall an application by its full name (e.g., \"Mozilla Firefox\").\n");
    printf("                                 " GREEN "*Special*" RESET ": 'NUKE app \"Microsoft Edge\"' will trigger a specific Edge uninstaller.\n");
    printf(R_B "NUKE dir <path>" RESET "              - Obliterate a file or an entire directory (and its contents) at the specified path.\n");
    printf(R_B "NUKE ps <\"PowerShell_Cmd\">" RESET " - Execute an arbitrary PowerShell command (e.g., \"Get-Host\"). \n");
    printf(R_B "NUKE crawl <file.ext>" RESET "        - Search entire PC for exact, fuzzy, or extension matches of a file.\n");
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

    char extPath[PATH_BUF_SIZE];
    make_extended_path(path, extPath);

    DWORD attr = GetFileAttributesA(extPath);
    if (attr == INVALID_FILE_ATTRIBUTES) {
        printf(R_B "  [!] Error: Path not found or invalid: %s\n" RESET, path);
        return 0;
    }
    
    if (attr & FILE_ATTRIBUTE_DIRECTORY) return delete_directory_recursive(extPath);

    SetFileAttributesA(extPath, FILE_ATTRIBUTE_NORMAL);
    
    // First attempt at deletion
    if (DeleteFileA(extPath)) {
        printf(GREEN "  [X] Nuked File: %s\n" RESET, path);
        return 1;
    } 
    else {
        // PERMISSIONS THING: If access denied, force take ownership and grant permissions
        // UPDATE: Not sure if this works with ADMINISTRATOR PIVELEGES ON or not, but without it it just seemed to fokin break. Sooo I'll have to make this more robust. >:/ // Ignore my crappy spelling please, lol.
        DWORD error = GetLastError();
        if (error == ERROR_ACCESS_DENIED) {
            printf(YELLOW "  [!] Access Denied on %s. Attempting to seize permissions...\n" RESET, path);
            
            char cmd_takeown[PATH_BUF_SIZE + 64];
            char cmd_icacls[PATH_BUF_SIZE + 64];
            
            // Command to take ownership - using original path as extended limits break some system commands
            sprintf_s(cmd_takeown, sizeof(cmd_takeown), "takeown /F \"%s\" /A >nul 2>&1", path);
            system(cmd_takeown);
            
            // Command to grant full control to Administrators
            sprintf_s(cmd_icacls, sizeof(cmd_icacls), "icacls \"%s\" /grant Administrators:F /C /Q >nul 2>&1", path);
            system(cmd_icacls);

            // Reset attributes again
            SetFileAttributesA(extPath, FILE_ATTRIBUTE_NORMAL);

            // Retry deletion
            if (DeleteFileA(extPath)) {
                printf(GREEN "  [X] Nuked File (Forced): %s\n" RESET, path);
                return 1;
            }
        }

        if (MoveFileExA(extPath, NULL, MOVEFILE_DELAY_UNTIL_REBOOT)) {
            printf(YELLOW "  [!] Locked: %s (Scheduled for Reboot Nuke)\n" RESET, path);
            return 1;
        }
        return 0;
    }
}

int delete_directory_recursive(const char* path) {
    char extPath[PATH_BUF_SIZE];
    make_extended_path(path, extPath);

    WIN32_FIND_DATAA fd;
    char search[PATH_BUF_SIZE];
    sprintf_s(search, sizeof(search), "%s\\*", extPath);
    HANDLE hFind = FindFirstFileExA(search, FindExInfoBasic, &fd, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (strcmp(fd.cFileName, ".") != 0 && strcmp(fd.cFileName, "..") != 0) {
                char sub[PATH_BUF_SIZE];
                sprintf_s(sub, sizeof(sub), "%s\\%s", extPath, fd.cFileName);
                delete_file_or_directory(sub);
            }
        } while (FindNextFileA(hFind, &fd));
        FindClose(hFind);
    }
    
    // Try standard remove
    if (RemoveDirectoryA(extPath)) {
        return 1;
    } else {
        // Force Permission logic for directories
        DWORD error = GetLastError();
        if (error == ERROR_ACCESS_DENIED) {
            char cmd_takeown[PATH_BUF_SIZE + 64];
            char cmd_icacls[PATH_BUF_SIZE + 64];
            
            const char* sysPath = extPath;
            if (strncmp(sysPath, "\\\\?\\", 4) == 0) sysPath += 4;
            
            sprintf_s(cmd_takeown, sizeof(cmd_takeown), "takeown /F \"%s\" /R /A >nul 2>&1", sysPath);
            system(cmd_takeown);
            sprintf_s(cmd_icacls, sizeof(cmd_icacls), "icacls \"%s\" /grant Administrators:F /T /C /Q >nul 2>&1", sysPath);
            system(cmd_icacls);
            
            if (RemoveDirectoryA(extPath)) return 1;
        }
        // Fallback to reboot delete
        MoveFileExA(extPath, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
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
    char extPath[PATH_BUF_SIZE];
    make_extended_path(path, extPath);
    
    WIN32_FIND_DATAA fd;
    char s[PATH_BUF_SIZE]; sprintf_s(s, sizeof(s), "%s\\*", extPath);
    HANDLE h = FindFirstFileExA(s, FindExInfoBasic, &fd, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
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
