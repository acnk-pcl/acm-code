# ACM code auto-push script
# Usage: .\git-push-acm.ps1 [optional commit message]

param(
    [string]$CommitMessage = "Update ACM solutions"
)

$codeDir = "C:\Users\Administrator\Desktop\oi"

# Enter code directory
Set-Location $codeDir

# Check if in Git repository
if (!(Test-Path ".git")) {
    Write-Host "❌ Current directory is not a Git repository!" -ForegroundColor Red
    Write-Host "Please run: git init && git remote add origin https://github.com/acnk-pcl/acm-code.git" -ForegroundColor Yellow
    exit 1
}

# Add all changes
Write-Host "🔄 Adding files..." -ForegroundColor Cyan
git add .

# Check if there are changes to commit
$hasChanges = git status --porcelain
if ([string]::IsNullOrEmpty($hasChanges)) {
    Write-Host "✅ No new changes to push" -ForegroundColor Green
    exit 0
}

# Commit changes
Write-Host "📝 Committing changes..." -ForegroundColor Cyan
git commit -m "$CommitMessage"

# Push to GitHub
Write-Host "📤 Pushing to GitHub..." -ForegroundColor Cyan
git push origin main

if ($LASTEXITCODE -eq 0) {
    Write-Host "✅ Push successful! OpenClaw will automatically analyze your new code." -ForegroundColor Green
    Write-Host "💡 Tip: Say 'analyze my latest code' in chat to get instant feedback" -ForegroundColor Yellow
} else {
    Write-Host "❌ Push failed! Please check network connection and GitHub credentials." -ForegroundColor Red
}