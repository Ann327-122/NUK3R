Hi!

If you wanted to commit (which I doubt due to the nature of the project, but anyway),
Thanks!
I've laid out some rough guidelines for if you choose to release your update:

# _**LEGAL DISCLAIMER & CONTRIBUTOR AGREEMENT**_:

BY CONTRIBUTING TO THIS PROJECT, YOU, THE CONTRIBUTOR, ACKNOWLEDGE AND AGREE TO THE FOLLOWING:

1.  **YOU ARE 100% RESPONSIBLE FOR YOUR OWN CODE AND TESTING.** ANY DAMAGE CAUSED BY YOUR CONTRIBUTIONS, WHETHER DURING TESTING OR IN ANY OTHER SCENARIO, IS SOLELY YOUR RESPONSIBILITY. THIS INCLUDES, BUT IS NOT LIMITED TO, SYSTEM INSTABILITY, DATA LOSS, OR ANY OTHER CATASTROPHIC FAILURE.

2.  **THE ORIGINAL DEVELOPER (ANN) IS NOT RESPONSIBLE FOR YOUR CHANGES.** YOU AGREE TO INDEMNIFY AND HOLD HARMLESS THE ORIGINAL COPYRIGHT HOLDER OF THIS PROJECT FROM ANY AND ALL CLAIMS, DAMAGES, OR LIABILITIES ARISING FROM YOUR CONTRIBUTIONS.

3.  **ALL CONTRIBUTIONS ARE PROVIDED "AS IS".** JUST LIKE THE REST OF THIS PROJECT, YOUR CONTRIBUTIONS WILL BE LICENSED UNDER THE INCLUDED MIT LICENSE AND CARRY ABSOLUTELY NO WARRANTY.

YOUR DECISION TO COMMIT CODE TO THIS REPOSITORY CONSTITUTES YOUR FULL AND UNCONDITIONAL ACCEPTANCE OF THESE TERMS. IF YOU DO NOT AGREE, DO NOT CONTRIBUTE.





===
===

# **SUGGESTED** Guidelines:

# 1. Keep your project optimized!
Try to optimize its speed as much as possible for a large range of hardware.
Make sure any file crawling or otherwise is optimized,
and keep the project lightweight.

# 2. THOROUGHLY TEST, AND TEST AGAIN.
Due to the nature of the project,
where files are being deleted,
and apps being uninstalled,
and other things in a way that can be irreversible,
a single bug could cause massive instability in the User's system or Environment.

# 3. IF MAKING A GUI WRAPPER FOR THE CURRENTLY CLI PROJECT:
KEEP ASSETS EXTERNAL IN A SIMILAR STYLE TO A `assets/type/subtype/` structure.
AND MAKE SURE IT LOOKS SEMI-PRESENTABLE WITHOUT THEM,
AND DOESN'T LOSE STABILITY IF THE FILES ARE MISSING.
KEEPING THEM EXTERNAL AND BUNDLED WITH THE APP MEANS EASIER MODDING AND DISTRIBUTION FOR OTHERS,
AND THE END USER.

# 4. KEEP IT EASY TO COMPILE AND EASY TO INSTALL ON THE USERS END.
Don't make it difficult for the user to install any packages.
Try to limit what you use unless it is a part of the exe.
So,
if it requires too much set-up on the user's end,
then don't do it.

# 5. DON'T BE WASTEFUL!
IF SOMETHING CAN BE IMPLEMENTED IN VANILLA C,
DON'T USE A PACKAGE OR LIBRARY FOR IT THAT'S JUST UN-NEEDED BLOAT!!



# 6. Make ports and changes ROBUST.
the entire app should have an equal level of stability, 
and similar codebase across all platforms, 
only making changes that are required or better on the respective system.




# 7. YOU ARE NOT REQUIRED TO ADD SAFETY FEATURES.***
I have slightly broken my "No safety feature ''rule'' that I had for MYSELF" -
by adding an emergency countdown in severe executions, 
you are not by any means required to keep this, update this, add new ones, 
but you can do whatever you like as long as its under my LICENSE and Rules**



Thanks!





p.s.

* Copyright © Ann 2026.

**This file is not containing required rules, these are mostly suggestions. The Only true requirement is adherance to the Header Disclaimer, and License or any other rules related to legal requirements, disclaimers, or otherwise.

*** You MUST include disclaimers and credits for the creator (Me, (Ann)) as stated under the LICENSE.txt File. AND a Disclaimer for yourself, Any damage caused by your version is on you unless you add specific legal disclaimers under your name, my name, and any other contributors. I am not responsible for damage caused by your changes or testing.
