v1.5.2

Added a *TINY* bit of safety because I got a little bit scared when bug testing. this command:
NUKE dir C:\Program Files\TESTFOLDERFORNUK3RDELETE\

It worked luckily.


I added stuff to make sure paths with spaces work correctly,

I also made a thing that tries to give itself permission over a file if it's initially denied permission.


v1.5.2 (Externals updated)

Provided a 'CONTRIBUTING.md' file containing a legal agreement and suggested guidelines for making branches or distributions or commits to the project.
Updated changelog (Fixed typo's and added a new 5.2 update log, Fixed another typo in this file. (Distrobutions -> distributions)). (Duh.)

Provided 'Inno Setup' installer script for anyone who needs it. (Find in the `/Build/` folder.)

Updated installers README to the correct version.


v2.7.5 (Security and second release!!!)

Created new release,
Added protection against malicious scripts whilst allowing for ***authorized*** automation scripts.

Added a new `NUKE crawl <file.extension>` command Which performs an interive crawl around your entire computer, and all of your drives to find: Matching files, fuzzy-matched files, of the specified type. And returns their paths.

Updated documentation files and things. (Duh,)


