$username = [System.Environment]::UserName
$date = (Get-Date).AddSeconds(-30)
Get-ChildItem -Recurse "C:\Users\$username\Downloads\" -include '*.exe' | Where-Object -Filter { $_.CreationTime -ge $date } | Select Name -ExpandProperty Name | Out-File -FilePath ".\blacklist.txt" -append -Encoding UTF8