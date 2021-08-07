# Connection using ``launcher_accounts.json``

Botcraft supports connecting using the ``launcher_accounts.json`` file created by the official Minecraft Launcher. For newer Microsoft Accounts, this is the only connection option available. Mojang recently updated the launcher so the ``accessToken`` is no longer saved inside this file. You will find below a quick fix I've found if you still want to use Botcraft with your Microsoft account.

Basically, the idea is still to use the Launcher to create a valid accessToken. However, even though this token is stored somewhere on your computer, it is now hidden. On Windows, I am pretty sure it's in ``launcher_msa_credentials.bin``, but as it is a DPAPI encrypted file I'm not sure how to extract it, or even if I should. On Linux and MacOS I have no clue where it is stored. So instead, I propose a different strategy: start a Minecraft process, find the command line used to invoke it from the launcher, and get the accessToken from here. You'll find below the detailed process for each OS.

## Linux

- Start Minecraft Launcher
- Log in with the account you want to use
- Click ``Play`` to launch a Minecraft session
- Open a terminal
- Use the following command:
```bash
ps aux | grep 'java' | grep -o -- "--accessToken [^ ]* " | cut -c 15-
```
Basically, this command just searches for the command line used to start Minecraft, and extract the given accessToken
- You can now close both Minecraft and the Launcher
- Open ``~\.minecraft\launcher_accounts.json``
- Paste the previously acquired accessToken in place of the empty string of the account corresponding to the ``activeAccountLocalId``

## Windows

- Start Minecraft Launcher
- Log in with the account you want to use
- Click ``Play`` to launch a Minecraft session
- Open a cmd prompt
- Use the following command:
```bash
wmic process where name="javaw.exe" get CommandLine
```
- Find the accessToken in all this mess (it should be at the end, if you know a nice and clean way to extract it from the full command line like in Linux, feel free to let me know, but cmd is not the most powerful tool...)
- You can now close both Minecraft and the Launcher
- Open ``%APPDATA%\.minecraft\launcher_accounts.json``
- Paste the previously acquired accessToken in place of the empty string of the account corresponding to the ``activeAccountLocalId``

## MacOS

I don't have any device running this OS, so I can't really test it, but something close to the Linux procedure should work. The file is located in ``~/Library/Application Support/minecraft`` though.

If the Linux command line does not work for mac and you find an equivalent, feel free to open an issue or a discussion to let me know and I will fill in this section with the details.

## Warning

After you copied the accessToken, the ``launcher_accounts.json`` file can be used to start Botcraft (for instance with the ``--jsonaccount`` command line argument in the examples). The token will be **removed** from the file the next time you start the official launcher, and you'll have to get it back using the same procedure.



