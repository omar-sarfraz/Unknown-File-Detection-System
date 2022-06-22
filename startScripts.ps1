Start-Process Powershell.exe -Argumentlist ".\FileWatcherScript.ps1" -WindowStyle Hidden
Start-Process powershell.exe -Argumentlist ".\RegisterEvent.ps1" -Verb runAs -WindowStyle Hidden