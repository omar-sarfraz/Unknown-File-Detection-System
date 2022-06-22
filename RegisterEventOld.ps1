Get-EventSubscriber | Unregister-Event
Register-CimIndicationEvent -ClassName Win32_ProcessStartTrace -SourceIdentifier "ProcessStarted"

while(1){

Start-Sleep -Seconds 1
$time = (Get-Date).AddSeconds(-30)
Get-Event | select timegenerated, @{Name='Event'; E = {$_.sourceeventargs.newevent.processname}} | where-object -Filter {$_.TimeGenerated -ge $time} | select Event -ExpandProperty Event | Set-Content "C:\Program Files\process.txt"

}