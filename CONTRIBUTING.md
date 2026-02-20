Hi!

If you wanted to commit (which I doubt due to the nature of the project, but anyway),
Thanks!
I've laid out some rough guidelines for if you choose to release your update:

# _**LEGAL DISCLAIMER & CONTRIBUTOR AGREEMENT**_:

BY CONTRIBUTING TO THIS PROJECT, YOU, THE CONTRIBUTOR, ACKNOWLEDGE AND AGREE TO THE FOLLOWING:

1.  **SHARED PROTECTION FROM THE END-USER.**
    This project is designed to be destructive. By contributing, you agree that your code is provided to the public with a total disclaimer of liability. You, as a contributor, and the Original Developer (Ann), shall not be held liable by any user for any damages, data loss, or system failures. We stand together in asserting that the User assumes 100% of the risk.

2.  **MANDATORY NON-LIABILITY ASSERTION.**
    To protect yourself from potential claims by end-users, you should clearly disclaim liability for your contributions. This ensures that the "Legal Fortress" of NUK3R remains consistent. 
    
    **How to protect yourself:**
    We strongly recommend you include a statement of non-liability in your Pull Request, code headers, or a `LIABILITY_STATEMENT.md` file in your distribution. This is to ensure the End-User knows that **neither you nor Ann** are responsible for what the software does.

3.  **MIT LICENSE AGREEMENT (NO WARRANTY).**
    By contributing, you agree to license your work under the project's existing MIT License. As stated in the LICENSE.txt: **"THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND."** This is our primary legal shield. There is no warranty of merchantability or fitness for a particular purpose.

4.  **NO INDEMNIFICATION REQUIRED.**
    Contributors are **NOT** required to indemnify the original developer. You are not responsible for the legal costs of others. However, you are responsible for your own actions and your own testing environment. If you damage your own hardware during development, that is your own responsibility.

YOUR DECISION TO COMMIT CODE TO THIS REPOSITORY CONSTITUTES YOUR ACCEPTANCE OF THESE TERMS. IF YOU DO NOT AGREE, DO NOT CONTRIBUTE.


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




# 8. MAINTAINER'S DISCRETION & FINAL SAY***
The Original Developer (Ann) reserves the absolute right to reject, close, or modify any Pull Request or contribution for any reason, including but not limited to:
*   Unnecessary code bloat or lack of optimization.
*   Incompatibility with the project’s vision or style.
*   Code that introduces unacceptable levels of instability.
*   Security concerns.

Submitting a contribution does not guarantee its inclusion in the main branch. If your contribution is rejected, you are encouraged to maintain it within your own fork under the terms of the MIT License.
Sorry in advance.


Thanks!





p.s.

* Copyright © Ann 2026.

**This file is not containing required rules, these are mostly suggestions. The Only true requirement is adherance to the Header Disclaimer, Rule #8, and License or any other rules related to legal requirements, disclaimers, or otherwise.



*** You MUST include disclaimers and credits for the creator (Me, (Ann)) as stated under the LICENSE.txt File. AND a Disclaimer for yourself, Any damage caused by your version is on you unless you add specific legal disclaimers under your name, my name, and any other contributors. I am not responsible for damage caused by your changes or testing.
