while(1){
Start-Sleep -Seconds 2
$time = (Get-Date).AddSeconds(-30)
Get-Process | select-object starttime, Name, Path | where-object -Filter {$_.starttime -ge $time} | Select-Object Name, Path | %{ "{0},{1}" -f $_.Name,$_.Path } | Set-Content "C:\Program Files\process.txt"
}