git add .
read -r -p "Your commit message: " message
git commit -m "$message"
git rm atm
git commit --amend --no-edit
git push