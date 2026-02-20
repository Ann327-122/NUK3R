Hi!

If you wanted to commit (which I doubt due to the nature of the project, but anyway),
Thanks!
I've laid out some rough guidelines for if you choose to release your update:

# _**LEGAL DISCLAIMER & CONTRIBUTOR AGREEMENT**_:

BY CONTRIBUTING TO THIS PROJECT, YOU, THE CONTRIBUTOR, ACKNOWLEDGE AND AGREE TO THE FOLLOWING:

1.  **DEFAULT LIABILITY FOR CONTRIBUTIONS.**
    By default, and unless you explicitly state otherwise as detailed below, you, the Contributor, assume full and sole liability for any and all damages, losses, or negative consequences arising from your contributions. This includes, but is not limited to, system instability, data loss, security vulnerabilities, or any other catastrophic failure, whether occurring during testing, integration, or in any operational scenario.

    **To Specify Non-Liability:**
    Should you wish to limit or disclaim liability for a specific contribution, you **MUST** clearly and prominently specify the scope and nature of such non-liability **within the documentation or metadata directly accompanying that contribution.** Examples include:
    *   A dedicated section in your Pull Request (PR) description explicitly stating the non-liability.
    *   A new file named `LIABILITY_STATEMENT.md` placed within the root directory of your specific contribution, detailing the limitations.
    *   A clear header or comment block within relevant code files that directly asserts non-liability.
    *   **Failure to explicitly specify non-liability in a clear and prominent manner means full liability, as outlined above, is retained by you.**

2.  **INDEMNIFICATION OF ORIGINAL DEVELOPER.**
    You further agree to indemnify and hold harmless the original copyright holder of this project (Ann), along with any project maintainers, developers, or entities associated with its distribution, from any and all claims, damages, losses, liabilities, costs, and expenses (including legal fees) arising from your contributions. This indemnification applies regardless of whether you have attempted to specify non-liability for your contributions, and covers any issues that may arise from such non-liability assertions themselves.

3.  **CONTRIBUTIONS PROVIDED "AS IS" WITH NO WARRANTY.**
    Just like the rest of this project, your contributions will be licensed under the included MIT License. All contributions are provided "AS IS," without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose, and noninfringement.

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