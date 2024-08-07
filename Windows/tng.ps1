param(
    [string]$filename
)

$directoryPath = "C:\Users\tng\e.zngdm"

if (!(Test-Path -Path $directoryPath)) {
    New-Item -Path $directoryPath -ItemType Directory
    New-Item -Path $directoryPath -Name "n.zngdm" -ItemType File
    Write-Host "This is the first time tng rus in this shell"
    Write-Host "the tng command write comment you name and editor with your custom ( and time )"
    Write-Host "Example"
    Write-Host "/// You name"
    Write-Host "/// Your Editor"
    Write-Host "/// the time"
    Write-Host "So what name  you Want to use:"
    Write-Host ""
    #then we echo the name and echo the editor to our form ( we echo it in our file e.zngdm and n.zngdm
} elseif (Test-Path -Path $directoryPath) {
    Write-Host "This is not the first run"
}

$editor = Get-Content -Path "C:\Users\tng\e.zngdm"
$name = Get-Content -Path "C:\Users\tng\n.zngdm"

New-Item -Path $filename -ItemType File

if ($filename -like "*.py" -or $filename -like "*.pyw" -or $filename -like "*.pyc" -or $filename -like "*.pyd" -or $filename -like "*.pyo" -or $filename -like "*.rb" -or $filename -like "*.rbw" -or $filename -like "*.rbx" -or $filename -like "*.rbo" -or $filename -like "*.gy") {
    Add-Content -Path $filename -Value "#editor = $editor"
    Add-Content -Path $filename -Value "#Created By $name"
    Add-Content -Path $filename -Value "#$(Get-Date -Format "yyyy.MM.dd HH:mm")"
}
elseif ($filename -like "*.cc" -or $filename -like "*.cpp" -or $filename -like "*.cxx" -or $filename -like "*.c" -or $filename -like "*.cs" -or $filename -like "*.csharp" -or $filename -like "*.go" -or $filename -like "*.gopkg" -or $filename -like "*.mod" -or $filename -like "*.java" -or $filename -like "*.class" -or $filename -like "*.js" -or $filename -like "*.jsx" -or $filename -like "*.jsm" -or $filename -like "*.mjs" -or $filename -like "*.node" -or $filename -like "*.ts" -or $filename -like "*.tsx" -or $filename -like "*.d.ts" -or $filename -like "*.cts" -or $filename -like "*.php" -or $filename -like "*.php3" -or $filename -like "*.php4" -or $filename -like "*.php5" -or $filename -like "*.phtml" -or $filename -like "*.inc" -or $filename -like "*.rs" -or $filename -like "*.rlib" -or $filename -like "*.toml" -or $filename -like "*.swift" -or $filename -like "*.swiftmodule" -or $filename -like "*.swiftinterface" -or $filename -like "*.swiftdoc") {
    Add-Content -Path $filename -Value "///editor = $editor"
    Add-Content -Path $filename -Value "///Created By $name"
    Add-Content -Path $filename -Value "///$(Get-Date -Format "yyyy.MM.dd HH:mm")"
}
elseif ($filename -like "*.lua" -or $filename -like "*.luac" -or $filename -like "*.moon" -or $filename -like "*.wlua" -or $filename -like "*.nse") {
    Add-Content -Path $filename -Value "--editor = $editor"
    Add-Content -Path $filename -Value "--Created By $name"
    Add-Content -Path $filename -Value "--$(Get-Date -Format "yyyy.MM.dd HH:mm")"
}
elseif ($filename -like "*.sh") {
    Add-Content -Path $filename -Value "#!/bin/bash"
    Add-Content -Path $filename -Value "#editor = $editor"
    Add-Content -Path $filename -Value "#Created By $name"
    Add-Content -Path $filename -Value "#$(Get-Date -Format "yyyy.MM.dd HH:mm")"
}
elseif ($filename -like "*csd") {
    Add-Content -Path $filename -Value ";editor = $editor"
    Add-Content -Path $filename -Value ";Created By $name"
    Add-Content -Path $filename -Value ";$(Get-Date -Format "yyyy.MM.dd HH:mm")"
    Add-Content -Path $filename -Value "<CsoundSynthesizer>"
    Add-Content -Path $filename -Value "<CsOptions>"
    Add-Content -Path $filename -Value "</CsOptions>"
    Add-Content -Path $filename -Value "<CsInstruments>"
    Add-Content -Path $filename -Value "</CsInstruments>"
    Add-Content -Path $filename -Value "<CsScore>"
    Add-Content -Path $filename -Value "</CsScore>"
    Add-Content -Path $filename -Value "</CsoundSynthesizer>"
}

exit 0
