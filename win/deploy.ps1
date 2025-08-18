param ($configuration)

Write Host "Deploying $configuration..."

if ($configuration -eq "Release") {
  $nuspecFile = Get-ChildItem -Filter "*.nuspec" | Select-Object -First 1
  $newVersion = $([System.DateTime]::Now.ToString("yyyy.M.d.Hmm"))

  if ($nuspecFile) {
      (Get-Content $nuspecFile.FullName) -replace '(<version>).*?(</version>)', "`$1 $newVersion `$2" | Set-Content $nuspecFile.FullName
      Write-Host "Updated version to $newVersion in $($nuspecFile.Name)"
	  rm    *.nupkg
	  nuget pack
	  nuget push *.nupkg -Source GitHub
  } else {
      Write-Host "No .nuspec file found."
  }
}