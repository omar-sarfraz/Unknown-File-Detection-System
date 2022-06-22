$username = [System.Environment]::UserName
$downloads = "C:\Users\$username\Downloads\"
$Path = $downloads
$FileFilter = '*.exe'  
$IncludeSubfolders = $true
$AttributeFilter = [IO.NotifyFilters]::FileName 

try
{
    $watcher = New-Object -TypeName System.IO.FileSystemWatcher -Property @{
    Path = $Path
    Filter = $FileFilter
    IncludeSubdirectories = $IncludeSubfolders
    NotifyFilter = $AttributeFilter
  }

  $action = {
    
    $details = $event.SourceEventArgs
    $Name = $details.Name
    $FullPath = $details.FullPath
    $OldFullPath = $details.OldFullPath
    $OldName = $details.OldName
    
    $ChangeType = $details.ChangeType
    
    $text = "{0} was {1}" -f $Name, $ChangeType
    Write-Host ""
    Write-Host $text -ForegroundColor DarkYellow
    
    switch ($ChangeType)
    {
      'Created'  { "$Name" | Out-File -FilePath .\blacklist.txt -append -Encoding UTF8}
    }
  }

  $handlers = . {
    Register-ObjectEvent -InputObject $watcher -EventName Created  -Action $action 
  }

  $watcher.EnableRaisingEvents = $true

  Write-Host "Watching for changes to $Path"

  do
  {
    Wait-Event -Timeout 1

  } while ($true)
}
finally
{
  $watcher.EnableRaisingEvents = $false

  $handlers | ForEach-Object {
    Unregister-Event -SourceIdentifier $_.Name
  }
  
  $handlers | Remove-Job
  
  $watcher.Dispose()
  
  Write-Warning "Event Handler disabled, monitoring ends."
}